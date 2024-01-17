#include "api.h"

#include <fmt/core.h>
#include <grpc/grpc.h>
#include <grpcpp/server_context.h>

#include "./generated/service.grpc.pb.h"
#include "./generated/service.pb.h"

using grpc::Status;

MailVerifierImpl::MailVerifierImpl(
    std::shared_ptr<EmailVerifier> email_verifier_ptr) {
  this->email_verifier = email_verifier_ptr.get();
}

Status MailVerifierImpl::SyntaxVerification(grpc::ServerContext *context,
                                            const VerificationRequest *request,
                                            VerificationResponse *reply) {
  auto result = this->email_verifier->regex_verify(request->email());

  reply->set_valid(result);
  reply->set_error_message(fmt::format("Email {0} {1} valid", request->email(), result ? "IS" : "IS NOT"));
  
  return Status::OK;
}

Status MailVerifierImpl::SimpleVerification(grpc::ServerContext *context,
                                            const VerificationRequest *request,
                                            VerificationResponse *reply) {
  reply->set_error_message(fmt::format("Hello {0}", request->email()));
  return Status::OK;
}

Status MailVerifierImpl::FullVerification(grpc::ServerContext *context,
                                          const VerificationRequest *request,
                                          VerificationResponse *reply) {
  reply->set_error_message(fmt::format("Hello {0}", request->email()));
  return Status::OK;
}
