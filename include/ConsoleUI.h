#pragma once
#include <vector>
#include <string>
#include <map>
#include "Movie.h"

namespace ConsoleUI {
    // 터미널 화면을 정리하고 타이틀을 렌더링합니다.
    void clearScreen();
    void printHeader(const std::string& title);

    // 영화 목록을 구조화된 표(Table) 형식으로 깔끔하게 출력합니다.
    void printMovieTable(const std::vector<Movie>& movies);

    // 장르별 평균 평점을 가로 막대 그래프 형식으로 출력합니다.
    void printAverageRatingBarChart(const std::map<std::string, double>& genreStats);

    // 진행 상황을 시각적으로 표시하는 로딩바 및 스피너 애니메이션
    void showProgressBar(const std::string& message, int durationMs);
    void showSpinner(const std::string& message, int durationMs);
    
    // 단순 줄바꿈 및 구분선 출력
    void printDivider(char symbol = '=', int width = 60);
}
