#ifndef GRPC_API_H
#define GRPC_API_H

#include <grpc/grpc.h>
#include <grpcpp/server_context.h>

#include "./generated/service.pb.h"
#include "./generated/service.grpc.pb.h"

using grpc::Status;

class MailVerifierImpl final : public MailVerifier::Service {
 public:
  Status SyntaxVerification(grpc::ServerContext *context, const VerificationRequest *request,
               VerificationResponse *reply) override;

  Status SimpleVerification(grpc::ServerContext *context, const VerificationRequest *request,
               VerificationResponse *reply) override;

  Status FullVerification(grpc::ServerContext *context, const VerificationRequest *request,
               VerificationResponse *reply) override;
};
// namespace api

#endif