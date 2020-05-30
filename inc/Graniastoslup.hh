#ifndef GRANIASTOSLUP_HH
#define GRANIASTOSLUP_HH

#include <math.h> 
#include "Figura.hh"
#include "Wektor.hh"
using std::vector;
using drawNS::Point3D;
using drawNS::APIGnuPlot3D;

class Graniastoslup : public Figura
{
    protected:
    /*!
    * \brief Pole przechowuje dane o wierzchołkach bazowych graniatosłupa
    */ 
    Wektor<double,3> bazaWierzcholkiG[12];

    /*!
    * \brief Pole przechowuje dane o wierzchołkach aktualnych danego graniastosłupa
    */ 
    Wektor<double,3> noweWierzcholkiG[12];

    /*!
    * \brief Funkcja aktualizująca pozycję wierzchołków, korzystająca ze srodka i orientacji
    */
    void zmienWierzcholki()
    {
        for(int i = 0; i<12; i++)
        {
            noweWierzcholkiG[i] = srodek + orientacja * bazaWierzcholkiG[i];
        }
    }

    public:
    /*!
    *\brief Konstruktor bezparametryczny graniastosłupa  
    */
    Graniastoslup()
    {
        bazaWierzcholkiG[0].ustaw(this->srodek[0], this->srodek[1] + 0.5, this->srodek[2] + 1);
        bazaWierzcholkiG[1].ustaw(this->srodek[0] + (sqrt(3)/2), this->srodek[1] + 0.5, this->srodek[2] + 0.5);
        bazaWierzcholkiG[2].ustaw(this->srodek[0] + (sqrt(3)/2), this->srodek[1] + 0.5, this->srodek[2] - 0.5);
        bazaWierzcholkiG[3].ustaw(this->srodek[0], this->srodek[1] + 0.5, this->srodek[2] - 1);
        bazaWierzcholkiG[4].ustaw(this->srodek[0] - (sqrt(3)/2), this->srodek[1] + 0.5, this->srodek[2] - 0.5);
        bazaWierzcholkiG[5].ustaw(this->srodek[0] - (sqrt(3)/2), this->srodek[1] + 0.5, this->srodek[2] + 0.5);
        bazaWierzcholkiG[6].ustaw(this->srodek[0], this->srodek[1] - 0.5, this->srodek[2] + 1);
        bazaWierzcholkiG[7].ustaw(this->srodek[0] + (sqrt(3)/2), this->srodek[1] - 0.5, this->srodek[2] + 0.5);
        bazaWierzcholkiG[8].ustaw(this->srodek[0] + (sqrt(3)/2), this->srodek[1] - 0.5, this->srodek[2] - 0.5);
        bazaWierzcholkiG[9].ustaw(this->srodek[0], this->srodek[1] - 0.5, this->srodek[2] - 1);
        bazaWierzcholkiG[10].ustaw(this->srodek[0] - (sqrt(3)/2), this->srodek[1] - 0.5, this->srodek[2] - 0.5);
        bazaWierzcholkiG[11].ustaw(this->srodek[0] - (sqrt(3)/2), this->srodek[1] - 0.5, this->srodek[2] + 0.5);
    }


