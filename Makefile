.PHONY: all clean update flash menuconfig config

# BUILD_TYPE := RELEASE
BUILD_TYPE := DEBUG

all: build
	cmake --build build/debug
	cmake --build build/release

build:
	cmake -G Ninja -S . -B build/debug -DCMAKE_BUILD_TYPE=DEBUG
	cmake -G Ninja -S . -B build/release -DCMAKE_BUILD_TYPE=RELEASE

clean:
	rm -r build

flash:
	cmake --build build --target flash

menuconfig: config
	ccmake . build
