#include <iostream>
using namespace std;

struct Tree{
    int val;
    Tree *left = NULL;
    Tree *right = NULL;
};
int global_array[1000][1000];
int total_global = 0;
int layer_global = 0;
int input_global = 0;
void helper(Tree **node, int layer){
    if (layer > layer_global)
        layer_global = layer;
    layer ++;
    cin >> input_global;
    if(input_global == -1){
        *node = NULL;
        return;
    }   
    else{
        (*node) = new Tree();
        total_global ++;
        (*node)->val = input_global;
        global_array[layer][global_array[layer][0] + 1] = input_global;
        global_array[layer][0] ++;
        helper(&(*node)->left, layer);
        helper(&(*node)->right, layer);
    }
}

void transform(Tree *tree, int *a, int i, int n){
    a[i] = tree->val;
    if (2*i + 1 < n && tree->left != NULL)
        transform(tree->left, a, 2*i + 1, n);
    if (2*i +2 < n && tree->right != NULL)
        transform(tree->right, a, 2*i + 2, n);
}

int main(){
    int n;
    cin >> n;
    Tree *t;
    helper(&t, 0);
    for(int i = 0; i < layer_global + 1; i ++){
        if(i%2 == 1){
            for(int j = 1; j < global_array[i][0] + 1; j++){
                cout << global_array[i][j] << " ";
            }
        }
        else{
            for(int j = global_array[i][0]; j > 0; j--){
                cout << global_array[i][j] << " ";
            }
        }
        cout << endl;
    }
    // int nn = 0;
    // int r = 1;
    // for(int i = 0; i < layer_global; i ++)
    //     nn += r;
    //     r *= 2;
    // int a[nn];
    // for(int i = 0; i < nn; i++){
    //     a[i] = -1;
    // }
    // transform(t, a, 0, nn);
    // int index = 1;
    // int q = 0;
    // int output = 0;
    // cout << a[0] << endl;
    // while(output < total_global - 1){
    //     if(q == 1){
    //         for(int i = index; i < 2*index + 1 && i < nn; i++){
    //             if(a[i] != -1){
    //                 cout << a[i] << " ";
    //                 output ++;
    //             }
    //         }
    //         cout << endl;
    //         q = 0;
    //         index = 2 *index + 1;
    //     }
    //     else{
    //         int max;
    //         if(nn > 2 * index + 1)
    //             max = 2 * index + 1;
    //         else 
    //             max = nn;
    //         for(int i = max - 1; i > index - 1; i--){
    //             if(a[i] != -1){
    //                 cout << a[i] << " ";
    //                 output++;
    //             }
    //         }
    //         cout << endl;
    //         q = 1;
    //         index = 2 * index + 1;
    //     }

    // }

}

// ----------------------------------------------------------------A
// struct Tree{
//     int val;
//     Tree *left = NULL;
//     Tree *right = NULL;
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

// void merge_Tree(Tree **t1, Tree **t2) {
//     if(*t2 == NULL)
//         return;
//     if(*t1 == NULL){
//         *t1 = *t2;
//         return;
//     }
//     else{
//         (*t1)->val += (*t2)->val;
//         merge_Tree(&(*t1)->left, &(*t2)->left);
//         merge_Tree(&(*t1)->right, &(*t2)->right);
//     }
// }
// void printTree(Tree *t){
//     cout << t->val << ' ';
//     if(t->left !=  NULL)
//         printTree(t->left);
//     else cout << "-1" << ' ';
//     if(t->right != NULL)
//         printTree(t->right);
//     else cout << "-1" << ' ';
// }

// int main(){
//     Tree *t1, *t2;
//     helper(&t1);
//     helper(&t2);
//     merge_Tree(&t1, &t2);
//     printTree(t1);
// }