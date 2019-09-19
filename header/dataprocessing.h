#pragma once
#include "type.h"
#include <iostream>
using namespace std;

Bipartite getBipartite(
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

vector<vector<int>> getCommunityResult(
  string filename = " "
);

void printProgress(
  int iterationNumber = 0, 
  int communityNumber = 0, 
  double modularity = 0.0
);

void printCommunity(
  vector<double> modularityCache,
  map<int,Node> nodeCache,
  string name, 
  char intercept = 'A', 
  int number = -1, 
  char nodetype = 'A'
);