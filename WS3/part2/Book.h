// Workshop 3 - Templates
// Created by: Jeevan Pant
// Date created: 2023/07/22

#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include<string>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>

namespace sdds {

	class Book {
		std::string m_title{}; // book title
		unsigned short m_numChapters{}; // number of chapters
		unsigned short m_numPages{}; // number of pages 
	public:
		Book();
		Book(const std::string& title, unsigned short numChapters, unsigned short numPages);
		~Book();

		operator bool() const; // part 1 addition
		bool operator>(const Book&) const; // part 2 addition
		bool operator<(const Book&) const; // part 2 addition
		double pagesChaptersRatio() const; // part 2 addition
		std::ostream& print(std::ostream& os) const;
	};
	std::ostream& operator<<(std::ostream&, const Book&);

}


#endif 
