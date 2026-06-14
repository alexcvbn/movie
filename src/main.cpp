#include <iostream>
#include <string>
#include <vector>
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "Recommender.h"

#include "ConsoleUI.h"
#include <iomanip>

void printMenu() {
    std::cout << "\n==================================================\n";
    std::cout << "             Movie Recommender System\n";
    std::cout << "==================================================\n";
    std::cout << "[ 영화 관리 ]\n";
    std::cout << "  1. 영화 추가\n";
    std::cout << "  2. 제목으로 검색\n";
    std::cout << "  3. 전체 목록 출력 (표)\n";
    std::cout << "  4. 평점순 정렬 출력\n";
    std::cout << "[ 사용자 관리 ]\n";
    std::cout << "  5. 사용자 추가\n";
    std::cout << "  6. 사용자 목록 출력\n";
    std::cout << "[ 평점 관리 ]\n";
    std::cout << "  7. 평점 입력\n";
    std::cout << "  8. 영화별 평점 보기\n";
    std::cout << "[ 추천 및 통계 ]\n";
    std::cout << "  9. 맞춤 영화 추천 (장르 필터 가능)\n";
    std::cout << "  10. 시스템 통계 분석 대시보드\n";
    std::cout << "  0. 종료\n";
    std::cout << "--------------------------------------------------\n";
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
        std::cout << "영화가 성공적으로 추가되었습니다.\n";
    } catch (const std::exception& e) {
        std::cerr << "오류: " << e.what() << "\n";
    }
}

void handleSearchMovie(MovieManager& mm) {
    std::string title;
    std::cout << "검색할 제목: "; std::cin >> title;
    Movie* m = mm.findTitle(title);
    if (m) {
        std::cout << "\n검색 결과:\n";
        std::cout << *m << "\n";
    }
    else    std::cout << "없는 영화입니다.\n";
}

void handlePrintSorted(const MovieManager& mm) {
    auto sorted = mm.getAllMovies();
    std::sort(sorted.begin(), sorted.end());
    ConsoleUI::printHeader("전체 영화 평점순 정렬 목록");
    ConsoleUI::printMovieTable(sorted);
}

void handleAddUser(UserManager& um) {
    std::string id, name, email;
    std::cout << "ID: ";    std::cin >> id;
    std::cout << "이름: "; std::cin >> name;
    std::cout << "이메일: "; std::cin >> email;
    try {
        um.addUser(User(id, name, email));
        std::cout << "사용자가 성공적으로 추가되었습니다.\n";
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
    
    User* u = um.findId(userId);
    if (!u) {
        std::cout << "등록되지 않은 사용자 ID입니다.\n";
        return;
    }

    std::string genreFilter;
    std::cout << "추천받을 장르 (필터링하지 않으려면 엔터 입력): ";
    std::cin.ignore();
    std::getline(std::cin, genreFilter);

    // 로딩바 애니메이션 표시
    ConsoleUI::showProgressBar("유사 사용자 매칭 및 평점 분석 중", 700);

    Recommender recommender(mm, um, rm);
    std::vector<Movie> result = recommender.recommend(userId, genreFilter);
    if (!result.empty()) {
        ConsoleUI::printHeader(userId + " 님을 위한 맞춤 추천 영화 목록");
        ConsoleUI::printMovieTable(result);
    } else {
        std::cout << "추천할 영화가 없습니다.\n";
    }
}

void handleStatisticsMenu(const MovieManager& mm) {
    while (true) {
        ConsoleUI::printHeader("시스템 통계 분석 메뉴");
        std::cout << "1. 전체 영화 평균 평점 조회\n";
        std::cout << "2. 장르별 평균 평점 시각화\n";
        std::cout << "3. 평점 상위 N개 영화 조회\n";
        std::cout << "4. 통계 리포트 파일 저장 (data/statistics_report.txt)\n";
        std::cout << "0. 이전 메뉴로 돌아가기\n";
        std::cout << "--------------------------------------------------\n";
        std::cout << "선택 > ";
        
        int choice;
        std::cin >> choice;
        if (choice == 0) break;
        
        switch (choice) {
            case 1: {
                try {
                    double avg = mm.getAverageRating();
                    ConsoleUI::printDivider('-', 50);
                    std::cout << "시스템 전체 영화 평균 평점: " 
                              << std::fixed << std::setprecision(2) << avg << " 점\n";
                    ConsoleUI::printDivider('-', 50);
                } catch (const std::exception& e) {
                    std::cerr << "오류: " << e.what() << "\n";
                }
                break;
            }
            case 2: {
                ConsoleUI::showSpinner("장르 데이터 집계 중", 500);
                auto stats = mm.getAverageRatingByGenre();
                ConsoleUI::printAverageRatingBarChart(stats);
                break;
            }
            case 3: {
                int n;
                std::cout << "조회할 영화 개수(N): ";
                std::cin >> n;
                if (n <= 0) {
                    std::cout << "올바른 숫자를 입력하세요.\n";
                    break;
                }
                ConsoleUI::showSpinner("랭킹 분석 중", 500);
                auto topN = mm.getTopN(n);
                ConsoleUI::printHeader("평점 상위 " + std::to_string(topN.size()) + "개 영화 랭킹");
                ConsoleUI::printMovieTable(topN);
                break;
            }
            case 4: {
                ConsoleUI::showSpinner("리포트 파일 생성 중", 600);
                bool success = mm.exportStatisticsReport("data/statistics_report.txt");
                if (success) {
                    std::cout << "통계 리포트가 성공적으로 저장되었습니다. (data/statistics_report.txt)\n";
                } else {
                    std::cout << "파일 저장에 실패했습니다.\n";
                }
                break;
            }
            default:
                std::cout << "잘못된 입력입니다.\n";
                break;
        }
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
            case 3: {
                ConsoleUI::printHeader("전체 등록 영화 목록");
                ConsoleUI::printMovieTable(movieManager.getAllMovies());
                break;
            }
            case 4: handlePrintSorted(movieManager);                                      break;
            case 5: handleAddUser(userManager);                                           break;
            case 6: userManager.printAll();                                               break;
            case 7: handleAddRating(movieManager, userManager, ratingManager);            break;
            case 8: handlePrintRatings(movieManager, ratingManager);                      break;
            case 9: handleRecommend(movieManager, userManager, ratingManager);            break;
            case 10: handleStatisticsMenu(movieManager);                                  break;
            default: std::cout << "잘못된 입력입니다.\n";
        }
    }

    movieManager.saveToFile("data/movies.csv");
    userManager.saveToFile("data/users.csv");
    ratingManager.saveToFile("data/ratings.csv");

    std::cout << "종료합니다.\n";
    return 0;
}
