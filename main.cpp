#include <iostream>
#include <cstdlib>
#include "header/dataprocessing.h"
using namespace std;

int main()
{
  char intercept = 'E'; 
  int number = 10000;
  char nodetype = 'A';
  string name = "Fakedata_20_30_50_800_96";

  cout << "please input intercept type, max number, nodetype and filename:"<<endl;
  cin >> intercept >> number >> nodetype >> name;

  Bipartite BipartiteNetwork = getBipartite( name, intercept, number );
  Unipartite UnipartiteNetwork = getUnipartite( name, intercept, number, nodetype);

  cout << name << " network init" << endl;

  return 0;
}