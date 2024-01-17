#ifndef SERVICE_PUBSUB_H
#define SERVICE_PUBSUB_H

#include <string>

#include "google/cloud/pubsub/publisher.h"
#include "generated/pubsub.pb.h"

using std::string;
using std::shared_ptr;

using google::cloud::pubsub::MakePublisherConnection;
using google::cloud::pubsub::MessageBuilder;
using google::cloud::pubsub::Publisher;
using google::cloud::pubsub::Topic;

namespace pubsub_service {

class PubsubService {
 private:
  Publisher* publisher;

 public:
  PubsubService(shared_ptr<Publisher> publisher);

  void publish(VerificationOutput message);
};

Publisher MakePublisher(string project_id, string topic_id);
}  // namespace service

#endif