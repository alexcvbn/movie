#include <iostream>
#include <string>
#include <vector>
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "Recommender.h"

void printMenu() {
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
    std::cout << "[ 추천 ]\n";
    std::cout << "9. 영화 추천\n";
    std::cout << "0. 종료\n";
    std::cout << "선택 > ";
}

// 동일 제목 영화가 여러 개일 때 사용자가 하나를 고르도록 함
Movie* selectMovieByTitle(MovieManager& mm, const std::string& title) {
    std::vector<Movie*> found = mm.findAllByTitle(title);
    if (found.empty()) {
        std::cout << "없는 영화입니다.\n";
        return nullptr;
    }
    if (found.size() == 1) return found[0];

    std::cout << "동일한 제목의 영화가 여러 개 있습니다.\n";
    for (const auto& m : found) std::cout << *m << "\n";
    int movieId;
    std::cout << "ID 선택: "; std::cin >> movieId;
    Movie* selected = mm.findMovieId(movieId);
    if (!selected) std::cout << "없는 ID입니다.\n";
    return selected;
}

void handleAddMovie(MovieManager& mm) {
    std::string title, genre;
    int year;
    std::cout << "제목: "; std::cin >> title;
    std::cout << "장르: "; std::cin >> genre;
    std::cout << "연도: "; std::cin >> year;
    try {
        mm.addMovie(Movie(0, title, genre, year));
    } catch (const std::exception& e) {
        std::cerr << "오류: " << e.what() << "\n";
    }
}

void handleSearchMovie(MovieManager& mm) {
    std::string title;
    std::cout << "검색할 제목: "; std::cin >> title;
    Movie* m = mm.findTitle(title);
    if (m) std::cout << *m << "\n";
    else    std::cout << "없는 영화입니다.\n";
}

void handleAddUser(UserManager& um) {
    std::string id, name, email;
    std::cout << "ID: ";    std::cin >> id;
    std::cout << "이름: "; std::cin >> name;
    std::cout << "이메일: "; std::cin >> email;
    try {
        um.addUser(User(id, name, email));
    } catch (const std::exception& e) {
        std::cerr << "오류: " << e.what() << "\n";
    }
}

void handleAddRating(MovieManager& mm, UserManager& um, RatingManager& rm) {
    std::string userId;
    std::cout << "유저 ID: "; std::cin >> userId;
    User* u = um.findId(userId);
    if (!u) { std::cout << "없는 사용자입니다.\n"; return; }

    std::string movieTitle;
    std::cout << "영화 제목: "; std::cin >> movieTitle;
    Movie* selected = selectMovieByTitle(mm, movieTitle);
    if (!selected) return;

    double score;
    std::cout << "평점 (0~5): "; std::cin >> score;
    try {
        Rating r(userId, selected->getId(), score);
        rm.addRating(r);
        selected->addRating(score);
        std::cout << "평점 등록 완료!\n";
    } catch (const std::exception& e) {
        std::cerr << "오류: " << e.what() << "\n";
    }
}

void handlePrintRatings(MovieManager& mm, RatingManager& rm) {
    std::string movieTitle;
    std::cout << "영화 제목: "; std::cin >> movieTitle;
    Movie* selected = selectMovieByTitle(mm, movieTitle);
    if (!selected) return;
    rm.printRatings(selected->getId());
}

void handleRecommend(MovieManager& mm, UserManager& um, RatingManager& rm) {
    std::string userId;
    std::cout << "유저 ID: "; std::cin >> userId;
    Recommender recommender(mm, um, rm);
    std::vector<Movie> result = recommender.recommend(userId);
    if (!result.empty()) {
        std::cout << "추천 영화 목록:\n";
        for (const auto& m : result) std::cout << m << "\n";
    }
}

int main() {
    MovieManager movieManager;
    UserManager  userManager;
    RatingManager ratingManager;

    movieManager.loadFromFile("data/movies.csv");
    userManager.loadFromFile("data/users.csv");
    ratingManager.loadFromFile("data/ratings.csv");

    int choice;
    while (true) {
        printMenu();
        std::cin >> choice;
        if (choice == 0) break;

        switch (choice) {
            case 1: handleAddMovie(movieManager);                                         break;
            case 2: handleSearchMovie(movieManager);                                      break;
            case 3: movieManager.printAll();                                              break;
            case 4: movieManager.printSorted();                                           break;
            case 5: handleAddUser(userManager);                                           break;
            case 6: userManager.printAll();                                               break;
            case 7: handleAddRating(movieManager, userManager, ratingManager);            break;
            case 8: handlePrintRatings(movieManager, ratingManager);                      break;
            case 9: handleRecommend(movieManager, userManager, ratingManager);            break;
            default: std::cout << "잘못된 입력입니다.\n";
        }
    }

    movieManager.saveToFile("data/movies.csv");
    userManager.saveToFile("data/users.csv");
    ratingManager.saveToFile("data/ratings.csv");

    std::cout << "종료합니다.\n";
    return 0;
}
