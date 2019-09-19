#pragma once
#include "type.h"
#include <iostream>
using namespace std;

int random(int min = 0, int max = 0);

vector<int> randomlist(int min = 0, int max = 0, int length = 0);

bool generationBipartite(
  int nodenum = 1,
  int edgenum = 1,
  int setmin = 1,
  int setmax = 1,
  int probability = 1
);
