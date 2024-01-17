#ifndef GRPC_API_H
#define GRPC_API_H

#include <grpc/grpc.h>
#include <grpcpp/server_context.h>

#include "./generated/service.pb.h"
#include "./generated/service.grpc.pb.h"

#include "./email_verifier.h"
#include "vrfy_client.h"

using grpc::Status;
using std::shared_ptr;

class MailVerifierImpl final : public MailVerifier::Service {

 private:
   EmailVerifier *email_verifier;
   VrfyClient *vrfy_client;

 public:
  MailVerifierImpl(shared_ptr<EmailVerifier> email_verifier, shared_ptr<VrfyClient> vrfy_client_ptr);

  Status SyntaxVerification(grpc::ServerContext *context, const VerificationRequest *request,
               VerificationResponse *reply) override;

  Status SimpleVerification(grpc::ServerContext *context, const VerificationRequest *request,
               VerificationResponse *reply) override;

  Status FullVerification(grpc::ServerContext *context, const VerificationRequest *request,
               VerificationResponse *reply) override;
};
// namespace api

#endif