#ifndef GRPC_API_H
#define GRPC_API_H

#include <grpc/grpc.h>
#include <grpcpp/server_context.h>

#include "./generated/service.pb.h"
#include "./generated/service.grpc.pb.h"

#include "./email_verifier.h"

using grpc::Status;

class MailVerifierImpl final : public MailVerifier::Service {

 private:
   EmailVerifier *email_verifier;

 public:
  MailVerifierImpl(std::shared_ptr<EmailVerifier> email_verifier);

  Status SyntaxVerification(grpc::ServerContext *context, const VerificationRequest *request,
               VerificationResponse *reply) override;

  Status SimpleVerification(grpc::ServerContext *context, const VerificationRequest *request,
               VerificationResponse *reply) override;

  Status FullVerification(grpc::ServerContext *context, const VerificationRequest *request,
               VerificationResponse *reply) override;
};
// namespace api

#endif