#ifndef DNS_H
#define DNS_H

#include <string>
#include <ldns/ldns.h>

using std::string;

class Dns {
 private:
  ldns_resolver *resolver;

 public:
  Dns();

  bool is_domain_valid(string email_address);
};

#endif