#include <iostream>
using namespace std;


int get_index(int *a, int number){
    return number == a[number] ? number : a[number] = get_index(a, a[number]);
}

int main(){
    int n, m, s, e;
    cin >> n >> m >> s >> e;
    int country[n][3];
    int links[n];
    for(int i = 0; i < n; i ++){
        links[i] = i;
    }
    int index = 0;
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
            country[index][0] = value[j];
            country[index][1] = temp[j];
            country[index][2] = temp[j + 1];
        }
    }
}


// ----------------------------------------------------------------B second edition (AC)
// class maxHeap{
//     int *array;
//     int len;
// public:
//     maxHeap(int n){
//         array = new int[n];
//         for(int i = 0; i < n; i ++){
//             array[i] = 0;
//         }
//         len = 0;
//     }

//     void add(int number){
//         array[len ++] = number;
//         this->upward_adjust(len - 1);
//     }

//     void pop(){
//         array[0] = array[len - 1];
//         len --;
//         this->downward_adjust(0);
//     }

//     int output(){
//         return array[0];
//     }

//     void downward_adjust(int position){
//         if(position * 2 + 1 >= len){
//             return;
//         }
//         else if(position * 2 + 2 >= len){
//             if(array[position] < array[position * 2 + 1]){
//                 int temp = array[position * 2 + 1];
//                 array[position * 2 + 1] = array[position];
//                 array[position] = temp;
//             }
//             else
//                 return;
//         }
//         else{
//             int max, a, b, c;
//             a = array[position];
//             b = array[2 * position + 1];
//             c = array[2 * position + 2];
//             max = a > b ? a : b;
//             max = max > c ? max : c;
//             if(max == a){
//                 return;
//             }
//             else if(max == b){
//                 array[position] = b;
//                 array[2 * position + 1] = a;
//                 return downward_adjust(2 * position + 1);
//             }
//             else{
//                 array[position] = c;
//                 array[2 * position + 2] = a;
//                 return downward_adjust(2 * position + 2);
//             }
//         }
//     }

//     void upward_adjust(int position){
//         int parent, kidl, kidr;
//         int p_kidl, p_kidr;
//         if(position == 0){
//             return;
//         }
//         if(position % 2 == 1){
//             parent = array[position / 2];
//             kidl = array[position];
//             p_kidl = position;
//             kidr = position + 1 == len ? -1 : array[position + 1];
//             p_kidr = position + 1;
//         }
//         else{
//             parent = array[position / 2 - 1];
//             kidl = array[position - 1];
//             p_kidl = position - 1;
//             kidr = array[position];
//             p_kidr = position;
//         }
//         if(parent >= kidl && parent >= kidr){
//             return;
//         }
//         else if(parent < kidl && parent > kidr){
//             array[position / 2] = kidl;
//             array[p_kidl] = parent;
//         }
//         else if(parent < kidr && parent > kidl){
//             array[position / 2 - 1] = kidr;
//             array[p_kidr] = parent;
//         }
//         else{
//             if(kidr >= kidl){
//                 array[position / 2 - 1] = kidr;
//                 array[p_kidr] = parent; 
//             }
//             else{
//                 array[position / 2] = kidl;
//                 array[p_kidl] = parent;
//             }
//         }
//         if(position % 2 == 1)
//             return upward_adjust(position / 2);
//         else
//             return upward_adjust(position / 2 - 1);
//     }
    
// };

// class minHeap{
//     int *array;
//     int len;
// public:
//     minHeap(int n){
//         array = new int[n];
//         for(int i = 0; i < n; i ++){
//             array[i] = 0;
//         }
//         len = 0;
//     }

//     void add(int number){
//         array[len ++] = number;
//         this->upward_adjust(len - 1);
//     }

//     void pop(){
//         array[0] = array[len - 1];
//         len --;
//         this->downward_adjust(0);
//     }

//     int output(){
//         return array[0];
//     }

//     void downward_adjust(int position){
//         if(position * 2 + 1 >= len){
//             return;
//         }
//         else if(position * 2 + 2 >= len){
//             if(array[position] > array[position * 2 + 1]){
//                 int temp = array[position * 2 + 1];
//                 array[position * 2 + 1] = array[position];
//                 array[position] = temp;
//             }
//             else
//                 return;
//         }
//         else{
//             int min, a, b, c;
//             a = array[position];
//             b = array[2 * position + 1];
//             c = array[2 * position + 2];
//             min = a < b ? a : b;
//             min = min < c ? min : c;
//             if(min == a){
//                 return;
//             }
//             else if(min == b){
//                 array[position] = b;
//                 array[2 * position + 1] = a;
//                 return downward_adjust(2 * position + 1);
//             }
//             else{
//                 array[position] = c;
//                 array[2 * position + 2] = a;
//                 return downward_adjust(2 * position + 2);
//             }
//         }
//     }

