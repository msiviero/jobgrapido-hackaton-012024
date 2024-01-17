#include <fmt/core.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server_builder.h>

#include <iostream>

#include "api.h"

using grpc::Server;
using grpc::ServerBuilder;

using std::unique_ptr;

int main() {
  // get configs
  auto server_port = getenv("PORT");
  auto server_address = fmt::format("0.0.0.0:{}", server_port ? server_port : "50051");

  // build api
  MailVerifierImpl email_verifier_api;

  // start a server
  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&email_verifier_api);

  unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
  return 0;
}
