#include <iostream>
using namespace std;


// ----------------------------------------------------------------D
// int main(){
//     cout << "false" << endl;
// }

// ----------------------------------------------------------------C
// int get_index(int *a, int number){
//     return number == a[number] ? number : a[number] = get_index(a, a[number]);
// }

// int main(){
//     int n, m;
//     cin >> n >> m;
//     int a[n], b[n];
//     for(int i=0; i<n; i ++){
//         a[i] = i;
//         b[i] = 0;
//     }
//     for(int i = 0; i < m; i ++){
//         int min, max;
//         cin >> min >> max;
//         min --;
//         max --;
//         int root_min = get_index(a, min);
//         int root_max = get_index(a, max);
//         a[root_max] = a[root_min];
//         // a[x] ++;
//         // b[y] ++;
//     }
//     int number = 0;
//     for(int i = 0; i < n; i ++){
//         int index = get_index(a, i);
//         b[index] ++;
//     }
//     for(int i = 0; i < n; i ++){
//         if(b[i] != 0)
//             number ++;
//     }
//     if(number > 0)
//         number --;
//     cout << number << endl;

// }



// ----------------------------------------------------------------B
int main(){
    int n;
    cin >> n;
    int q[n], inv_q[n];
    for(int i=0; i<n; i++){
        cin >> q[i];
        inv_q[q[i]] = i;
    }
    int times = 0;
    for(int i=0; i<n; i+=2){
        if(q[i]%2 == 0 && q[i+1] != q[i]+1){
            times ++;
            int pair = inv_q[q[i] + 1];
            int temp = q[i+1];
            q[i+1] = q[pair];
            q[pair] = temp;
            temp = inv_q[i + 1];
            inv_q[i + 1] = inv_q[q[i] + 1];
            inv_q[q[i] + 1] = temp;
        }
        if(q[i]%2 == 1 && q[i+1] != q[i]-1){
            times ++;
            int pair = inv_q[q[i] - 1];
            int temp = q[i+1];
            q[i+1] = q[pair];
            q[pair] = temp;
            temp = inv_q[i + 1];
            inv_q[i + 1] = inv_q[q[i] - 1];
            inv_q[q[i] - 1] = temp;
        }
    }
    cout << times << endl;

}


// ----------------------------------------------------------------A
// int main(){
//     int column, row;
//     cin >> row >> column;
//     int grid[row][column];
//     for(int i = 0; i < row; i ++){
//         for(int j = 0; j < column; j ++){
//             cin >> grid[i][j];
//         }
//     }
//     int C = 0;
//     for(int i = 0; i < row; i ++){
//         for(int j = 0; j < column; j ++){
//             if(grid[i][j] == 1){
//                 if(i == 0){
//                     C ++;
//                 }
//                 if(i == row - 1){
//                     C ++;
//                 }
//                 if(j == 0){
//                     C ++;
//                 }
//                 if(j == column - 1){
//                     C ++;
//                 }
//                 if(i != 0 && grid[i - 1][j] == 0){
//                     C ++;
//                 }
//                 if(i != row - 1 && grid[i + 1][j] == 0){
//                     C ++;
//                 }
//                 if(j != 0 && grid[i][j - 1] == 0){
//                     C ++;
//                 }
//                 if(j != column - 1 && grid[i][j + 1] == 0){
//                     C ++;
//                 }
//             }
//         }
//     }
//     cout << C << endl;
// }