//     void upward_adjust(int position){
//         int parent, kidl, kidr;
//         int p_kidl, p_kidr;
//         if(position == 0){
//             return;
//         }
//         if(position % 2 == 1){
//             parent = array[position / 2];
//             kidl = array[position];
//             p_kidl = position;
//             kidr = position + 1 == len ? 1000001 : array[position + 1];
//             p_kidr = position + 1;
//         }
//         else{
//             parent = array[position / 2 - 1];
//             kidl = array[position - 1];
//             p_kidl = position - 1;
//             kidr = array[position];
//             p_kidr = position;
//         }
//         if(parent <= kidl && parent <= kidr){
//             return;
//         }
//         else if(parent > kidl && parent < kidr){
//             array[position / 2] = kidl;
//             array[p_kidl] = parent;
//         }
//         else if(parent > kidr && parent < kidl){
//             array[position / 2 - 1] = kidr;
//             array[p_kidr] = parent;
//         }
//         else{
//             if(kidr <= kidl){
//                 array[position / 2 - 1] = kidr;
//                 array[p_kidr] = parent; 
//             }
//             else{
//                 array[position / 2] = kidl;
//                 array[p_kidl] = parent;
//             }
//         }
//         if(position % 2 == 1)
//             return upward_adjust(position / 2);
//         else
//             return upward_adjust(position / 2 - 1);
//     }
    
// };


// int main(){
//     int m, n;
//     cin >> m >> n;
//     int array[n];
//     for(int i = 0; i < n; i ++){
//         cin >> array[i];
//     }
//     maxHeap *maxheap = new maxHeap(n);
//     minHeap *minheap = new class minHeap(n);
//     int t = 0, tt = 0;
//     for(int i = 0; i < n; i ++){
//         if(tt == 1 && i % m == 0){
//             minheap->add(maxheap->output());
//             maxheap->pop();
//             t = 1;
//         }
//         if(t == 1 && array[i] > minheap->output()){
//             minheap->add(array[i]);
//             maxheap->add(minheap->output());
//             minheap->pop();
//         }
//         else
//             maxheap->add(array[i]);
//         cout << maxheap->output() << " ";
//         tt = 1;
//     }
//     cout << endl;

// }


// ----------------------------------------------------------------B first edition
// int partition(int *array, int start, int end, int m){
//     // 采用快排中的划分思想，将数组按照一个数划分为两半，左大右小，
//     // 按照m的大小递归左边的部分或右边的部分，或是直接输出
//     // 和第一题中的函数一摸一样
//     if(start == end){ // base case
//         return array[start];
//     }
//     int pat = array[end];
//     int index = start;
//     for(int i = start; i < end; i++){
//         if(array[i] >= pat){
//             int temp = array[i];
//             array[i] = array[index];
//             array[index] = temp;
//             index ++;
//         }
//     }
//     array[end] = array[index];
//     array[index] = pat;
//     if(index == m){
//         return pat;
//     }
//     else if(index > m){
//         return partition(array, start, index - 1, m);
//     }
//     else{
//         return partition(array, index + 1, end, m);
//     }
// }

// int main(){
//     int m, n;
//     cin >> m >> n;
//     int array[n];
//     for(int i = 0; i < n; i ++){
//         cin >> array[i];
//     }
//     double judge;
//     int number;
//     for(int i = 1; i < n + 1; i ++){
//         judge = (double)i / (double)m;
//         number = i / m;
//         if(number == judge){ // 判断上取整
//             cout <<  partition(array, 0, i - 1, number - 1) << ' ';
//         }
//         else{
//             cout << partition(array, 0, i - 1, number) << ' ';
//         }
//     }
//     cout << endl;
// }


// ----------------------------------------------------------------A
// int partition(int *array, int start, int end, int m){
//     // 采用快排中的划分思想，将数组按照一个数划分为两半，左大右小，
//     // 按照m的大小递归左边的部分或右边的部分，或是直接输出
//     if(start == end){ // base case
//         return array[start];
//     }
//     int pat = array[end];
//     int index = start;
//     for(int i = start; i < end; i++){
//         if(array[i] >= pat){
//             int temp = array[i];
//             array[i] = array[index];
//             array[index] = temp;
//             index ++;
//         }
//     }
//     array[end] = array[index];
//     array[index] = pat;
//     if(index == m){
//         return pat;
//     }
//     else if(index > m){
//         return partition(array, start, index - 1, m);
//     }
//     else{
//         return partition(array, index + 1, end, m);
//     }
// }

// int main(){
//     int m, n;
//     cin >> m >> n;
//     m --;  // 程序从0开始计数，因此m自减1
//     int array[n];
//     for(int i = 0; i < n; i ++){
//         cin >> array[i];
//     }
//     int result;
//     result = partition(array, 0, n - 1, m);
//     cout << result << endl;
// }