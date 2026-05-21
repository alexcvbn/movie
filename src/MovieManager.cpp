#include "MovieManager.h"
#include "Movie.h"
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

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

void MovieManager::loadFromFile(const std::string& filename){
    std::ifstream file(filename);
    if(!file.is_open()) {
        std::cout << filename << " 파일 없음, 빈 상태 시작\n ";
        return;
    }

    std::string line;
    getline(file, line);
    
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        getline(ss, token, ','); int id = stoi(token);
        getline(ss, token, ','); std::string title = token;
        getline(ss, token, ','); std::string genre = token;
        getline(ss, token, ','); int year = stoi(token);
        getline(ss, token, ','); double totalRating = stod(token);
        getline(ss, token, ','); int ratingCount = stoi(token);
        Movie m(id, title, genre, year);
        for (int i = 0; i < ratingCount; i++) {
            m.addRating(totalRating / ratingCount);
        }
        movies.push_back(m);
        if (id >= nextId) nextId = id + 1;
    }
    file.close();
}

void MovieManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << filename << " 저장 실패\n";
        return;
    }
    file << "id,title,genre,year,totalRating,ratingCount\n";
    for (const auto& m : movies) {
        file << m.getId() << ","
             << m.getTitle() << ","
             << m.getGenre() << ","
             << m.getReleaseYear() << ","
             << m.getAverageRating() * m.getRatingCount() << ","
             << m.getRatingCount() << "\n";
    }
    file.close();
}

int MovieManager::size() const {
    return movies.size();
}
