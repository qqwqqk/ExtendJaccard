#include <iostream>
#include <cstdlib>
#include "header/datageneration.h"
using namespace std;

int main(){
  string name = "test"; 
  int setnum = 4;
  int setmin = 20;
  int setmax = 30;
  int edgenum = 80;
  int probability = 80;

  generationBipartite(setnum, setmin, setmax, edgenum, probability);

  cout<<"generation network\t" << setnum <<'\t'<< setmin<<'\t' << setmax <<'\t'<< edgenum <<'\t'<< probability << "\tsuccess" << endl;

  return 0;
}