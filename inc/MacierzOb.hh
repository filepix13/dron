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
    /*!
    * \brief Konstruktor bezparametryczny, tworzy macierz jednostkową
    */
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

    /*!
    * \brief Konstruktor parametryczny macierzy
    * \param M - Macierz która ma zostać macierzą obrotu
    */
    MacierzOb(const Macierz<double,3> & M) : Macierz<double,3>(M)
    {
        MacierzOb X;
        X = M;
        
        if(X.sprawdzanie())
            *this = X;
        else
        {
            std::cout << "Podana macierz nie jest macierzą obrotu" << std::endl << std::endl;
            exit(1);
        }
        
    }


    /*!
    * \brief Konstruktor parametryczny
    * \param os - oś o jaką obracamy
    * \param stopnie - stopnie o jakie mamy obrócić
    */
    MacierzOb(char os,double stopnie)
    {
        double rad = stopnie*PI/180;

        if(os == 'z')
        {
            tab[0][0] = cos(rad);
            tab[0][1] = -sin(rad);
            tab[0][2] = 0;
            tab[1][0] = sin(rad);
            tab[1][1] = cos(rad);
            tab[1][2] = 0;
            tab[2][0] = 0;
            tab[2][1] = 0;
            tab[2][2] = 1;
        } else if(os == 'y')
        {
            tab[0][0] = cos(rad);
            tab[0][1] = 0;
            tab[0][2] = sin(rad);
            tab[1][0] = 0;
            tab[1][1] = 1;
            tab[1][2] = 0;
            tab[2][0] = -sin(rad);
            tab[2][1] = 0;
            tab[2][2] = cos(rad);
        } else if(os == 'x')
        {
            tab[0][0] = 1;
            tab[0][1] = 0;
            tab[0][2] = 0;
            tab[1][0] = 0;
            tab[1][1] = cos(rad);
            tab[1][2] = -sin(rad);
            tab[2][0] = 0;
            tab[2][1] = sin(rad);
            tab[2][2] = cos(rad);
        } else
        {
            std::cerr << "Program nie posiada takiej opcji, obracać można tylko wokół osi z oraz x" << std::endl << std::endl;
            exit(1);
        }

        for(int i=0; i<3; i++)      /* eliminacja błędu przy obliczaniu zera */
        {
            for(int j=0; j<3; j++)
            {
                if(tab[i][j]<EPSILON && tab[i][j]>-EPSILON)
                    tab[i][j]=0;
            }
        }
    }

    /*!
    * \brief Funkcja sprawdza czy macierz jest macierzą obrotu
    */
    bool sprawdzanie()
    { 
        if(Wyznacznik() == 1 && *this * transpozycja2() == transpozycja2() * *this)
            return true;
        else 
            return false;
    }
};



#endif
