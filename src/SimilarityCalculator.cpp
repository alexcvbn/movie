#include "SimilarityCalculator.h"
#include <cmath>

int SimilarityCalculator::calculate(
    const std::vector<Rating>& user1,
    const std::vector<Rating>& user2)
{
    int    commonCount   = 0;
    double scoreDiffSum  = 0.0;

    for (const Rating& r1 : user1) {
        for (const Rating& r2 : user2) {
            if (r1.getMovieid() == r2.getMovieid()) {
                commonCount++;
                scoreDiffSum += std::abs(r1.getScore() - r2.getScore());
            }
        }
    }

    if (commonCount == 0) return NO_COMMON_SCORE;

    return static_cast<int>(commonCount * COMMON_BONUS - scoreDiffSum * SCORE_DIFF_WEIGHT);
}