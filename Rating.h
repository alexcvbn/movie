#pragma once
#include <string>
class Rating {


private:

    std::string userId; // 평가한 사용자
    int movieId; // 평가 대상 영화
    double score; // 0.0 ~ 5.0



    public:
        Rating(std::string userId, int movieId, double score);
        double getScore() const;
        int getMovieid() const;
        std::string getUserid() const;
        
        void display() const;


// TODO: 생성자 (score 유효성 검사 포함)
// getter, display()
// ⚠ score 가 0~5 범위인지 확인!
};
