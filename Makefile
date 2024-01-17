.PHONY: build

build:
	#rm -rf build src/generated
	#mkdir -p src/generated
	conan install . --output-folder=build --build=missing
	cd build && cmake .. -DCMAKE_TOOLCHAIN_FILE=build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
	cd build && cmake --build .	

run:
	make build
	GOOGLE_APPLICATION_CREDENTIALS=gcp-credentials.json GCP_PROJECT_ID='friendly-anthem-321516' GCP_PUBSUB_TOPIC='test-marco' ./build/grpc-server
