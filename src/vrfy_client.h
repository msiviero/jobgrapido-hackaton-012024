#ifndef VRFY_CLIENT_H
#define VRFY_CLIENT_H

#include <grpc/grpc.h>
#include <grpcpp/channel.h>

#include "./generated/vrfy.grpc.pb.h"
#include "./generated/vrfy.pb.h"

using grpc::Channel;
using std::string;

class VrfyClient {
 private:
  std::unique_ptr<VrfyService::Stub> stub;

 public:
  VrfyClient(std::shared_ptr<Channel> channel);

  bool verify(string email);
};

#endif