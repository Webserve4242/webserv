#include "LocationConfig.hpp"

LocationConfig::LocationConfig():_autoindex(false), _chunked_transferencoding_allow(false), _server_tokens(1),
_client_body_buffer_size(8000), _client_body_timeout(60), _client_header_buffer_size(1024), _client_header_timeout(60),
_client_max_body_size(1048576), _keepaliverequests(0), _keepalive_timeout(0), _maxBodySize(1024), _default_type("application/octet-stream"){}

LocationConfig::~LocationConfig(){}

bool	LocationConfig::ready_boolean_fieldvalue(const std::string &field_value)
{
	std::string	field_value_without_lastsemicolon = ConfigHandlingString::get_value_without_lastsemicolon(field_value);

	if (field_value_without_lastsemicolon == "on")
		return (true);
	return (false);
}

int		LocationConfig::ready_int_fieldvalue(const std::string &field_value)
{
	std::string	field_value_without_lastsemicolon = ConfigHandlingString::get_value_without_lastsemicolon(field_value);

	return (NumericHandle::str_to_int(field_value_without_lastsemicolon));
}

size_t	LocationConfig::ready_size_t_fieldvalue(const std::string &field_value)
{
	std::string	field_value_without_lastsemicolon = ConfigHandlingString::get_value_without_lastsemicolon(field_value);

	return (static_cast<size_t>(NumericHandle::str_to_int(field_value_without_lastsemicolon)));
}

std::string		LocationConfig::ready_string_fieldvalue(const std::string &field_value)
{
	std::string	field_value_without_lastsemicolon = ConfigHandlingString::get_value_without_lastsemicolon(field_value);

	return (field_value_without_lastsemicolon);
}

std::vector<std::string>	LocationConfig::ready_string_vector_fieldvalue(const std::string &field_value)
{
	std::vector<std::string>	anser_vector;
	std::string					field_value_without_lastsemicolon = ConfigHandlingString::get_value_without_lastsemicolon(field_value);
	std::istringstream			values_splited_by_empty(field_value_without_lastsemicolon);
	std::string					value_splited_by_empty;

	while (std::getline(values_splited_by_empty, value_splited_by_empty, ' '))
		anser_vector.push_back(value_splited_by_empty);
	return (anser_vector);
}

