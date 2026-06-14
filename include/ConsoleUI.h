#pragma once
#include <vector>
#include <string>
#include <map>
#include "Movie.h"

namespace ConsoleUI {
    void clearScreen();
    void printHeader(const std::string& title);
    void printMovieTable(const std::vector<Movie>& movies);
    void printAverageRatingBarChart(const std::map<std::string, double>& genreStats);
    void showProgressBar(const std::string& message, int durationMs);
    void showSpinner(const std::string& message, int durationMs);
    void printDivider(char symbol = '=', int width = 60);
}
