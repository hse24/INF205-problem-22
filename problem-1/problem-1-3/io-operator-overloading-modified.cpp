//edited by Henrik Sam Eyde, NMBU
#include "journal-article-index.h"
#include <iostream>
#include <sstream>
#include <fstream>

int main()
{
   litindex::JournalArticleIndex jai_i;
   jai_i.set_bibliographic_data(
      "IEEE_Access", 9, 0, 152333, 152346, 2021, "doi:10.1109/access.2021.3126429"
   );
   jai_i.set_page(152345);
   std::clog << "JournalArticleIndex jai_i:\n" << jai_i << "\n";

   std::clog << "\nWriting jai_i into a filestream.\n";
   std::ofstream ostream ("file.txt");
   ostream << jai_i; 
   ostream.close();
   std::string line;
   std::ifstream myfile ("file.txt");
   if (!myfile.is_open()) {
	   std::cerr << "Error opening the file\n"; 
	  return 1;
   }
   while (getline(myfile, line))
   {
	std::cout << line << '\n';
   }
   
   litindex::JournalArticleIndex jai_j;
   std::clog << "\nReading jai_j from the file stream.\n";
   myfile >> jai_j; //dette får jeg ikke til
   std::clog << "JournalArticleIndex jai_j:\n" << jai_j << "\n";
   myfile.close();
}
