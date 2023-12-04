#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "Movie.h"

namespace sdds {
    Movie::Movie() { releaseYear = 0; }

    const std::string& Movie::title() const {
        return movieTitle;
    }
    
    Movie::Movie(const std::string& strMovie) {
        std::stringstream ss(strMovie);
        std::string item;
        getline(ss, item, ',');
        movieTitle = trim(item);
        getline(ss, item, ',');
        releaseYear = stoi(trim(item));
        getline(ss, item, '\0');
        description = trim(item);
    }
    
    std::string Movie::trim(const std::string& str) {   
        const auto strBegin = str.find_first_not_of(" ");
        const auto strEnd = str.find_last_not_of(" ");
        const auto strRange = strEnd - strBegin + 1;

        return str.substr(strBegin, strRange);
    }

    Movie::Movie(const Movie& copyMovie) {
        movieTitle = copyMovie.movieTitle;
        releaseYear = copyMovie.releaseYear;
        description = copyMovie.description;
    }

    std::ostream &operator<<(std::ostream &os, const Movie &movie) {
        os << std::setw(40) << movie.movieTitle << " | " 
            << std::setw(4) << movie.releaseYear << " | "
            << movie.description << std::endl;

        return os;
    }
}