all: cmake all test

cmake:
	mkdir -p build
	cd build && cmake ../

test: cmake
	cd build && env GTEST_COLOR=1 make testcommon test ARGS=-VV

clean:
	rm -rf build

veryclean:
	rm -rf build gitdeps

