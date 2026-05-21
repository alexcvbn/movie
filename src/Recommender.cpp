#include "Recommender.h"
#include <iostream>

Recommender::Recommender(MovieManager& mm, UserManager& um, RatingManager& rm)
    : movieManager(mm), userManager(um), ratingManager(rm) {}

std::vector<Movie> Recommender::recommend(const std::string& userId) {
    
    std::vector<Rating> myRatings = ratingManager.findByUser(userId);

    // 엣지 케이스 1
    if (myRatings.empty()) {
        std::cout << "평점을 먼저 입력해주세요.\n";
        return {};
    }

    // 2. 가장 비슷한 유저 찾기
    std::string bestUserId = "";
    int bestSim = -101;

    for (const auto& u : userManager.getAllUsers()) {
        if (u.getId() == userId) continue;  // 자기 자신 제외

        std::vector<Rating> otherRatings = ratingManager.findByUser(u.getId());
        int sim = SimilarityCalculator::calculate(myRatings, otherRatings);

        if (sim > bestSim) {
            bestSim = sim;
            bestUserId = u.getId();
        }
    }

    // 엣지 케이스 2
    if (bestUserId.empty() || bestSim == -100) {
        std::cout << "추천할 수 있는 유저가 없습니다.\n";
        return {};
    }

  
    std::vector<Rating> bestUserRatings = ratingManager.findByUser(bestUserId);
    std::vector<Movie> result;

    for (const auto& r : bestUserRatings) {
        // 이미 본건지 확인
        bool alreadySeen = false;
        for (const auto& my : myRatings) {
            if (my.getMovieid() == r.getMovieid()) {
                alreadySeen = true;
                break;
            }
        }
        if (!alreadySeen) {
            Movie* m = movieManager.findMovieId(r.getMovieid());
            if (m) result.push_back(*m);
        }
    }

    return result;
}