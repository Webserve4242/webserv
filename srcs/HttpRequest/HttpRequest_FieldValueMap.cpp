#include "Color.hpp"
#include "Constant.hpp"
#include "HttpRequest.hpp"
#include "HttpMessageParser.hpp"

namespace {

// auth-param    = token BWS "=" BWS ( token / quoted-string )
bool is_auth_param(const std::string &str) {
	std::size_t pos;

	if (str.empty()) { return false; }

	pos = 0;
	while (HttpMessageParser::is_tchar(str[pos])) {
		++pos;
	}
	if (pos == 0) { return false; }

	HttpMessageParser::skip_ows(str, &pos);
	if (str[pos] != '=') { return false; }
	HttpMessageParser::skip_ows(str, &pos);

	return HttpMessageParser::is_token(&str[pos])
		   || HttpMessageParser::is_quoted_string(&str[pos]);
}

// credentials   = auth-scheme [ 1*SP ( token68 / #auth-param ) ]
//                                     ^^^^^^^^^^^^^^^^^^^^^^
bool is_valid_auth_param(const std::string &auth_param) {
	return (HttpMessageParser::is_token68(auth_param)
			|| is_auth_param(auth_param));
}

// auth-scheme   = token
bool is_valid_auth_scheme(const std::string &auth_scheme) {
	return HttpMessageParser::is_token(auth_scheme);
}

Result<int, int> validate_credentials(const std::map<std::string, std::string> &credentials) {
	const std::size_t AUTH_SCHEME_ONLY = 1;
	std::map<std::string, std::string>::const_iterator itr;
	std::string auth_scheme, auth_param;

	itr = credentials.find(std::string(AUTH_SCHEME));
	if (itr == credentials.end()) {
		return Result<int, int>::err(ERR);
	}
	auth_scheme = itr->second;
	if (!is_valid_auth_scheme(auth_scheme)) {
		return Result<int, int>::err(ERR);
	}

	itr = credentials.find(std::string(AUTH_PARAM));
	if (itr == credentials.end()) {
		if (credentials.size() == AUTH_SCHEME_ONLY) {
			return Result<int, int>::ok(OK);
		}
		return Result<int, int>::err(ERR);
	}
	auth_param = itr->second;
	if (!is_valid_auth_param(auth_param)) {
		return Result<int, int>::err(ERR);
	}
	return Result<int, int>::ok(OK);
}

// credentials   = auth-scheme [ 1*SP ( token68 / #auth-param ) ]
// auth-scheme   = token
Result<std::string, int> parse_auth_scheme(const std::string &field_value,
										   std::size_t start_pos,
										   std::size_t *end_pos) {
	std::string auth_scheme;
	std::size_t len;

	if (!end_pos) { return Result<std::string, int>::err(ERR); }
	if (field_value.empty()) { return Result<std::string, int>::err(ERR); }

	len = 0;
	while (HttpMessageParser::is_tchar(field_value[start_pos + len])) {
		++len;
	}
	auth_scheme = field_value.substr(start_pos, len);

	// std::cout << CYAN << "  auth_scheme:[" << auth_scheme << "]" << RESET << std::endl;
	// std::cout << CYAN << "  start_pos:[" << start_pos << "]" << RESET << std::endl;
	// std::cout << CYAN << "  len:[" << len << "]" << RESET << std::endl;

	*end_pos = start_pos + len;
	return Result<std::string, int>::ok(auth_scheme);
}

// credentials   = auth-scheme [ 1*SP ( token68 / #auth-param ) ]
// auth-param    = token BWS "=" BWS ( token / quoted-string )
// token68       = 1*( ALPHA / DIGIT / "-" / "." / "_" / "~" / "+" / "/" ) *"="
Result<std::string, int> parse_auth_param(const std::string &field_value,
										  std::size_t start_pos,
										  std::size_t *end_pos) {
	std::string auth_param;
	std::size_t pos, len;

	if (!end_pos) { return Result<std::string, int>::err(ERR); }
	if (field_value.empty()) { return Result<std::string, int>::err(ERR); }

	pos = start_pos;
	if (field_value[pos] != SP) { return Result<std::string, int>::err(ERR); }
	++pos;

	auth_param = field_value.substr(pos);
	len = auth_param.length();
	*end_pos = pos + len;
	return Result<std::string, int>::ok(auth_param);
}

// Authorization: <type> <credentials>

// Authorization = credentials
// credentials   = auth-scheme [ 1*SP ( token68 / #auth-param ) ]
// https://datatracker.ietf.org/doc/html/rfc7235#section-4.2
Result<std::map<std::string, std::string>, int> parse_credentials(const std::string &field_value) {
	std::map<std::string, std::string> credentials;
	std::string auth_scheme, auth_param;
	Result<std::string, int> auth_scheme_result, auth_param_result;
	std::size_t pos, end_pos;

	pos = 0;
	auth_scheme_result = parse_auth_scheme(field_value, pos, &end_pos);
	if (auth_scheme_result.is_err()) {
		return Result<std::map<std::string, std::string>, int>::err(ERR);
	}
	credentials[std::string(AUTH_SCHEME)] = auth_scheme_result.get_ok_value();
	// std::cout << YELLOW << " auth_scheme:[" << auth_scheme_result.get_ok_value() << "]" << RESET << std::endl;
	// std::cout << YELLOW << " &str[pos]:[" << &field_value[pos] << "]" << RESET << std::endl;
	// std::cout << YELLOW << " &str[end]:[" << &field_value[end_pos] << "]" << RESET << std::endl;
	pos = end_pos;

	if (field_value[pos] != '\0') {
		auth_param_result = parse_auth_param(field_value, pos, &end_pos);
		if (auth_param_result.is_err()) {
			return Result<std::map<std::string, std::string>, int>::err(ERR);
		}
		credentials[std::string(AUTH_PARAM)] = auth_param_result.get_ok_value();
		// std::cout << YELLOW << " auth_param:[" << auth_param_result.get_ok_value() << "]" << RESET << std::endl;
	}
	pos = end_pos;

	if (field_value[pos] != '\0') {
		return Result<std::map<std::string, std::string>, int>::err(ERR);
	}
	return Result<std::map<std::string, std::string>, int>::ok(credentials);
}

Result<std::map<std::string, std::string>, int> parse_and_validate_credentials(
												const std::string &field_value) {
	Result<std::map<std::string, std::string> , int> parse_result;
	Result<int, int> validate_result;
	std::map<std::string, std::string> credentials;

	parse_result = parse_credentials(field_value);
	if (parse_result.is_err()) {
		return Result<std::map<std::string, std::string>, int>::err(ERR);
	}
	credentials = parse_result.get_ok_value();

	validate_result = validate_credentials(credentials);
	if (validate_result.is_err()) {
		return Result<std::map<std::string, std::string>, int>::err(ERR);
	}
	return Result<std::map<std::string, std::string>, int>::ok(credentials);
}


}  // namespace

