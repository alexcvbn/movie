#include <iostream>
#include <string>
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"

int main() {
    MovieManager movieManager;
    UserManager userManager;
    RatingManager ratingManager;

    int choice;

    while (true) {
        std::cout << "\n=== Movie Recommender ===\n";
        std::cout << "[ 영화 ]\n";
        std::cout << "1. 영화 추가\n";
        std::cout << "2. 제목으로 검색\n";
        std::cout << "3. 전체 목록 출력\n";
        std::cout << "4. 평점순 정렬 출력\n";
        std::cout << "[ 사용자 ]\n";
        std::cout << "5. 사용자 추가\n";
        std::cout << "6. 사용자 목록 출력\n";
        std::cout << "[ 평점 ]\n";
        std::cout << "7. 평점 입력\n";
        std::cout << "8. 영화별 평점 보기\n";
        std::cout << "0. 종료\n";
        std::cout << "선택 > ";
        std::cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            std::string title, genre;
            int year;
            std::cout << "제목: "; std::cin >> title;
            std::cout << "장르: "; std::cin >> genre;
            std::cout << "연도: "; std::cin >> year;
            movieManager.addMovie(Movie(0, title, genre, year));

        } else if (choice == 2) {
            std::string title;
            std::cout << "검색할 제목: "; std::cin >> title;
            Movie* m = movieManager.findTitle(title);
            if (m) std::cout << *m << "\n";
            else std::cout << "없는 영화입니다.\n";

        } else if (choice == 3) {
            movieManager.printAll();

        } else if (choice == 4) {
            movieManager.printSorted();

        } else if (choice == 5) {
            std::string id, name, email;
            std::cout << "ID: "; std::cin >> id;
            std::cout << "이름: "; std::cin >> name;
            std::cout << "이메일: "; std::cin >> email;
            userManager.addUser(User(id, name, email));

        } else if (choice == 6) {
            userManager.printAll();

        } else if (choice == 7) {
            std::string userId, movieTitle;
            double score;
            std::cout << "유저 ID: "; std::cin >> userId;
            std::cout << "영화 제목: "; std::cin >> movieTitle;
            std::cout << "평점 (0~5): "; std::cin >> score;
            try {
                Movie* m = movieManager.findTitle(movieTitle);
                if (!m) {
                    std::cout << "없는 영화입니다.\n";
                } else {
                    User* u = userManager.findId(userId);
                    if (!u) {
                        std::cout << "없는 사용자입니다.\n";
                    } else {
                        Rating r(userId, m->getId(), score);
                        ratingManager.addRating(r);
                        m->addRating(score);
                        std::cout << "평점 등록 완료!\n";
                    }
                }
            } catch (const std::exception& e) {
                std::cerr << "오류: " << e.what() << "\n";
            }

        } else if (choice == 8) {
            std::string movieTitle;
            std::cout << "영화 제목: "; std::cin >> movieTitle;
            Movie* m = movieManager.findTitle(movieTitle);
            if (!m) {
                std::cout << "없는 영화입니다.\n";
            } else {
                ratingManager.printRatings(m->getId());
            }

        } else {
            std::cout << "잘못된 입력입니다.\n";
        }
    }

    std::cout << "종료합니다.\n";
    return 0;
}