#ifndef WIRNIK_HH
#define WIRNIK_HH

#include "Graniastoslup.hh"

class Wirnik : public Graniastoslup
{
    public:
    /*!
    * \brief Konstruktor bezparametryczny Wirnika
    */
    Wirnik(){};
    
    /*!
    * \brief Funkcja obraca drona wokół osi W o 10 stopni
    */
    void obrotW()
    {   
        MacierzOb M('y', 10);

        zmien_orient(M);
    }


    /*!
    * \brief Funkcja zmienia srodek wirnika na podane dane
    * \param x Współrzędna x wektora
    * \param y Współrzędna y wektora
    * \param z Współrzędna z wektora
    */
    void zmianSrodek(double x, double y, double z)
    {
        srodek[0] = x;
        srodek[1] = y;
        srodek[2] = z; 
    }
};


#endif