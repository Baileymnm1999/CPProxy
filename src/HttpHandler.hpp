#ifndef __HTTPHANDLER__
#define __HTTPHANDLER__

#include <string>
#include "Types.hpp"

class HttpHandler
{
  private:
    String type, host, path, request;

  public:
    HttpHandler(/* args */);
    ~HttpHandler();
    HttpHandler parseRequest(String);
    String getRequest();
};

#endif