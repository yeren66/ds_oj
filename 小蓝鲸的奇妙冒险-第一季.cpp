#include <iostream>
using namespace std;


// ----------------------------------------------------------------A
int partition(int *array, int start, int end, int m){
    // 采用快排中的划分思想，将数组按照一个数划分为两半，左大右小，
    // 按照m的大小递归左边的部分或右边的部分，或是直接输出
    if(start == end){ // base case
        return array[start];
    }
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
    if(index == m){
        return pat;
    }
    else if(index > m){
        return partition(array, start, index - 1, m);
    }
    else{
        return partition(array, index + 1, end, m);
    }
}

int main(){
    int m, n;
    cin >> m >> n;
    m --;  // 程序从0开始计数，因此m自减1
    int array[n];
    for(int i = 0; i < n; i ++){
        cin >> array[i];
    }
    int result;
    result = partition(array, 0, n - 1, m);
    cout << result << endl;
}