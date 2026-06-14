#include "ConsoleUI.h"
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>

namespace ConsoleUI {

    void clearScreen() {
        for (int i = 0; i < 3; ++i) {
            std::cout << "\n";
        }
    }

    void printDivider(char symbol, int width) {
        std::cout << std::string(width, symbol) << "\n";
    }

    void printHeader(const std::string& title) {
        printDivider('=', 70);
        std::cout << "  " << title << "\n";
        printDivider('=', 70);
    }

    // UTF-8 문자열의 한글(2칸)과 영문/숫자(1칸)를 고려한 실제 출력 너비를 계산합니다.
    static int getVisualWidth(const std::string& str) {
        int width = 0;
        for (size_t i = 0; i < str.length();) {
            unsigned char c = str[i];
            if (c < 0x80) {
                width += 1;
                i += 1;
            } else if ((c & 0xE0) == 0xC0) {
                width += 2;
                i += 2;
            } else if ((c & 0xF0) == 0xE0) {
                // 한글 등 3바이트 UTF-8 문자는 콘솔 상에서 2칸을 차지합니다.
                width += 2;
                i += 3;
            } else if ((c & 0xF8) == 0xF0) {
                width += 2;
                i += 4;
            } else {
                width += 1;
                i += 1;
            }
        }
        return width;
    }

    // 주어진 visual 너비에 맞춰 문자열 뒤에 공백 패딩을 추가합니다.
    static std::string padString(const std::string& str, int targetWidth) {
        int curWidth = getVisualWidth(str);
        if (curWidth >= targetWidth) return str;
        return str + std::string(targetWidth - curWidth, ' ');
    }

    void printMovieTable(const std::vector<Movie>& movies) {
        if (movies.empty()) {
            std::cout << "표시할 영화 데이터가 없습니다.\n";
            return;
        }

        // 테두리 문자 정의 (단순한 ASCII 스타일)
        const std::string border = "+----+------------------------------+--------------+--------+----------+";

        std::cout << border << "\n";
        
        // 헤더 출력
        std::cout << "| " << padString("ID", 2) << " | "
                  << padString("영화 제목", 28) << " | "
                  << padString("장르", 12) << " | "
                  << padString("평점", 6) << " | "
                  << padString("평가건수", 8) << " |\n";

        std::cout << border << "\n";

        for (const auto& m : movies) {
            // 평점을 소수점 2자리 문자열로 변환
            std::stringstream ssRating;
            ssRating << std::fixed << std::setprecision(2) << m.getAverageRating();

            std::stringstream ssCount;
            ssCount << m.getRatingCount() << " 건";

            std::cout << "| " << std::setw(2) << m.getId() << " | "
                      << padString(m.getTitle(), 28) << " | "
                      << padString(m.getGenre(), 12) << " | "
                      << padString(ssRating.str(), 6) << " | "
                      << padString(ssCount.str(), 8) << " |\n";
        }

        std::cout << border << "\n";
    }

    void printAverageRatingBarChart(const std::map<std::string, double>& genreStats) {
        if (genreStats.empty()) {
            std::cout << "통계 데이터가 존재하지 않습니다.\n";
            return;
        }

        printHeader("장르별 평균 평점 통계 시각화");

        for (const auto& [genre, rating] : genreStats) {
            // 평점을 0.0 ~ 5.0 기준 25칸 스케일로 정규화
            int barLength = static_cast<int>((rating / 5.0) * 25.0);
            if (barLength > 25) barLength = 25;
            if (barLength < 0) barLength = 0;

            std::string bar = std::string(barLength, '=') + std::string(25 - barLength, ' ');

            std::stringstream ssRating;
            ssRating << std::fixed << std::setprecision(2) << rating;

            std::cout << padString(genre, 14) << ": [" << bar << "] " << ssRating.str() << " 점\n";
        }
        printDivider('=', 70);
    }

    void showProgressBar(const std::string& message, int durationMs) {
        int steps = 20;
        int stepDuration = durationMs / steps;
        for (int i = 0; i <= steps; ++i) {
            std::cout << "\r" << message << " [";
            for (int j = 0; j < i; ++j) std::cout << "=";
            for (int j = i; j < steps; ++j) std::cout << " ";
            std::cout << "] " << (i * 100 / steps) << "%";
            std::cout.flush();
            std::this_thread::sleep_for(std::chrono::milliseconds(stepDuration));
        }
        std::cout << "\n";
    }

    void showSpinner(const std::string& message, int durationMs) {
        char spinner[] = {'|', '/', '-', '\\'};
        int steps = durationMs / 100;
        for (int i = 0; i < steps; ++i) {
            std::cout << "\r" << message << " " << spinner[i % 4];
            std::cout.flush();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::cout << "\r" << message << " 완료!\n";
    }
}
