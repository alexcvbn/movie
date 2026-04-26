CXX = g++
CXXFLAGS = -Wall -std=c++11

TARGET = movie_recommender

SRCS = main.cpp Movie.cpp Rating.cpp User.cpp MovieManager.cpp UserManager.cpp RatingManager.cpp
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

main.o: main.cpp MovieManager.h UserManager.h RatingManager.h
MovieManager.o: MovieManager.cpp MovieManager.h Movie.h
UserManager.o: UserManager.cpp UserManager.h User.h
RatingManager.o: RatingManager.cpp RatingManager.h Rating.h
Movie.o: Movie.cpp Movie.h
User.o: User.cpp User.h
Rating.o: Rating.cpp Rating.h