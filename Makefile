CXX = g++
CXXFLAGS = -Wall -std=c++17 -g

TARGET = movie_recommender

SRCS = src/main.cpp src/Movie.cpp src/Rating.cpp src/User.cpp src/MovieManager.cpp src/UserManager.cpp src/RatingManager.cpp src/SimilarityCalculator.cpp src/Recommender.cpp
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

src/main.o: src/main.cpp src/MovieManager.h src/UserManager.h src/RatingManager.h
src/MovieManager.o: src/MovieManager.cpp src/MovieManager.h src/Movie.h
src/UserManager.o: src/UserManager.cpp src/UserManager.h src/User.h
src/RatingManager.o: src/RatingManager.cpp src/RatingManager.h src/Rating.h
src/Movie.o: src/Movie.cpp src/Movie.h
src/User.o: src/User.cpp src/User.h
src/Rating.o: src/Rating.cpp src/Rating.h
src/SimilarityCalculator.o: src/SimilarityCalculator.cpp src/SimilarityCalculator.h src/Rating.h
src/Recommender.o: src/Recommender.cpp src/Recommender.h src/MovieManager.h src/UserManager.h src/RatingManager.h src/SimilarityCalculator.h