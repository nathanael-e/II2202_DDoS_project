#include "server_http.hpp"
#include "client_http.hpp"
#include <iostream>
#include <thread>
#include<string>

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;

int main()
{
	HttpServer server(8081, 1);
	
	server.resource["^.+$"]["GET"]=[](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request) {
        
        std::stringstream content_stream;
        content_stream << "<h1>Request from " << request->remote_endpoint_address << " (" << request->remote_endpoint_port << ")</h1>";
        content_stream << request->method << " " << request->path << " HTTP/" << request->http_version << "<br>";
        
        for(auto& header: request->header)
            content_stream << header.first << ": " << header.second << "<br>";
        
        content_stream.seekp(0, std::ios::end);

   	    HttpClient client("localhost:8080");
    	auto r1=client.request("GET", request->path);
        
        std::stringstream ss;
	    ss << r1->content.rdbuf(); 
        std::string res = ss.str();	

        *response <<  "HTTP/1.1 200 OK\r\nContent-Length: " << res.size() << "\r\n\r\n" << res;
    };
    

    std::thread server_thread([&server](){server.start();});
	
	server_thread.join();
	return 0;
}
