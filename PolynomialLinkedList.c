#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
	int coef;
	int exp;
	struct Node * next;
}Node,*Polynomial;

Polynomial h[26]={NULL},cp[26]={NULL};
int stack[100];
char infix[100], postfix[100],a[100];

Polynomial create();
Polynomial insertTerm(Polynomial poly, int coef, int exp);
void printPoly(Polynomial p);
void printAllPoly(Polynomial p,int i);
void display(Polynomial p);
Polynomial add(Polynomial p1, Polynomial p2);
Polynomial subtract(Polynomial p1, Polynomial p2);
Polynomial multiply(Polynomial p1, Polynomial p2);

int priority(char op);
void inToPostfix(char infix[], char postfix[]);
Polynomial eval();
Polynomial cal(char op, Polynomial p1, Polynomial p2);

int main(){
	
	int i=0,flag=0,asc=0;
	char alph[10];
	
	int choice=0;
	do{
	scanf("%d",&choice);
		switch(choice){
			case 1://InputPoly
				scanf("%s",alph);
				asc=alph[0]-64;
				h[asc]=NULL;
				h[asc] = create();
				break;
			case 2://PrintPolys
				scanf("%s",alph);
				asc=alph[0]-64;
				printPoly(h[asc]);
				break;
			case 3://PrintAllPolys
				i=0;
				flag=0;
				while(i++<26){
					if(h[i] == NULL) 
						flag=0;
					else
						flag=1;break;
				}
				if(flag==0){
					printf("no polynomial\n");
				}
				else{
					i=0;
					while(i++<26){
						printAllPoly(h[i],i);
					}
				}
				break;
			case 4://PolyMultiOperation
				for(i=0;i<26;i++){
					cp[i]=NULL;
					cp[i] = h[i];
				}
				scanf("%s",infix);
				inToPostfix(infix,postfix);
				Polynomial result = NULL;
				result=eval();
				display(result);
				break;
		}
	}while(choice!=5);
	printf("leave");
}

Polynomial create() {
	int v=0,d=0;
	
	Polynomial poly = NULL;
	while(scanf("%d\n%d",&v,&d)){
		if(v==-1 && d==-1)
			break;
		else
			poly = insertTerm(poly, v, d);
	}
	return poly;
}

Polynomial insertTerm(Polynomial poly, int coef, int exp) {

	if (coef == 0) return poly;
	Polynomial current = poly;

	if (poly == NULL) {		//create the head of the polynomial
		poly = (Polynomial) malloc (sizeof(Node));
		poly->coef = coef;
		poly->exp = exp;
		poly->next = NULL;
	}
	else if (poly->exp < exp) {	//replace the head of the polynomial
		Polynomial n = (Polynomial) malloc (sizeof(Node));
		n->coef = coef;
		n->exp = exp;
		n->next = poly;
		poly = n;
	}
	else if (poly->exp == exp) {	//add like terms in the head
		poly->coef += coef;
	}
	else {	//adding terms anywhere after the head

		while (current->next != NULL && exp < current->next->exp) {
			current = current->next;
		}	//done traversing the list
		if (current->next == NULL) {	//add term to end of the list
			current->next = (Polynomial) malloc (sizeof(Node));
			current= current->next;

			current->next = NULL;
			current->coef = coef;
			current->exp = exp;
		}
		else if (current->next->exp == exp) {	//combine like terms
			current->next->coef += coef;
		}
		else {	//add the new term in the middle of the list
			Polynomial n = (Polynomial) malloc (sizeof(Node));
			n->coef = coef;
			n->exp = exp;
			//TODO: use get_line() to read input from the command line
			n->next = current->next;
			current->next = n;
		}
	}
	return poly;
}

void printPoly(Polynomial p) {
	Polynomial current = p;
	if(current==NULL){
		printf("polynomialis not exist\n");
	}
	else{
		while (current != NULL) {
			if (current != p && current->coef >= 0) printf("+");
			else if (current->coef < 0) printf("-");
	
			//print the coefficient and the term x if applicable
			if (current->coef > 0) printf("%d", current->coef);
			else if (current->coef == 1 && current->exp  == 0) printf("%d", current->coef);
			else if (current->coef < 0) printf("%d", -current->coef);
	
			if (current->coef != 0 && current->exp != 0) printf("x");
	
			if (current->coef != 0 && current->exp != 0) printf("^%d", current->exp);
	
			if (current->next != NULL) current = current->next;
			else current = NULL;
		}
		printf("\n");
	}
}

void printAllPoly(Polynomial p,int i) {
	Polynomial current = p;
	if(current!=NULL){
		printf("%c=",i+64);
		while (current != NULL) {
			if (current != p && current->coef >= 0) printf("+");
			else if (current->coef < 0) printf("-");
	
			//print the coefficient and the term x if applicable
			if (current->coef > 0) printf("%d", current->coef);
			else if (current->coef == 1 && current->exp  == 0) printf("%d", current->coef);
			else if (current->coef < 0) printf("%d", -current->coef);
	
			if (current->coef != 0 && current->exp != 0) printf("x");
	
			if (current->coef != 0 && current->exp != 0) printf("^%d", current->exp);
	
			if (current->next != NULL) current = current->next;
			else current = NULL;
		}
		printf("\n");
	}
}

