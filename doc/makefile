.PHONY: all clean

all: doxygen/xml
	sphinx-build -b html source build

clean:
	rm -rf build doxygen

doxygen/xml:
	doxygen
