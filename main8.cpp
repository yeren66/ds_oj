#include<iostream>
using namespace std;

void swap(int* a, int* b)
{
    int temp = *b;
    *b = *a;
    *a = temp;
}
 
void max_heapify(int arr1[], int arr2[], int arr3[], int start, int end) 
{
    //建立父节点指标和子节点指标
    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end)  //若子节点指标在范围内才做比较
	{
		if (son + 1 <= end && arr1[son] < arr1[son + 1]) 
            //先比较两个子节点大小，选择最大的
            son++;
        if (arr1[dad] > arr1[son]) //如果父节点大於子节点代表调整完毕，直接跳出函数
            return;
        else  //否则交换父子内容再继续子节点和孙节点比较
        {
            swap(&arr1[dad], &arr1[son]);
			swap(&arr2[dad], &arr2[son]);
			swap(&arr3[dad], &arr3[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}
 
void heap_sort(int arr1[], int arr2[], int arr3[], int len) 
{
    int i;
    //初始化，i从最後一个父节点开始调整
    for (i = len / 2 - 1; i >= 0; i--)
        max_heapify(arr1, arr2, arr3, i, len - 1);
    //先将第一个元素和已排好元素前一位做交换，再重新调整，直到排序完毕
    for (i = len - 1; i > 0; i--) 
    {
        swap(&arr1[0], &arr1[i]);
		swap(&arr2[0], &arr2[i]);
		swap(&arr3[0], &arr3[i]);
        max_heapify(arr1, arr2, arr3, 0, i - 1);
    }
}

int main(){
	int n;
	cin >> n;
	int Avalue[n], Bvalue[n], Tvalue[n];
	for(int i=0; i < n; i ++){
		cin >> Avalue[i];
	}
	for(int i=0; i<n; i ++){
		cin >> Bvalue[i];
		Tvalue[i] = Avalue[i] + Bvalue[i];
	}
	// for(int i=0; i<n; i ++){
	// 	int max = Tvalue[i];
	// 	int index = i;
	// 	for(int j=i; j < n; j++){
	// 		if(Tvalue[j] > max){
	// 			max = Tvalue[j];
	// 			index = j;
	// 		}
	// 	}
	// 	Tvalue[index] = Tvalue[i];
	// 	Tvalue[i] = max;
	// 	int temp = Avalue[index];
	// 	Avalue[index] = Avalue[i];
	// 	Avalue[i] = temp;
	// 	temp = Bvalue[index];
	// 	Bvalue[index] = Bvalue[i];
	// 	Bvalue[i] = temp;
	// }
	heap_sort(Tvalue, Avalue, Bvalue, n);
	// for(int i = 0; i < n; i ++){
	// 	cout << Tvalue[i] << " ";
	// }
	// cout << endl;
	// for(int i = 0; i < n; i ++){
	// 	cout << Avalue[i] << " ";
	// }
	// cout << endl;
	// for(int i = 0; i < n; i ++){
	// 	cout << Bvalue[i] << " ";
	// }
	// cout << endl;
	int sumA = 0, sumB = 0;
	int flag = 0;
	for(int i = n - 1; i > -1; i --){
		if(flag == 0)
			sumA += Avalue[i];
		else
			sumB += Bvalue[i];
		flag = 1 - flag;
	}
	if(sumA > sumB){
		cout << 1 << endl;
	}
	else if(sumA < sumB){
		cout << -1 << endl;
	}
	else{
		cout << 0 << endl;
	}

}

// ----------------------------------------------------------------C
// int N = 10000;

// int main(){
//     int n;
//     cin >> n;
//     int column[N], row[N];
//     for(int i=0; i<N; i++){
//         column[i] = 0;
//         row[i] = 0;
//     }
//     int record[2*n];
//     for(int i=0; i< n; i ++){
//         int x, y;
//         cin >> x >> y;
//         record[2 * i] = x;
//         record[2 * i + 1] = y;
//         row[x] ++;
//         column[y] ++;
//     }
//     bool done = false;
//     int result = 0;
//     while(!done){
//         // cout << "  ";
//         // for(int i=0; i<n; i ++){
//         //     cout << row[i] << " ";
//         // }
//         // cout << endl;
//         // for (int i=0; i<n; i++){
//         //     cout << column[i] << endl;
//         // }

//         int flag = 0;
//         for(int i=0; i<n; i ++){
//             int x = record[2 * i];
//             int y = record[2 * i + 1];
//             if((row[x] == 1 && column[y] > 1) || (column[y] == 1 && row[x] > 1)){
//                 row[x] --;
//                 column[y] --;
//                 result ++;
//                 flag = 1;
//                 break;
//             }
//         }
//         if(flag == 0){
//             for(int i=0; i<n; i ++){
//                 int x = record[2 * i];
//                 int y = record[2 * i + 1];
//                 if(row[x] > 1 && column[y] > 1){
//                     row[x] --;
//                     column[y] --;
//                     result ++;
//                     flag = 1;
//                     break;
//                 }
//             }
//         }
//         if(flag == 0){
//             cout << result << endl;
//             done = true;
//         }
//     }
// }

//----------------------------------------------------------------B
// void HeapAjust(int *, int, int);

// //建立大顶堆
// void BulidHeap(int Ele[],int len)
// {
// 	int i;
// 	for(i=len/2;i>0;i--)  
// 	{
// 	//	printf("%d",i);
// 		HeapAjust(Ele,i,len);
// 	}
// }
// //堆调整
// void HeapAjust(int Ele[],int k,int len)
// {
	
// 	int i;
// 	Ele[0]=Ele[k];
// 	for(i=2*k;i<=len;i*=2)
// 	{
// 		if(i<len&&Ele[i]<Ele[i+1])
// 		{
// 			i++;
// 		}
// 		if(Ele[0]>=Ele[i])
// 		{
// 			break;
// 		}		
// 		else
// 		{
// 			Ele[k]=Ele[i];
// 	    	k=i;	
// 		}
// 	}
// 	Ele[k]=Ele[0];
//    // for(i=1;i<=len;i++)
// 	//{
// 	   //printf("@%d",Ele[i]);
				
// 	//}
// 	//printf("\n");
// }
// //堆排序
// void HeapSort(int Ele[],int len)
// {
// 	int i,temp;
// 	//for(i=1;i<=len;i++)
// //	{
// 	  // printf("@%d",Ele[i]);
			
// 	//}
// 	//printf("\n");
// 	BulidHeap(Ele,len);
// 	for(i=len;i>1;i--)
// 	{
// 		temp=Ele[i];
// 		Ele[i]=Ele[1];
// 		Ele[1]=temp;
// 		HeapAjust(Ele,1,i-1);
// 	}
// }


// int main(){
//     int n;
//     cin >> n;
//     int Avalue[n], Bvalue[n];
//     for(int i=0; i<n; i ++){
//         cin >> Avalue[i];
//     }
//     for(int i=0; i<n; i ++){
//         cin >> Bvalue[i];
//     }
//     int sumA = 0;
//     int sumB = 0;
//     int flag = 0;
//     int player = 0;
//     for(int i=0; i<n; i ++){
//         int max = -1;
//         int index = 0;
//         for(int j=0; j<n; j++){
//             if(Avalue[j] > max){
//                 max = Avalue[j];
//                 index = j;
//                 flag = 0;
//             }
//         }
//         for(int j=0; j<n; j++){
//             if(Bvalue[j] > max){
//                 max = Bvalue[j];
//                 index = j;
//                 flag = 1;
//             }
//         }
//         if(player == 0){
//             // if(flag == 0){
//             //     sumA += Avalue[index];
//             //     Avalue[index] = -1;
//             // }
//             // else{
//             //     sumA += Bvalue[index];
//             //     Bvalue[index] = -1;
//             // }
//             sumA += Avalue[index];
//             Avalue[index] = -1;
//             Bvalue[index] = -1;
//             player = 1 - player;
//         }
//         else{
//             // if(flag == 0){
//             //     sumB += Avalue[index];
//             //     Avalue[index] = -1;
//             // }
//             // else{
//             //     sumB += Bvalue[index];
//             //     Bvalue[index] = -1;
//             // }
//             sumB += Bvalue[index];
//             Avalue[index] = -1;
//             Bvalue[index] = -1;
//             player = 1 - player;
//         }

//     }
//     if (sumA > sumB){
//         cout << 1 << endl;
//     }
//     else if(sumB > sumA){
//         cout << -1 << endl;
//     }
//     else{
//         cout << 0 << endl;
//     }

// }



//----------------------------------------------------------------A
// struct Tree{
//     int val;
//     Tree *left = NULL;
//     Tree *right = NULL;
// };
// int result, input_global;
// int layer_global = 0;
// void helper(Tree **node, int layer){
//     cin >> input_global;
//     if(input_global == -1){
//         *node = NULL;
//         return;
//     }   
//     else{
//         if (layer > layer_global){
//             layer_global = layer;
//             result = input_global;
//         }
//         layer ++;
//         (*node) = new Tree();
//         (*node)->val = input_global;
//         helper(&(*node)->left, layer);
//         helper(&(*node)->right, layer);
//     }
// }

// int main(){
//     int n;
//     cin >> n;
//     Tree *root;
//     helper(&root, 0);
//     cout << result << endl;
// }