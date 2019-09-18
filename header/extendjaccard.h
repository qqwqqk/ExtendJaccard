#pragma once
#include "type.h"
#include <iostream>
using namespace std;

double calculationExtendJaccard(vector<Edge> edges, char nodetype, int item_i = 0, int item_j = 0);

double calculationExtendJaccard(map<int,Node> nodes, vector<Edge> edges, char nodetype, int item_i = 0, int item_j = 0);

double calculationModularity(map<int,Node> nodes, vector<Edge> edges);

map<int, int> calculationMergeList(vector<Link> links);

int calculationCommunityNumber(map<int,Node> nodes);
