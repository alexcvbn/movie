CXX = g++
CXXFLAGS = -Wall -std=c++11

TARGET = movie_app

SRCS = main.cpp Movie.cpp Rating.cpp User.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

main.o: main.cpp Movie.h Rating.h User.h
Movie.o: Movie.cpp Movie.h
Rating.o: Rating.cpp Rating.h
User.o: User.cpp User.h