#ifndef INTERFEJSPRZESZKODY_HH
#define INTERFEJSPRZESZKODY_HH

#include <vector>
#include <memory>
#include "InterfejsDrona.hh"

class InterfejsPrzeszkody
{
    public:
    /*!
    * \brief Funkcja sprawdza kolizję przeszkody z dronem
    */
    virtual bool czy_kolizja(std::shared_ptr<InterfejsDrona> dron) = 0;
};

#endif