FieldValueMap* HttpRequest::ready_ValueMap(const std::string &field_value, char delimiter) {
	std::map<std::string, std::string>	value_map;
	std::stringstream					ss(field_value);
	std::string							line;

	while(std::getline(ss, line, delimiter))
		value_map[StringHandler::obtain_word_before_delimiter(StringHandler::obtain_withoutows_value(line), '=')] \
		= StringHandler::obtain_word_after_delimiter(StringHandler::obtain_withoutows_value(line), '=');
	return (new FieldValueMap(value_map));
}

FieldValueMap* HttpRequest::ready_ValueMap(const std::string &field_value) {
	std::map<std::string, std::string> value_map;
	std::stringstream	ss(field_value);
	std::string			line;

	while(std::getline(ss, line, ';'))
		value_map[StringHandler::obtain_word_before_delimiter(StringHandler::obtain_withoutows_value(line), '=')] \
		= StringHandler::obtain_word_after_delimiter(StringHandler::obtain_withoutows_value(line), '=');
	return (new FieldValueMap(value_map));
}

FieldValueMap* HttpRequest::ready_ValueMap(const std::string &only_value, const std::string &field_value) {
	std::map<std::string, std::string>	value_map;
	std::stringstream					ss(field_value);
	std::string							line;
	std::string							skipping_word;

	while(std::getline(ss, line, ';'))
	{
		skipping_word = StringHandler::obtain_withoutows_value(line);
		value_map[StringHandler::obtain_word_before_delimiter(skipping_word, '=')] \
		= StringHandler::obtain_withoutows_value(StringHandler::obtain_word_after_delimiter(skipping_word, '='));
	}
	return (new FieldValueMap(only_value, value_map));
}

