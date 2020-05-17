#ifndef DRON_HH
#define DRON_HH

#include "Prostopadloscian.hh"
#include "Wirnik.hh" 
#include <unistd.h>


/*!
* \brief Klasa modeluje menu do sterowania dronem
*/ 
class Dron : public Prostopadloscian
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

    public:
    /*!
    * \brief Konstruktor parametryczny
    * \param api - gunplot
    */
    Dron(std::shared_ptr<drawNS::Draw3DAPI> &api)
    {   
        L.zmianSrodek(-1,-1.5,0);
        L.zmienWierzcholkiW(srodek, orientacja);
        P.zmianSrodek(1,-1.5,0);
        P.zmienWierzcholkiW(srodek, orientacja);

        index[0] = rysuj(api);
        index[1] = L.rysuj(api);
        index[2] = P.rysuj(api);
    }

    /*!
    * \brief Funkcja przesuwa drona, oraz animuje jego ruch
    * \param api - wskaźnik na gunplota,
    * \param b - wartość y wektora o jaką przesuwamy drona
    * \param kat- kąt obrotu wokół osi X
    */
    void Przesun(std::shared_ptr<drawNS::Draw3DAPI> &api, double b, double kat)
    {   
        Wektor<double,3> W;

        W.ustaw(0,b/100,0);
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
    void obrot(std::shared_ptr<drawNS::Draw3DAPI> &api, double kat)
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
};



#endif