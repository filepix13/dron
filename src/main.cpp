#include <iostream>
#include "Dr3D_gnuplot_api.hh"
#include "Wektor.hh"
#include "Dron.hh"
#include "Plaszczyzna.hh"
#include "InterfejsDrona.hh"
#include "InterfejsPrzeszkody.hh"
#include "Powierzchnia.hh"
#include "Dno.hh"
#include "PrzeszkodaProst.hh"

using std::vector;
using drawNS::Point3D;
using drawNS::APIGnuPlot3D;
using std::cout;
using std::endl;


int main() {

  Wektor<double, 3> scena(10,10,12);
  Wektor<double, 3> srodek(3,0,0);
  Wektor<double, 3> srodekP(-3,0,0);
  Wektor<double, 3> srodekx(3,5,0);

  std::shared_ptr<drawNS::Draw3DAPI> api(new APIGnuPlot3D(-scena[0],scena[0],-scena[1], scena[1],-scena[2],scena[2],0));

  char c;
  double ruch, kat;
  std::shared_ptr<Dron> d(new Dron(api, srodek));
  std::shared_ptr<Dron> dA(new Dron(api, srodekx));

  std::vector<std::shared_ptr<InterfejsPrzeszkody>> przeszkoda
  {
    std::make_shared<Powierzchnia>(api, scena[0],scena[1],(scena[2]-2), "blue"),
    std::make_shared<Dno>(api, scena[0],scena[1],(-scena[2]+2), "grey"),
    std::make_shared<PrzeszkodaProst>(api, srodekP),
  };
  przeszkoda.push_back(d);
  przeszkoda.push_back(dA);

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
      d->Przesun(api,ruch,kat,przeszkoda);
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

      d->obrot(api,kat);
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
}