bool	LocationConfig::ready_locationblock_keyword(const std::string &field_key, const std::string &field_value)
{
	std::vector<std::string>	field_keys;

	field_keys.push_back("autoindex");
	field_keys.push_back("chunked_transferencoding_allow");
	field_keys.push_back("server_tokens");
	field_keys.push_back("client_body_buffer_size");
	field_keys.push_back("client_body_timeout");
	field_keys.push_back("client_header_buffer_size");
	field_keys.push_back("client_header_timeout");
	field_keys.push_back("client_max_body_size");
	field_keys.push_back("keepaliverequests");
	field_keys.push_back("keepalive_timeout");
	field_keys.push_back("listen");
	field_keys.push_back("maxBodySize");
	field_keys.push_back("accesslog");
	field_keys.push_back("default_type");
	field_keys.push_back("errorlog");
	field_keys.push_back("port");
	field_keys.push_back("root");
	field_keys.push_back("allow_methods");
	field_keys.push_back("index");
	field_keys.push_back("server_name");
	field_keys.push_back("cgi_path");
	field_keys.push_back("alias");
	field_keys.push_back("upload_path");
	field_keys.push_back("error_page");
	field_keys.push_back("return");  // 未実装

	// if (std::find(field_keys.begin(), field_keys.end(), field_key) == field_keys.end())
	// {
	// 	return false;
	// } 当てはまらないものをfalseにするかどうか
    if (field_key == "autoindex")
    {
		if (!(field_value == "on" || field_value == "off"))
			return false;
		this->_autoindex = this->ready_boolean_fieldvalue(field_value);
		return true;
	}
    else if (field_key ==  "chunked_transferencoding_allow")
    {
		if (!(field_value == "on" || field_value == "off"))
			return false;
		this->_chunked_transferencoding_allow = this->ready_boolean_fieldvalue(field_value);
		return true;
	}
    else if (field_key ==  "server_tokens")
    {
		if (!(NumericHandle::is_positive_and_under_intmax_int(field_value)))
			return false;
		this->_server_tokens = this->ready_int_fieldvalue(field_value);
		return true;
	}
	else if (field_key ==  "client_body_buffer_size")
    {
		if (!(NumericHandle::is_positive_and_under_intmax_int(field_value)))
			return false;
		this->_client_body_buffer_size = this->ready_size_t_fieldvalue(field_value);
		return true;
	}
	else if (field_key ==  "client_body_timeout")
    {
		if (!(NumericHandle::is_positive_and_under_intmax_int(field_value)))
			return false;
		this->_client_body_timeout = this->ready_size_t_fieldvalue(field_value);
		return true;
	}
	else if (field_key ==  "client_header_buffer_size")
    {
		if (!(NumericHandle::is_positive_and_under_intmax_int(field_value)))
			return false;
		this->_client_header_buffer_size = this->ready_size_t_fieldvalue(field_value);
		return true;
	}
	else if (field_key ==  "client_header_timeout")
    {
		if (!(NumericHandle::is_positive_and_under_intmax_int(field_value)))
			return false;
		this->_client_header_timeout = this->ready_size_t_fieldvalue(field_value);
		return true;
	}
	else if (field_key ==  "client_max_body_size")
    {
		if (!(NumericHandle::is_positive_and_under_intmax_int(field_value)))
			return false;
		this->_client_max_body_size = this->ready_size_t_fieldvalue(field_value);
		return true;
	}
	else if (field_key ==  "keepaliverequests")
    {
		if (!(NumericHandle::is_positive_and_under_intmax_int(field_value)))
			return false;
		this->_keepaliverequests = this->ready_size_t_fieldvalue(field_value);
		return true;
	}
	else if (field_key ==  "keepalive_timeout")
    {
		if (!(NumericHandle::is_positive_and_under_intmax_int(field_value)))
			return false;
		this->_keepalive_timeout = this->ready_size_t_fieldvalue(field_value);
		return true;
	}
	else if (field_key ==  "maxBodySize")
    {
		if (!(NumericHandle::is_positive_and_under_intmax_int(field_value)))
			return false;
		this->_maxBodySize = this->ready_size_t_fieldvalue(field_value);
		return true;
	}
	else if (field_key ==  "accesslog")
    {
		this->_accesslog = this->ready_string_fieldvalue(field_value);
		return true;
	}
	else if (field_key ==  "default_type")
    {
		this->_default_type = this->ready_string_fieldvalue(field_value);
		return true;
	}
	else if (field_key ==  "errorlog")
    {
		this->_errorlog = this->ready_string_fieldvalue(field_value);
		return true;
	}
	else if (field_key ==  "root")
    {
		this->_root = this->ready_string_fieldvalue(field_value);
		return true;
	}
	else if (field_key ==  "cgi_path")
	{
		this->_cgi_path = this->ready_string_fieldvalue(field_value);
		return true;
	}
	else if (field_key ==  "alias")
    {
		this->_alias = this->ready_string_fieldvalue(field_value);
		return true;
	}
	else if (field_key ==  "upload_path")
    {
		this->_upload_path = this->ready_string_fieldvalue(field_value);
		return true;
	}
	else if (field_key ==  "allow_methods")
    {
		this->_allowmethod_set = this->ready_string_vector_fieldvalue(field_value);
		return true;
	}
	else if (field_key ==  "index")
    {
		this->_indexpage_set = this->ready_string_vector_fieldvalue(field_value);
		return true;
	}
	else if (field_key ==  "error_page")
    {
		this->_errorpage_set = this->ready_string_vector_fieldvalue(field_value);
		return true;
	}
	else if (field_key ==  "server_name")
    {
		this->_server_name = this->ready_string_vector_fieldvalue(field_value);
		return true;
	}
	return (true);
}

