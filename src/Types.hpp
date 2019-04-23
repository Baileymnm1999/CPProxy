#ifndef __TYPES__
#define __TYPES__

#include <string>
#include <thread>
#include <map>

typedef std::string String;
typedef std::thread Thread;

template <typename key, typename value>
using Map = std::map<key, value>;

#endif