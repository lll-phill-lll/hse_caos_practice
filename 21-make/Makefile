CXX = g++
CXXFLAGS = --std=c++17 -MMD

TARGET=fractal
SRC = main.cpp julia.cpp color.cpp
OBJECTS = $(SRC:.cpp=.o)
DEPENDS = $(SRC:.cpp=.d)

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)


%.o: %.cpp 
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS) $(DEPENDS) image.ppm

-include $(DEPENDS)

.PHONY: clean run
