#ifndef SDDS_MOVIE_H
#define SDDS_MOVIE_H
#include <string>

namespace sdds {
    class Movie {
        std::string movieTitle;
        int releaseYear;
        std::string description;

    public:
        Movie();
        const std::string& title() const;
        Movie(const std::string& strMovie);
        template<typename T>
        void fixSpelling(T& spellChecker) {
            spellChecker(description);
            spellChecker(description);
            spellChecker(movieTitle);
        };
        std::string trim(const std::string& str);
        Movie(const Movie& copyMovie);
        friend std::ostream &operator<<(std::ostream &os, const Movie &movie);
    };
}

#endif