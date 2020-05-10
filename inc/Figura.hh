#ifndef FIGURA_HH
#define FIGURA_HH

#include <iostream>
#include "MacierzOb.hh"
#include "Wektor.hh"
#include "InterfejsRysowania.hh"


/*!
* \brief Klasa przechowuje dane o środku figury oraz jej macierzy obrotu
*/ 
class Figura
{   
    public:
    /*!
    * \brief Pole przechowuje dane o macierzy obrotu figury
    */ 
    MacierzOb orientacja;

    /*!
    * \brief Pole przechowuje współrzędne środka figury
    */ 
    Wektor<double,3> srodek;

    public:
    /*!
    * \brief Funkcja zmieniająca macierz obrotu
    * \param M - Macierz o którą obracamy,
    */
    void zmien_orient(MacierzOb & M)
    {   
        orientacja *= M;
    }

    /*!
    * \brief Funkcja przesuwająca środek figury
    * \param Przez - wektor o który przesuwamy
    */
    void przesuniecie(Wektor<double,3> & Przez)
    {
        srodek += orientacja * Przez;
    }
};


#endif