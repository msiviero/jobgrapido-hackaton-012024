#ifndef DNS_H
#define DNS_H

#include <string>

using std::string;

class Dns {
 public:
  bool resolve(string email_address);
};

#endif