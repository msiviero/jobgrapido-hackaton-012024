.PHONY: build

build:
	make clean
	mkdir -p src/generated
	#protoc --cpp_out=./src/generated/ proto/*.proto 
	conan install . --output-folder=build --build=missing
	cd build && cmake .. -DCMAKE_TOOLCHAIN_FILE=build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
	cd build && cmake --build .	

clean:
	rm -rf build src/generated

grpcui:
	grpcui -plaintext -import-path=./proto -proto=service.proto 127.0.0.1:50051
