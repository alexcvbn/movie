#pragma once
#include <vector>
#include <string>
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "SimilarityCalculator.h"

class Recommender {
public:
    static constexpr double MIN_RECOMMEND_SCORE = 3.0;

private:
    MovieManager& movieManager;
    UserManager& userManager;
    RatingManager& ratingManager;

public:
    Recommender(MovieManager& mm, UserManager& um, RatingManager& rm);
    std::vector<Movie> recommend(const std::string& userId, const std::string& genreFilter = "");
};