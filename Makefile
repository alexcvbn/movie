CXX = g++
CXXFLAGS = -Wall -std=c++17 -g -Iinclude

TARGET = movie_recommender

SRCS = src/main.cpp src/Movie.cpp src/Rating.cpp src/User.cpp src/MovieManager.cpp src/UserManager.cpp src/RatingManager.cpp src/SimilarityCalculator.cpp src/Recommender.cpp src/ConsoleUI.cpp
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

src/main.o: src/main.cpp include/MovieManager.h include/UserManager.h include/RatingManager.h include/Recommender.h include/ConsoleUI.h
src/MovieManager.o: src/MovieManager.cpp include/MovieManager.h include/Movie.h include/BaseManager.h
src/UserManager.o: src/UserManager.cpp include/UserManager.h include/User.h include/BaseManager.h
src/RatingManager.o: src/RatingManager.cpp include/RatingManager.h include/Rating.h include/BaseManager.h
src/Movie.o: src/Movie.cpp include/Movie.h
src/User.o: src/User.cpp include/User.h
src/Rating.o: src/Rating.cpp include/Rating.h
src/SimilarityCalculator.o: src/SimilarityCalculator.cpp include/SimilarityCalculator.h include/Rating.h
src/Recommender.o: src/Recommender.cpp include/Recommender.h include/MovieManager.h include/UserManager.h include/RatingManager.h include/SimilarityCalculator.h
src/ConsoleUI.o: src/ConsoleUI.cpp include/ConsoleUI.h include/Movie.h