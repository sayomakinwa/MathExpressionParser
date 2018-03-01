#include <stdio.h>
#include <math.h>
#include "intstack.h"
#include "list2.h"

long isoperator(long c) { if(c==43||c==45||c==42||c==47||c==37||c==94) return 1; else return 0;}

long calc (long op1, long op, long op2)
{
	switch (op) {
		case 43: return op1+op2; break;
		case 45: return op1-op2; break;
		case 42: return op1*op2; break;
		case 47: return op1/op2; break;
		case 37: return op1%op2; break;
		case 94: return pow(op1, op2); break;
		default: return 0;
	}
}

long precedence(char x)
{
    if(x=='(') return(0);
    if(x=='^') return(1);
    if(x=='+'||x=='-') return(2);
    if(x=='*'||x=='/' || x=='%') return(3);
    return(4);
}

void evaluate (list l)
{
	long op1, op2=0, k=0, calcresult;
	component *ptr;
	if (empty(l)) printf ("List is empty");
	else
	{
		ptr = l->next;
		while (ptr->next != NULL)
		{
			++k;
			if (!isoperator(ptr->element))
			{
				op1 = op2;
				op2 = ptr->element;
				ptr = ptr->next;
			}
			else
			{
				calcresult = calc (op1, ptr->element, op2);
				delete (k,&l);
				insert_in_list (calcresult,k,&l);
				delete (k-1,&l);
				delete (k-2,&l);
				ptr = l->next;
				k=0;
			}
		}
		++k;
		calcresult = calc (op1, ptr->element, op2);
		delete (k,&l);
		insert_in_list (calcresult,k,&l);
		delete (k-1,&l);
		delete (k-2,&l);
	}
	printf("\nThe result of the evaluation: ");
	printlist(l);
}

long main ()
{
	char *str,c,token;
	long i=0,k,x;
	list postfix;
	stack s;
	
	init(&postfix);
	initialize (&s);
	
	printf ("Input any mathematical expression (valid operations include +,-,*,/,%% and ^);\nInput a negative number in the form '(0-n)', e.g. '(0-5)' for '-5':\n");
	str = (char*)malloc(sizeof(char));
	while (c!='\n')
	{
		c=getc(stdin);
		str = (char*)realloc(str, (i+1)*sizeof(char));
		str[i++] = c;
	}
	str[i-1] = '\0';
	k=1;
	for(i=0; str[i]!='\0'; i++)
    {
        token = str[i];
        if(isdigit(token)) 
        	insert_in_list (token-'0', k++, &postfix);
        else if(token == '(') push (&s, '(');
        else if(token == ')')
        	while((x=pop(&s))!='(')
	        	insert_in_list (x, k++, &postfix);
        else {
            while(precedence(token)<=precedence(top(s)) && !stackempty(s))
            {
				x=pop(&s);
				insert_in_list (x, k++, &postfix);
            }
            push(&s,token);
        }
    }

    while(!stackempty(s))
    {
		x=pop(&s);
        insert_in_list (x, k++, &postfix);
    }
    printf ("The postfix version of the expression is: ");
	printlist (postfix);
	evaluate (postfix);
	return 0;
}
