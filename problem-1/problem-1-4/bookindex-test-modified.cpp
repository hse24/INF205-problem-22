//edited by Henrik Sam Eyde, NMBU
#include "book-index.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

namespace
{
   void start_chapter(litindex::BookIndex b)
   {
      std::cout << "start_chapter(litindex::BookIndex b)\n";

      b.next_chapter();
      b.out();  // print status
   }
}

int main()
{
   std::cout << "\nBookIndex example:\n";
   litindex::BookIndex idx(1, 11, 24);
   
   litindex::BookIndex* address = &idx;
   
   idx.out();  // print status
   start_chapter(idx);
   idx.out();  // print status
	       //
   //read from file:
   std::fistream myfile("test.txt");
   std::string line;
   std::string number = myfile.get_line(myfile, line);
   int n = std::stoi(number);
   std::stringstream ss;
   std::string fileline;
   int c;
   int s;
   int p;
   for (int i = 0; i < n; i++) {
	   fileline = myfile.get_line(myfile, line);
	   ss = std::stringstream(fileline);
	   ss >> c;
	   ss >> s;
	   ss >> p;
	   idx = litindex::BookIndex(c, s, p);
	   idx.out();
   }
}

