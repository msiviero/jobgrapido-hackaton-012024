
#include "email_verifier.h"

#include <re2/re2.h>

#include <iostream>

#include <string.h>
#include <memory.h>

using std::string;

const RE2 email_regex(
    "(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\\.[a-z0-9!#$%&'*+/"
    "=?^_`{|}~-]+)*|\"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\["
    "\x01-\x09\x0b\x0c\x0e-\x7f])*\")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\\.)"
    "+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9]["
    "0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-z0-9-]*[a-z0-9]:(?"
    ":[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-"
    "\x7f])+)\\])");

EmailVerifier::EmailVerifier(std::shared_ptr<Dns> dns_ptr) {
  this->dns = dns_ptr.get();
}

bool EmailVerifier::dns_verify(const string email) {
  auto domain = this->extract_domain(email);
  return this->dns->is_domain_valid(domain);
}

bool EmailVerifier::regex_verify(const string email) {
  return RE2::FullMatch(email, email_regex);
}

bool EmailVerifier::smtp_verify(const string email) { return false; }

string EmailVerifier::extract_domain(string email) {
  auto separator_position = email.find("@");

  if (separator_position == string::npos) {
    return "";
  }
  return email.substr(email.find("@") + 1, email.length());
}