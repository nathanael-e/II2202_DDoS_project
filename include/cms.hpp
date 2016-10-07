#ifndef CMS_HPP
#define CMS_HPP

#include<string>
#include<vector>
#include<memory>
#include "server_http.hpp"
#include "client_http.hpp"
#include "server.hpp"

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;
using d_servers = std::unique_ptr<HttpClient>;

namespace II2202
{
    class CMS
        :public HttpServer
    {
        public:
            CMS(const unsigned short, int);
            void add_server(const std::string ip);
        
        private:
            void add_reseources();
            std::vector<d_servers> servers;
    };
}
#endif
