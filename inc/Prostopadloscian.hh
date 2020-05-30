#ifndef PROSTOPADLOSCIAN_HH
#define PROSTOPADLOSCIAN_HH

#include "Figura.hh"
#include "Wektor.hh"

using std::vector;
using drawNS::Point3D;
using drawNS::APIGnuPlot3D;
using std::cout;
using std::endl;


/*!
* \brief Klasa modeluje wierzchołki prostopadłościanu w oparciu o środek i macierz obrotu
*/ 
class Prostopadloscian : public Figura
{
    protected:
    /*!
    * \brief Pole przechowuje dane o wierzchołkach bazowych prostopadłościanu
    */ 
    Wektor<double,3> bazaWierzcholki[8];

    /*!
    * \brief Pole przechowuje dane o wierzchołkach aktualnych danego prostopadłościanu
    */ 
    Wektor<double,3> noweWierzcholki[8];


    /*!
    * \brief Funkcja aktualizująca pozycję wierzchołków, korzystająca ze srodka i orientacji
    * \param M - Macierz o którą obracamy,
    */
    void zmienWierzcholki()
    {
        for(int i = 0; i<8; i++)
        {
            noweWierzcholki[i] = srodek + orientacja * bazaWierzcholki[i];
        }
    }

    public:
    /*!
    * \brief Konstruktor bezparametryczny
    */
    Prostopadloscian()
    {   
        bazaWierzcholki[0].ustaw(this->srodek[0] + 1, this->srodek[1] + 1, this->srodek[2] + 1);
        bazaWierzcholki[1].ustaw(this->srodek[0] - 1, this->srodek[1] + 1, this->srodek[2] + 1);
        bazaWierzcholki[2].ustaw(this->srodek[0] - 1, this->srodek[1] - 1, this->srodek[2] + 1);
        bazaWierzcholki[3].ustaw(this->srodek[0] + 1, this->srodek[1] - 1, this->srodek[2] + 1);
        bazaWierzcholki[4].ustaw(this->srodek[0] + 1, this->srodek[1] + 1, this->srodek[2] - 1);
        bazaWierzcholki[5].ustaw(this->srodek[0] - 1, this->srodek[1] + 1, this->srodek[2] - 1);
        bazaWierzcholki[6].ustaw(this->srodek[0] - 1, this->srodek[1] - 1, this->srodek[2] - 1);
        bazaWierzcholki[7].ustaw(this->srodek[0] + 1, this->srodek[1] - 1, this->srodek[2] - 1);
    };

    
    /*!
    * \brief Konstruktor parametryczny
    * \param W - przechowuje współrzędne w których ma się pojawić prostopadłościan
    */
    Prostopadloscian(Wektor<double, 3> W)
    {   
        srodek = W;
        bazaWierzcholki[0].ustaw(this->srodek[0] + 1, this->srodek[1] + 1, this->srodek[2] + 1);
        bazaWierzcholki[1].ustaw(this->srodek[0] - 1, this->srodek[1] + 1, this->srodek[2] + 1);
        bazaWierzcholki[2].ustaw(this->srodek[0] - 1, this->srodek[1] - 1, this->srodek[2] + 1);
        bazaWierzcholki[3].ustaw(this->srodek[0] + 1, this->srodek[1] - 1, this->srodek[2] + 1);
        bazaWierzcholki[4].ustaw(this->srodek[0] + 1, this->srodek[1] + 1, this->srodek[2] - 1);
        bazaWierzcholki[5].ustaw(this->srodek[0] - 1, this->srodek[1] + 1, this->srodek[2] - 1);
        bazaWierzcholki[6].ustaw(this->srodek[0] - 1, this->srodek[1] - 1, this->srodek[2] - 1);
        bazaWierzcholki[7].ustaw(this->srodek[0] + 1, this->srodek[1] - 1, this->srodek[2] - 1);
    };


    /*!
    * \brief Funkcja rysująca aktualne wierzchołki w gunplocie
    * \param api - uruchomiony gunplot
    */   
    int rysuj(std::shared_ptr<drawNS::Draw3DAPI> &api) override
    {
        zmienWierzcholki();

        int ind = api->draw_polyhedron(vector<vector<Point3D> > 
        {{
            drawNS::Point3D(noweWierzcholki[0][0], noweWierzcholki[0][1], noweWierzcholki[0][2]), 
            drawNS::Point3D(noweWierzcholki[1][0], noweWierzcholki[1][1], noweWierzcholki[1][2]),
            drawNS::Point3D(noweWierzcholki[2][0], noweWierzcholki[2][1], noweWierzcholki[2][2]), 
            drawNS::Point3D(noweWierzcholki[3][0], noweWierzcholki[3][1], noweWierzcholki[3][2])
            },{
            drawNS::Point3D(noweWierzcholki[4][0], noweWierzcholki[4][1], noweWierzcholki[4][2]),
            drawNS::Point3D(noweWierzcholki[5][0], noweWierzcholki[5][1], noweWierzcholki[5][2]),
            drawNS::Point3D(noweWierzcholki[6][0], noweWierzcholki[6][1], noweWierzcholki[6][2]),
            drawNS::Point3D(noweWierzcholki[7][0], noweWierzcholki[7][1], noweWierzcholki[7][2])    
        }},"red");//rysuje czerowny prostopadłościan

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
