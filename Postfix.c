#include <stdio.h> 
#include <stdlib.h> 

int stack[100],Value[26];
char infix[100], postfix[100],alph[100],newpostfix[100];

void getValue(char infix[],int Value[]){ 
    int i=0,j=0,k=0,n=0;
    for(i = 0, j = 0; infix[i] != '\0'; i++){ 
        if(infix[i]<='z'&&infix[i]>='a'){
            alph[j++] = infix[i];
        }
    }
	for(i = 0; i < alph[i]!='\0'; i++){
	  	for(j = i + 1; alph[j] != '\0'; j++){
	  		if(alph[j] == alph[i]){
	  			for(k = j; alph[k] != '\0'; k++){
					alph[k] = alph[k + 1];
				}
	 		}
		}
	}
	for(i=0;alph[i]!='\0';i++){
		scanf("%d",&n);
		Value[alph[i]-97]=n;
	}
} 

double cal(char op, double p1, double p2) { 
    double p3=1;
	int r=0;
    switch(op) { 
        case '+': return p1 + p2; 
        case '-': return p1 - p2; 
        case '*': return p1 * p2; 
        case '/': return p1 / p2; 
        case '^':
			for(r=0;r<p2;r++){
				p3*=p1;
			}
			return p3;
    } 
}

int priority(char op) { 
    switch(op) { 
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': 			return 3;
        default:            return 0;
    } 
} 

void inToPostfix(char infix[], char postfix[]) {
    int i, j, top;
    for(i = 0, j = 0, top = 0; infix[i] != '\0'; i++) switch(infix[i]) { 
        case '(':              // 運算子堆疊 
            stack[++top] = infix[i]; 
            break; 
        case '+': case '-': case '*': case '/': case'^':
            while(priority(stack[top]) >= priority(infix[i])) { 
                postfix[j] = stack[top];
                newpostfix[j] = stack[top];
                j++,top--;
            } 
            stack[++top] = infix[i]; // 存入堆疊 
            break; 
        case ')': 
            while(stack[top] != '(') { // 遇 ) 輸出至 ( 
                postfix[j] = stack[top];
                newpostfix[j] = stack[top];
                j++,top--;
            } 
            top--;  // 不輸出 ( 
            break; 
        default:  // 運算元直接輸出 
            postfix[j] = Value[infix[i]-97]+'0';
            newpostfix[j] = infix[i];
            j++;
    }
    while(top > 0) { 
        postfix[j] = stack[top];
        newpostfix[j] = stack[top];
        j++,top--;
    }
} 

double eval(char infix[],int Value[],int size){
    char opnd[2] = {'\0'};
    
    int top, i;
    for(top = 0, i = 0; postfix[i] != '\0'; i++) switch(postfix[i]) { 
        case '+': case '-': case '*': case '/': case '^':
            stack[top - 1] = cal(postfix[i], stack[top - 1], stack[top]); 
            top--; 
            break; 
        default: 
            opnd[0] = postfix[i];
            stack[++top] = atof(opnd);
    }             
    return stack[top];
}

int main(void) { 
	int i;
    scanf("%s",infix);
    getValue(infix,Value);
	inToPostfix(infix,postfix);
	printf("Postfix expression:%s\n",newpostfix);
	printf("getValue:\n");
	printf("eval:%.0f", eval(infix,Value,5));
    return 0; 
}
