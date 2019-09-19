#include "../header/nmi.h"


//计算信息熵
double getInformationEntropy(vector<int> &x, int nodenumber){
  const double p1 = 1.0 * x.size() / nodenumber;
  const double p0 = 1 - p1;
  double h1 = p1 > 0 ? -1 * p1 * log2(p1) : 0;
  double h0 = p0 > 0 ? -1 * p0 * log2(p0) : 0;
  return h0 + h1;
}

//计算联合熵
double getJointEntropy(vector<int> &x, vector<int> &y, int nodenumber){
  set<int> sub_x, sub_y, sub_xy;
  for(int i=0; i<x.size(); i++){
    sub_x.insert(x[i]); sub_xy.insert(x[i]);
  }
  for(int i=0; i<y.size(); i++){
    sub_y.insert(y[i]); sub_xy.insert(y[i]);
  }

  double p00 = 1.0 * (nodenumber - sub_xy.size()) / nodenumber;
  double p10 = 1.0 * (sub_xy.size() - sub_y.size()) / nodenumber;
  double p01 = 1.0 * (sub_xy.size() - sub_x.size()) / nodenumber;
  double p11 = 1.0 * (sub_xy.size() - p10 - p01) / nodenumber;

  double h11 = p11 > 0 ? -1 * p11 * log2(p11) : 0;
  double h10 = p10 > 0 ? -1 * p10 * log2(p10) : 0;
  double h01 = p01 > 0 ? -1 * p01 * log2(p01) : 0;
  double h00 = p00 > 0 ? -1 * p00 * log2(p00) : 0;

  if(h11 + h00 >= h01 + h10){
    return h00 + h01 + h10 + h11;
  } else {
    return getInformationEntropy(x, nodenumber) + getInformationEntropy(y, nodenumber);
  }
}

//计算子条件熵
double getSubConditionEntropy(vector<int> &x, vector<int> &y, int nodenumber){
  return getJointEntropy(x,y,nodenumber) - getInformationEntropy(y, nodenumber);
}

//计算最好子条件熵
double getBestSubConditionEntropy(vector<int> &x, vector<vector<int>> &Y, int nodenumber){
  double result = getSubConditionEntropy(x,Y[0],nodenumber);
  for(int i=1; i<Y.size(); i++){
    double cache = getSubConditionEntropy(x,Y[i],nodenumber);
    result = result < cache ? result : cache;
  }
  return result;
}

//计算标准子条件熵
double getStandardSubConditionalEntropy(vector<int> &x, vector<vector<int>> &Y, int nodenumber){
  double source = getBestSubConditionEntropy(x,Y,nodenumber);
  double factor = getInformationEntropy(x, nodenumber);
  return source / factor;
}

//计算条件熵
double getConditionEntropy(vector<vector<int>> &X, vector<vector<int>> &Y, int nodenumber){
  double result = 0;
  for(int i=0; i<X.size(); i++){
    result += getStandardSubConditionalEntropy(X[i],Y,nodenumber);
  }
  return result;
}

//计算标准条件熵
double getStandardConditionEntropy(vector<vector<int>> &X, vector<vector<int>> &Y, int nodenumber){
  double result = 0;
  for(int i=0; i<X.size(); i++){
    result += getBestSubConditionEntropy(X[i],Y,nodenumber);
  }
  return result / X.size();
}

//计算不重复总节点数量
int getNodeNumber(vector<vector<int>> &x, vector<vector<int>> &y){
  set<int> nodeCount;
  for(int i=0; i<x.size(); i++){
    for(vector<int>::iterator iter = x[i].begin(); iter!=x[i].end(); iter++){
      nodeCount.insert(*iter);
    }
  }
  for(int i=0; i<y.size(); i++){
    for(vector<int>::iterator iter = y[i].begin(); iter!=y[i].end(); iter++){
      nodeCount.insert(*iter);
    }
  }
  return nodeCount.size();
}

//计算标准互信息
double calculationNMI(vector<vector<int>> &x, vector<vector<int>> &y){
  double result = 0;
  if(x.size() == 0 || y.size() == 0){ return result; }
  int nodenumber = getNodeNumber(x,y);

  result = 1 - 0.5 * (getStandardConditionEntropy(x,y,nodenumber) + getStandardConditionEntropy(y,x,nodenumber));

  return result;
}