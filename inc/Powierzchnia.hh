#ifndef POWIERZCHNIA_HH
#define POWIERZCHNIA_HH

#include "Plaszczyzna.hh"

class Powierzchnia : public Plaszczyzna
{
    public:
    /*!
    * \brief Konstruktor parametryczny powierzchni
    * \param W - jest to wektor wymiarów
    * \param k - jest to string koloru
    */
    Powierzchnia(std::shared_ptr<drawNS::Draw3DAPI> &api, Wektor<double, 3> W, std::string k)
    {
        wymiary = W;
        kolor = k;

        index[4] = rysuj(api);
    }


    /*!
    * \brief Konstruktor parametryczny powierzchni
    * \param x - wymiar x powierzchni
    * \param y - wymiar y powierzchni
    * \param z - wymiar z powierzchni
    * \param k - string koloru 
    */
    Powierzchnia(std::shared_ptr<drawNS::Draw3DAPI> &api, double x, double y, double z, std::string k)
    {
        wymiary[0] = x;
        wymiary[1] = y;
        wymiary[2] = z;
        kolor = k;

        index[4] = rysuj(api);
    }


    /*!
    * \brief Funkcja sprawdza kolizję drona z powierzchnią
    * \param dron - wskaźnik na dron którym prowadzimy
    */
    bool czy_kolizja(std::shared_ptr<InterfejsDrona> dron) override
    {
        Wektor<double, 3> Wek = dron->zwrocSrodek();

        if(Wek[2] >= wymiary[2])
        {
            std::cout << std::endl << "Dron wypłynął na powierzchnię" << std::endl << std::endl;
            return true;
        }
        else 
            return false;
    }
};

#endif
