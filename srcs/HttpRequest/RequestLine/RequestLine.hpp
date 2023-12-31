#pragma once

# include <string>
# include "Result.hpp"

class RequestLine {
 public:
	RequestLine();
	RequestLine(const RequestLine &other);
	RequestLine& operator=(const RequestLine &rhs);
	~RequestLine();

	std::string	get_method() const;
	std::string get_request_target() const;
	std::string	get_http_version() const;

	Result<int, int> parse_and_validate(const std::string &line);

 private:
	Result<int, int> parse(const std::string &line);
	Result<int, int> validate() const;

	std::string _method;
	std::string _request_target;
	std::string _http_version;
};
