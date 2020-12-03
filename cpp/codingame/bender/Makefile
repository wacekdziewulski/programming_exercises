CXX=g++
CXXFLAGS=-std=c++11 -g -O0
TEST_LDFLAGS=-lpthread
SOURCE_DIR=Bender
TARGET=${SOURCE_DIR}/Bender

SRC=$(wildcard ${SOURCE_DIR}/*.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRC))

TEST_OBJS=$(patsubst %.cpp,%.o,$(TEST_SRC))

.phony : all

all : default

default: ${TARGET}

${TARGET}: ${OBJS}
	${CXX} ${OBJS} -o ${TARGET}

${SOURCE_DIR}/%.o: ${SOURCE_DIR}/%.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

clean:
	rm -f ${TARGET} ${SOURCE_DIR}/*.o
