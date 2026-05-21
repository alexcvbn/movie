#include "Rating.h"
#include <stdexcept> 
#include <iostream>
#include <string>


Rating::Rating(std::string userId, int movieId, double score)
    : userId(userId), movieId(movieId), score(score) 
{
    
    if (score < 0.0 || score > 5.0) {
        throw std::invalid_argument("별점은 0.0에서 5.0 사이여야 합니다.");
    }
}

double Rating::getScore() const {return score;}
int Rating::getMovieid() const {return movieId;}
std::string Rating::getUserid() const {return userId;}

void Rating::display() const {
    std::cout << "평점: " << getScore() << "\n";
    std::cout << "영화: " << getMovieid() << "\n";
    std::cout << "유저: " <<getUserid() << "\n";
}