#include <iostream>
using namespace std;


// ----------------------------------------------------------------C
// int get_index(int *a, int number){
//     return number == a[number] ? number : a[number] = get_index(a, a[number]);
// }

// int main(){
//     int n = 1000;
//     cin >> n;
//     int roads_[100000], vernues_[100000];
//     for(int i = 0; i < n; i ++){
//         roads_[i] = 0;
//         vernues_[i] = 0;
//     }
//     int max = 0;
//     for(int i = 0; i < n; i ++){
//         cin >> roads_[i] >> vernues_[i];
//         if(roads_[i] > max){
//             max = roads_[i];
//         }
//         if(vernues_[i] > max){
//             max = vernues_[i];
//         }
//     }
//     int a[max + 1];
//     for(int i = 0; i < max + 1; i ++){
//         a[i] = i;
//     }
//     for(int i = 0; i < n; i ++){
//         if(get_index(a, roads_[i]) == get_index(a, vernues_[i])){
//             cout << roads_[i] << ' ' << vernues_[i] << endl;
//             break;
//         }
//         else{
//             a[get_index(a, roads_[i])] = a[get_index(a, vernues_[i])];
//         }
//     }

// }

//  ----------------------------------------------------------------B
void quick_sort(int *array, int start, int end){
    if(start >= end){
        return;
    }
    else{
        int pat = array[end];
        int index = start;
        for(int i = start; i < end; i++){
            if(array[i] >= pat){
                int temp = array[i];
                array[i] = array[index];
                array[index] = temp;
                index ++;
            }
        }
        array[end] = array[index];
        array[index] = pat;
        quick_sort(array, start, index - 1);
        quick_sort(array, index + 1, end);
    }
}

int helper(int *slave, int n, int target){
    int number = 1;
    int gap = 0;
    int position = n - 1;
    for(int i=1; i<n; i++){
        if(slave[i] == slave[i - 1])
            number ++;
        else{
            gap = slave[i - 1] - slave[i];
            position = i;
            break;
        }
    }
    if(target <= number * gap || gap == 0){
        double temp = (double)target / number;
        int temp_ = target / number;
        if((double)temp_ != temp)
            temp_ ++;
        return slave[position] + gap - temp_;  
    }
    else{
        for(int i = 0; i < number; i ++){
            slave[i] = slave[position];
        }
        return helper(slave, n, target - number * gap);
    }
}

int main(){
    int n, m;
    cin >> n >> m;
    int slave[n];
    for(int i = 0; i < n; i ++){
        cin >> slave[i];
    }
    quick_sort(slave, 0, n - 1);
    cout << helper(slave, n, m) << endl;

}


// ----------------------------------------------------------------A
// int helper(int *tree, int start, int end){
//     if(end - start <= 1){
//         return 1;
//     }
//     int gap = tree[end - 1];
//     int position = end - 1;
//     for(int i = start; i < end; i ++){
//         if(gap < tree[i]){
//             position = i;
//             break;
//         }
//     }
//     for(int i = position; i < end; i ++){
//         if(gap > tree[i]){
//             return 0;
//         }
//     }
//     if(helper(tree, start, position) == 1 && helper(tree, position, end-1) == 1){
//         return 1;
//     }
//     return 0;
// }

// int main(){
//     int n;
//     cin >> n;
//     int tree[n];
//     for (int i = 0; i < n; i ++){
//         cin >> tree[i];
//     }
//     cout << helper(tree, 0, n) << endl;

// }