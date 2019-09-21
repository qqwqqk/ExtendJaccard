#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
using namespace std;

double calculationNMI(vector<vector<int>> &X, vector<vector<int>> &Y);

/*
  Another commonly used evaluation criteria is Normalized Mutual Information(NMI).
  NMI is often used to detect the difference between the results of the division and the true partition of the network and calculate the correct rate.
  Danon et al.confirmed the reliability of NMI.
  For two different types of A and B, the NMI is defined as follows:
  $$
  NMI = \frac{-2 \sum_{i=1}^{C_{A}}\sum_{j=1}^{C_{B}} C_{ij}log(\frac{C_{ij} \cdot N}{C_{i} \cdot C_{j}}) }{\sum_{i=1}^{C_{A}}C_{ij} \cdot log(\frac{C_{i\cdot}}{N})+\sum_{j=1}^{C_{B}}C_{ij} \cdot log(\frac{C_{\cdot j}}{N})}
  $$
  where N is the number of nodes, C is a confusion matrix, the element Cij in the matrix indicates the number tha the nodes belonging to the community i in the A division also belong to communities j in the B division.
  CA(CB) is the number of communities in A(B) division, Ci·(C·j) is the sum of elements in matrix C.
  The greater the value of NMI, the more similarity between A and B division, when the NMI value is 1, it indicates that A and B are the same division of the network.

*/

// NMI = \frac{-2 \sum_{i}\sum_{j} N_{ij}log(\frac{N_{ij} \cdot N}{N_{i} \cdot N_{j}}) }{\sum_{i}N_{i \cdot}  log(\frac{N_{i\cdot}}{N})+\sum_{j}N_{\cdot j}  log(\frac{N_{\cdot j}}{N})}
