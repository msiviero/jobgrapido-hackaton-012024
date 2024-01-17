cmake_minimum_required(VERSION 3.20)

project(grpc-server CXX)

add_executable(${PROJECT_NAME} 
  src/main.cpp
  src/generated/service.grpc.pb.cc
  src/generated/service.pb.cc

  src/api/hello.cpp
  src/api/health.cpp
  src/service/pubsub.cpp
)
