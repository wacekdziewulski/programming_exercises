CXX=g++
CXXFLAGS=-I. -std=c++14 -lpthread -g
DEPS = Task.hpp TaskExecutor.hpp
OBJ = Task.o TaskExecutor.o main.o 

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

task_executor: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)
