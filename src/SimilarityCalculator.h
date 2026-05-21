#pragma once
#include <vector>
#include "Rating.h"

class SimilarityCalculator {
public:
    static int calculate(
        const std::vector<Rating>& user1,
        const std::vector<Rating>& user2
    );
};