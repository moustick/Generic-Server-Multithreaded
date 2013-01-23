//
// mainBuffer.cpp for  in /home/cottin_j//Documents/rtype-2015-cottin_j/src
// 
// Made by joffrey cottin
// Login   <cottin_j@epitech.net>
// 
// Started on  Sun Jan 20 01:12:12 2013 joffrey cottin
// Last update Sun Jan 20 19:46:26 2013 joffrey cottin
//


#include <iostream>
#include "Buffer/Buffer.hpp"

using namespace buffer;

int main(void)
{
  Buffer test(24);
  std::string a1("j'aimerais");
  std::string a2("pas");
  std::string a3("m'arracher");
  std::string a4("une");
  std::string a5;
  std::string a6("couille");
  std::string str;

  std::string OUT;

  std::cout << "PUSH 1 : j'aimerais " << a1.size()<< std::endl;
  test.push(a1);
  std::cout << "PUSH 2 : pas " << a2.size()<< std::endl;
  test.push(a2);
  std::cout << "PUSH 3 : m'arracher "<< a3.size()<< std::endl;
  test.push(a3);
  std::cout << "PUSH 4 : une "<< a4.size()<< std::endl;
  test.push(a4);
  std::cout << "PUSH 5 : """ << a5.size()<<std::endl;
  test.push(a5);
  std::cout << "PUSH 6 : couille "<< a6.size() <<std::endl;
  test.push(a6);
  std::cout << "PUSH 6" << std::endl;

  std::cout << test.getPiece(OUT, 15) << std::endl;
  OUT.clear();
  std::cout << test.getPiece(OUT, 10) << std::endl;
  OUT.clear();
  std::cout << test.getPiece(OUT, 5) << std::endl;
  OUT.clear();

  std::cout << "POP1- " << test.pop(OUT, 22) <<  std::endl;
  OUT.clear();

  std::cout << "POP2- " <<   test.pop(OUT, 20) << std::endl;
  OUT.clear();
  std::cout <<"POP:1 " << test.pop(OUT, 1) << std::endl;
  std::cout << "POP:0 "<< test.pop(OUT, 0) << std::endl;
  OUT.clear();
  std::cout << "POP:23 "<< test.pop(OUT, 23) << std::endl;
  OUT.clear();
  std::cout << "POP:9 "<< test.pop(OUT, 9) << std::endl;
  OUT.clear();
  std::cout << test.pop(OUT, 100) << std::endl;
}
