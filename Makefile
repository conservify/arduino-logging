all: cmake build test

cmake:
	mkdir -p build
	cd build && cmake ../

build:
	cd build && make

test: cmake
	cd build && env GTEST_COLOR=1 make testcommon test ARGS=-VV

clean:
	rm -rf build

veryclean:
	rm -rf build gitdeps

.PHONY: build
