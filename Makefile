all: main

CXX = clang++
override CXXFLAGS += -g -Wno-everything

SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.cpp' -print | sed -e 's/ /\\ /g')
HEADERS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)

#main: $(SRCS) $(HEADERS)
#	$(CXX) $(CXXFLAGS) $(SRCS) -o "$@"

main:
	(cd ./PRODASFA/Problem_Situation/P4;	g++ main.cpp -o main;	./main)

main-debug: $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -O0 $(SRCS) -o "$@"

clean:
	rm -f main main-debug