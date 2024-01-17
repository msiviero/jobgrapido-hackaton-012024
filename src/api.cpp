#include "api.h"

#include <grpc/grpc.h>
#include <grpcpp/server_context.h>

#include "./generated/service.grpc.pb.h"

using grpc::Status;

Status MailVerifierImpl::SyntaxVerification(grpc::ServerContext *context,
                                            const VerificationRequest *request,
                                            VerificationResponse *reply) {

  reply->set_text(fmt::format("Hello {0}", request->email()));
  return Status::OK;
}