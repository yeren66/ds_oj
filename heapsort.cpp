#include <iostream>
using namespace std;

class maxHeap{
    int array[40];
    int len;
public:
    maxHeap(int n){
        // array = new int[n];
        for(int i = 0; i < n; i ++){
            array[i] = 0;
        }
        len = 0;
    }

    void add(int number){
        array[len ++] = number;
        this->upward_adjust(len - 1);
    }

    void pop(){
        array[0] = array[len - 1];
        len --;
        this->downward_adjust(0);
    }

    int output(){
        return array[0];
    }

    void downward_adjust(int position){
        if(position * 2 + 1 >= len){
            return;
        }
        else if(position * 2 + 2 >= len){
            if(array[position] < array[position * 2 + 1]){
                int temp = array[position * 2 + 1];
                array[position * 2 + 1] = array[position];
                array[position] = temp;
            }
            else
                return;
        }
        else{
            int max, a, b, c;
            a = array[position];
            b = array[2 * position + 1];
            c = array[2 * position + 2];
            max = a > b ? a : b;
            max = max > c ? max : c;
            if(max == a){
                return;
            }
            else if(max == b){
                array[position] = b;
                array[2 * position + 1] = a;
                return downward_adjust(2 * position + 1);
            }
            else{
                array[position] = c;
                array[2 * position + 2] = a;
                return downward_adjust(2 * position + 2);
            }
        }
    }

    void upward_adjust(int position){
        int parent, kidl, kidr;
        int p_kidl, p_kidr;
        if(position == 0){
            return;
        }
        if(position % 2 == 1){
            parent = array[position / 2];
            kidl = array[position];
            p_kidl = position;
            kidr = position + 1 == len ? -1 : array[position + 1];
            p_kidr = position + 1;
        }
        else{
            parent = array[position / 2 - 1];
            kidl = array[position - 1];
            p_kidl = position - 1;
            kidr = array[position];
            p_kidr = position;
        }
        if(parent >= kidl && parent >= kidr){
            return;
        }
        else if(parent < kidl && parent > kidr){
            array[position / 2] = kidl;
            array[p_kidl] = parent;
        }
        else if(parent < kidr && parent > kidl){
            array[position / 2 - 1] = kidr;
            array[p_kidr] = parent;
        }
        else{
            if(kidr >= kidl){
                array[position / 2 - 1] = kidr;
                array[p_kidr] = parent; 
            }
            else{
                array[position / 2] = kidl;
                array[p_kidl] = parent;
            }
        }
        if(position % 2 == 1)
            return upward_adjust(position / 2);
        else
            return upward_adjust(position / 2 - 1);
    }
    
};

class minHeap{
    int array[40];
    int len;
public:
    minHeap(int n){
        // array = new int[n];
        for(int i = 0; i < n; i ++){
            array[i] = 0;
        }
        len = 0;
    }

    void add(int number){
        array[len ++] = number;
        this->upward_adjust(len - 1);
    }

    void pop(){
        array[0] = array[len - 1];
        len --;
        this->downward_adjust(0);
    }

    int output(){
        return array[0];
    }

    void downward_adjust(int position){
        if(position * 2 + 1 >= len){
            return;
        }
        else if(position * 2 + 2 >= len){
            if(array[position] > array[position * 2 + 1]){
                int temp = array[position * 2 + 1];
                array[position * 2 + 1] = array[position];
                array[position] = temp;
            }
            else
                return;
        }
        else{
            int min, a, b, c;
            a = array[position];
            b = array[2 * position + 1];
            c = array[2 * position + 2];
            min = a < b ? a : b;
            min = min < c ? min : c;
            if(min == a){
                return;
            }
            else if(min == b){
                array[position] = b;
                array[2 * position + 1] = a;
                return downward_adjust(2 * position + 1);
            }
            else{
                array[position] = c;
                array[2 * position + 2] = a;
                return downward_adjust(2 * position + 2);
            }
        }
    }

    void upward_adjust(int position){
        int parent, kidl, kidr;
        int p_kidl, p_kidr;
        if(position == 0){
            return;
        }
        if(position % 2 == 1){
            parent = array[position / 2];
            kidl = array[position];
            p_kidl = position;
            kidr = position + 1 == len ? 1000001 : array[position + 1];
            p_kidr = position + 1;
        }
        else{
            parent = array[position / 2 - 1];
            kidl = array[position - 1];
            p_kidl = position - 1;
            kidr = array[position];
            p_kidr = position;
        }
        if(parent <= kidl && parent <= kidr){
            return;
        }
        else if(parent > kidl && parent < kidr){
            array[position / 2] = kidl;
            array[p_kidl] = parent;
        }
        else if(parent > kidr && parent < kidl){
            array[position / 2 - 1] = kidr;
            array[p_kidr] = parent;
        }
        else{
            if(kidr <= kidl){
                array[position / 2 - 1] = kidr;
                array[p_kidr] = parent; 
            }
            else{
                array[position / 2] = kidl;
                array[p_kidl] = parent;
            }
        }
        return upward_adjust(position / 2);
    }
    
};

int main(){
    int n = 30;

    maxHeap *heap = new maxHeap(n);
    int array[n];
    for(int i = 0; i < n; i ++){
        array[i] = rand() % 120;
        if(array[i] == 99){
            int j = 0;
        }
        heap->add(array[i]);
        cout << array[i] << ' ';
    }
    cout << endl;
    for(int i = 0; i < n; i ++){
        cout << heap->output() << ' ';
        heap->pop();
    }
    cout << endl;
    
}