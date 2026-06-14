#include "MovieManager.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <numeric>

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
        try {
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
        } catch (const std::exception& e) {
            std::cerr << "movies.csv 파싱 오류, 해당 줄 스킵: " << line << "\n";
        }
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

const std::vector<Movie>& MovieManager::getAllMovies() const {
    return movies;
}

std::vector<Movie> MovieManager::filterByGenre(const std::string& genre) const {
    std::vector<Movie> result;
    std::copy_if(movies.begin(), movies.end(), std::back_inserter(result),
        [&genre](const Movie& m) {
            return m.getGenre() == genre;
        }
    );
    return result;
}

double MovieManager::getAverageRating() const {
    if (movies.empty()) {
        throw std::runtime_error("영화 데이터가 없습니다.");
    }
    double sum = std::accumulate(movies.begin(), movies.end(), 0.0,
        [](double acc, const Movie& m) {
            return acc + m.getAverageRating();
        }
    );
    return sum / movies.size();
}

std::map<std::string, double> MovieManager::getAverageRatingByGenre() const {
    std::map<std::string, double> sumByGenre;
    std::map<std::string, int> countByGenre;
    
    for (const auto& movie : movies) {
        sumByGenre[movie.getGenre()] += movie.getAverageRating();
        countByGenre[movie.getGenre()]++;
    }
    
    std::map<std::string, double> avgByGenre;
    for (const auto& [genre, sum] : sumByGenre) {
        avgByGenre[genre] = sum / countByGenre[genre];
    }
    return avgByGenre;
}

std::vector<Movie> MovieManager::getTopN(int n) const {
    auto sorted = movies;
    if (n > static_cast<int>(sorted.size())) {
        n = sorted.size();
    }
    std::partial_sort(sorted.begin(), sorted.begin() + n, sorted.end(),
        [](const Movie& m1, const Movie& m2) {
            return m1.getAverageRating() > m2.getAverageRating();
        }
    );
    return std::vector<Movie>(sorted.begin(), sorted.begin() + n);
}

bool MovieManager::exportStatisticsReport(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    
    file << "==================================================\n";
    file << "       영화 추천 시스템 통계 리포트 (M4)\n";
    file << "==================================================\n\n";
    
    try {
        file << "1. 전체 영화 평균 평점: " << getAverageRating() << " 점\n\n";
    } catch (const std::exception& e) {
        file << "1. 전체 영화 평균 평점: N/A (데이터 없음)\n\n";
    }
    
    file << "2. 장르별 평균 평점:\n";
    auto genreStats = getAverageRatingByGenre();
    for (const auto& [genre, rating] : genreStats) {
        file << "   - " << genre << ": " << rating << " 점\n";
    }
    file << "\n";
    
    file << "3. 평점 상위 5개 영화:\n";
    auto top5 = getTopN(5);
    for (size_t i = 0; i < top5.size(); ++i) {
        file << "   " << (i + 1) << "위. " << top5[i].getTitle() 
             << " (평점: " << top5[i].getAverageRating() << " 점, " 
             << top5[i].getRatingCount() << "건 평가)\n";
    }
    
    file.close();
    return true;
}
