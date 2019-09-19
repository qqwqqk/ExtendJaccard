#include <iostream>
#include <cstdlib>
#include "header/nmi.h"
using namespace std;

int main(){
  vector<vector<int>> x = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10}};
	vector<vector<int>> y = {{1, 2, 3, 4 }, {5, 6, 7}, {8, 9, 10}};

  double res1 = calculationNMI(x,y);
  double res2 = calculationNMI(y,x);

  cout << res1 << endl;
  cout << res2 << endl;

  return 0;
}