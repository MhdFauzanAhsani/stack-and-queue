#include "queue.h"
#include <iostream>
#include <vector>

using namespace std;

void sliding_window(vector<int> num, int n, int k){
    Queue q; init(&q);
    
    int cur_sum = 0;
    for(int i = 0; i < n; i++){
        enqueue(&q, num[i]);
        cur_sum += num[i];
        
        if (i >= k){
            cur_sum -= front(&q);
            dequeue(&q);
        }
        if (i >= k - 1) cout << cur_sum << ' ';
    }
};

int main(){
    int n, k; cin >> n >> k;
    
    vector<int> num(n);
    
    for(int i = 0; i < n; i++){
        cin >> num[i];
    }
    
    sliding_window(num, n, k);
    return 0;
}
