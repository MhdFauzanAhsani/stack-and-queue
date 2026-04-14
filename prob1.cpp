#include "stack.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isOperator(string c){
    return c == "+" || c == "-" || c == "*" || c == "/";
}

int calculate(int a, int b, char op){
    switch(op){
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        
    }
    return 0;
}

int rpn(vector<string> expr, int n){
    Stack stk;
    init(&stk);
    
    for(int i = 0; i < n; i++){
        string token = expr[i];
        
        if(isOperator(token)){
            int val2 = peek(&stk); pop(&stk);
            int val1 = peek(&stk); pop(&stk);
            
            int res = calculate(val1, val2, token[0]);
            push(&stk, res);
        }
        else {
            int num = stoi(token);
            push(&stk, num);
        }
    }
    return peek(&stk);
}


int main(){
    int n; cin >> n;
    vector<string> str (n);
    
    for(int i = 0; i < n; i++){
        cin >> str[i];
    }
    
    int ans = rpn(str, n);
    cout << ans;
    return 0;   
}
