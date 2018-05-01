default: cmake
	cd build && make

all: default

cmake:
	mkdir -p build
	cd build && cmake ../

test: all
	cd build && env GTEST_COLOR=1 make testcommon test ARGS=-VV

clean:
	rm -rf build

veryclean:
	rm -rf build gitdeps

