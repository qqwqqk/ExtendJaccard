#pragma once
#include "type.h"
#include <iostream>
using namespace std;

Bipartite getBipartite(
  string name, 
  char intercept = 'A', 
  int number = -1
);

Bipartite pretreatmentBipartite(
  string name, 
  char intercept = 'A', 
  int number = -1
);

Unipartite getUnipartite(
  string name, 
  char intercept = 'A', 
  int number = -1,
  char nodetype = 'A'
);

Unipartite pretreatmentUnipartite(
  string name, 
  char intercept = 'A', 
  int number = -1, 
  char nodetype = 'A'
);
