#ifndef __HTTPHANDLER__
#define __HTTPHANDLER__

#include <string>
#include <map>
#include "Types.hpp"

class HttpHandler
{
private:
  String type, host, path, port;
  Map<String, String> headerMap;

public:
  HttpHandler(/* args */);
  ~HttpHandler();
  HttpHandler parseRequest(String);
  String getRequest();
  int getPort();
  String getHost();
  // void sendRequest();
};

#endif