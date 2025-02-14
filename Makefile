# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Target executable
TARGET = main

# Source files and object files
SRCS = src/main.cpp src/log.cpp src/VertexTensor.cpp src/TensorArray.cpp src/Render.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
