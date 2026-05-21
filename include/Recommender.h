#pragma once
#include <vector>
#include <string>
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "SimilarityCalculator.h"

class Recommender {
private:
    MovieManager& movieManager;
    UserManager& userManager;
    RatingManager& ratingManager;

public:
    Recommender(MovieManager& mm, UserManager& um, RatingManager& rm);
    std::vector<Movie> recommend(const std::string& userId);
};