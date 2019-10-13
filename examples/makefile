SRCS=$(wildcard *.cpp)
TARGETS=$(patsubst %.cpp,%,$(SRCS))

.PHONY: all clean

all: $(TARGETS)
clean:
	rm -f $(TARGETS)

%: %.cpp
	$(CXX) -std=c++17 $< -o $@ -I ../include
