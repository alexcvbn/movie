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
    movies.push_back(movie);
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
