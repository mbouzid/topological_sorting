CXX		= g++
RM		= rm 
SRCS		= src/main.cpp src/vertex.cpp src/arc.cpp src/directed_graph.cpp src/strfun.cpp
OBJECTS		= objects/main.o objects/vertex.o objects/arc.o objects/directed_graph.o objects/strfun.o 
STD		= -std=c++11
WARN		= -Wall
TMPS		= src/*~

##### Building rules
all: topological_sorting
	@echo "Building complete."

###### Linking
topological_sorting: $(OBJECTS)
	$(CXX) $(WARN) $(STD) -o topological_sorting  $(OBJECTS)
	@echo "Linking done."

###### Compiling
objects/main.o: src/main.cpp 
	$(CXX) -c $(STD) -o objects/main.o src/main.cpp
objects/vertex.o: src/vertex.cpp 
	$(CXX) -c $(STD) -o objects/vertex.o src/vertex.cpp
objects/arc.o: src/arc.cpp 
	$(CXX) -c $(STD) -o objects/arc.o src/arc.cpp
objects/directed_graph.o: src/directed_graph.cpp 
	$(CXX) -c $(STD) -o objects/directed_graph.o src/directed_graph.cpp
objects/strfun.o: src/strfun.cpp 
	$(CXX) -c $(STD) -o objects/strfun.o src/strfun.cpp