// Authorization: <type> <credentials>

// Authorization = credentials
// credentials   = auth-scheme [ 1*SP ( token68 / #auth-param ) ]
// auth-scheme   = token
// auth-param    = token BWS "=" BWS ( token / quoted-string )
// token68       = 1*( ALPHA / DIGIT / "-" / "." / "_" / "~" / "+" / "/" ) *"="
// https://datatracker.ietf.org/doc/html/rfc7235#section-4.2
Result<int, int> HttpRequest::set_authorization(const std::string &field_name,
												const std::string &field_value) {
	std::map<std::string, std::string> credentials;
	Result<std::map<std::string, std::string> , int> result;

	if (is_valid_field_name_registered(field_name)) {
		return Result<int, int>::err(ERR);
	}

	result = parse_and_validate_credentials(field_value);
	if (result.is_ok()) {
		credentials = result.get_ok_value();
		this->_request_header_fields[field_name] = new FieldValueMap(credentials);
	}
	return Result<int, int>::ok(STATUS_OK);
}

// 複数OK
// todo: Content-Disposition
// bnf??
Result<int, int> HttpRequest::set_content_disponesition(const std::string &field_name, const std::string &field_value) {
	std::stringstream	ss(field_value);
	std::string			only_value;
	std::string			except_onlyvalue_line;
	std::string 		line;

	std::getline(ss, only_value, ';');
	while (std::getline(ss, line, ';'))
		except_onlyvalue_line = except_onlyvalue_line + line;
	_request_header_fields[field_name] = this->ready_ValueMap(only_value, except_onlyvalue_line);
	return Result<int, int>::ok(STATUS_OK);
}

// todo: Cookie
Result<int, int> HttpRequest::set_cookie(const std::string &field_name, const std::string &field_value) {
	_request_header_fields[field_name] = this->ready_ValueMap(field_value);
	return Result<int, int>::ok(STATUS_OK);
}

// todo: Forwarded
Result<int, int> HttpRequest::set_forwarded(const std::string &field_name, const std::string &field_value) {
	_request_header_fields[field_name] = this->ready_ValueMap(field_value);
	return Result<int, int>::ok(STATUS_OK);
}


// todo: Host
// Host: <host>:<port>

