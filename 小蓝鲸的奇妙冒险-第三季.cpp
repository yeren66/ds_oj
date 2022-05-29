#include <iostream>
using namespace std;

#define maxV 10000001

int main(){
    int n, m, s, e;
    cin >> n >> m >> s >> e;
    int country[n][n];
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++){
            if(i == j){
                country[i][j] = 0;
            }
            else
                country[i][j] = maxV;
        }
    }
    bool S[n];     // S用来判断各点与起点之间是否有道路连通
    int record[n]; // record用来存放起点s距各点的距离
    int path[n];   // path用来记录各点到起点的路径
    for(int i = 0; i < m; i ++){
        int p;
        cin >> p;
        int temp[p];
        int value[p - 1];
        for(int j = 0; j < p; j ++){
            cin >> temp[j];
        }
        for(int j = 0; j < p - 1; j ++){
            cin >> value[j];
            country[temp[j]][temp[j + 1]] = value[j];
            country[temp[j + 1]][temp[j]] = value[j];
        }
    }
    // 采用Dijkstra算法
    for(int i = 0; i < n; i ++){
        record[i] = country[s][i]; // 用起点到各点的直接距离初始化record数组
        S[i] = false;
        if(i != s && record[i] < maxV)
            path[i] = s;           // 如果record有值则说明该点与起点有路径相连
        else
            path[i] = -1;          // 否则说明目前并无路径相连
    }
    S[s] = true;
    int min;
    for(int i = 0; i < n; i ++){
        min = maxV;
        int u = s;
        for(int j = 0; j < n; j ++){ // 从剩余节点中找出离目前连通集合最短的点u
            if(S[j] == false && record[j] < min){
                u = j; min = record[j];
            }
        }
        S[u] = true;
        for(int j = 0; j < n; j ++){ // 比较加入点u后剩余节点与集合间点最短距离有无变化，用最小值替换
            int w = country[u][j];
            if(S[j] == false && w < maxV && record[u] + w < record[j]){
                record[j] = record[u] + w;
                path[j] = u;
            }
        }
    }
    if(record[e] == maxV){
        cout << -1 << endl;
    }
    else{
        cout << record[e] << endl;
    }
}