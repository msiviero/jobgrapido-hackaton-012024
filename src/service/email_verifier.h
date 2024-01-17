#ifndef SERVICE_EMAIL_VERIFIER_H
#define SERVICE_EMAIL_VERIFIER_H

#include <string>

using std::string;

class EmailVerifier {
 public:
  bool verify(string email_address);

  bool regex_verify(string email_address);

  bool smtp_verify(string email_address);
};

#endif