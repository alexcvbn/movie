#include "MovieManager.h"
#include <iostream>
#include <algorithm>


void MovieManager::addMovie(const Movie& movie) {
    for (const auto& m : movies) {
        if (m == movie) {  
            std::cout << "이미 등록되어 있는 영화입니다.\n";
            return;
        }
    }
    Movie newMovie(nextId, movie.getTitle(), movie.getGenre(), movie.getReleaseYear());
    nextId++;
    movies.push_back(newMovie);
}

void MovieManager::printAll() const {
    if (movies.empty()) {
        std::cout << "등록된 영화가 없습니다.\n";
        return;
    }

    for (const auto& m : movies) {
        std::cout << m << "\n";
    }
}

void MovieManager::printSorted() {
    std::vector<Movie> sorted = movies;
    std::sort(sorted.begin(), sorted.end());
    for (const auto& m : sorted) {
        std::cout << m << "\n";
    }
}

Movie* MovieManager::findTitle(const std::string& title) {
    for (auto& m : movies) {
        if (m.getTitle() == title) return &m;
    }
    return nullptr;
}

Movie* MovieManager::findMovieId(int id) {
    for (auto& m : movies) {
        if (m.getId() == id) return &m;
    }
    return nullptr;
}

std::vector<Movie*> MovieManager::findAllByTitle(const std::string& title) {
    std::vector<Movie*> result;
    for (auto& m : movies) {
        if (m.getTitle() == title) result.push_back(&m);
    }
    return result;
}
