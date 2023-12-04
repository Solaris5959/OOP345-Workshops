#include <iostream>
#include <iomanip>
#include <fstream>
#include "RideRequest.h"

namespace sdds {
	RideRequest::RideRequest() {
		price = -1;
		discount = 0;
	}

	void RideRequest::read (std::istream& istr) {
                if (istr) {
                    char readBuff[64];

                    istr.getline(customer_name, 11, ',');
                    istr.getline(details, 26, ',');
                    istr.getline(readBuff, 64, ',');
                    price = std::stoi(readBuff);
                    istr.getline(readBuff, 64);
                    discount = readBuff[0] == 'Y';
                }
            }

	void RideRequest::display() {
                static int num_called = 0;
                num_called++;

                if (price != -1) {
                    std::cout << std::left << std::setw(2) << num_called << ". "
                        << std::left << std::setw(10) << customer_name << "|"
                        << std::left << std::setw(25) << details << "|"
                        << std::left << std::setw(12) << std::setprecision(2) 
                        << price * g_taxrate;
                        
                    if (discount)
                        std::cout << "|" << std::right << std::setw(13) 
                        << (price * g_taxrate) * g_discount; 
                        

                    std::cout << "\n";
                }
                else {
                    std::cout << "COUNTER. No Ride Request\n";
                }
            }

}