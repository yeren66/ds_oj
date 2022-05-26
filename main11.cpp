#include <iostream>
using namespace std;
#include <random>


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

int helper(int *slave, int start, int n, int target){
    int number = start + 1;
    int gap = 0;
    int position = n - 1;
    for(int i=start + 1; i<n; i++){
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
        return helper(slave, position, n, target - number * gap);
    }
}

int N;
int M;
int* v;
int partition(int* arr, int left, int right){
	int a = arr[right];
	int i, j;
	for(i = left - 1, j = i + 1; j <= right; j ++){
		if(arr[j] <= a){
			i ++;
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	return i;
}
void QuickSort(int* arr, int left, int right){
	if(left >= right){
		return;
	}
	int p = partition(arr, left, right);
	QuickSort(arr, left, p - 1);
	QuickSort(arr, p + 1, right);
}
int solution(){
	QuickSort(v, 0, N - 1);
	int x = v[N / 2];
	while(1){
		int z = 0;
		int count = 0;
		for(int i = 0; i < N; i ++){
			if(v[i] - x > 0){
				z += (v[i] - x);
				count ++;
			}
		}
		int gap = z - M;
		int y;
		if(gap >= 0)
			y = x + gap / count;
		else{
			y = x + gap / N;
			if(y == x)
				y = y - 1;
		}
	// cout << " gap : " << gap << " v : " << x << " v_next : " << y << endl;
		if(x == y)
			break;
		else
			x = y;
	}
	return x;
}
// int main(){
// 	cin >> N >> M;
// 	v = new int[N];
// 	for(int i = 0; i < N; i ++){
// 		cin >> v[i];
// 	}
// 	cout << solution() << endl;
// }

int main(){
    int n, m;
    // cin >> n >> m;
    for(int i = 300; i < 10000; i ++){
        n = i;
        n ++;
        N = n;
        m = rand()%10000000;
        M = m;
        // cout << i << ':' << n << ' ' << m << endl;
        int slave[n];
        v = new int[N];
        for(int i = 0; i < n; i ++){
            slave[i] = rand()%10000000;
            v[i] = slave[i];
            // cout << slave[i] << ' ';
        }
        cout << endl;
        quick_sort(slave, 0, n - 1);
        int result1 = helper(slave, 0, n, m);
        int result2 = solution();
        if (result1 != result2){
            cout << i << ':' << n << ' ' << m << endl;
            // for(int i = 0; i < n; i ++){
            //     cout << slave[i] << ' ';
            // }
            // cout << endl;
            cout << "result1 = " << result1 << endl;
            cout << "result2 = " << result2 << endl;
            
        }

    }

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