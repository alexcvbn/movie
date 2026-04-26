#pragma once
#include "Rating.h"
#include <vector>

class RatingManager {
    private:
        std::vector<Rating> ratings;
    public:
        void addRating(const Rating& rating);
        void printRatings(int movieId) const;
};
