#include <string>
#include <iostream>
#include <map>

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
    // Split request into request line and headers
    String requestLine, headers;
    int split = req.find('\r');
    requestLine = req.substr(0, split);
    headers = req.substr(split + 2, req.size() - split - 2);

    // State machine to get request type, host, path, and port
    int state = 0, portReached = 0;
    for (auto c : requestLine)
    {
        if (state == 0) // state 0 - get request type
        {
            if (c != ' ')
                type += c;
            else
                state = 1;
        }
        else if (state == 1) // state 1 - parsing host and port
        {
            if (portReached)
            {
                port += c;
            }
            if (c == ':')
                portReached = 1;
            if (c != '/')
                host += c;
            else if (host == "http:" || host == "https:") // get rid of http prefixes
            {
                host = "";
                state = 9;
            }
            else
            {
                path = "/";
                state = 2;
            }
        }
        else if (state == 2) // state 2 - parsing path to request
        {
            if (c != ' ')
                path += c;
            else
                break;
        }
        else if (state == 9) // filler state to account for "//" int http://
            state = 1;
    }

    // State machine to parse the rest of the header into a map
    state = 0;
    String key, value;
    std::map<String, String> map;
    for (auto c : headers)
    {
        if (state == 0) // state 0 - looking at header tag or key value
        {
            if (c == ':')
                state = 1;
            else
                key += c;
        }
        else if (state == 1) // state 1 is a filler to accomodate a ' ' character after ':'
            state = 2;
        else if (state == 2) // state 2 - looking at the value for the current tag
        {
            if (c == '\r') // end of value so put key and value into map
            {
                state = 3;
                headerMap[key] = value;
                key = value = "";
            }
            else
                value += c;
        }
        if (state == 3 && c == '\n') // end of line so go back to first state
            state = 0;
    }

    return *this;
}

String HttpHandler::getRequest()
{
    String req = type + " " + path + " HTTP/1.0\r\n" +
                 "Host: " + host + "\r\n";
    for (auto header : headerMap)
    {
        req += header.first + ": " + header.second + "\r\n";
    }
    req += "\r\n";
    return req;
}
