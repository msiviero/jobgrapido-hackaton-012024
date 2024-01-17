set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(PROTO_BINARY_DIR "${CMAKE_CURRENT_LIST_DIR}/src/generated")

cmake_minimum_required(VERSION 3.20)

project(grpc-verify CXX)

find_package(fmt REQUIRED)
find_package(re2 REQUIRED)
find_package(ldns REQUIRED)

find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(google-cloud-cpp CONFIG REQUIRED)

add_library(
    ${PROJECT_NAME}-objects OBJECT 
    "${CMAKE_CURRENT_LIST_DIR}/proto/service.proto"
    "${CMAKE_CURRENT_LIST_DIR}/proto/vrfy.proto"
    "${CMAKE_CURRENT_LIST_DIR}/proto/pubsub.proto"
)

add_executable(${PROJECT_NAME} 
  src/main.cpp
  
  src/generated/service.grpc.pb.cc
  src/generated/service.pb.cc
  src/generated/vrfy.grpc.pb.cc
  src/generated/vrfy.pb.cc

  src/api.cpp
  src/dns.cpp
  src/pubsub.cpp
  src/vrfy_client.cpp
  src/email_verifier.cpp
)

protobuf_generate(
    TARGET ${PROJECT_NAME}-objects
    LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=\$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
    IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}/proto"
    PROTOC_OUT_DIR ${PROTO_BINARY_DIR}
    PROTOC_OPTIONS "--experimental_allow_proto3_optional"
)

protobuf_generate(
    TARGET ${PROJECT_NAME}-objects
    IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}/proto"
    PROTOC_OUT_DIR ${PROTO_BINARY_DIR}
    PROTOC_OPTIONS "--experimental_allow_proto3_optional"
)

target_link_libraries(${PROJECT_NAME} fmt::fmt)
target_link_libraries(${PROJECT_NAME} ldns::ldns)
target_link_libraries(${PROJECT_NAME} re2::re2)
target_link_libraries(${PROJECT_NAME} gRPC::grpc++)
target_link_libraries(${PROJECT_NAME} google-cloud-cpp::google-cloud-cpp)

target_link_libraries(${PROJECT_NAME}-objects PUBLIC gRPC::grpc++)
