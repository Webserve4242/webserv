#include "../includes/LocationConfig.hpp"
#include "../includes/ServerConfig.hpp"
#include "../includes/HandlingString.hpp"

ServerConfig::ServerConfig():_maxBodySize(1024), _chunked_transferencoding_allow(false),
_keepaliverequests(0), _keepalive_timeout(0), _server_tokens(1), _autoindex(false), _client_body_buffer_size(8000),
_client_body_timeout(60), _client_header_buffer_size(1024), _client_header_timeout(60), _client_maxbody_size(1048576),
_default_type("application/octet-stream")
{

}

ServerConfig::~ServerConfig(){}

// ServerConfig& ServerConfig::operator=(const ServerConfig& other)
// {
// 	(void)other;
// 	return (*this);
// }

// ServerConfig& ServerConfig::operator=(ServerConfig& other)
// {
// 	(void)other;
// 	return (*this);
// }

bool ServerConfig::serverkeyword_ch(const std::string& word)
{
	const std::string server_keyset_arr[] = {
        "listen", "server_name", "root", "index", "allow_methods", "error_page", "types", "cgi_extension",
        "chunked_transfer_encoding", "access_log", "error_log", "keepalive_requests",
        "keepalive_timeout", "server_tokens", "autoindex", "rewrite", "return", "client_body_buffer_size",
        "client_body_timeout", "client_header_buffer_size", "client_header_timeout",
        "client_max_body_size", "default_type"
    };

    const std::set<std::string> server_keyset
    (
        server_keyset_arr,
        server_keyset_arr + sizeof(server_keyset_arr) / sizeof(server_keyset_arr[0])
    );  // NOLINT

    if (server_keyset.count(word) > 0)
        return true;
    return false;
}

bool	ServerConfig::serverkeyword_insert(std::string const &line, size_t pos)
{
	std::istringstream	splited_woeds(line);
	std::string			key_word;
	std::string			val;
	std::string			val_two;

	splited_woeds >> key_word >> val_two;
	val = HandlingString::skip_lastsemicoron(val_two);
	if (this->serverkeyword_ch(key_word) == false)
		throw ServerConfig::ServerKeywordError(key_word, pos);
	if (key_word == "listen")
		this->set_port(val);
	else if (key_word == "cgi_extension")  // 何するかわかってない
		;
	else if (key_word == "server_name")
		this->set_servername(HandlingString::inputarg_tomap_without_firstword(line));
	else if (key_word == "root")
		this->set_root(val);
	else if (key_word == "index")
		this->set_indexpage_set(HandlingString::inputarg_tomap_without_firstword(line));
	else if (key_word == "allow_methods")
		this->set_allowmethod_set(HandlingString::inputarg_tomap_without_firstword(line));
	else if (key_word == "error_page")
		this->set_errorlog(val);
	else if (key_word == "chunked_transfer_encoding")
	{
		if (val != "on" && val != "off")
			return (false);
		this->set_chunked_transferencoding_allow(HandlingString::return_matchpattern("on", "off", val));
	}
	else if (key_word == "access_log")
		this->set_accesslog(val);
	else if (key_word == "error_log")
		this->set_errorlog(val);
	else if (key_word == "keepalive_requests")
	{
		if (HandlingString::check_under_intmax(val) == false)
			return (false);
		this->set_keepaliverequests(HandlingString::str_to_int(HandlingString::skip_lastsemicoron(val)));
	}
	else if (key_word == "keepalive_timeout")  // timeoutの実装がC++98のみでは難しい、Cでも許可された関数にない
	{
		if (HandlingString::check_under_intmax(val) == false)
			return (false);
		this->set_keepalive_timeout(HandlingString::str_to_int(HandlingString::skip_lastsemicoron(val)));
	}
	else if (key_word == "server_tokens")
		;
	else if (key_word == "autoindex")
	{
		if (val != "on" && val != "off")
			return (false);
		this->set_autoindex(HandlingString::return_matchpattern("on", "off", val));
	}
	else if (key_word == "rewrite")  // 何するのかわからん
		;
	else if (key_word == "return")  // 何するのかわからん
		;
	else if (key_word == "client_body_buffer_size")  // 単位付きで入ってくる場合に対応する必要性、簡単のために単位なしに一旦する
	{
		if (HandlingString::check_under_intmax(val) == false)
			return (false);
		this->set_client_body_buffer_size(HandlingString::str_to_int(HandlingString::skip_lastsemicoron(val)));
	}
	else if (key_word == "client_body_timeout")
	{
		if (HandlingString::check_under_intmax(val) == false)
			return (false);
		this->set_client_body_timeout(HandlingString::str_to_int(HandlingString::skip_lastsemicoron(val)));
	}
	else if (key_word == "client_header_buffer_size")
	{
		if (HandlingString::check_under_intmax(val) == false)
			return (false);
		this->set_client_header_buffer_size(HandlingString::str_to_int(HandlingString::skip_lastsemicoron(val)));
	}
	else if (key_word == "client_header_timeout")
	{
		if (HandlingString::check_under_intmax(val) == false)
			return (false);
		this->set_client_header_timeout(HandlingString::str_to_int(HandlingString::skip_lastsemicoron(val)));
	}
	else if (key_word == "client_max_body_size")
	{
		if (HandlingString::check_under_intmax(val) == false)
			return (false);
		this->set_client_maxbody_size(HandlingString::str_to_int(HandlingString::skip_lastsemicoron(val)));
	}
	else if (key_word == "default_type")
		this->set_default_type(val);
	else
		return (false);
	return (true);
}

