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
  Wektor<double, 3> srodekA(3,0,0);
  Wektor<double, 3> srodekP(-3,0,0);
  Wektor<double, 3> srodekB(3,5,0);

  std::shared_ptr<drawNS::Draw3DAPI> api(new APIGnuPlot3D(-scena[0],scena[0],-scena[1], scena[1],-scena[2],scena[2],0));

  char c, nazwaDr;
  int ktoryDr = 0;
  double ruch, kat;
  std::shared_ptr<Dron> dA(new Dron(api, srodekA));
  std::shared_ptr<Dron> dB(new Dron(api, srodekB));

  std::vector<std::shared_ptr<InterfejsPrzeszkody>> przeszkoda
  {
    std::make_shared<Powierzchnia>(api, scena[0],scena[1],(scena[2]-2), "blue"),
    std::make_shared<Dno>(api, scena[0],scena[1],(-scena[2]+2), "grey"),
    std::make_shared<PrzeszkodaProst>(api, srodekP),
  };
  przeszkoda.push_back(dA);
  przeszkoda.push_back(dB);

  std::cout << "r - zadaj ruch na wprost" << std::endl;
  std::cout << "o - zmień orientację" << std::endl;
  std::cout << "z - zmień drona" << std::endl;
  std::cout << "m - wyświetl menu" << std::endl << std::endl;
  std::cout << "k - zakończ działanie programu" << std::endl << std::endl;

  while(1)
  {
    std::cout << "Ilość istniejących obiektów figura: " << Figura::zwroc_istniejace() << std::endl;
    std::cout << "Ilość utworzonych obiektów figura: " << Figura::zwroc_utworzone() << std::endl;
    std::cout << "Ilość istniejących obiektów wektor: " << Wektor<double,3>::zwroc_istniejace() << std::endl;
    std::cout << "Ilość utworzonych obiektów wektor: " << Wektor<double,3>::zwroc_utworzone() << std::endl << std::endl;

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

      if(ktoryDr == 1)      
        dA->Przesun(api,ruch,kat,przeszkoda);
      else if(ktoryDr == 2)
        dB->Przesun(api,ruch,kat,przeszkoda);
      else if(ktoryDr == 0)
        std::cout << "Proszę najpierw wybrać drona." << std::endl << std::endl;

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
      
      if(ktoryDr == 1)      
        dA->obrot(api,kat);
      else if(ktoryDr == 2)
        dB->obrot(api,kat);
      else if(ktoryDr == 0)
        std::cout << "Proszę najpierw wybrać drona." << std::endl << std::endl;
      
      break;

    case 'z':
      std::cout << "Współrzędne drona A: " << dA->zwrocSrodek();
      std::cout << "Współrzędne drona B: " << dB->zwrocSrodek() << std::endl;
      std::cout << "Jakiego drona chcesz wybrać?: ";
      std::cin >> nazwaDr;
      if(std::cin.fail())
      {
        std::cin.clear( );
        std::cin.ignore(1000,'\n');
        std::cout << "Powinna zostać podana litera A lub B" << std::endl << std::endl;
        break;
      }

      if(nazwaDr == 'A')
        ktoryDr = 1;
      else if(nazwaDr == 'B')
        ktoryDr = 2;
      else
        std::cout << "Niestety nie ma takiego drona. Dostępne drony to A i B " << std::endl << std::endl;

      break;

    case 'm':
      std::cout << "r - zadaj ruch na wprost" << std::endl;
      std::cout << "o - zmień orientację" << std::endl;
      std::cout << "z - zmień drona" << std::endl;
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
