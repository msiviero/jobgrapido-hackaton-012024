#include "api.h"

#include <fmt/core.h>
#include <grpc/grpc.h>
#include <grpcpp/server_context.h>

#include "generated/service.grpc.pb.h"
#include "generated/service.pb.h"
#include "generated/pubsub.pb.h"
#include "pubsub.h"
#include "vrfy_client.h"

using grpc::Status;
using std::shared_ptr;

using pubsub_service::PubsubService;

MailVerifierImpl::MailVerifierImpl(
    shared_ptr<EmailVerifier> email_verifier_ptr,
    shared_ptr<VrfyClient> vrfy_client_ptr,
    shared_ptr<PubsubService> pubsub_service_ptr) {
  this->email_verifier = email_verifier_ptr.get();
  this->vrfy_client = vrfy_client_ptr.get();
  this->pubsub_service = pubsub_service_ptr.get();
}

Status MailVerifierImpl::SyntaxVerification(grpc::ServerContext *context,
                                            const VerificationRequest *request,
                                            VerificationResponse *reply) {
  auto email = request->email();
  auto result = this->email_verifier->regex_verify(email);

  reply->set_valid(result);
  reply->set_error_message(
      fmt::format("Email {0} {1} valid", email, result ? "IS" : "IS NOT"));

  return Status::OK;
}

Status MailVerifierImpl::SimpleVerification(grpc::ServerContext *context,
                                            const VerificationRequest *request,
                                            VerificationResponse *reply) {
  auto email = request->email();
  auto syntax_result = this->email_verifier->regex_verify(email);

  if (!syntax_result) {
    reply->set_valid(false);
    reply->set_error_message(
        fmt::format("Email {0} syntax IS NOT valid", email));
    return Status::OK;
  }

  auto dns_result = this->email_verifier->dns_verify(email);
  if (!dns_result) {
    reply->set_valid(false);
    reply->set_error_message(
        fmt::format("Email {0} domain IS NOT valid (no MX record)", email));
    return Status::OK;
  }

  reply->set_valid(true);
  reply->set_error_message(fmt::format("Email {0} IS valid", email));
  return Status::OK;
}

Status MailVerifierImpl::FullVerification(grpc::ServerContext *context,
                                          const VerificationRequest *request,
                                          VerificationResponse *reply) {
  auto email = request->email();
  auto syntax_result = this->email_verifier->regex_verify(email);

  if (!syntax_result) {
    auto err_msg = fmt::format("Email {0} syntax IS NOT valid", email);

    reply->set_valid(false);
    reply->set_error_message(err_msg);

    VerificationOutput message;
    message.set_email(email);
    message.set_error_message(err_msg);
    message.set_valid(false);

    this->pubsub_service->publish(message);
    return Status::OK;
  }

  auto dns_result = this->email_verifier->dns_verify(email);

  if (!dns_result) {
    auto err_msg =
        fmt::format("Email {0} domain IS NOT valid (no MX record)", email);

    reply->set_valid(false);
    reply->set_error_message(err_msg);

    VerificationOutput message;
    message.set_email(email);
    message.set_error_message(err_msg);
    message.set_valid(false);

    this->pubsub_service->publish(message);
    return Status::OK;
  }

  auto vrfy_result = this->vrfy_client->verify(email);
  if (!dns_result) {
    auto err_msg = fmt::format(
        "Email {0} domain IS NOT valid (failed VRFY remote)", email);

    reply->set_valid(false);
    reply->set_error_message(err_msg);

    VerificationOutput message;
    message.set_email(email);
    message.set_error_message(err_msg);
    message.set_valid(false);
    return Status::OK;
  }

  reply->set_valid(true);
  reply->set_error_message(fmt::format("Email {0} IS valid", email));

  VerificationOutput message;
  message.set_email(email);
  message.set_error_message("");
  message.set_valid(true);
  return Status::OK;
}
