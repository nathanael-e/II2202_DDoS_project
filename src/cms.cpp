#include "cms.hpp"

using namespace II2202;

CMS::CMS(const unsigned short port, int n_threads)
    :HttpServer(port, n_threads)
{
    add_reseources();
}

void CMS::add_reseources()
{
    resource["^.*$"]["GET"] = [&](std::shared_ptr<Response> response, std::shared_ptr<Request> request)
    {

        for(auto it = servers.begin(); it != servers.end(); it++)
        {
            auto answer = it->get()->request("GET", "/getSessions");
            std::stringstream ss;
            ss<<answer->content.rdbuf();
            int sessions = std::stoi(ss.str());

            if(sessions <= 20)
            {
                auto ans  = it->get()->request("GET", request->path);
                std::stringstream s2;
                s2<<ans->content.rdbuf();
                std::string s = s2.str();
                *response << "HTTP/1.1 200 OK\r\nContent-Length: " << s.size() << "\r\n\r\n" << s;
                break;
             }
        }
    }; 
}

void CMS::add_server(const std::string ip)
{
    servers.push_back(std::make_unique<HttpClient>(ip));
}
