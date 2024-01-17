#ifndef EMAIL_VERIFIER_H
#define EMAIL_VERIFIER_H

#include <re2/re2.h>

#include <string>

#include "dns.h"

using std::string;

class EmailVerifier {
 private:
  string extract_domain(string email);
  Dns *dns;

 public:
  EmailVerifier(std::shared_ptr<Dns> dns);

  bool dns_verify(string email);
  bool regex_verify(string email);
  bool smtp_verify(string email);
};

#endif