#include <iostream>
#include <cstdlib>
#include "header/dataprocessing.h"
#include "header/extendjaccard.h"
using namespace std;

int main()
{
 string name = "Fakedata_20_30_50_800_96";
  char intercept = 'E'; 
  int number = 10000;
  char nodetype = 'A';

  const int termination = 20;            //最大迭代次数

  Bipartite BipartiteNetwork = getBipartite( name, intercept, number );
  Unipartite UnipartiteNetwork = getUnipartite( name, intercept, number, nodetype);

  // cout<<"init network"<<endl; exit(1);

  const vector<Edge> bipartiteEdgeCache = BipartiteNetwork.getEdges();        //计算EJ用二分网络原始边连接信息
  const vector<Edge> unipartiteEdgeCache = UnipartiteNetwork.getEdges();      //计算模块度用投影网络边连接信息
  
  map<int,Node> nodeCache = UnipartiteNetwork.getNodes();                     //社区合并过程记录节点信息
  vector<Link> linkCache;                                                     //社区合并过程记录连接信息
  map<string, double> linkUpdate;                                             //单次合并过程更新的连接

  //初始化 degree of nodeCache 与 bpi of linkCache
  vector<Edge> initCache = UnipartiteNetwork.getEdges();  
  for(int i=0; i<initCache.size(); i++){
    int node_a = initCache[i].getNodeA();
    int node_b = initCache[i].getNodeB();

    nodeCache[node_a].addDegree();
    nodeCache[node_b].addDegree();

    double gc = calculationExtendJaccard(bipartiteEdgeCache, nodetype, node_a, node_b);
    Link item = {community_a: node_a, community_b: node_b, extendjaccard:gc };
    linkCache.push_back(item);
  }

  int communityNumber = nodeCache.size();                                     //当前社区数目
  double modularity = calculationModularity(nodeCache, unipartiteEdgeCache);  //当前的模块度
  vector<double> modularityCache;                                             //模块度缓存
  modularityCache.push_back(modularity);

  printProgress(modularityCache.size() - 1, communityNumber, modularity);     //输出初始信息

  int iteration = 0;
  while(communityNumber > 1 && iteration < termination){
    linkUpdate.clear();
    map<int, int> mergeList = calculationMergeList(linkCache);
  
    //更新nodeCache
    for(map<int, Node>::iterator iter_node = nodeCache.begin(); iter_node != nodeCache.end(); iter_node++){
      int original_tag = iter_node->second.getCommunityTag();
      map<int,int>::iterator iter_cache = mergeList.find(original_tag);
      int current_tag = iter_cache != mergeList.end() ? iter_cache->second : original_tag;
      iter_node->second.addListTag(current_tag);
    }

    //更新linkCache
    for(int i=0; i<linkCache.size(); i++){
      map<int,int>::iterator iter_a = mergeList.find(linkCache[i].community_a);
      map<int,int>::iterator iter_b = mergeList.find(linkCache[i].community_b);

      if(iter_a == mergeList.end() && iter_b == mergeList.end()){ continue; } 
      
      const int key_a = iter_a == mergeList.end() ? linkCache[i].community_a : iter_a->second;
      const int key_b = iter_b == mergeList.end() ? linkCache[i].community_b : iter_b->second;
      const string key_link = key_a < key_b ? to_string(key_a)+"_"+to_string(key_b) : to_string(key_b)+"_"+to_string(key_a);
      map<string, double>::iterator iter_link = linkUpdate.find(key_link);

      if(iter_link != linkUpdate.end() || key_a == key_b){
        linkCache.erase(linkCache.begin() + i);
        i--;
      } else {
        double gc = calculationExtendJaccard(nodeCache, bipartiteEdgeCache, nodetype, key_a, key_b);
        linkCache[i].community_a = key_a; linkCache[i].community_b = key_b; linkCache[i].extendjaccard = gc;
        linkUpdate.insert(pair<string,double>(key_link, gc));
      }
    }

    //更新当前社区数量以及模块度相关
    communityNumber = calculationCommunityNumber(nodeCache);
    modularity = calculationModularity(nodeCache, unipartiteEdgeCache);
    if(modularity <= modularityCache.back()){ iteration++; } else { iteration = 0; }
    modularityCache.push_back(modularity);

    printProgress(modularityCache.size() - 1, communityNumber, modularity);     //输出合并进度
  }

  printCommunity(modularityCache, nodeCache, name, intercept, number, nodetype);

  return 0;
}