#include <iostream>
#include "Dr3D_gnuplot_api.hh"
#include "Wektor.hh"
#include "Macierz.hh"
#include "MacierzOb.hh"
#include "Figura.hh"
#include "Prostopadloscian.hh"
#include "Dron.hh"


using std::vector;
using drawNS::Point3D;
using drawNS::APIGnuPlot3D;
using std::cout;
using std::endl;


int main() {

  std::shared_ptr<drawNS::Draw3DAPI> api(new APIGnuPlot3D(-10,10,-10,10,-10,10,0));
  Wektor<double,3> przesu;
  MacierzOb M;
  char c;
  double ruch, kat;
  Dron d(api);

  std::cout << "r - zadaj ruch na wprost" << std::endl;
  std::cout << "o - zmień orientację" << std::endl;
  std::cout << "m - wyświetl menu" << std::endl << std::endl;
  std::cout << "k - zakończ działanie programu" << std::endl << std::endl;

  while(1)
  {
    std::cout << "Wybierz opcję działania: ";
    std::cin >> c;
    std::cout << endl;

    switch (c)
    {
    case 'r':
      std::cout << "Podaj wartość kąta (wznoszenia/opadania) w stopniach: ";
      std::cin >> kat;
      if(std::cin.fail())
      {
        std::cin.clear( );
        std::cin.ignore(1000,'\n');
        std::cout << "Powinna zostać podana liczba rzeczywista" << std::endl << std::endl;
        break;
      }

      std::cout << "Podaj wartość odległości o jaką ma się przesunąć dron: ";
      std::cin >> ruch;

      if(std::cin.fail())
      {
        std::cin.clear( );
        std::cin.ignore(1000,'\n');
        std::cout << "Powinna zostać podana liczba rzeczywista" << std::endl << std::endl;
        break;
      }      
      d.Przesun(api,ruch,kat);
      break;
    
    case 'o':
      std::cout << "Podaj wartość kąta obrotu w stopniach: ";
      std::cin >> kat;
      if(std::cin.fail())
      {
        std::cin.clear( );
        std::cin.ignore(1000,'\n');
        std::cout << "Powinna zostać podana liczba rzeczywista" << std::endl << std::endl;
        break;
      }

      d.obrot(api,kat);
      break;

    case 'm':
      std::cout << "r - zadaj ruch na wprost" << std::endl;
      std::cout << "o - zmień orientację" << std::endl;
      std::cout << "m - wyświetl menu" << std::endl << std::endl;
      std::cout << "k - zakończ działanie programu" << std::endl;
      break;

    case 'k':
      return 0;
      break;

    default:
      std::cout << "Błędna opcja, spróbuj wybrać inną opcję." << std::endl;
      break;
    }
  }



  /*std::shared_ptr<drawNS::Draw3DAPI> api(new APIGnuPlot3D(-5,5,-5,5,-5,5,1000)); //włacza gnuplota, pojawia się scena [-5,5] x [-5,5] x [-5,5] odświeżana co 1000 ms
  drawNS::Draw3DAPI * api = new APIGnuPlot3D(-5,5,-5,5,-5,5,1000); //alternatywnie zwykły wskaźnik
  api->change_ref_time_ms(0); //odświeżanie sceny zmienione na opcję "z każdym pojawieniem się lub zniknięciem kształtu"


  int a=api->draw_line(drawNS::Point3D(0,0,0),drawNS::Point3D(2,0,0)); //rysuje linię pomiędzy (0,0,0) a (2,0,0), zapamiętuje id kształtu w zmiennej a 
  api->draw_line(drawNS::Point3D(0,0,0),drawNS::Point3D(0,0,5),"red"); //rysuje czerwoną linie pomiędzy (0,0,0) a (0,0,5)

  cout << endl << "pojawiły się 2 linie: czarna i czerwona" << endl;  
  wait4key();

  api->erase_shape(a); //usuwa kształt o id a
  cout << "czarna linia zniknęła" << endl;

  wait4key();

  api->draw_polygonal_chain(vector<Point3D> {drawNS::Point3D(0,0,0),
	drawNS::Point3D(0,4,0),drawNS::Point3D(4,4,0),
	drawNS::Point3D(4,0,0),drawNS::Point3D(4,0,4)},"purple"); //rysuje fioletową łamaną
  cout << "pojawiła się fioletowa łamana" << endl;
  
  wait4key();
  api->change_ref_time_ms(1000);
  int b=api->draw_polygonal_chain(vector<Point3D> {drawNS::Point3D(0,0,0),
	drawNS::Point3D(0,-4,0),drawNS::Point3D(-4,-4,0),
	drawNS::Point3D(-4,0,0),drawNS::Point3D(-4,0,-4)},"green");
  cout << "pojawiła się zielona łamana" << endl;
  
  wait4key();
  api->change_shape_color(b,"yellow");//zmienia kolor
  cout << "zmiana koloru z zielonej na żółtą" << endl;

  wait4key();
  api->draw_polyhedron(vector<vector<Point3D> > 
  {{
	drawNS::Point3D(-1,1,1), drawNS::Point3D(1,1,1), drawNS::Point3D(-1,-1,1), drawNS::Point3D(1,-1,1)
      },{
	drawNS::Point3D(-1,1,-1), drawNS::Point3D(1,1,-1), drawNS::Point3D(-1,-1,-1), drawNS::Point3D(1,-1,-1)     
	  },{
  drawNS::Point3D(-1,1,-1), drawNS::Point3D(1,1,-1), drawNS::Point3D(-1,1,1), drawNS::Point3D(1,1,1)
    },{
  drawNS::Point3D(-1,-1,-1), drawNS::Point3D(1,-1,-1), drawNS::Point3D(-1,-1,1), drawNS::Point3D(1,-1,1)
    }
  },"blue");//rysuje niebieski graniastosłup

  wait4key();
  api->change_ref_time_ms(-1);//odświerzanie sceny zmienione na opcję "tylko za pomocą metody redraw()"

  api->draw_polyhedron(vector<vector<Point3D> > {{
	drawNS::Point3D(0,0,0), drawNS::Point3D(0,1,0), drawNS::Point3D(1,1,0)
      },{
	drawNS::Point3D(0,0,3), drawNS::Point3D(0,1,3), drawNS::Point3D(1,2,4)       
	  }},"blue");//rysuje niebieski graniastosłup
  cout << "nie pojawiła się niebieski graniastosłup" << endl;
  
  wait4key();

  api->redraw();//odświerzenie sceny
  cout << "dopiero teraz pojawiła się niebieski graniastosłup" << endl;

  wait4key();
  api->change_ref_time_ms(0);

  api->draw_surface(vector<vector<Point3D> > {{
	drawNS::Point3D(-4,-2,-4), drawNS::Point3D(-4,0,-4), drawNS::Point3D(-4,2,-4)
	  },{
	drawNS::Point3D(-2,-2,-4), drawNS::Point3D(-2,0,-4), drawNS::Point3D(-2,2,-4)       
	  },{
	drawNS::Point3D(-0,-2,-4), drawNS::Point3D(-0,0,-3), drawNS::Point3D(-0,2,-4)       
	  },{
	drawNS::Point3D(2,-2,-4), drawNS::Point3D(2,0,-4), drawNS::Point3D(2,2,-4)       
	  },{
	drawNS::Point3D(4,-2,-4), drawNS::Point3D(4,0,-4), drawNS::Point3D(4,2,-4)       
	  }},"grey");//rysuje szarą powierzchnie
  cout << "pojawiła się szara powierzchnia" << endl;

  
  wait4key();*/
  
  
  //delete api;//dla zwykłych wskaźników musimy posprzątać
}
