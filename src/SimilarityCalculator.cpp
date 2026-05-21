#include "SimilarityCalculator.h"
#include "Rating.h"
#include <vector>
#include <cstdlib>

int SimilarityCalculator::calculate(
    const std::vector<Rating>& user1,
    const std::vector<Rating>& user2)
{
    int commonCount = 0;
    int scoreDiffSum = 0;

    for (const Rating& r1 : user1) {
        for (const Rating& r2 : user2) {
            if (r1.getMovieid() == r2.getMovieid()) {
                commonCount++;
                scoreDiffSum += std::abs(r1.getScore() - r2.getScore());
            }
        }
    }

    if (commonCount == 0) return -100;

    // 평점 차이에 가중치 2 적용, 평점의 유사도를 더 중요하게 생각했음
   
    return commonCount * 10 - (scoreDiffSum * 2);
}