#include "Movie.h"
#include "Rating.h"
#include <iostream>
#include <stdexcept>

static constexpr int MIN_YEAR = 1888;
static constexpr int MAX_YEAR = 2100;

Movie::Movie()
    : id(0), releaseYear(0),
      totalRating(0.0), ratingCount(0) {}

Movie::Movie(int id, const std::string& title,
             const std::string& genre, int year)
    : id(id), title(title), genre(genre),
      releaseYear(year),
      totalRating(0.0), ratingCount(0)
{
    if (title.empty())
        throw std::invalid_argument("제목이 비어 있습니다.");
    if (year < MIN_YEAR || year > MAX_YEAR)
        throw std::out_of_range("연도는 " + std::to_string(MIN_YEAR) +
                                "~" + std::to_string(MAX_YEAR) + " 사이여야 합니다.");
}

int         Movie::getId()           const { return id; }
std::string Movie::getTitle()        const { return title; }
std::string Movie::getGenre()        const { return genre; }
int         Movie::getReleaseYear()  const { return releaseYear; }
int         Movie::getRatingCount()  const { return ratingCount; }

double Movie::getAverageRating() const {
    if (ratingCount == 0) return 0.0;
    return totalRating / ratingCount;
}

void Movie::addRating(double r) {
    if (r < Rating::MIN_SCORE || r > Rating::MAX_SCORE) return;
    totalRating += r;
    ratingCount++;
}


bool Movie::operator==(const Movie& other) const {
    return title == other.title && releaseYear == other.releaseYear;
}

bool Movie::operator<(const Movie& other) const {
    return getAverageRating() > other.getAverageRating();
}

std::ostream& operator<<(std::ostream& os, const Movie& m) {
    os << m.id << ". " << m.title
       << " (" << m.releaseYear << ")"
       << "  장르: " << m.genre
       << "  평점: " << m.getAverageRating()
       << " (" << m.ratingCount << "건)";
    return os;
}