void ServerConfig::set_locations(std::string &key, LocationConfig &locationconf){ _locations[key] = locationconf; }


// std::string								_port;
// std::vector<std::string>				_server_name;
// std::string								_root;
// std::vector<std::string>				_indexpage_set;
// std::vector<std::string>				_allowmethod_set;
// size_t 									_maxBodySize;
// ErrorPage 								_errorpage;//これめっちゃおかしい使い方できる　error_page 403 404 500 503 =404 /custom_404.html;
// bool									_chunked_transferencoding_allow;
// std::string								_accesslog;
// std::string								_errorlog;
// size_t									_keepaliverequests;
// size_t									_keepalive_timeout;
// int										_server_tokens;
// bool									_autoindex;
// size_t									_client_body_buffer_size;
// size_t									_client_body_timeout;
// size_t									_client_header_buffer_size;
// size_t									_client_header_timeout;
// size_t									_client_maxbody_size;
// std::string								_default_type;

void ServerConfig::value_check()
{
	if (this->_indexpage_set.empty() == true)
		this->_indexpage_set.push_back("index.html");
	if (this->_allowmethod_set.empty() == true)
	{
		std::cout << "check" << std::endl;
		this->_allowmethod_set.push_back("GET");
		// this->_allowmethod_set.push_back("HEAD"); HEADは一旦実装しないはずなので無視
		this->_allowmethod_set.push_back("POST");
	}
}

#define RESET_COLOR "\033[0m"
#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"
#define YELLOW_COLOR "\033[33m"
#define BLUE_COLOR "\033[34m"
#define MAGENTA_COLOR "\033[35m"
#define CYAN_COLOR "\033[36m"

void ServerConfig::show_serverconfig_allinfo()
{
	std::cout << "server name is " << GREEN_COLOR;
	HandlingString::show_vector_contents(this->_server_name);
	std::cout << RESET_COLOR << std::endl;
	std::cout << "root is " << GREEN_COLOR << this->_root << RESET_COLOR << std::endl;
	std::cout << "index page is " << GREEN_COLOR;
	HandlingString::show_vector_contents(this->_indexpage_set);
	std::cout << RESET_COLOR << std::endl;
	std::cout << "allowmethod is " << GREEN_COLOR;
	HandlingString::show_vector_contents(this->_allowmethod_set);
	std::cout << RESET_COLOR << std::endl;
	std::cout << "maxbodysize is " << GREEN_COLOR << HandlingString::int_to_str(this->_maxBodySize) << RESET_COLOR << std::endl;
	std::cout << BLUE_COLOR << "## ERROR PAGE SHOW ##" << RESET_COLOR << std::endl;
	this->_errorpage.show_wrrorpage_infos();
	std::cout << BLUE_COLOR << "## ## ## ## ## ## ## ##" << RESET_COLOR << std::endl;
	if (this->_chunked_transferencoding_allow == true)
		std::cout << "transfer encoding is " << GREEN_COLOR << "<< ALLOWED!! >>" << RESET_COLOR << std::endl;
	else
		std::cout << "transfer encoding is " << GREEN_COLOR << "<< NOT ALLOWED!! >>" << RESET_COLOR << std::endl;
	std::cout << "access log is " << GREEN_COLOR << this->_accesslog << RESET_COLOR << std::endl;
	std::cout << "error log is " << GREEN_COLOR << this->_errorlog << RESET_COLOR << std::endl;
	std::cout << "keepalive request is " << GREEN_COLOR << HandlingString::int_to_str(this->_keepaliverequests) << RESET_COLOR << std::endl;
	std::cout << "keepalive timeout is " << GREEN_COLOR << HandlingString::int_to_str(this->_keepalive_timeout) << RESET_COLOR << std::endl;
	if (this->_autoindex == true)
		std::cout << "autoindex is " << GREEN_COLOR << "<< ON!! >>" << RESET_COLOR << std::endl;
	else
		std::cout << "autoindex is " << GREEN_COLOR << "<< OFF!! >>" << RESET_COLOR << std::endl;
	std::cout << "client body buffersize is " << GREEN_COLOR << HandlingString::int_to_str(this->_client_body_buffer_size) << RESET_COLOR << std::endl;
	std::cout << "client body timeout " << GREEN_COLOR << HandlingString::int_to_str(this->_client_body_timeout) << RESET_COLOR << std::endl;
	std::cout << "client header buffersize is " << GREEN_COLOR << HandlingString::int_to_str(this->_client_header_buffer_size) << RESET_COLOR << std::endl;
	std::cout << "client header timeout " << GREEN_COLOR << HandlingString::int_to_str(this->_client_header_timeout) << RESET_COLOR << std::endl;
	std::cout << "client max body size " << GREEN_COLOR << HandlingString::int_to_str(this->_client_maxbody_size) << RESET_COLOR << std::endl;
	std::cout << "default type is " << GREEN_COLOR << this->_default_type << RESET_COLOR << std::endl;
}