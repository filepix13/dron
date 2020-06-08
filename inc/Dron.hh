#ifndef DRON_HH
#define DRON_HH

#include "InterfejsDrona.hh"
#include "InterfejsPrzeszkody.hh"
#include "Prostopadloscian.hh"
#include <unistd.h>



/*!
* \brief Klasa modeluje menu do sterowania dronem
*/ 
class Dron : public InterfejsDrona, public InterfejsPrzeszkody, public Prostopadloscian, public std::enable_shared_from_this<Dron>
{   
    public:
    /*!
    * \brief Konstruktor parametryczny
    * \param api - gunplot
    */
    Dron(std::shared_ptr<drawNS::Draw3DAPI> &api, Wektor<double, 3> W)
    {
        srodek = W;
        Prostopadloscian p(W);

        L.zmienWierzcholkiW(srodek, orientacja);
        P.zmienWierzcholkiW(srodek, orientacja);

        index[0] = rysuj(api);
        index[1] = L.rysuj(api);
        index[2] = P.rysuj(api);
    }

    /*!
    * \brief Funkcja zwraca pole środek drona
    */
    Wektor<double, 3> zwrocSrodek() override
    {
        return srodek;
    }

    /*!
    * \brief Funkcja zwraca pole R drona
    */
    double zwrocR() override
    {
        return R;
    }

    /*!
    * \brief Funkcja przesuwa drona, oraz animuje jego ruch
    * \param api - wskaźnik na gunplota,
    * \param b - wartość y wektora o jaką przesuwamy drona
    * \param kat- kąt obrotu wokół osi X
    * \param kolekcja_przeszkod - przeszkody z którymi koliduje dron
    */
    void Przesun(std::shared_ptr<drawNS::Draw3DAPI> &api, double b, double kat, std::vector<std::shared_ptr<InterfejsPrzeszkody>> kolekcja_przeszkod) override
    {   
        Wektor<double,3> W;
        Wektor<double,3> Back;

        W.ustaw(0,b/100,0);
        Back.ustaw(0,-0.1,0);
        MacierzOb a('x',kat/100);
        MacierzOb pa('x',-kat/100);

        if(kat>90 || kat<-90)
        {
            std::cout << "Kąt powinen być >= -90 oraz <= 90"<< std::endl << std::endl;
            return;
        }

        for(int i = 0; i<100; i++)
        {   
            usun(api, index[0]);
            usun(api, index[1]);
            usun(api, index[2]);

            zmien_orient(a);
            L.obrotW();
            L.zmienWierzcholkiW(srodek, orientacja);
            P.obrotW();
            P.zmienWierzcholkiW(srodek, orientacja);

            index[0] = rysuj(api);
            index[1] = L.rysuj(api);
            index[2] = P.rysuj(api);
            usleep(5000);
        }
        
        for(int i = 0; i<100; i++)     
        {   
            usun(api, index[0]);
            usun(api, index[1]);
            usun(api, index[2]);

            przesuniecie(W);
            L.obrotW();
            L.zmienWierzcholkiW(srodek, orientacja);
            P.obrotW();
            P.zmienWierzcholkiW(srodek, orientacja);

            index[0] = rysuj(api);
            index[1] = L.rysuj(api);
            index[2] = P.rysuj(api);
            usleep(5000);

            for (auto elem : kolekcja_przeszkod)        /* Sprawdzanie kolizji dla każdej klatki ruchu*/
            {
                if(elem->czy_kolizja(shared_from_this()))
                {   
                    usun(api, index[0]);
                    usun(api, index[1]);
                    usun(api, index[2]);

                    przesuniecie(Back);
                    L.obrotW();
                    L.zmienWierzcholkiW(srodek, orientacja);
                    P.obrotW();
                    P.zmienWierzcholkiW(srodek, orientacja);

                    index[0] = rysuj(api);
                    index[1] = L.rysuj(api);
                    index[2] = P.rysuj(api);
                    usleep(5000);

                    i=100;
                    break;
                }
            }
        }

        for(int i = 0; i<100; i++)
        {   
            usun(api, index[0]);
            usun(api, index[1]);
            usun(api, index[2]);

            zmien_orient(pa);
            L.obrotW();
            L.zmienWierzcholkiW(srodek, orientacja);
            P.obrotW();
            P.zmienWierzcholkiW(srodek, orientacja);

            index[0] = rysuj(api);
            index[1] = L.rysuj(api);
            index[2] = P.rysuj(api);
            usleep(5000);
        }
    }


    /*!
    * \brief Funkcja obraca drona wokół osi Z oraz animuje ten ruch
    * \param api - wskaźnik na gunplota,
    * \param kat- kąt obrotu wokół osi Z,
    */
    void obrot(std::shared_ptr<drawNS::Draw3DAPI> &api, double kat) override
    {   
        MacierzOb M('z', kat/100);

        for(int i = 0; i<100; i++)
        {   
            usun(api, index[0]);
            usun(api, index[1]);
            usun(api, index[2]);

            zmien_orient(M);
            L.obrotW();
            L.zmienWierzcholkiW(srodek, orientacja);
            P.obrotW();
            P.zmienWierzcholkiW(srodek, orientacja);

            index[0] = rysuj(api);
            index[1] = L.rysuj(api);
            index[2] = P.rysuj(api);
            usleep(25000);
        }
    }


    /*!
    * \brief Funkcja sprawdza kolizję drona z dronem
    * \param dron - wskaźnik na dron którym prowadzimy
    */
    bool czy_kolizja(std::shared_ptr<InterfejsDrona> dron) override
    {
        Wektor<double, 3> Wek = dron->zwrocSrodek();
        if(Wek[0] == srodek[0] && Wek[1] == srodek[1] && Wek[2] == srodek[2])
            return false;

        if(Wek[0] <= srodek[0] + 2*dron->zwrocR() && Wek[0] >= srodek[0] - 2*dron->zwrocR())
        {
            if(Wek[1] <= srodek[1] + 2*dron->zwrocR() && Wek[1] >= srodek[1] - 2*dron->zwrocR())
            {
                if(Wek[2] <= srodek[2] + 2*dron->zwrocR() && Wek[2] >= srodek[2] - 2*dron->zwrocR())
                {
                    std::cout << std::endl << "Nastąpiła kolizja drona z dronem" << std::endl << std::endl;
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