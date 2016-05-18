
all: build

SRC := cext07.cpp

.PHONY: build clean

build: $(SRC)
	python3 setup.py build_ext --inplace

clean:
	rm -rf *.so build
