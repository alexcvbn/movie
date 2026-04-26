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
        Movie* findMovieId(int id);
        std::vector<Movie*> findAllByTitle(const std::string& title);
        //겹치는 영화 목록 출력이 가능하게 하는 함수!

};

