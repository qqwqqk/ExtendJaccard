#include "../header/dataprocessing.h"
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <set>
using namespace std;

Bipartite getBipartite(string name, char intercept, int number ){
  const string split = "_";
  const string _intercept(1,intercept);
  const string _number = number > 0 ? to_string(number) : "0";
  const string netpath = "dataset/netdata/" + name + split + _intercept + _number + ".txt";

  ifstream infile;
  string line;
  const char dilem = ' ';
  vector<Edge> edgeCache;
  map<int,int> nodeCacheA, nodeCacheB;
  map<int,int>::iterator iter;

  //按行读取TXT文件，并解析
  infile.open(netpath, ios::in);
  if(!infile){
    cout<< "read bipartite file error in " << netpath <<endl;
    exit(0);
  }

  while(!infile.eof()){
    getline(infile, line);
    int linePos = 0;
    int lineSize = 0;
    string cache;
    vector<int> array;

    for(int i = 0 ; i < line.size(); i++){
      if(line[i] == dilem){
        lineSize = i - linePos;
        cache = line.substr(linePos, lineSize);
        array.push_back(stoi(cache));
        linePos = i+1;
      }
    }
    cache = line.substr(linePos, line.size() - linePos);
    if(cache.size()>0){ array.push_back(stoi(cache)); }

    //记录两人种类型节点数量并将解析的内容写入边对象缓存
    if(array.size() > 1){
      iter = nodeCacheA.find(array[0]);
      if(iter == nodeCacheA.end()){
        pair<int,int> value(array[0],0);
        nodeCacheA.insert(value);
      }
      iter = nodeCacheB.find(array[1]);
      if(iter == nodeCacheB.end()){
        pair<int,int> value(array[1],0);
        nodeCacheB.insert(value);
      }
      edgeCache.push_back(Edge(array[0],array[1]));
    }
  }
  infile.close();

  //验证解析情况
  //cout << "NodeCacheA\t" << nodeCacheA.size() << endl;
  //cout << "NodeCacheB\t" << nodeCacheB.size() << endl;
  //cout << "EdgeCache\t" << edgeCache.size() << endl << endl;

  //写入Bipartite

  Bipartite Network(name);
  for(int i=0; i<edgeCache.size(); i++){
    Network.addEdge(edgeCache[i]);
  }
  for(iter = nodeCacheA.begin(); iter != nodeCacheA.end(); iter++){
    Network.addNodeA(Node(iter->first));
  }
  for(iter = nodeCacheB.begin(); iter != nodeCacheB.end(); iter++){
    Network.addNodeB(Node(iter->first));
  }

  return Network;
}

Unipartite getUnipartite(string name, char intercept, int number , char nodetype){
  const string split = "_";
  const string _intercept(1,intercept);
  const string _number = number > 0 ? to_string(number) : "0";
  const string _nodetype(1,nodetype);
  const string unipartitepath = "dataset/netdata/" + name + "_Single" + _nodetype + split + _intercept + _number +    ".txt";

  ifstream infile;
  string line;
  const char dilem = ' ';
  vector<Edge> edgeCache;
  map<int,int> nodeCache;
  map<int,int>::iterator iter;

  //按行读取TXT文件，并解析
  infile.open(unipartitepath, ios::in);
  if(!infile){ 
    cout<< "read unipartite file error in "<< unipartitepath <<endl;
    exit(0);
  }

  while(!infile.eof()){
    getline(infile, line);
    int linePos = 0;
    int lineSize = 0;
    string cache;
    vector<int> array;

    for(int i = 0 ; i < line.size(); i++){
      if(line[i] == dilem){
        lineSize = i - linePos;
        cache = line.substr(linePos, lineSize);
        array.push_back(stoi(cache));
        linePos = i+1;
      }
    }
    cache = line.substr(linePos, line.size() - linePos);
    if(cache.size()>0){ array.push_back(stoi(cache)); }

    //记录两人种类型节点数量并将解析的内容写入边对象缓存
    if(array.size() > 1){
      iter = nodeCache.find(array[0]);
      if(iter == nodeCache.end()){
        pair<int,int> value(array[0],0);
        nodeCache.insert(value);
      }
      iter = nodeCache.find(array[1]);
      if(iter == nodeCache.end()){
        pair<int,int> value(array[1],0);
        nodeCache.insert(value);
      }
      edgeCache.push_back(Edge(array[0],array[1]));
    }
  }
  infile.close();

  //写入Unipartite

  Unipartite unipartiteNetwork(name);
  for(int i=0; i<edgeCache.size(); i++){
    unipartiteNetwork.addEdge(edgeCache[i]);
  }
  for(iter = nodeCache.begin(); iter != nodeCache.end(); iter++){
    unipartiteNetwork.addNode(Node(iter->first));
  }

  return unipartiteNetwork;
}


void printProgress(int iterationNumber, int communityNumber, double modularity){
  cout << "IterationNumber:" << setw(4) << iterationNumber << '\t';
  cout << "CommunityNumber:" << setw(4) << communityNumber << '\t';
  cout << "Modularity:" << setw(9) << setiosflags(ios::fixed) << setprecision(5) << modularity << '\t' << endl;
}

void printCommunity(vector<double> modularityCache, map<int,Node> nodeCache,string name, char intercept, int number, char nodetype){
  const string split = "_";
  const string _intercept(1, intercept);
  const string _number = number > 0 ? to_string(number) : "0";
  const string _nodetype(1, nodetype);
  const string resultpath = "dataset/labeldata/" + name + "_Result" + _nodetype + split + _intercept + _number + ".txt";

  set<int> communityCache;
  //写入Bipartite，并输出到TXT文件
  ofstream outfile( resultpath , ios::out);
  if(!outfile){ cout<<"file open error!"<<endl; exit(1); } 

  vector<double>::iterator modularityMax = std::max_element(begin(modularityCache), end(modularityCache));
  int modularityIndex = distance(begin(modularityCache), modularityMax);

  for(map<int, Node>::iterator iter_node = nodeCache.begin(); iter_node != nodeCache.end(); iter_node++){
    int communityTag = iter_node->second.getCommunityTag(modularityIndex);
    communityCache.insert(communityTag);
    outfile << iter_node->first << '\t' << communityTag << '\n';
  }

  outfile.close();

  cout << "\nmodularityMax:\t" << *modularityMax << "\tcommunityNumber:\t" << communityCache.size() << endl;
}
