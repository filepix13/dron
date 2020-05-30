#ifndef DNO_HH
#define DNO_HH

#include "Plaszczyzna.hh"

class Dno : public Plaszczyzna
{
    public:
    /*!
    * \brief Konstruktor parametryczny Dna
    * \param W - jest to wektor wymiarów
    * \param k - jest to string koloru
    */
    Dno(std::shared_ptr<drawNS::Draw3DAPI> &api, Wektor<double, 3> W, std::string k)
    {
        wymiary = W;
        kolor = k;

        index[5] = rysuj(api);
    }


    /*!
    * \brief Konstruktor parametryczny Dna
    * \param x - wymiar x dna
    * \param y - wymiar y dna
    * \param z - wymiar z dna
    * \param k - string koloru 
    */
    Dno(std::shared_ptr<drawNS::Draw3DAPI> &api, double x, double y, double z, std::string k)
    {
        wymiary[0] = x;
        wymiary[1] = y;
        wymiary[2] = z;
        kolor = k;

        index[5] = rysuj(api);
    }


    /*!
    * \brief Funkcja sprawdza kolizję drona z dnem
    * \param dron - wskaźnik na dron którym prowadzimy
    */
    bool czy_kolizja(std::shared_ptr<InterfejsDrona> dron) override
    {
        Wektor<double, 3> Wek = dron->zwrocSrodek();

        if(Wek[2] <= (wymiary[2] + dron->zwrocR()))
        {
            std::cout << std::endl << "Nastąpiła kolizja drona z dnem" << std::endl << std::endl;
            return true;
        }
        else 
            return false;
    }
};

#endif