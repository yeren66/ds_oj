#include <iostream>
using namespace std;
#include <map>

template <class T>
struct _DISJOINTSET {
    T _st;//起点
    T _ed;//终点
    map<T, T> ds;//并查集
    map<T, int> ranks;
 
    _DISJOINTSET() : _st(0), _ed(0) {}
    _DISJOINTSET(T *st, int n) {
        init(st, n);
    }
 
    /*
    st 表示起点
    ed 表示终点
    */
    void init(T *st, int n) {
        // if (ed<st) {
        //     return;
        // }
        for (int i = 0; i < n; i ++) {
            ds[st[i]] = st[i];
            ranks[st[i]]=0;
        }
        _st = st[0];
        _ed = st[n - 1];
    }
 
    //查找x的父亲
    T find_root(T x) {
        return x==ds[x]?x:ds[x]=find_root(ds[x]);
    }
 
    //建立关系
    void union_set(T x, T y) {
        T x_root=find_root(x);
        T y_root=find_root(y);
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
 
    //查找x和y是否在同一个父亲
    bool relation(T x, T y) {
        return find_root(x)==find_root(y);
    }
};

struct junc{
    int index;
    int val;
    // bool operator <(junc& a){
    //     return a.index < this->index;
    // }
    bool operator ==(junc& a){
        return a.index == this->index;
    }
    bool operator !=(junc& a){
        return a.index != this->index;
    }
};

bool find(junc *price, int n, int a, int b, int *result, int flag=0){
    _DISJOINTSET<junc> *set0 = new _DISJOINTSET<junc>(price, n);
    _DISJOINTSET<junc> *set1 = new _DISJOINTSET<junc>(price, n);
    for(int i = 0; i < n; i ++){
        if(set0->find_root(price[i]) == price[i] || set1->find_root(price[i]) == price[i]){
            for(int j = i + 1; j < n; j ++){
                if(price[i].val + price[j].val == a){
                    set0->union_set(price[i], price[j]);
                }
                else if(price[i].val + price[j].val == b){
                    set1->union_set(price[i], price[j]);
                }
            }
        }
    }
    int index = 0;
    for(int i = 0; i < n; i ++){
        if(set0->ranks[price[i]] == 0 && set1->ranks[price[i]] == 0){
            if(price[i].val*2 != a && price[i].val*2 != b){
                return false;
            }
            if(price[i].val*2 == a){
                result[price[i].index] = 0;
                if(flag == 1){
                    result[price[i].index] = 1 - result[price[i].index];
                }
            }
            if(price[i].val*2 == b){
                result[price[i].index] = 1;
                if(flag == 1){
                    result[price[i].index] = 1 - result[price[i].index];
                }
            }
        }
        else if(set0->ranks[price[i]] != 0 && set1->ranks[price[i]] == 0){
            result[price[i].index] = 0;
            if(flag == 1){
                    result[price[i].index] = 1 - result[price[i].index];
                }
        }
        else if(set0->ranks[price[i]] == 0 && set1->ranks[price[i]] != 0){
            result[price[i].index] = 1;
            if(flag == 1){
                    result[price[i].index] = 1 - result[price[i].index];
                }
        }
        else{
            price[index] = price[i];
            index ++;
        }
    }
    if(index != 0){
        return find(price, index, a, b, result, 1 - flag);
    }
    return true;
}

int main(){
    int n, a, b;
    cin >> n >> a >> b;
    junc price[n];
    for(int i = 0; i < n; i ++){
        price[i].index = i;
        cin >> price[i].val;
    }
    int result[n];
    bool ret = find(price, n, a, b, result);
    if(!ret)
        cout << "0" << endl;
    else{
        cout << "1" << endl;
        for(int i = 0; i < n; i++){
            cout << result[i];
            if(i < n - 1)
                cout << " ";
        }
    }

}



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