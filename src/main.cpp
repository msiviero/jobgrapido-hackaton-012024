#include <iostream>
#include <fmt/core.h>

int main() {
  auto server_address = fmt::format("0.0.0.0:{}", 50051);
  std::cout << server_address;
  return 0;
}
