#ifndef __PROXY__
#define __PROXY__

#include <string>

#include "Socket.hpp"
#include "Types.hpp"

class Proxy
{
private:
  Socket client;
  String handleClient(int);
  void handleHttp();
  int identifyRequest(String);
  Socket forward(String, String, int);

public:
  static const int HTTP = 0b00;
  Proxy(Socket);
  ~Proxy();
  void startInstance(int);
};

#endif