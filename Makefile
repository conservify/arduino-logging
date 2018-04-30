default: gitdeps cmake
	cd build && make

cmake:
	mkdir -p build
	cd build && cmake ../

gitdeps:
	simple-deps --config examples/basic/arduino-libraries

clean:
	rm -rf build

veryclean:
	rm -rf build gitdeps

