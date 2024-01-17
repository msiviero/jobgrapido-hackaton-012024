#include "pubsub.h"

#include "google/cloud/pubsub/publisher.h"
#include "generated/pubsub.pb.h"

namespace pubsub_service {
PubsubService::PubsubService(shared_ptr<Publisher> publisher) {
  this->publisher = publisher.get();
}

void PubsubService::publish(VerificationOutput message) try {

  string serialized;
  message.SerializeToString(&serialized);

  auto id = publisher->Publish(MessageBuilder{}.SetData(serialized).Build()).get();
  if (!id) {
    throw std::move(id).status();
  }
} catch (google::cloud::Status const& status) {
  std::cerr << "google::cloud::Status thrown: " << status << "\n";
}

Publisher MakePublisher(string project_id, string topic_id) {
  return Publisher(MakePublisherConnection(Topic(project_id, topic_id)));
}
}  // namespace pubsub_service