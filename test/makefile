BUILD_DIR=build

.PHONY: all clean

all: test

${BUILD_DIR}:
	mkdir build

${BUILD_DIR}/%.o: %.cpp ${BUILD_DIR}
	$(CXX) -std=c++17 -I ../include -c -o $@ $<

test: $(patsubst %.cpp,${BUILD_DIR}/%.o,$(wildcard *.cpp))
	$(CXX) -o $@ $^

clean:
	rm -rf ${BUILD_DIR}
	rm -f test
