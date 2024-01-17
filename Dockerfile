FROM alpine

COPY ./build/grpc-verify /usr/local/bin/grpc-verify

ENTRYPOINT ["/usr/local/bin/grpc-verify"]
