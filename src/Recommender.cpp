#include "Recommender.h"
#include <iostream>

Recommender::Recommender(MovieManager& mm, UserManager& um, RatingManager& rm)
    : movieManager(mm), userManager(um), ratingManager(rm) {}

std::vector<Movie> Recommender::recommend(const std::string& userId) {
    
    std::vector<Rating> myRatings = ratingManager.findByUser(userId);

    if (myRatings.empty()) {
        std::cout << "평점을 먼저 입력해주세요.\n";
        return {};
    }

    std::string bestUserId;
    int bestSim = SimilarityCalculator::NO_COMMON_SCORE - 1;

    for (const auto& u : userManager.getAllUsers()) {
        if (u.getId() == userId) continue;

        std::vector<Rating> otherRatings = ratingManager.findByUser(u.getId());
        int sim = SimilarityCalculator::calculate(myRatings, otherRatings);

        if (sim > bestSim) {
            bestSim = sim;
            bestUserId = u.getId();
        }
    }

    if (bestUserId.empty() || bestSim == SimilarityCalculator::NO_COMMON_SCORE) {
        std::cout << "추천할 수 있는 유저가 없습니다.\n";
        return {};
    }

    std::vector<Rating> bestUserRatings = ratingManager.findByUser(bestUserId);
    std::vector<Movie> result;

    for (const auto& r : bestUserRatings) {
        bool alreadySeen = false;
        for (const auto& my : myRatings) {
            if (my.getMovieid() == r.getMovieid()) {
                alreadySeen = true;
                break;
            }
        }
        if (!alreadySeen && r.getScore() >= MIN_RECOMMEND_SCORE) {
            Movie* m = movieManager.findMovieId(r.getMovieid());
            if (m) result.push_back(*m);
        }
    }

    return result;
}