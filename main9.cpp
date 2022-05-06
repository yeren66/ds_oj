#include <iostream>
using namespace std;

struct DisjointSet{
    int n;
    int *ds;
    int *ranks;

    DisjointSet(int n){
        this->n = n;
        this->ds = new int[n];
        this->ranks = new int[n];
        for(int i = 0; i < n; i ++){
            ds[i] = i;
            ranks[i] = 0;
        }
    }

    int find_root(int x) {
        return x==ds[x]?x:ds[x]=find_root(ds[x]);
    }

    void union_set(int x, int y) {
        int x_root=find_root(x);
        int y_root=find_root(y);
        if (x_root!=y_root) {
            if (ranks[x_root]>ranks[y_root]) {
                ds[y_root]=x_root;
            } else if (ranks[x_root]<ranks[y_root]) {
                ds[x_root]=y_root;
            } else {
                ds[x_root]=y_root;
                ranks[y_root]++;
            }
        }
    }

    bool relation(int x, int y) {
        return find_root(x)==find_root(y);
    }

};


int main(){
    int n, k;
    cin >> n >> k;
    DisjointSet *set = new DisjointSet(n);
    int record[n];
    for(int i = 0; i < n; i ++){
        record[i] = -1;
    }
    int sum = 0;
    for(int i = 0; i < k; i ++){
        int x, y;
        cin >> x >> y;
        x --;
        y --;
        if(x == y){ // condition 3
            sum ++;
            continue;
        }
        if(x > n - 1 || y > n - 1){ // condition 2
            sum ++;
            continue;
        }
        // condition 1
        if(!set->relation(x, y)){
            if(record[x] == -1 && record[y] == -1){ // never meet x and y before
                record[x] = 1;
                record[y] = 0;	
            }
            else if(record[x] != -1 && record[y] == -1){ // meet x only
                record[y] = (record[x] + 2) % 3;
            }
            else if(record[y] != -1 && record[x] == -1){ // meet y only
                record[x] = (record[y] + 1) % 3;
            }
            else{ // meet x and y both before, change y(x also right)
                int root = set->find_root(y);
                int gap = record[y] - (record[x] + 2) % 3;
                for(int i = 0; i < n; i ++){ // 这里复杂度太高，不用并查集，换双向链表可以降复杂度，即可解决问题
                    if(set->find_root(i) == root){
                        record[i] = (record[i] - gap) % 3;
                        if(record[i] < 0) record[i] += 3;
                    }
                }
            }
            set->union_set(x, y);
        }
        else{ 
            if(record[y] != (record[x] + 2) % 3){
                sum ++;
            }
        }
    }
    cout << sum << endl;
}


//----------------------------------------------------------------B
// #include <map>

// template <class T>
// struct _DISJOINTSET {
//     T _st;//起点
//     T _ed;//终点
//     map<T, T> ds;//并查集
//     map<T, int> ranks;
 
//     _DISJOINTSET() : _st(0), _ed(0) {}
//     _DISJOINTSET(T st, T ed) {
//         init(st, ed);
//     }
 
//     /*
//     st 表示起点
//     ed 表示终点
//     */

//     void init(T st, T ed) {
//         if (ed<st) {
//             return;
//         }
//         for (T i=st; i<=ed; i++) {
//             ds[i]=i;
//             ranks[i]=0;
//         }
//         _st = st;
//         _ed = ed;
//     }
 
//     //查找x的父亲
//     T find_root(T x) {
//         return x==ds[x]?x:ds[x]=find_root(ds[x]);
//     }
 
//     //建立关系
//     void union_set(T x, T y) {
//         T x_root=find_root(x);
//         T y_root=find_root(y);
//         if (x_root!=y_root) {
//             if (ranks[x_root]>ranks[y_root]) {
//                 ds[y_root]=x_root;
//             } else if (ranks[x_root]<ranks[y_root]) {
//                 ds[x_root]=y_root;
//             } else {
//                 ds[x_root]=y_root;
//                 ranks[y_root]++;
//             }
//         }
//     }
 
//     //查找x和y是否在同一个父亲
//     bool relation(T x, T y) {
//         return find_root(x)==find_root(y);
//     }
// };


