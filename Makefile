all: build test

cmake:
	mkdir -p build
	cd build && cmake ../

build: cmake
	$(MAKE) -C build

test: build
	env GTEST_COLOR=1 $(MAKE) -C build testcommon test ARGS=-VV

clean:
	rm -rf build

veryclean:
	rm -rf build gitdeps

.PHONY: build
