#include "server.hpp"

using namespace II2202;

Server::Session::Session(std::atomic<int>& session)
    :n_sessions(&session)
{
    (*n_sessions)++;
}

Server::Session::~Session()
{
    (*n_sessions)--;
}

Server::Server(const unsigned short port, int n_threads)
    :HttpServer(port, n_threads)
{
    add_resources(); 
}

void Server::add_resources()
{
    resource["^/work$"]["GET"] = [&](std::shared_ptr<Response> response, std::shared_ptr<Request> /*request*/)
    {
        std::thread work_thread([&, response]()
            {
                Session new_session{n_sessions};
                std::this_thread::sleep_for(std::chrono::seconds(10));
                std::string message="Work done";
                *response << "HTTP/1.1 200 OK\r\nContent-Length: " << message.length() << "\r\n\r\n" << message;
            });

        work_thread.detach();
    }; 
    resource["^/getSessions$"]["GET"] = [&](std::shared_ptr<Response> response, std::shared_ptr<Request> /*request*/)
    {
        std::thread work_thread([&, response]()
            {
		
                Session new_session{n_sessions};
                int iSessions = getSessions();
                std::stringstream ssSessions;
                ssSessions << iSessions;
                std::string message= ssSessions.str();
                *response << "HTTP/1.1 200 OK\r\nContent-Length: " << message.length() << "\r\n\r\n" << message;
            });

        work_thread.detach();
    }; 

}

int Server::getSessions()
{
    return n_sessions;
}

Server::~Server(){}
