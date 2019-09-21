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
    cout<< "init bipartite from meta data" <<endl;
    pretreatmentBipartite(name, intercept, number);
    infile.open(netpath, ios::in);
  } else {
    cout<< "read bipartite file from bipartite network" <<endl;
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

Bipartite pretreatmentBipartite(string name, char intercept, int number ){
  const string split = "_";
  const string _intercept(1,intercept);
  const string _number = number > 0 ? to_string(number) : "0";
  const string inputpath = "dataset/metadata/" + name + ".txt";
  const string outputpath = "dataset/netdata/" + name + split + _intercept + _number + ".txt";

  ifstream infile;
  string line;
  const char dilem = ',';
  vector<Edge> edgeCache;
  map<int,int> nodeCacheA, nodeCacheB;
  map<int,int>::iterator iter;

  //按行读取TXT文件，并解析
  infile.open(inputpath, ios::in);
  if(!infile){ cout<< "can't find meta file! "<< inputpath <<endl; exit(1); }
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
    if(array.size() > 2){
      iter = nodeCacheA.find(array[1]);
      if(iter == nodeCacheA.end()){
        pair<int,int> value(array[1],0);
        nodeCacheA.insert(value);
      }
      iter = nodeCacheB.find(array[2]);
      if(iter == nodeCacheB.end()){
        pair<int,int> value(array[2],0);
        nodeCacheB.insert(value);
      }
      edgeCache.push_back(Edge(array[1],array[2]));
    }
  }
  infile.close();

  //验证解析情况
  //cout << "NodeCacheA\t" << nodeCacheA.size() << endl;
  //cout << "NodeCacheB\t" << nodeCacheB.size() << endl;
  //cout << "EdgeCache\t" << edgeCache.size() << endl << endl;

  //截取子网络
  if(number >= 0){
    //截取边信息
    switch(intercept){    
      case 'A':
        if(nodeCacheA.size() <= number){
          break;
        } else {
          for(int i=0; i < edgeCache.size();){
            if(edgeCache[i].getNodeA() > number){
              edgeCache.erase(edgeCache.begin()+i);
            } else {
              i++;
            }
          }
          break;
        }
      case 'B':
        if(nodeCacheB.size() <= number){
          break;
        } else {
          for(int i=0; i < edgeCache.size();){
            if(edgeCache[i].getNodeB() > number){
              edgeCache.erase(edgeCache.begin()+i);
            } else {
              i++;
            }
          }
          break;
        }
      case 'E':
        if(edgeCache.size() <= number){
          break;
        } else {
          edgeCache.erase(edgeCache.begin()+number,edgeCache.end());
          break;
        }
      default:
        cout << "Illegal interception input" << endl;
        exit(0);
    }
    //截取点信息
    nodeCacheA.clear();
    nodeCacheB.clear();
    for(int i=0;i<edgeCache.size();i++){
      iter = nodeCacheA.find(edgeCache[i].getNodeA());
      if(iter == nodeCacheA.end()){
        pair<int,int> value(edgeCache[i].getNodeA(),0);
        nodeCacheA.insert(value);
      }
      iter = nodeCacheB.find(edgeCache[i].getNodeB());
      if(iter == nodeCacheB.end()){
        pair<int,int> value(edgeCache[i].getNodeB(),0);
        nodeCacheB.insert(value);
      }
    }
  }

  //验证截取情况
  //cout << "NodeCacheA\t" << nodeCacheA.size() << endl;
  //cout << "NodeCacheB\t" << nodeCacheB.size() << endl;
  //cout << "EdgeCache\t" << edgeCache.size() << endl << endl;

  //连通性检测，划分全连通子图
  if(true){
    struct SubBipartiteCache{
      vector<Edge> subEdges;
      map<int,int> subNodeA, subNodeB;
    };

    vector<SubBipartiteCache> Networks;
    int index = 0, tag=0, maxA=0, maxB=0, maxE=0;

    //将全部子图存入subCache
    while(!nodeCacheA.empty() && !nodeCacheB.empty()){
      SubBipartiteCache subCache;

      iter = nodeCacheA.begin();
      subCache.subNodeA.insert(pair<int,int> (iter->first, 0));
      nodeCacheA.erase(iter);
      int length = 0;
      while(1){
        length = subCache.subNodeB.size();
        //遍历边集合，将与A类型节点有连接的所有B类型节点转移存储到子图B类节点集合，将连接的边转移存储到子图的边集合
        for(int i=0; i<edgeCache.size();){
          iter = subCache.subNodeA.find(edgeCache[i].getNodeA());
          if(iter != subCache.subNodeA.end()){
            //在子图类型B节点集合中添加
            iter = subCache.subNodeB.find(edgeCache[i].getNodeB());
            if(iter == subCache.subNodeB.end()){ subCache.subNodeB.insert(pair<int, int> (edgeCache[i].getNodeB(), 0)); }
            //删除原类型B节点集合中对应数据
            iter = nodeCacheB.find(edgeCache[i].getNodeB());
            if(iter != nodeCacheB.end()){ nodeCacheB.erase(iter); }
            //转移边集合中对应数据到子图边集合
            subCache.subEdges.push_back(edgeCache[i]);
            edgeCache.erase(edgeCache.begin()+i);
          } else {
            i++;
          }
        }

        //如果已经不存在与A类型相连的B类型节点，退出循环
        if(subCache.subNodeB.size() == length ){ break; }

        //遍历边集合，将与B类型节点有连接的所有B类型节点转移存储到子图A类节点集合，将连接的边转移存储到子图的边集合
        for(int i=0; i<edgeCache.size();){
          iter = subCache.subNodeB.find(edgeCache[i].getNodeB());
          if(iter != subCache.subNodeB.end()){
            //在子图类型A节点集合中添加
            iter = subCache.subNodeA.find(edgeCache[i].getNodeA());
            if(iter == subCache.subNodeA.end()){ subCache.subNodeA.insert(pair<int, int> (edgeCache[i].getNodeA(), 0)); }
            //删除原类型A节点集合中对应数据
            iter = nodeCacheA.find(edgeCache[i].getNodeA());
            if(iter != nodeCacheA.end()){ nodeCacheA.erase(iter); }
            //转移边集合中对应数据到子图边集合
            subCache.subEdges.push_back(edgeCache[i]);
            edgeCache.erase(edgeCache.begin()+i);
          } else {
            i++;
          }
        }
      }

      maxA = maxA > subCache.subNodeA.size() ? maxA : subCache.subNodeA.size();
      maxB = maxB > subCache.subNodeB.size() ? maxB : subCache.subNodeB.size();
      maxE = maxE > subCache.subEdges.size() ? maxE : subCache.subEdges.size();

      Networks.push_back(subCache);
    }

    //寻找最大全连通子图的下标
    switch(intercept){
      case 'A':
        for(int i=0; i<Networks.size(); i++){
          if(Networks[i].subNodeA.size() == maxA){
            index = i; break;
          }
        }
        break;
      case 'B':
        for(int i=0; i<Networks.size(); i++){
          if(Networks[i].subNodeB.size() == maxB){
            index = i; break;
          }
        }
        break;
      case 'E':
        for(int i=0; i<Networks.size(); i++){
          if(Networks[i].subEdges.size() == maxE){
            index = i; break;
          }
        }
        break;
      default:
        cout << "Illegal interception input" << endl;
        exit(0);
    }

    //将最大全连通子图写入缓存
    edgeCache.clear();
    nodeCacheA.clear();
    nodeCacheB.clear();
    edgeCache = Networks[index].subEdges;
    iter = Networks[index].subNodeA.begin();
    tag = 1;
    while(iter != Networks[index].subNodeA.end()){
      nodeCacheA.insert(pair<int, int> (iter->first, tag));
      iter++; tag++;         
    }
    iter = Networks[index].subNodeB.begin();
    tag = 1;
    while(iter != Networks[index].subNodeB.end()){
      nodeCacheB.insert(pair<int, int> (iter->first, tag));
      iter++; tag++;         
    }
  }

  //验证连通情况
  cout << "NodeCacheA\t" << nodeCacheA.size() << endl;
  cout << "NodeCacheB\t" << nodeCacheB.size() << endl;
  cout << "EdgeCache\t" << edgeCache.size() << endl << endl;

  //重新排序
  if(false){
    int reSortA, reSortB;
    for(int i=0; i<edgeCache.size(); i++){
      reSortA = nodeCacheA[edgeCache[i].getNodeA()];
      reSortB = nodeCacheB[edgeCache[i].getNodeB()];
      edgeCache[i] = Edge(reSortA,reSortB);
    }
  }

  //验证排序情况
  //cout << "NodeCacheA\t" << nodeCacheA.size() << endl;
  //cout << "NodeCacheB\t" << nodeCacheB.size() << endl;
  //cout << "EdgeCache\t" << edgeCache.size() << endl << endl;


  //写入Bipartite，并输出到TXT文件
  ofstream outfile( outputpath , ios::out);
  if(!outfile){ cout<<"file open error!"<<endl; exit(1); } 

  Bipartite Network(name);
  for(int i=0; i<edgeCache.size(); i++){
    Network.addEdge(edgeCache[i]);
    outfile << edgeCache[i].getNodeA() << ' ' << edgeCache[i].getNodeB() << '\n';
  }
  for(iter = nodeCacheA.begin(); iter != nodeCacheA.end(); iter++){
    Network.addNodeA(Node(iter->second));
  }
  for(iter = nodeCacheB.begin(); iter != nodeCacheB.end(); iter++){
    Network.addNodeB(Node(iter->second));
  }

  outfile.close();

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
    cout << "init unipartite from bipartite data" << endl;
    pretreatmentUnipartite(name, intercept, number, nodetype);
    infile.open(unipartitepath, ios::in);
  } else {
    cout<< "read unipartite file from unipartite network" <<endl;
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

Unipartite pretreatmentUnipartite(string name, char intercept, int number , char nodetype){
  const string split = "_";
  const string _intercept(1,intercept);
  const string _number = number > 0 ? to_string(number) : "0";
  const string _nodetype(1,nodetype);
  const string unipartitepath = "dataset/netdata/" + name + "_Single" + _nodetype + split + _intercept + _number +    ".txt";

  Bipartite bipartiteNetwork = getBipartite(name, intercept, number);
  map<int,Node> bipartiteNodesA = bipartiteNetwork.getNodesA();
  map<int,Node> bipartiteNodesB = bipartiteNetwork.getNodesB();
  vector<Edge> bipartiteEdges = bipartiteNetwork.getEdges();

  vector<int> nodeCache;
  map<int, Node> nodeMap;
  map<string, Edge> edgeMap;

  switch(nodetype){
    case 'A':
      //遍历B类型节点
      for(map<int,Node>::iterator iter = bipartiteNodesB.begin(); iter != bipartiteNodesB.end(); iter++){
        int nodeID = iter->first;
        nodeCache.clear();
        //遍历边节点，将所有与B类型节点相连的A类型节点写入nodeCache缓存;将未存入nodeMap的节点存入nodeMap
        for(int i=0; i<bipartiteEdges.size(); i++){
          if(nodeID == bipartiteEdges[i].getNodeB()){
            nodeCache.push_back(bipartiteEdges[i].getNodeA());

            map<int, Node>::iterator nodeIter = nodeMap.find(nodeID);
            if(nodeIter == nodeMap.end()){
              nodeMap.insert(pair<int, Node> (nodeID, Node(nodeID)));
            }
          }
        }
        //遍历nodeCache,将未保存的edge写入edgeMap
        for(int i=0; i<nodeCache.size(); i++){
          for(int j=i+1; j<nodeCache.size(); j++){
            int node_1, node_2;
            if(nodeCache[i] < nodeCache[j]){ node_1 = nodeCache[i]; node_2 = nodeCache[j]; } 
            else { node_1 = nodeCache[j]; node_2 = nodeCache[i]; }
            string edgeKey =  to_string(node_1) + '-' + to_string(node_2);

            map<string, Edge>::iterator edgeIter = edgeMap.find(edgeKey);
            if(edgeIter == edgeMap.end()){ 
              edgeMap.insert(pair<string, Edge> (edgeKey, Edge(node_1, node_2)));
            }
          }
        }
      }
      break;
    case 'B':
      //遍历A类型节点
      for(map<int,Node>::iterator iter = bipartiteNodesA.begin(); iter != bipartiteNodesA.end(); iter++){
        int nodeID = iter->first;
        nodeCache.clear();
        //遍历边节点，将所有与A类型节点相连的B类型节点写入nodeCache缓存;将未存入nodeMap的节点存入nodeMap
        for(int i=0; i<bipartiteEdges.size(); i++){
          if(nodeID == bipartiteEdges[i].getNodeA()){
            nodeCache.push_back(bipartiteEdges[i].getNodeB());

            map<int, Node>::iterator nodeIter = nodeMap.find(nodeID);
            if(nodeIter == nodeMap.end()){
              nodeMap.insert(pair<int, Node> (nodeID, Node(nodeID)));
            }
          }
        }
        //遍历nodeCache,将未保存的edge写入edgeMap
        for(int i=0; i<nodeCache.size(); i++){
          for(int j=i+1; j<nodeCache.size(); j++){
            int node_1, node_2;
            if(nodeCache[i] < nodeCache[j]){ node_1 = nodeCache[i]; node_2 = nodeCache[j]; } 
            else { node_1 = nodeCache[j]; node_2 = nodeCache[i]; }
            string edgeKey =  to_string(node_1) + '-' + to_string(node_2);

            map<string, Edge>::iterator edgeIter = edgeMap.find(edgeKey);
            if(edgeIter == edgeMap.end()){ 
              edgeMap.insert(pair<string, Edge> (edgeKey, Edge(node_1, node_2)));
            }
          }
        }
      }
      break;
    default:
      cout<< "Invalid node type input " <<endl;
      exit(0);
  }

  //写入Bipartite，并输出到TXT文件
  ofstream outfile( unipartitepath , ios::out);
  if(!outfile){ cout<<"file open error!"<<endl; exit(1); } 

  Unipartite unipartiteNetwork( name + "_Single" + _nodetype );
  for(map<int, Node>::iterator nodeIter = nodeMap.begin(); nodeIter != nodeMap.end(); nodeIter++){
    unipartiteNetwork.addNode(nodeIter->second);
  }
  for(map<string, Edge>::iterator edgeIter = edgeMap.begin(); edgeIter != edgeMap.end(); edgeIter++){
    unipartiteNetwork.addEdge(edgeIter->second);
    outfile << edgeIter->second.getNodeA() << ' ' << edgeIter->second.getNodeB() << '\n';
  }

  outfile.close();

  return unipartiteNetwork;
}
