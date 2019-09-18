#include <iostream>
#include <cstdlib>
#include "header/dataprocessing.h"
using namespace std;

int main()
{
 string name = "Fakedata_4_20_30_80_80";
  char intercept = 'E'; 
  int number = 10000;
  char nodetype = 'A';

  Bipartite BipartiteNetwork = getBipartite( name, intercept, number );
  Unipartite UnipartiteNetwork = getUnipartite( name, intercept, number, nodetype);

  cout << name << " network init" << endl;

  return 0;
}