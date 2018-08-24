all: build test

cmake:
	mkdir -p build
	cd build && cmake ../

build: cmake
	cd build && make

test: build
	cd build && env GTEST_COLOR=1 make testcommon test ARGS=-VV

clean:
	rm -rf build

veryclean:
	rm -rf build gitdeps

.PHONY: build
