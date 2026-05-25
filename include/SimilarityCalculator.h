#pragma once
#include <vector>
#include "Rating.h"

class SimilarityCalculator {
public:
    static constexpr int    COMMON_BONUS      = 10;
    static constexpr int    SCORE_DIFF_WEIGHT = 2;
    static constexpr int    NO_COMMON_SCORE   = -100;

    static int calculate(
        const std::vector<Rating>& user1,
        const std::vector<Rating>& user2
    );
};