/*
 Host = uri-host [ ":" port ]
 uri-host = IP-literal / IPv4address / reg-name
 IP-literal = "[" ( IPv6address / IPvFuture  ) "]"
 IPvFuture  = "v" 1*HEXDIG "." 1*( unreserved / sub-delims / ":" )

      IPv6address =                            6( h16 ":" ) ls32
                  /                       "::" 5( h16 ":" ) ls32
                  / [               h16 ] "::" 4( h16 ":" ) ls32
                  / [ *1( h16 ":" ) h16 ] "::" 3( h16 ":" ) ls32
                  / [ *2( h16 ":" ) h16 ] "::" 2( h16 ":" ) ls32
                  / [ *3( h16 ":" ) h16 ] "::"    h16 ":"   ls32
                  / [ *4( h16 ":" ) h16 ] "::"              ls32
                  / [ *5( h16 ":" ) h16 ] "::"              h16
                  / [ *6( h16 ":" ) h16 ] "::"

      ls32        = ( h16 ":" h16 ) / IPv4address
                  ; least-significant 32 bits of address

      h16         = 1*4HEXDIG
                  ; 16 bits of address represented in hexadecimal

      IPv4address = dec-octet "." dec-octet "." dec-octet "." dec-octet

      dec-octet   = DIGIT                 ; 0-9
                  / %x31-39 DIGIT         ; 10-99
                  / "1" 2DIGIT            ; 100-199
                  / "2" %x30-34 DIGIT     ; 200-249
                  / "25" %x30-35          ; 250-255

 reg-name    = *( unreserved / pct-encoded / sub-delims )
 unreserved    = ALPHA / DIGIT / "-" / "." / "_" / "~"
 pct-encoded   = "%" HEXDIG HEXDIG
 sub-delims    = "!" / "$" / "&" / "'" / "(" / ")" / "*" / "+" / "," / ";" / "="

 port          = *DIGIT

https://datatracker.ietf.org/doc/html/rfc3986#appendix-A
 */
// todo:
//  map[uri_host]
//  map[port]
// 0 <= port <= 65535
Result<int, int> HttpRequest::set_host(const std::string &field_name, const std::string &field_value)
{
	// std::string	first_value;
	// std::string	second_value;

	if (std::count(field_value.begin(), field_value.end(), ':') == 1)
	{
		std::string	first_value = HttpMessageParser::obtain_withoutows_value(HttpMessageParser::obtain_word_before_delimiter(field_value, ':'));
		std::string	second_value = HttpMessageParser::obtain_withoutows_value(HttpMessageParser::obtain_word_after_delimiter(field_value, ':'));
		if (first_value == "" || second_value == "")
		{
			this->_status_code = 400;
			return Result<int, int>::err(STATUS_BAD_REQUEST);
		}
	}
	else if (std::count(field_value.begin(), field_value.end(), ':') > 1)
	{
		this->_status_code = 400;
		return Result<int, int>::err(STATUS_BAD_REQUEST);
	}
	this->_request_header_fields[field_name] = this->ready_TwoValueSet(field_value, ':');
	return Result<int, int>::ok(STATUS_OK);
}


// todo: Keep-Alive
Result<int, int> HttpRequest::set_keep_alive(const std::string &field_name, const std::string &field_value) {
	_request_header_fields[field_name] = this->ready_ValueMap(field_value, ',');
	return Result<int, int>::ok(STATUS_OK);
}

// todo: Set-Cookie
Result<int, int> HttpRequest::set_set_cookie(const std::string &field_name, const std::string &field_value) {
	_request_header_fields[field_name] = this->ready_ValueMap(field_value);
	return Result<int, int>::ok(STATUS_OK);
}

// todo: Proxy-Authorization
// Proxy-Authorization: <type> <credentials>
Result<int, int> HttpRequest::set_proxy_authorization(const std::string &field_name, const std::string &field_value)
{
	if (std::count(field_value.begin(), field_value.end(), ' ') == 1)
	{
		std::string	first_value = HttpMessageParser::obtain_withoutows_value(HttpMessageParser::obtain_word_before_delimiter(field_value, ' '));
		std::string	second_value = HttpMessageParser::obtain_withoutows_value(HttpMessageParser::obtain_word_after_delimiter(field_value, ' '));
		if (first_value == "" || second_value == "")
		{
			this->_status_code = 400;
			return Result<int, int>::err(STATUS_BAD_REQUEST);
		}
	}
	else if (std::count(field_value.begin(), field_value.end(), ' ') > 1)
	{
		this->_status_code = 400;
		return Result<int, int>::err(STATUS_BAD_REQUEST);
	}
	this->_request_header_fields[field_name] = this->ready_TwoValueSet(field_value, ' ');
	return Result<int, int>::ok(STATUS_OK);
}
