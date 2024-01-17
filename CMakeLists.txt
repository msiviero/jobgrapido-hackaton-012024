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
)
add_executable(${PROJECT_NAME} 
  src/main.cpp
)

#protobuf_generate(
#    TARGET ${PROJECT_NAME}-objects
#    LANGUAGE grpc
#    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
#    PLUGIN "protoc-gen-grpc=\$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
#    IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}/proto"
#    PROTOC_OUT_DIR ${PROTO_BINARY_DIR}
#    PROTOC_OPTIONS "--experimental_allow_proto3_optional"
#)

#protobuf_generate(
#    TARGET ${PROJECT_NAME}-objects
#    IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}/proto"
#    PROTOC_OUT_DIR ${PROTO_BINARY_DIR}
#    PROTOC_OPTIONS "--experimental_allow_proto3_optional"
#)

target_link_libraries(${PROJECT_NAME} fmt::fmt)
target_link_libraries(${PROJECT_NAME} ldns::ldns)
target_link_libraries(${PROJECT_NAME} re2::re2)
target_link_libraries(${PROJECT_NAME} gRPC::grpc++)
target_link_libraries(${PROJECT_NAME} google-cloud-cpp::google-cloud-cpp)

target_link_libraries(${PROJECT_NAME}-objects PUBLIC gRPC::grpc++)
