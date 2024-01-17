.PHONY: build

build:
	make clean
	mkdir -p src/generated
	conan install . --output-folder=build --build=missing
	cd build && cmake --debug-output .. -DCMAKE_TOOLCHAIN_FILE=build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
	cd build && cmake --build .	

clean:
	rm -rf build src/generated
