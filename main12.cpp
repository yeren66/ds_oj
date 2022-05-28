#include <iostream>
using namespace std;


// ----------------------------------------------------------------C
// int abs(int a){
//     if(a < 0) return -a;
//     return a;
// }

// int get_index(int *a, int number){
//     return number == a[number] ? number : a[number] = get_index(a, a[number]);
// }

// int main(){
//     int n;
//     cin >> n;
//     int position[2*n];
//     int links[n];
//     for(int i = 0; i < n; i ++){
//         cin >> position[2*i] >> position[2*i+1];
//         links[i] = i;
//     }
//     int record[n*n][3];
//     int size = 0;
//     for(int i = 0; i < n - 1; i ++){
//         for(int j = i + 1; j < n; j ++){
//             record[size][0] = abs(position[2*i] - position[2*j]) + abs(position[2*j+1] - position[2*i+1]);
//             record[size][1] = i;
//             record[size][2] = j;
//             size ++;
//         }
//     }
//     for(int i = 0; i < size; i ++){
//         int minimum = record[i][0];
//         int index = i;
//         for(int j = i + 1; j < size; j ++){
//             if(record[j][0] < minimum){
//                 minimum = record[j][0];
//                 index = j;
//             }
//         }
//         int temp = record[i][0];
//         record[i][0] = record[index][0];
//         record[index][0] = temp;
//         temp = record[i][1];
//         record[i][1] = record[index][1];
//         record[index][1] = temp;
//         temp = record[i][2];
//         record[i][2] = record[index][2];
//         record[index][2] = temp;
//     }
//     int total = 0;
//     for(int i = 0; i < size; i ++){
//         if(get_index(links, record[i][1]) != get_index(links, record[i][2])){
//             links[get_index(links, record[i][1])] = get_index(links, record[i][2]);
//             total += record[i][0];
//         }
//     }
//     cout << total << endl;
// }


// -------------------------------------------------------------B
int get_index(int *a, int number){
    return number == a[number] ? number : a[number] = get_index(a, a[number]);
}


int main(){
    int n;
    cin >> n;
    int links[n];
    long long int record[3 * n];
    for(int i = 0; i < n; i ++){
        links[i] = 0;
    }
    long long int total = 0;
    for(int i = 0; i < n - 1; i ++){
        int u, v, w;
        cin >> u >> v >> w;
        total += w;
        u --; v --; 
        record[3*i] = u;
        record[3*i + 1] = v;
        record[3*i + 2] = w;
    }
    int count = 0;
    while(count < n - 1){
        for(int i = 0; i < n - 1; i ++){
            if(record[3*i] == -1)
                continue;
            if(record[3*i] == 0 || links[record[3*i]] != 0){
                links[record[3*i + 1]] = record[3*i + 2] + links[record[3*i]];
                record[3*i] = -1;
                count ++;
            }
            else if(record[3*i + 1] == 0 || links[record[3*i + 1]] != 0){
                links[record[3*i]] = record[3*i + 2] + links[record[3*i + 1]];
                record[3*i] = -1;
                count ++;
            }
        }
    }
    int max = 0;
    for(int i = 0; i < n; i ++){
        if(links[i] > max){
            max = links[i];
        }
    }
    cout << total * 2 - max << endl;
}


// ----------------------------------------------------------------A
// int get_index(int *a, int number){
//     return number == a[number] ? number : a[number] = get_index(a, a[number]);
// }

// int main(){
//     int n;
//     cin >> n;
//     int links[n];
//     for(int i = 0; i < n; i ++){
//         links[i] = i;
//     }
//     // int redLine[n][n];
//     for(int i = 0; i < n; i ++){
//         for(int j = 0; j < n; j ++){
//             int x;
//             cin >> x;
//             // cin >> redLine[i][j];
//             if(x == 1 && i != j){
//                 if(get_index(links, i) != get_index(links, j)){
//                     links[get_index(links, i)] = get_index(links, j);
//                 }
//             }
//         }
//     }
//     int total = 0;
//     for(int i = 0; i < n; i ++){
//         if(links[i] == i){
//             total ++;
//         }
//     }
//     cout << total << endl;

// }
