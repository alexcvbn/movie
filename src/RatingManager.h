#pragma once
#include "Rating.h"
#include <vector>
#include "BaseManager.h"

class RatingManager: public BaseManager {
    private:
        std::vector<Rating> ratings;
    public:
        void addRating(const Rating& rating);
        void printRatings(int movieId) const;
        void loadFromFile(const std::string& filename) override;
        void saveToFile(const std::string& filename) const override;
        int size() const override;
        std::vector<Rating> findByUser(const std::string& userId) const;
};
