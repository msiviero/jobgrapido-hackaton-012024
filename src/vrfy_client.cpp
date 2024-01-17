
#include "vrfy_client.h"

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <string.h>

#include "./generated/vrfy.grpc.pb.h"
#include "./generated/vrfy.pb.h"

using grpc::ClientContext;
using grpc::Status;

using std::string;

VrfyClient::VrfyClient(std::shared_ptr<Channel> channel)
    : stub(VrfyService::NewStub(channel)) {}

bool VrfyClient::verify(string email) {
  ClientContext context;

  VrfyRequest request;
  request.set_email(email);

  VrfyResponse reply;

  Status status = stub->Verify(&context, request, &reply);

  if (status.ok()) {
    return reply.status_code() == 0;
  } else {
    std::cerr << status.error_code() << ": " << status.error_message()
              << std::endl;
    return false;
  }
}
