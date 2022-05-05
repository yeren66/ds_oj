#include <iostream>
using namespace std;

int main(){
	int n;
	cin >> n;
	int int[n] = {0};
	for(int i = 0; i < n; i ++){
		cin >> init[i];
	}
	bool record[n];
	for(int i = 0; i < n; i ++){
		record[i] = true;
	}
	int flag = 0;
	while(flag == 0){
		flag = 1;
		for(int i = 0; i < n; i ++){
			if(!record[i])
				continue;
			else{
				if(init[i] > 0){
					int next = i;
					for(int j = i + 1; j < n; j ++){
						if(record[j]){
							next = j;
							break;
						}
					}
					if(next == i)
						break;
					if(init[next] > 0)
						continue;
					else if(init[i] + init[next] > 0){
						record[next] = false;
					}
					else if(init[i] + init[next] == 0){
						record[i] = false;
						record[next] = false;
					}
					else
					{
						record[i] = false;
					}
					flag = 0;
				}
				else{
					int next = i;
					for(int j = i - 1; j > -1; j --){
						if(record[j]){
							next = j;
							break;
						}
					}
					if(init[next] < 0)
						continue;
					else if(init[i] + init[next] < 0){
						init[next] = false;
					}
					else if(init[i] + init[next] == 0){
						record[i] = false;
						record[next] = false;
					}
					else{
						record[i] = false;
					}
					flag = 0;
				}
			}
		}
	
	}
	for(int i = 0; i < n; i ++){
		if(record[i])
			cout << init[i] << " ";
	}
	cout << endl;


}
