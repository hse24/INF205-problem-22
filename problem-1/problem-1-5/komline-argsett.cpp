//edited by Henrik Sam Eyde, NMBU
#include <iostream>
#include <set>  // for std::set
#include <list>
#include <string>  // vi vil konvertere C-strengane til C++-strengar

int main(int argc, char** argv)
{
   std::cout << "\nargv[0] er namnet til den kÃ¸yrbare fila: " << argv[0] << "\n";
   
   std::set<std::string> argumentsett{};
   std::list<std::string> argumentliste{};
   
   /*
    * med dette filtrerer vi ut duplikat; settet er automatisk sortert
    */
   for(int i = 0; i < argc; i++)
   {
	   bool is_in = argumentsett.find(argv[i]) != argumentsett.end(); 
      argumentsett.insert(std::string(argv[i]));
      if (!is_in) {
	      argumentliste.push_back(argv[i]);
      }
   }
   
   /*
    * iterere gjennom settet
    * for Ã¥ iterere over ein STL-datastruktur bruker vi ein tilsvarande iterator
    */
   for(std::list<std::string>::iterator s = argumentliste.begin(); s != argumentliste.end(); s = std::next(s))
      std::cout << "\targument: \"" << *s << "\"\n";
}