bool	LocationConfig::get_autoindex(void){ return (this->_autoindex); }
bool	LocationConfig::get_chunked_transferencoding_allow(void){ return (this->_chunked_transferencoding_allow); }
int		LocationConfig::get_server_tokens(void){ return (this->_server_tokens); }
size_t	LocationConfig::get_client_body_buffer_size(void){ return (this->_client_body_buffer_size); }
size_t	LocationConfig::get_client_body_timeout(void){ return (this->_client_body_timeout); }
size_t	LocationConfig::get_client_header_buffer_size(void){ return (this->_client_header_buffer_size); }
size_t	LocationConfig::get_client_header_timeout(void){ return (this->_client_header_timeout); }
size_t	LocationConfig::get_client_max_body_size(void){ return (this->_client_max_body_size); }
size_t	LocationConfig::get_keepaliverequests(void){ return (this->_keepaliverequests); }
size_t	LocationConfig::get_keepalive_timeout(void){ return (this->_keepalive_timeout); }
size_t 	LocationConfig::get_maxBodySize(void){ return (this->_maxBodySize); }
std::string	LocationConfig::get_alias(void){ return (this->_alias); }
// error_page		LocationConfig::get	_errorpage_set;//これめっちゃおかしい使い方できる　error_page 403 404 500 503 =404 /custom_404.html;
std::string	LocationConfig::get_accesslog(void){ return (this->_accesslog); }
std::string	LocationConfig::get_cgi_path(void){ return (this->_cgi_path); }
std::string	LocationConfig::get_default_type(void){ return (this->_default_type); }
std::string	LocationConfig::get_errorlog(void){ return (this->_errorlog); }
std::string	LocationConfig::get_upload_path(void){ return (this->_upload_path); }
std::string	LocationConfig::get_root(void){ return (this->_root); }
std::vector<std::string> LocationConfig::get_allowmethod_set(void){ return (this->_allowmethod_set); }
std::vector<std::string> LocationConfig::get_indexpage_set(void){ return (this->_indexpage_set); }
std::vector<std::string> LocationConfig::get_server_name(void){ return (this->_server_name); }
std::vector<std::string> LocationConfig::get_errorpage_set(void){ return (this->_errorpage_set); }

void	LocationConfig::clear_location_keyword()
{
	this->_autoindex = false;
	this->_chunked_transferencoding_allow = false;
	this->_server_tokens = 1;
	this->_client_body_buffer_size = 8000;
	this->_client_body_timeout = 60;
	this->_client_header_buffer_size = 1024;
	this->_client_header_timeout = 60;
	this->_client_max_body_size = 1048576;
	this->_keepaliverequests = 0;
	this->_keepalive_timeout = 0;
	this->_maxBodySize = 1024;
	this->_alias = "";
	this->_accesslog = "";
	this->_cgi_path = "";
	this->_default_type = "application/octet-stream";
	this->_errorlog = "";
	this->_upload_path = "";
	this->_root = "";
	this->_allowmethod_set.clear();
	this->_indexpage_set.clear();
	this->_server_name.clear();
	this->_errorpage_set.clear();
}

void LocationConfig::set_serverblock_infs(const ServerConfig &other)
{
	this->set_autoindex(other.get_autoindex());
	this->set_chunked_transferencoding_allow(other.get_chunked_transferencoding_allow());
	this->set_server_tokens(other.get_server_tokens());
	this->set_client_body_buffer_size(other.get_client_body_buffer_size());
	this->set_client_header_timeout(other.get_client_header_timeout());
	this->set_client_max_body_size(other.get_client_maxbody_size());
	this->set_keepaliverequests(other.get_keepaliverequests());
	this->set_keepalive_timeout(other.get_keepalive_timeout());
	this->set_maxBodySize(other.get_maxBodySize());
	this->set_accesslog(other.get_accesslog());
	this->set_default_type(other.get_default_type());
	this->set_default_type(other.get_default_type());
	this->set_errorlog(other.get_errorlog());
	this->set_root(other.get_root());
	this->set_allowmethod_set(other.get_allowmethod_set());
	this->_indexpage_set.clear();
}