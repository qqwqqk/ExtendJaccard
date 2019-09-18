#include <iostream>
#include <cstdlib>
#include "header/datageneration.h"
using namespace std;

int main(){
  string name = "test"; 
  int setnum = 4;
  int setsize = 20;
  int edgenum = 60;
  int probability = 80;

  generationBipartite(setnum, setsize, edgenum, probability);

  cout<<"generation network\t" << setnum <<'\t'<< setsize<<'\t'<< edgenum <<'\t'<< probability << "\tsuccess" << endl;

  return 0;
}