#include <iostream>
using namespace std;
#include <string>

void quick_sort(int *array, int start, int end, int *addition){
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
                temp = addition[i];
                addition[i] = addition[index];
                addition[index] = temp;
                index ++;
            }
        }
        array[end] = array[index];
        array[index] = pat;
        quick_sort(array, start, index - 1, addition);
        quick_sort(array, index + 1, end, addition);
    }
}

int get_index(int *a, int number){
    return number == a[number] ? number : a[number] = get_index(a, a[number]);
}

int main(){
    int n, m;
    cin >> n >> m;
    int value[n];
    int sequence[n];
    int seet[n];
    int reward[n];
    int counting[n];
    int tong[n];
    for(int i = 0; i < n; i ++){
        cin >> value[i];
        sequence[i] = i;
        seet[i] = i;
        reward[i] = 0;
        counting[i] = 0;
        tong[i] = 0;
    }
    quick_sort(value, 0, n - 1, sequence);
    // int edges[m][m];
    // for(int i = 0; i < m; i ++){
    //     for(int j = 0; j < m; j ++){
    //         edges[i][j] = 0;
    //     }
    // }
    for(int i = 0; i < m; i ++){
        int a, b;
        cin >> a >> b;
        if(get_index(seet, a) != get_index(seet, b)){
            seet[get_index(seet, a)] = get_index(seet, b);
        }
        tong[a] ++;
        tong[b] ++;
        // edges[a][b] = 1;
        // edges[b][a] = 1;
    }
    for(int i = 0; i < n; i ++){
        if(counting[get_index(seet, sequence[i])] < 5 && tong[get_index(seet, sequence[i])] > 1){
            reward[get_index(seet, sequence[i])] += value[i];
            counting[get_index(seet, sequence[i])] ++;
        }
    }
    int history = 0;
    for(int i = 0; i < n; i ++){
        history = history > reward[i] ? history : reward[i];
    }
    cout << history << endl;
}


// ----------------------------------------------------------------C
// int get_index(int *a, int number){
//     return number == a[number] ? number : a[number] = get_index(a, a[number]);
// }

// int main(){
//     int n, m;
//     cin >> n >> m;
//     int course[n];
//     for(int i = 0; i < n; i ++){
//         course[i] = i;
//     }
//     int a, b;
//     int t = 0;
//     for(int i = 0; i < m; i ++){
//         cin >> a >> b;
//         if(get_index(course, a) != get_index(course, b)){
//             course[get_index(course, a)] = get_index(course, b);
//         }
//         else{
//             if(a != b){
//                 t = 1;
//                 break;
//             }
//         }
//     }
//     if(t == 1){
//         cout << "False" << endl;
//     }
//     else{
//         cout << "True" << endl;
//     }
// }


// ----------------------------------------------------------------B
// struct Node{
//     int count = 0;
//     Node * next = NULL;
// };

// int main(){
//     string input;
//     cin >> input;
//     Node *start = new Node();
//     start->count = 0;
//     Node *temp = start;
//     int history = 0;
//     for(int i = 0; i < input.size(); i++){
//         if(input[i] == 'M'){
//             Node *now = new Node();
//             now->next = temp;
//             temp = now;
//         }
//         else{
//             int number = temp->count;
//             if(temp == start){
//                 history = number > history ? number : history;
//                 start->count = 0;
//             }
//             else{
//                 temp = temp->next;
//                 temp->count += number + 2;
//             }
//         }
//     }
//     while(temp != start){
//         history = history > temp->count ? history : temp->count;
//         temp = temp->next;
//     }
//     history = history > start->count ? history : start->count;
//     cout << history << endl;
// }

// ----------------------------------------------------------------A
// int main(){
//     int n, t;
//     cin >> n >> t;
//     int salary[n];
//     int sum = 0;
//     for(int i = 0; i < n; i ++){
//         cin >> salary[i];
//         sum += salary[i];
//     }
//     int m_min = sum / t;
//     int m_max = sum / t + n;
//     int salary_sum;
//     for(int i = m_min; i <= m_max; i ++){
//         salary_sum = 0;
//         for(int j = 0; j < n; j ++){
//             double temp = (double) salary[j] / (double) i;
//             int temp_ = salary[j] / i; 
//             if(temp != temp_)
//                 temp_ ++;
//             salary_sum += temp_;
//         }
//         if(salary_sum <= t){
//             m_min = i;
//             break;
//         }
//     }
//     cout << m_min << endl;
// }