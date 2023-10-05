#include "ConfigHandlingString.hpp"

bool ConfigHandlingString::is_nomeanig_line(const std::string &line)
{
	std::string	line_without_ows = HandlingString::obtain_without_ows_value(line);

	if (line_without_ows[0] == '#' || line_without_ows.empty())
		return (true);
	return (false);
}

std::string	ConfigHandlingString::get_value_without_lastsemicolon(const std::string &value)
{
	return (value.substr(0, value.length() - 1));
}