void display(Polynomial p) {
	Polynomial current = p;

	while (current != NULL) {
		if (current != p && current->coef >= 0) printf("+");
		else if (current->coef < 0) printf("-");

		//print the coefficient and the term x if applicable
		if (current->coef > 0) printf("%d", current->coef);
		else if (current->coef == 1 && current->exp  == 0) printf("%d", current->coef);
		else if (current->coef < 0) printf("%d", -current->coef);

		if (current->coef != 0 && current->exp != 0) printf("x");

		if (current->coef != 0 && current->exp != 0) printf("^%d", current->exp);

		if (current->next != NULL) current = current->next;
		else current = NULL;
	}
	printf("\n");
}

Polynomial add(Polynomial p1, Polynomial p2) {
	//verify the inputs
	if (p1 == NULL && p2 != NULL) return p2;
	if (p1 != NULL && p2 == NULL) return p1;
	if (p1 == NULL && p2 == NULL) return NULL;

	Polynomial polySum, c1, c2, cSum;

	polySum = NULL;
	cSum = polySum;		//pointers for incrementation
	c1 = p1;
	c2 = p2;

	while (c1 != NULL || c2 != NULL) {	//while there are still terms to add
		int newCoef = 0;
		int newExp = 0;

		if (c1 != NULL && c2 != NULL) {	//if both terms exist
			if (c1->exp == c2->exp) {	//add like terms
				newCoef = c1->coef + c2->coef;
				newExp = c1->exp;

				c1 = c1->next;	//next terms in both polynomials
				c2 = c2->next;
			}
			else if (c1->exp > c2->exp) {	//add the larger term
				newCoef = c1->coef;
				newExp = c1->exp;

				c1 = c1->next;	//next term in polynomial addition source
			}
			else {			//add the larger term (c2 > c1)
				newCoef = c2->coef;
				newExp = c2->exp;

				c2 = c2->next;	//next term in polynomial source
			}
		}
		else if (c2 == NULL) {	//if either term is null, add the other one
			newCoef = c1->coef;
			newExp = c1->exp;

			c1 = c1->next;
		}
		else {
			newCoef = c2->coef;
			newExp = c2->exp;

			c2 = c2->next;
		}

		polySum = insertTerm(polySum, newCoef, newExp);
	}

	return polySum;
}

Polynomial subtract(Polynomial p1, Polynomial p2) {
	Polynomial difference;
	Polynomial c2 = p2;

	//negate p2
	while (c2 != NULL) {
		c2->coef *= -1;
		c2 = c2->next;
	}

	difference = add(p1, p2);

	//put p2 back to normal
	c2 = p2;
	while (c2 != NULL) {
		c2->coef *= -1;
		c2 = c2->next;
	}
	return difference;
}

Polynomial multiply(Polynomial p1, Polynomial p2) {
	if (p1 == NULL && p2 != NULL) return p2;
	if (p1 != NULL && p2 == NULL) return p1;
	if (p1 == NULL && p2 == NULL) return NULL;

	Polynomial polyProd, c1, c2;
	int newCoef = 0;
	int newExp = 0;

	polyProd = NULL;
	c1 = p1;
	c2 = p2;

	while (c1 != NULL) {
		c2 = p2;
		while (c2 != NULL) {
			//use create methods
			newCoef = c1->coef * c2->coef;
			newExp = c1->exp + c2->exp;

			polyProd = insertTerm(polyProd, newCoef, newExp);
			c2 = c2->next;
		}
		c1 = c1->next;
	}
	return polyProd;
}

int priority(char op) { 
    switch(op) { 
        case '+': case '-': return 1;
        case '*': 		    return 2;
        default:            return 0;
    } 
} 

void inToPostfix(char infix[], char postfix[]) {
    int i, j, top;
    for(i = 0, j = 0, top = 0; infix[i] != '\0'; i++) switch(infix[i]) { 
        case '(':              // 運算子堆疊 
            stack[++top] = infix[i]; 
            break; 
        case '+': case '-': case '*':
            while(priority(stack[top]) >= priority(infix[i])) { 
                postfix[j] = stack[top];
                j++,top--;
            } 
            stack[++top] = infix[i]; // 存入堆疊 
            break; 
        case ')': 
            while(stack[top] != '(') { // 遇 ) 輸出至 ( 
                postfix[j] = stack[top];
                j++,top--;
            } 
            top--;  // 不輸出 ( 
            break; 
        default:  // 運算元直接輸出 
            postfix[j] = infix[i];
            j++;
    }
    while(top > 0) { 
        postfix[j] = stack[top];
        j++,top--;
    }
} 

Polynomial cal(char op, Polynomial p1, Polynomial p2) { 
	Polynomial r = NULL;
    switch(op) { 
        case '+':
			r=add(p1,p2); 
			return r; 
        case '-': 
			r=subtract(p1,p2); 
			return r; 
        case '*': 
			r=multiply(p1,p2); 
			return r; 
    }
}

Polynomial eval(){
    char opnd[2] = {'\0'};
    
    int top, i;
    for(top = 0, i = 0; postfix[i] != '\0'; i++) {
    	switch(postfix[i]) {
	        case '+': case '-': case '*':
	            cp[a[top - 1]-64] = cal(postfix[i], cp[a[top - 1]-64], h[a[top]-64]);
	            top--;
	            break; 
	        default: 
	            opnd[0] = postfix[i];
	            a[++top] = opnd[0];
	    }
	}   
	return cp[a[top]-64];
}
