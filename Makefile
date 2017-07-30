OBJ			= objects
BIN			= binary

INC_PATH	= -IE:/Libs/boost_1_64_0
LIB_PATH	= -LE:/Libs/boost_1_64_0/stage/lib
USED_LIBS	= -lboost_filesystem-mgw51-mt-1_64 -lboost_system-mgw51-mt-s-1_64

CXX			= clang++ -c
LINK		= clang++

CXXFLAGS	= -std=c++14 -O2 -Wall

.PHONY: build clean refresh run

build: $(BIN)/DependencyCheck.exe
run: $(BIN)/DependencyCheck.exe
	$(BIN)/DependencyCheck.exe
clean:
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/*.exe
refresh: clean build

$(OBJ)/dependency_check.o: dependency_check.h dependency_check.cpp
	mkdir -p $(OBJ)
	$(CXX) $(CXXFLAGS) $(INC_PATH) dependency_check.cpp -o $(OBJ)/dependency_check.o

$(OBJ)/main.o: dependency_check.h main.cpp
	mkdir -p $(OBJ)
	$(CXX) $(CXXFLAGS) $(INC_PATH) main.cpp -o $(OBJ)/main.o

$(BIN)/DependencyCheck.exe: $(OBJ)/dependency_check.o $(OBJ)/main.o
	mkdir -p $(BIN)
	$(LINK) $^ $(LIB_PATH) $(USED_LIBS) -o $@
