#include "api.h"

#include <grpc/grpc.h>
#include <grpcpp/server_context.h>

#include <fmt/core.h>

#include "./generated/service.pb.h"
#include "./generated/service.grpc.pb.h"

using grpc::Status;


Status MailVerifierImpl::SyntaxVerification(grpc::ServerContext *context,
                                            const VerificationRequest *request,
                                            VerificationResponse *reply) {

  reply->set_error_message(fmt::format("Hello {0}", request->email()));
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