    /*!
    *\brief Konstruktor parametryczny Graniastosłupa
    *\param x - Współrzędna x srodka graniastosłupa
    *\param y - Współrzędna y srodka graniastosłupa 
    *\param z - Współrzędna z srodka graniastosłupa   
    */
    Graniastoslup(double x, double y, double z)
    {
        srodek.ustaw(x,y,z);
        bazaWierzcholkiG[0].ustaw(this->srodek[0], this->srodek[1] + 0.5, this->srodek[2] + 1);
        bazaWierzcholkiG[1].ustaw(this->srodek[0] + (sqrt(3)/2), this->srodek[1] + 0.5, this->srodek[2] + 0.5);
        bazaWierzcholkiG[2].ustaw(this->srodek[0] + (sqrt(3)/2), this->srodek[1] + 0.5, this->srodek[2] - 0.5);
        bazaWierzcholkiG[3].ustaw(this->srodek[0], this->srodek[1] + 0.5, this->srodek[2] - 1);
        bazaWierzcholkiG[4].ustaw(this->srodek[0] - (sqrt(3)/2), this->srodek[1] + 0.5, this->srodek[2] - 0.5);
        bazaWierzcholkiG[5].ustaw(this->srodek[0] - (sqrt(3)/2), this->srodek[1] + 0.5, this->srodek[2] + 0.5);
        bazaWierzcholkiG[6].ustaw(this->srodek[0], this->srodek[1] - 0.5, this->srodek[2] + 1);
        bazaWierzcholkiG[7].ustaw(this->srodek[0] + (sqrt(3)/2), this->srodek[1] - 0.5, this->srodek[2] + 0.5);
        bazaWierzcholkiG[8].ustaw(this->srodek[0] + (sqrt(3)/2), this->srodek[1] - 0.5, this->srodek[2] - 0.5);
        bazaWierzcholkiG[9].ustaw(this->srodek[0], this->srodek[1] - 0.5, this->srodek[2] - 1);
        bazaWierzcholkiG[10].ustaw(this->srodek[0] - (sqrt(3)/2), this->srodek[1] - 0.5, this->srodek[2] - 0.5);
        bazaWierzcholkiG[11].ustaw(this->srodek[0] - (sqrt(3)/2), this->srodek[1] - 0.5, this->srodek[2] + 0.5);
    }


    /*!
    * \brief Funkcja aktualizująca pozycję wierzchołków, korzystająca ze srodka i orientacji wirnika, oraz ze środka i orientacji drona
    * \param dr_sr Środek drona
    * \param dr_orient Macierz orientacji drona
    */
    void zmienWierzcholkiW(Wektor<double,3> dr_sr, MacierzOb dr_orient)
    {
        for(int i = 0; i<12; i++)
        {
            noweWierzcholkiG[i] = dr_sr + dr_orient * srodek + dr_orient * orientacja * bazaWierzcholkiG[i];
        }
    }


    /*!
    * \brief Funkcja rysująca aktualne wierzchołki w gunplocie
    * \param api - uruchomiony gunplot
    */   
    int rysuj(std::shared_ptr<drawNS::Draw3DAPI> &api) override
    {
        //zmienWierzcholki();

        int ind = api->draw_polyhedron(vector<vector<Point3D> > 
        {{  
            drawNS::Point3D(noweWierzcholkiG[0][0], noweWierzcholkiG[0][1], noweWierzcholkiG[0][2]),
            drawNS::Point3D(noweWierzcholkiG[1][0], noweWierzcholkiG[1][1], noweWierzcholkiG[1][2]),
            drawNS::Point3D(noweWierzcholkiG[2][0], noweWierzcholkiG[2][1], noweWierzcholkiG[2][2]),
            drawNS::Point3D(noweWierzcholkiG[3][0], noweWierzcholkiG[3][1], noweWierzcholkiG[3][2]),
            drawNS::Point3D(noweWierzcholkiG[4][0], noweWierzcholkiG[4][1], noweWierzcholkiG[4][2]),
            drawNS::Point3D(noweWierzcholkiG[5][0], noweWierzcholkiG[5][1], noweWierzcholkiG[5][2])
            },{
            drawNS::Point3D(noweWierzcholkiG[6][0], noweWierzcholkiG[6][1], noweWierzcholkiG[6][2]),
            drawNS::Point3D(noweWierzcholkiG[7][0], noweWierzcholkiG[7][1], noweWierzcholkiG[7][2]), 
            drawNS::Point3D(noweWierzcholkiG[8][0], noweWierzcholkiG[8][1], noweWierzcholkiG[8][2]), 
            drawNS::Point3D(noweWierzcholkiG[9][0], noweWierzcholkiG[9][1], noweWierzcholkiG[9][2]),
            drawNS::Point3D(noweWierzcholkiG[10][0], noweWierzcholkiG[10][1], noweWierzcholkiG[10][2]), 
            drawNS::Point3D(noweWierzcholkiG[11][0], noweWierzcholkiG[11][1], noweWierzcholkiG[11][2])
        }},"purple");//rysuje fioletowy graniastosłup
        
        return ind;
    }

    /*!
    * \brief Funkcja usuwająca kształ z gunplota
    * \param api - uruchomiony gunplot
    * \param ind - indeks figury którą usuwamy
    */
    void usun(std::shared_ptr<drawNS::Draw3DAPI> &api, int ind) override
    {
        api->erase_shape(ind);
    }
};

#endif