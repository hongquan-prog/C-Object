.PHONY: all clean update flash menuconfig config

all: build
	cmake --build build/debug
	cmake --build build/release

build:
	cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=DEBUG
	cmake -S . -B build/release -DCMAKE_BUILD_TYPE=RELEASE

clean:
	rm -r build
