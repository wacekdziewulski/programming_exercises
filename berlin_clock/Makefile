CXX=g++
CXXFLAGS=-std=c++11 -g -O0
TEST_SLIBS=/usr/lib/libgtest.a
TEST_LDFLAGS=-lpthread
TARGET=time

SRC=$(wildcard src/*.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRC))

TEST_SRC=$(wildcard test/*.cpp) $(filter-out src/main.cpp, $(SRC))
TEST_OBJS=$(patsubst %.cpp,%.o,$(TEST_SRC))

default: ${TARGET} test

test: ${TEST_OBJS}
	${CXX} ${TEST_OBJS} ${TEST_SLIBS} ${TEST_LDFLAGS} -o test_${TARGET}

test/%.o: test/%.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

${TARGET}: ${OBJS}
	${CXX} ${OBJS} -o ${TARGET}

src/%.o: src/%.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

clean:
	rm -f ${TARGET} test_${TARGET} src/*.o test/*.o
