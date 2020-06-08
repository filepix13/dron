#ifndef FIGURA_HH
#define FIGURA_HH

#include <iostream>
#include "MacierzOb.hh"
#include "Wektor.hh"
#include "InterfejsRysowania.hh"


/*!
* \brief Klasa przechowuje dane o środku figury oraz jej macierzy obrotu
*/ 
class Figura : public InterfejsRysowania
{   
    protected:
    /*!
    * \brief Pole przechowuje dane o macierzy obrotu figury
    */ 
    MacierzOb orientacja;

    /*!
    * \brief Pole przechowuje współrzędne środka figury
    */ 
    Wektor<double,3> srodek;

    /*!
    * \brief Pole zlicza ilość obiektów klasy figura które istnieją
    */
    static int ile_istnieje;

    /*!
    * \brief Pole zlicza ilość obiektów klasy figura które utworzono
    */
    static int ile_utworzono;

    public:
    /*!
    * \brief Konstruktor bezparametryczny
    */
    Figura()
    {
        ile_istnieje++;
        ile_utworzono++;
    }
    

    /*!
    * \brief Konstruktor kopiujący
    * \param nowy - Figura którą kopiujemy
    */
    Figura(const Figura & nowy) : orientacja(nowy.orientacja), srodek(nowy.srodek) 
    {
        ile_istnieje++;
        ile_utworzono++;
    }


    /*!
    * \brief Dekonstuktor
    */
    ~Figura()
    {
        ile_istnieje--;
    }

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

    /*!
    * \brief Funckja zwraca ilość istniejących obiektów klasy figura
    */
    static int zwroc_istniejace()
    {
        return ile_istnieje;
    }


    /*!
    * \brief Funckja zwraca ilość utworzonych obiektów klasy figura
    */
    static int zwroc_utworzone()
    {
        return ile_utworzono;
    }
};

int Figura::ile_istnieje = 0;
int Figura::ile_utworzono = 0;



#endif