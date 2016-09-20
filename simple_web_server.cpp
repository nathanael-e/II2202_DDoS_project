#include "server_http.hpp"
#include "client_http.hpp"
#include <iostream>
#include <thread>

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;

int main()
{
	HttpServer server(8081, 1);

    std::thread server_thread([&server](){server.start();});
	
	server_thread.join();
	return 0;
}
