
#include "email_verifier.h"

#include <string>

using std::string;

bool EmailVerifier::verify(const string email) {
  return false;
}

bool EmailVerifier::regex_verify(const string email) {
  return false;
}

bool EmailVerifier::smtp_verify(const string email) {
  return false;
}