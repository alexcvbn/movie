#pragma once
#include <string>

class Rating {
public:
    static constexpr double MIN_SCORE = 0.0;
    static constexpr double MAX_SCORE = 5.0;

private:
    std::string userId;
    int         movieId;
    double      score;

public:
    Rating(std::string userId, int movieId, double score);
    double      getScore()   const;
    int         getMovieid() const;
    std::string getUserid()  const;
    void        display()    const;
};