// bool find(map<int, int> reflect, int *arr, int n, int a, int b, int *result){
//     _DISJOINTSET<int> *set0 = new _DISJOINTSET<int>(0, n);
//     _DISJOINTSET<int> *set1 = new _DISJOINTSET<int>(0, n);
//     map<int, int>::iterator it;
//     for(int i = 0; i < n; i ++){
//         int pa = a - arr[i];
//         int pb = b - arr[i];
//         it = reflect.find(pa);
//         if(it != reflect.end()){
//             set0->union_set(i, it->second);
//         }
//         it = reflect.find(pb);
//         if(it != reflect.end()){
//             set1->union_set(i, it->second);
//         }
//     }
//     int flag = 1;
//     while(flag == 1){
//         flag = 0;
//         for(int i = 0; i < n; i ++){
//             if(result[i] != -1)
//                 continue;
//             if((set0->ds[i] != i || set0->ranks[i] != 0) && (set1->ds[i] == i && set1->ranks[i] == 0)){
//                 result[i] = 0;
//                 int another = reflect.find(a - arr[i])->second;
//                 result[another] = 0;
//                 it = reflect.find(b - arr[another]);
//                 if(it != reflect.end()){
//                     int another_pair = it->second;
//                     set1->ds[another_pair] = another_pair;
//                     set1->ranks[another_pair] = 0; 
//                 }
//                 flag = 1;
//             }
//             else if((set1->ds[i] != i || set1->ranks[i] != 0) && (set0->ds[i] == i && set0->ranks[i] == 0)){
//                 result[i] = 1;
//                 int another = reflect.find(b - arr[i])->second;
//                 result[another] = 1;
//                 it = reflect.find(a - arr[another]);
//                 if(it != reflect.end()){
//                     int another_pair = it->second;
//                     set0->ds[another_pair] = another_pair;
//                     set0->ranks[another_pair] = 0; 
//                 }
//                 flag = 1;
//             }
//             else if((set1->ds[i] == i || set1->ranks[i] == 0) && (set0->ds[i] == i && set0->ranks[i] == 0)){
//                 if(arr[i] *2 != a && arr[i] *2 != b){
//                     return false;
//                 }
//                 else if(arr[i] *2 == a){
//                     result[i] = 0;
//                 }
//                 else {
//                     result[i] = 1;
//                 }
//                 flag = 1;
//             }
//             else{
//                 continue;
//             }
//         }
//     }
//     return true;
// }


// int main(){
//     int n, a, b;
//     cin >> n >> a >> b;
//     map<int, int> reflection;
//     int arr[n];
//     int result[n];
//     for(int i = 0; i < n; i ++){
//         result[i] = -1;
//         int x;
//         cin >> x;
//         arr[i] = x;
//         reflection[x] = i;
//     }
//     bool ret = find(reflection, arr, n, a, b, result);
//     if(!ret)
//         cout << "0" << endl;
//     else{
//         cout << "1" << endl;
//         for(int i = 0; i < n; i++){
//             cout << result[i];
//             if(i < n - 1)
//                 cout << " ";
//         }
//     }

// }



//----------------------------------------------------------------A
// struct Tree{
//     int val;
//     Tree *left = NULL;
//     Tree *right = NULL;
// };

// struct Node{
//     int val;
//     Node *next = NULL;
//     Node(int val) : val(val){}
//     Node* insert(Node* node){
//         Node *temp = this->next;
//         this->next = node;
//         node->next = temp;
//     }
// };

// int input_global = 0;
// void helper(Tree **node){
//     cin >> input_global;
//     if(input_global == -1){
//         *node = NULL;
//         return;
//     }   
//     else{
//         (*node) = new Tree();
//         (*node)->val = input_global;
//         helper(&(*node)->left);
//         helper(&(*node)->right);
//     }
// }


// int search(Tree *t, int x, Node* n){
//     if(t == NULL) return 0;
//     if(t->val == x){
//         n->insert(new Node(t->val));
//         return 1;
//     } 
//     else{
//         int ret1 = search(t->left, x, n);
//         int ret2 = search(t->right, x, n);
//         if(ret1 + ret2 > 0){
//             n->insert(new Node(t->val));
//             return 1;
//         }
//         else
//             return 0;
//     }
// }


// int main(){
//     Tree *t;
//     helper(&t);
//     int x, y;
//     cin >> x >> y;
//     Node *x1 = new Node(0);
//     Node *x2 = new Node(0);
//     search(t, x, x1);
//     search(t, y, x2);
//     int result = 0;
//     while(x1 != NULL && x2 != NULL){
//         if(x1->val == x2->val)
//             result = x1->val;
//         else
//             break;
//         x1 = x1->next;
//         x2 = x2->next;
//     }
//     cout << result << endl;
// }