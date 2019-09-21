#include <iostream>
#include <cstdlib>
#include "header/datageneration.h"
using namespace std;

int main(){
  int nodenum = 1000;
  int edgenum = 500;
  int setmin = 10;
  int setmax = 100;
  int probability = 10;

  cout << "please input nodenum edgenum setmin setmax and probability:" << endl;
  cin >> nodenum >> edgenum >> setmin >> setmax >> probability;

  generationBipartite(nodenum, edgenum, setmin, setmax, probability);

  cout<<"generation network\t" << nodenum <<'\t' << edgenum <<'\t'<< setmin<<'\t' << setmax <<'\t'<< probability << "\tsuccess" << endl;

  return 0;
}