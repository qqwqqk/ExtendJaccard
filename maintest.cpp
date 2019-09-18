#include <iostream>
#include <cstdlib>
#include "header/datageneration.h"
using namespace std;

int main(){
  string name = "test"; 
  int setnum = 25;
  int setmin = 30;
  int setmax = 50;
  int edgenum = 1000;
  int probability = 80;

  generationBipartite(setnum, setmin, setmax, edgenum, probability);

  cout<<"generation network\t" << setnum <<'\t'<< setmin<<'\t' << setmax <<'\t'<< edgenum <<'\t'<< probability << "\tsuccess" << endl;

  return 0;
}