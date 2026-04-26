#include "RatingManager.h"
#include <iostream>

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