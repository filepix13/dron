#ifndef PLASZCZYZNA_HH
#define PLASZCZYZNA_HH

#include "InterfejsRysowania.hh"
#include "InterfejsPrzeszkody.hh"
#include "Wektor.hh"
#include <string>

using std::vector;
using drawNS::Point3D;
using drawNS::APIGnuPlot3D;

class Plaszczyzna : public InterfejsRysowania, public InterfejsPrzeszkody
{   
    protected:
    /*!
    * \brief Pole przechowuje wymiary płaszczyzny
    */
    Wektor<double, 3> wymiary;

    /*!
    * \brief Pole przechowuje kolor płaszczyzny
    */
    std::string kolor;
    
    public:
    /*!
    * \brief Konstruktor bezparametryczny Płaszczyzny
    */
    Plaszczyzna() = default;


    /*!
    * \brief Funkcja ta rysuje płaszczyznę w oparciu o wymiary maksymalne 
    */
    int rysuj(std::shared_ptr<drawNS::Draw3DAPI> &api) override
    {
        int indeks = api->draw_surface(vector<vector<Point3D> > {{
        drawNS::Point3D(wymiary[0],wymiary[1],wymiary[2]), drawNS::Point3D(wymiary[0],0,wymiary[2]), drawNS::Point3D(wymiary[0],-wymiary[1],wymiary[2])
        },{
        drawNS::Point3D(wymiary[0]/2,wymiary[1],wymiary[2]), drawNS::Point3D(wymiary[0]/2,0,wymiary[2]), drawNS::Point3D(wymiary[0]/2,-wymiary[1],wymiary[2])  
        },{
        drawNS::Point3D(0,wymiary[1],wymiary[2]), drawNS::Point3D(0,0,wymiary[2]), drawNS::Point3D(0,-wymiary[1],wymiary[2])
        },{
        drawNS::Point3D(-wymiary[0]/2,wymiary[1],wymiary[2]), drawNS::Point3D(-wymiary[0]/2,0,wymiary[2]), drawNS::Point3D(-wymiary[0]/2,-wymiary[1],wymiary[2])
        },{
        drawNS::Point3D(-wymiary[0],wymiary[1],wymiary[2]), drawNS::Point3D(-wymiary[0],0,wymiary[2]), drawNS::Point3D(-wymiary[0],-wymiary[1],wymiary[2])
        }}, kolor);

        return indeks;        
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