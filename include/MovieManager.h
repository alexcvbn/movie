#pragma once
#include <vector>
#include <string>
#include <map>
#include "Movie.h"
#include "BaseManager.h"

class MovieManager : public BaseManager {
    private:
        std::vector<Movie> movies;
        int nextId = 1;
    
    public:
        void addMovie(const Movie& movie);
        void printAll() const;
        void printSorted();
        Movie* findTitle(const std::string& title);
        Movie* findMovieId(int id);
        std::vector<Movie*> findAllByTitle(const std::string& title);

        const std::vector<Movie>& getAllMovies() const;
        std::vector<Movie> filterByGenre(const std::string& genre) const;
        double getAverageRating() const;
        std::map<std::string, double> getAverageRatingByGenre() const;
        std::vector<Movie> getTopN(int n) const;
        bool exportStatisticsReport(const std::string& filename) const;

        void loadFromFile(const std::string& filename) override;
        void saveToFile(const std::string& filename) const override;
        int size() const override;
        
};

