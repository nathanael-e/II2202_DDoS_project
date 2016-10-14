#include "server.hpp"
#include <fstream>

using namespace II2202;

Server::Thread_counter::Thread_counter(std::atomic<int>& N_threads)
    :n_threads(&N_threads)
{
    (*n_threads)++;
}

Server::Thread_counter::~Thread_counter()
{
    (*n_threads)--;
}

Server::Server(const unsigned short port, int n_threads)
    :HttpServer(port, n_threads)
{}

Server::~Server()
{
    if(server_thread.joinable())
        server_thread.join();
}

void Server::start_server()
{
    server_thread = std::thread(([this](){this->start();}));
}

void Server::do_work(std::shared_ptr<HttpServer::Response>& response, std::shared_ptr<HttpServer::Request>& request)
{
    std::thread work_thread = std::thread([response, request, this]()
                {
                    Thread_counter new_thread(n_threads);
                    std::string s = "Work done";
                    
                    std::ifstream file;
                    file.open("bigassdoc");
                    char output[10000];
                    if(file.is_open()){
                        while(!file.eof()){
                            file >> output;
                            
                        }
                    }
                    std::stringstream ss;
                    ss << output;
                    s = ss.str();
                   // std::this_thread::sleep_for(std::chrono::seconds(5));
                    *response << "HTTP/1.1 200 OK\r\nContent-Length: " << s.length()  << "\r\n\r\n" << s;
                });

    work_thread.detach();
}

int Server::getSessions()
{
    return n_threads;
}

float Server::server_load() const
{
    return (float) n_threads / (float) MAX_THREADS;
}

bool Server::isFull() const
{
    if(n_threads >= MAX_THREADS)
        return true;
    else
        return false;
}
