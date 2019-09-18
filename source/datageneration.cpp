#include "../header/datageneration.h"
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <set>
using namespace std;

uint32_t xor128(void) {
  static uint32_t x = 123456789;
  static uint32_t y = 362436069;
  static uint32_t z = 521288629;
  static uint32_t w = 88675123;
  uint32_t t;
  t = x ^ (x << 11);
  x = y; y = z; z = w;
  return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
}

int random(int min, int max){
  int num = xor128() % (max - min + 1) + min;
  return num;
};

int randomsize(){
  int size = 0;
  int seed = random(0, 9);
  if(seed < 5 ){ size = 2;}
  else if(seed < 8){ size = 3; }
  else if(seed < 9){ size = 4; }
  else {size = 5;}
  return size;
}

vector<int> randomlist(int min, int max, int size){
  set<int> cache;
  while(cache.size()<size){
    cache.insert(random(min,max));
  }
  vector<int> result;
  for(set<int>::iterator iter = cache.begin(); iter!=cache.end(); iter++){
    result.push_back(*iter);
  }
  return result;
}

bool generationBipartite(int setnum, int setmin, int setmax, int edgenum, int probability){
  vector<vector<int>> networks;
  int count = 0;
  for(int i=0 ; i < setnum; i++){
    vector<int> lists;
    int setsize = random(setmin, setmax);
    for(int j=0; j < setsize; j++){
      lists.push_back( count++ );
    }
    networks.push_back(lists);
  }

  vector<vector<int>> edges;
  for(int i=0; i<edgenum; i++){
    int size = randomsize();
    int poss = random(1, 100);

    set<int> cache;
    if(poss < probability){
      int base = random(0, setnum-1);
      int length = networks[base].size();
      while(cache.size()<size){
        int pos = random(0, length - 1);
        cache.insert(networks[base][pos]); 
      }
    } else {
      while(cache.size()<size){
        int item = random(0, count - 1);
        cache.insert(item); 
      }
    }

    vector<int> lists;
    for(set<int>::iterator iter = cache.begin(); iter!=cache.end(); iter++){
      lists.push_back(*iter);
    }

    edges.push_back(lists);
  }

  const string split = "_";
  const string str = to_string(setnum) +split+ to_string(setmin)+split+ to_string(setmax)+split + to_string(edgenum)+split + to_string(probability);
  const string fackpath = "dataset/metadata/Fakedata_" + str + ".txt";
  const string labelpath = "dataset/tagdata/Fakedata_label_" + str + ".txt";
  int index = 0;

  ofstream outfile1(fackpath , ios::out);
  if(!outfile1){ cout << fackpath <<" open error!"<<endl; exit(1); } 
  index = 0;
  for(int i=0; i<edgenum; i++){
    vector<int> cache = edges[i];
    for(int j=0; j<edges[i].size(); j++){
      for(int k=j+1; k<edges[i].size(); k++){
        outfile1 << ++index << ',' << edges[i][j] << ',' << edges[i][k] << '\n';
      }
    }
  }
  outfile1.close();

  ofstream outfile2(labelpath , ios::out);
  if(!outfile2){ cout << labelpath <<" open error!"<<endl; exit(1); } 
  index = 0;
  for(int i=0 ; i < setnum; i++){
    for(vector<int>::iterator iter = networks[i].begin(); iter != networks[i].end(); iter++){
      outfile2 << *iter << ' ' << i << '\n';
    }
  }
  outfile2.close();

  return false;
}