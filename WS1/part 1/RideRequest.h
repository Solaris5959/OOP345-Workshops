/*
    OOP345 W1
    Connor McDonald - 136123221
    Sep 19, 2023
*/
#ifndef SDDS_RIDEREQUEST_H
#define SDDS_RIDEREQUEST_H
#endif

double g_taxrate, g_discount;

namespace sdds {

    class RideRequest {
        private:
            char customer_name [11];
            char details [26];
            double price = -1;
            bool discount;

        public:
            RideRequest();
            void read (std::istream& istr);
            void display();
    };
}