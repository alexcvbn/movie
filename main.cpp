#include <iostream>
#include <vector>
#include "Movie.h"
#include "User.h"
#include "Rating.h"

int main() {
    
    std::vector<Movie> movies;
    movies.push_back(Movie(1, "기생충", "드라마", 2019));
    movies.push_back(Movie(2, "인터스텔라", "SF", 2014));

    
    User user1("alex3372534", "황재민", "alex3372534@naver.com");
    User user2("아이브팬", "장원영", "IVE@gmail.com");
   
    try {
        
        Rating r1(user1.getId(), movies[0].getId(), 4.8); 
        Rating r2(user2.getId(), movies[1].getId(), 3.2);
        Rating r3(user1.getId(), movies[1].getId(), 1.0);
        
        movies[0].addRating(r1.getScore());
        movies[1].addRating(r2.getScore());
        movies[1].addRating(r3.getScore());

        std::cout << user1.getName() << "님이 " << movies[0].getTitle() 
                  << "에 평점을 남겼습니다.\n" << std::endl;
        std::cout << user2.getName() << "님이 " << movies[1].getTitle() 
                  << "에 평점을 남겼습니다.\n" << std::endl;
        std::cout << user1.getName() << "님이 " << movies[1].getTitle() 
                  << "에 평점을 남겼습니다.\n" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "평점 등록 오류: " << e.what() << std::endl;
    }

    
    for (const auto& m : movies) {
        m.display();
    }

    return 0;
}