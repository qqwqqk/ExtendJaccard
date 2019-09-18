#include <iostream>
#include <cstdlib>
#include "header/datageneration.h"
using namespace std;

int main(){
  string name = "test"; 
  int setnum = 20;
  int setmin = 20;
  int setmax = 100;
  int edgenum = 1000;
  int probability = 90;

  generationBipartite(setnum, setmin, setmax, edgenum, probability);

  cout<<"generation network\t" << setnum <<'\t'<< setmin<<'\t' << setmax <<'\t'<< edgenum <<'\t'<< probability << "\tsuccess" << endl;

  return 0;
}