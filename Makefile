CXX=g++
RM=rm -f 
SRCS= src/*.cpp
OBJS=$(subst %.cpp,%.o,$(SRCS))
STD=-std=c++11
WARN=-Wall
TMPS= src/*~
all: topological_sorting
topological_sorting: $(OBJS)
	$(CXX) $(WARN) $(STD) -o topological_sorting  $(OBJS)
%.o: %.cpp 
	$(CXX) -c $<
clean:
	$(RM) $(TMPS)
dist-clean: clean 
	$(RM) topological_sorting
