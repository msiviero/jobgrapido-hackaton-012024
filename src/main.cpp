#include <fmt/core.h>
#include <google/cloud/pubsub/publisher.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server_builder.h>
#include <re2/re2.h>

#include <iostream>

#include "api.h"
#include "email_verifier.h"
#include "pubsub.h"

using grpc::Server;
using grpc::ServerBuilder;

using std::make_shared;
using std::unique_ptr;

using pubsub_service::PubsubService;

int main() {
  // get configs
  auto pubsub_project = getenv("PUBSUB_PROJECT");
  auto pubsub_topic = getenv("PUBSUB_TOPIC");

  auto vrfy_endpoint = getenv("VRFY_ENDPOINT");
  auto vrfy_port = getenv("VRFY_PORT");

  auto server_port = getenv("SERVER_PORT");
  auto server_address =
      fmt::format("0.0.0.0:{}", server_port ? server_port : "50051");

  // build deps
  auto channel =
      grpc::CreateChannel(fmt::format("{}:{}", vrfy_endpoint, vrfy_port),
                          grpc::InsecureChannelCredentials());
  auto dns = make_shared<Dns>();
  auto email_verifier = make_shared<EmailVerifier>(dns);
  auto vrfy_client = make_shared<VrfyClient>(channel);

  auto publisher =
      make_shared<Publisher>(pubsub_service::MakePublisher(pubsub_project, pubsub_topic));
  auto pubsub_service = make_shared<PubsubService>(publisher);

  // build api
  MailVerifierImpl email_verifier_api(email_verifier, vrfy_client);

  // start a server
  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&email_verifier_api);

  unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
  return 0;
}
