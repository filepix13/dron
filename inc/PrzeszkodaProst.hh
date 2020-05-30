#ifndef PRZESZKODAPROST_HH
#define PRZESZKODAPROST_HH

#include "Prostopadloscian.hh"
#include "InterfejsPrzeszkody.hh"

class PrzeszkodaProst : public Prostopadloscian, public InterfejsPrzeszkody
{
    public:
    /*!
    * \brief Konstruktor paramteryczny PrzeszkodyProst
    * \param api - wskaźnik na gunplot
    * \param W - współrzędne miejsca w którym ma się pojawić przeszkoda
    */
    PrzeszkodaProst(std::shared_ptr<drawNS::Draw3DAPI> &api, Wektor<double, 3> W)
    {
        srodek = W;
        Prostopadloscian p(W);

        index[6] = rysuj(api);
    }


    /*!
    * \brief Funkcja sprawdza kolizję drona z przeszkodą prostokątną
    * \param dron - wskaźnik na dron którym prowadzimy
    */
    bool czy_kolizja(std::shared_ptr<InterfejsDrona> dron) override
    {
        Wektor<double, 3> Wek = dron->zwrocSrodek();

        if(Wek[0] <= srodek[0] + (dron->zwrocR()+1) && Wek[0] >= srodek[0] - (dron->zwrocR()+1))
        {
            if(Wek[1] <= srodek[1] + (dron->zwrocR()+1) && Wek[1] >= srodek[1] - (dron->zwrocR()+1))
            {
                if(Wek[2] <= srodek[2] + (dron->zwrocR()+1) && Wek[2] >= srodek[2] - (dron->zwrocR()+1))
                {
                    std::cout << std::endl << "Nastąpiła kolizja drona z przeszkodą" << std::endl << std::endl;
                    return true;
                }
                else 
                    return false;
            }
            else 
                return false;
        }
        else 
            return false;
    }
};

#endif