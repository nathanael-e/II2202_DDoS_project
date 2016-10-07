#include "server_http.hpp"
#include "client_http.hpp"
#include <iostream>

using namespace std;

typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;
typedef SimpleWeb::Client<SimpleWeb::HTTP> HttpClient;

int main()
{
	HttpServer server(8081, 1);
	
	
    //GET-example for the path /info
    //Responds with request-information
    server.resource["^/$"]["GET"]=[](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
        stringstream content_stream;
        content_stream << "<h1>Request from " << request->remote_endpoint_address << " (" << request->remote_endpoint_port << ")</h1>";
        content_stream << request->method << " " << request->path << " HTTP/" << request->http_version << "<br>";
        for(auto& header: request->header) {
            content_stream << header.first << ": " << header.second << "<br>";
        }
        
        //find length of content_stream (length received using content_stream.tellp())
        content_stream.seekp(0, ios::end);
        //Client examples
   	HttpClient client("localhost:8080");
    	auto r1=client.request("GET", "/index.html");
	stringstream ss;
	ss << r1->content.rdbuf(); 
	string res = ss.str();	
	//cout << r1 -> content.seekp(0, ios::end) << endl;
        *response <<  "HTTP/1.1 200 OK\r\nContent-Length: " << res.size() << "\r\n\r\n" << res;// r1->content.rdbuf();//content_stream.rdbuf();
    };

	thread server_thread([&server](){
        //Start server
        server.start();
    });
	this_thread::sleep_for(chrono::seconds(1));
	server_thread.join();
	std::cout << "Hej"<<endl;
	return 0;
}
