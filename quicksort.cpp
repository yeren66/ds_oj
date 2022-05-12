#include <iostream>
using namespace std;
#include <random>

void quick_sort(int *array, int start, int end){
    if(start >= end){
        return;
    }
    else{
        int pat = array[end];
        int index = start;
        for(int i = start; i < end; i++){
            if(array[i] <= pat){
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

int main(){
    int n = 30;
    int a[n];
    for(int i = 0; i < n; i ++){
        a[i] = rand() % 200;
        cout << a[i] << " ";
    }
    cout << endl;

    quick_sort(a, 0, n - 1);

    for(int i = 0; i < n; i ++){
        cout << a[i] << " ";
    }
    cout << endl;

}