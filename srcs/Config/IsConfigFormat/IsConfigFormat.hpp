#ifndef SRCS_CONFIG_ISCONFIGFORMAT_ISCONFIGFORMAT_HPP_
#define SRCS_CONFIG_ISCONFIGFORMAT_ISCONFIGFORMAT_HPP_

#include <string>
#include <vector>
#include "../LocationConfig/LocationConfig.hpp"
#include "../ServerConfig/ServerConfig.hpp"
#include "../../HandlingString/HandlingString.hpp"
#include "../ConfigHandlingString/ConfigHandlingString.hpp"

class IsConfigFormat
{
	private:
		IsConfigFormat();
		IsConfigFormat(const IsConfigFormat &other);
		IsConfigFormat& operator=(const IsConfigFormat &other);
		~IsConfigFormat();
	public:
		static	bool	is_start_location_block(const std::string &config_line, \
												std::string *config_location_path);
		static	bool	is_start_location_block(const std::string &config_line);
		static	bool	is_start_server_block(const std::string &config_line);
		static	bool	is_location_block_config(const std::string &config_line, \
													bool *in_location_block);
		static	bool	ready_location_block_config(const std::string &config_line, \
													bool *in_location_block, \
													LocationConfig *location_config, \
													std::vector<std::string> *field_key_map);
		static	bool	ready_server_block_format(const std::string &config_line, \
													bool *in_server_block, \
													ServerConfig *server_config, \
													std::vector<std::string> *field_key_vector);
};

#endif  // SRCS_CONFIG_ISCONFIGFORMAT_ISCONFIGFORMAT_HPP_