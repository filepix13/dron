#ifndef MACIERZOB_HH
#define MACIERZOB_HH

#include "Macierz.hh"
#include <iostream>
#include <math.h>

#define PI 3.14159265359
#define EPSILON 2.07267e-10

class MacierzOb : public Macierz<double,3>
{
    public:
    MacierzOb()
    {
        tab[0][0] = 1;
        tab[0][1] = 0;
        tab[0][2] = 0;
        tab[1][0] = 0;
        tab[1][1] = 1;
        tab[1][2] = 0;
        tab[2][0] = 0;
        tab[2][1] = 0;
        tab[2][2] = 1;
    }

    MacierzOb(const Macierz<double,3> & M) : Macierz<double,3>(M)
    {
        *this = M;
    }

    void obrotZ(double stopnie)
    {
        double rad = stopnie*PI/180;

        tab[0][0] = cos(rad);
        tab[0][1] = -sin(rad);
        tab[0][2] = 0;
        tab[1][0] = sin(rad);
        tab[1][1] = cos(rad);
        tab[1][2] = 0;
        tab[2][0] = 0;
        tab[2][1] = 0;
        tab[2][2] = 1;

        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {
                if(tab[i][j]<EPSILON && tab[i][j]>-EPSILON)
                    tab[i][j]=0;
            }
        }
    }

    MacierzOb obrotX(double stopnie)
    {
        double rad = stopnie*PI/180;

        tab[0][0] = 1;
        tab[0][1] = 0;
        tab[0][2] = 0;
        tab[1][0] = 0;
        tab[1][1] = cos(rad);
        tab[1][2] = -sin(rad);
        tab[2][0] = 0;
        tab[2][1] = sin(rad);
        tab[2][2] = cos(rad);

        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {
                if(tab[i][j]<EPSILON && tab[i][j]>-EPSILON)
                    tab[i][j]=0;
            }
        }

        return *this;
    }

};



#endif
