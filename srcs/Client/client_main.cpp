#include <fstream>
#include <iostream>
#include "Client.hpp"
#include "Color.hpp"

namespace {
	std::string RESPONSE_MSG = "GET / HTTP/1.1\r\n"
							   "Host: 127.0.0.1\r\n"
							   "Accept-Encoding: deflate, gzip;q=1.0, *;q=0.5\r\n"
							   "Accept-Language: en-US,en;q=0.5\r\n"
							   // "Content-Length: 2147483648\r\n"
							   "\r\n";
	std::string SERVER_IP = "127.0.0.1";
	std::string SERVER_PORT = "8080";
}  // namespace

int main() {
	try {
		std::cout << "Request message:[" << std::endl;
		std::cout << YELLOW << RESPONSE_MSG << RESET "\n]" << std::endl;

		Client client = Client("127.0.0.1", "8080");
		client.process_server_connect(RESPONSE_MSG);

		std::string response_msg = client.get_recv_message();
		std::cout << "Response message:[" << std::endl;
		std::cout << CYAN << response_msg << RESET "\n]" << std::endl;

		std::ofstream file("client_response.txt");
		if (file.is_open()) {
			file << response_msg;
			file.close();
		}
		// std::fflush(stdout);
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
