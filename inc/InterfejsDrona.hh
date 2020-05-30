#ifndef INTERFEJSDRONA_HH
#define INTERFEJSDRONA_HH

#include <vector>
#include <memory>
#include "Wirnik.hh" 

class InterfejsPrzeszkody;

class InterfejsDrona
{
    protected:
    /*!
    * \brief Lewy wirnik drona
    */
    Wirnik L;

    /*!
    * \brief Prawy wirnik drona
    */
    Wirnik P;

    /*!
    * \brief Promień sfery wokół drona, potrzebny do kolizji
    */
    double R=2;
    
    public:
    /*!
    * \brief Konstruktor bezparametryczny z listą inicjalizującą wirniki
    */
    InterfejsDrona() : L(-1,-1.5,0), P(1,-1.5,0){};


    /*!
    * \brief Funkcja zwraca pole środek drona
    */
    virtual Wektor<double, 3> zwrocSrodek() = 0;


    /*!
    * \brief Funkcja zwraca pole R drona
    */
    virtual double zwrocR() = 0;


    /*!
    * \brief Funkcja przesuwa drona, oraz animuje jego ruch
    * \param api - wskaźnik na gunplota,
    * \param b - wartość y wektora o jaką przesuwamy drona
    * \param kat- kąt obrotu wokół osi X
    * \param kolekcja_przeszkod - przeszkody z którymi koliduje dron
    */
    virtual void Przesun(std::shared_ptr<drawNS::Draw3DAPI> &api, double b, double kat, std::vector<std::shared_ptr<InterfejsPrzeszkody>> kolekcja_przeszkod) = 0;
    

    /*!
    * \brief Funkcja sprawdza kolizję drona z dronem
    * \param dron - wskaźnik na dron którym prowadzimy
    */
    virtual void obrot(std::shared_ptr<drawNS::Draw3DAPI> &api, double kat) = 0;
};

#endif