#pragma once
#include <vector>
#include <string>
#include "Movie.h"

class MovieManager {
    private:
        std::vector<Movie> movies;
        int nextId;
    
    public:
        void addMovie(const Movie& movie);
        void printAll() const;
        void printSorted();
        Movie* findTitle(const std::string& title);

};

