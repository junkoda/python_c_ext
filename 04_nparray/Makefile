all: build

SRC := cext04.c

.PHONY: build clean

build: $(SRC)
	python3 setup.py build_ext --inplace

clean:
	rm -rf build
