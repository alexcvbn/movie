#include "RatingManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void RatingManager::addRating(const Rating& rating) {
    ratings.push_back(rating);
}

void RatingManager::printRatings(int movieId) const {
    bool found = false;
    for (const auto& r : ratings) {
        if (r.getMovieid() == movieId) {
            std::cout << "유저: " << r.getUserid()
                      << "  평점: " << r.getScore() << "\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "평점이 없습니다.\n";
    }
}
void RatingManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << filename << " 파일 없음, 빈 상태로 시작\n";
        return;
    }
    std::string line;
    getline(file, line); // 헤더 스킵
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        getline(ss, token, ','); std::string userId = token;
        getline(ss, token, ','); int movieId = stoi(token);
        getline(ss, token, ','); double score = stod(token);
        ratings.push_back(Rating(userId, movieId, score));
    }
    file.close();
}

void RatingManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << filename << " 저장 실패\n";
        return;
    }
    file << "userId,movieId,score\n";
    for (const auto& r : ratings) {
        file << r.getUserid() << ","
             << r.getMovieid() << ","
             << r.getScore() << "\n";
    }
    file.close();
}

int RatingManager::size() const {
    return ratings.size();
}