#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H
#include <string>

namespace sdds {
    class Book {
        std::string author;
        std::string titleBook;
        std::string countryPublished;
        int yearPublished;
        double salePrice;
        std::string description;

    public:
        Book();
        Book(const std::string& strBook);
        const std::string title() const;
        const std::string country() const;
        const std::size_t year() const;
        double& price();
        std::string trim(const std::string& str);
        friend std::ostream &operator<<(std::ostream &os, const Book &book);
    };
}

#endif