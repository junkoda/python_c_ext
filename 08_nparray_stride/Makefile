all: build

SRC := cext08.c

.PHONY: build clean

build: $(SRC)
	python3 setup.py build_ext --inplace

clean:
	rm -rf build
