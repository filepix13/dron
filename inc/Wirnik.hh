#ifndef WIRNIK_HH
#define WIRNIK_HH

#include "Graniastoslup.hh"
#include <math.h> 

class Wirnik : public Graniastoslup
{
    public:
    /*!
    * \brief Konstruktor bezparametryczny Wirnika
    */
    Wirnik() = default;


    /*!
    *\brief Konstruktor parametryczny Wirnika
    *\param x - Współrzędna x srodka Wirnika
    *\param y - Współrzędna y srodka Wirnika 
    *\param z - Współrzędna z srodka Wirnika   
    */
    Wirnik(double x, double y, double z)
    {
        srodek.ustaw(x,y,z);
        Graniastoslup g(x,y,z);
    }
    

    /*!
    * \brief Funkcja obraca drona wokół osi W o 10 stopni
    */
    void obrotW()
    {   
        MacierzOb M('y', 10);

        zmien_orient(M);
    }
};


#endif