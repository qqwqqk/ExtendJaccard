#include <iostream>
#include <cstdlib>
#include "header/datageneration.h"
using namespace std;

int main(){
  int nodenum = 800;
  int edgenum = 800;
  int setmin = 30;
  int setmax = 50;
  int probability = 10;

  cout << "please input nodenum edgenum setmin setmax and probability:" << endl;
  cin >> nodenum >> edgenum >> setmin >> setmax >> probability;

  generationBipartite(nodenum, edgenum, setmin, setmax, probability);

  cout<<"generation network\t" << nodenum <<'\t' << edgenum <<'\t'<< setmin<<'\t' << setmax <<'\t'<< probability << "\tsuccess" << endl;

  return 0;
}