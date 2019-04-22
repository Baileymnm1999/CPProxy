#include <string>

#include "HttpHandler.hpp"
#include "Types.hpp"

HttpHandler::HttpHandler()
{
}

HttpHandler::~HttpHandler()
{
}

HttpHandler HttpHandler::parseRequest(String req)
{
    String data;

    if (req.substr(0, 3) == "GET")
    {
        type = "GET";
        data = req.substr(4, req.size() - 4);
    }
    else if (req.substr(0, 4) == "POST")
    {
        type = "POST";
        data = req.substr(5, req.size() - 5);
    }
    else if (req.substr(0, 4) == "HEAD")
    {
        type = "HEAD";
        data = req.substr(5, req.size() - 5);
    }

    int end;
    if (data.substr(0, 7) == "http://")
    {
        // Maths
        end = data.substr(7, data.size() - 7).find('/');
        host = data.substr(7, end);
        path = data.substr(end + 7, data.find(' ') - end - 7);
    }

    end = data.find('\n') + 1;
    request = type + " " + path + " HTTP/1.0\r\n" +
              "Host: " + host + "\r\n" +
              data.substr(end, data.size() - end);
    return *this;
}

String HttpHandler::getRequest()
{
    return request;
}
