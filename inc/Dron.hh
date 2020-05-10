#ifndef DRON_HH
#define DRON_HH

#include "Prostopadloscian.hh" 
#include <unistd.h>


class Dron : public Prostopadloscian
{   
    protected:
    int index;

    public:
    Dron(std::shared_ptr<drawNS::Draw3DAPI> &api)
    {   
        index = rysuj(api);
    }

    void Przesun(std::shared_ptr<drawNS::Draw3DAPI> &api, double b, double kat)
    {
        Wektor<double,3> W;
        MacierzOb M;
        W.ustaw(0,b/100,0);

        if(kat>90 || kat<-90)
        {
            std::cout << "Kąt powinen być >= -90 oraz <= 90"<< std::endl << std::endl;
            return;
        }

        M.obrotX(kat/100);

        for(int i = 0; i<100; i++)
        {   
            usun(api, index);
            zmien_orient(M);;
            index = rysuj(api);
            usleep(5000);
        }
        
        for(int i = 0; i<100; i++)
        {   
            usun(api, index);
            przesuniecie(W);
            index = rysuj(api);
            usleep(5000);
        }

        M.obrotX(-kat/100);

        for(int i = 0; i<100; i++)
        {   
            usun(api, index);
            zmien_orient(M);;
            index = rysuj(api);
            usleep(5000);
        }
    }

    void obrot(std::shared_ptr<drawNS::Draw3DAPI> &api, double kat)
    {   
        MacierzOb M;
        M.obrotZ(kat/100);

        for(int i = 0; i<100; i++)
        {   
            usun(api, index);
            zmien_orient(M);;
            index = rysuj(api);
            usleep(25000);
        }
        
    }


};



#endif