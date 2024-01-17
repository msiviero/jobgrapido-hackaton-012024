#ifndef EMAIL_VERIFIER_H
#define EMAIL_VERIFIER_H

#include <string>
#include <re2/re2.h>

using std::string;

class EmailVerifier {
 
 public:
  EmailVerifier();

  bool verify(string email_address);
  bool regex_verify(string email_address);
  bool smtp_verify(string email_address);
};

#endif