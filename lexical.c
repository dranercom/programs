#include <stdio.h>
#include <string.h>

char *keywords = "intfloachrwed", temp[100], stack[20], top=-1;

int FA[17][13] = 
		{1, 0, 0, 3, 0, 0, 0, 7, 0, 0, 12, 0, 16
		, 0, 2, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0
		, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		, 0, 0, 0, 0, 4, 10, 0, 0, 0, 0, 0, 0, 0
		, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0
		, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0
		, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0
		, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0
		, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, 0, 0
		, 0, 0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0
		, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, 0, 0
		, 0, 0, 0, 0, 0, 0, 0, 0, 13, 0, 0, 0, 0
		, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0
		, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0
		, 0, 0, 0, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0};

int idFA[3][2] = {1, 2, 1, 1, 0, 2};
/*
	i	n	t	f	l	o	a	c	h	r	w	e	d
	1	0	0	3	0	0	0	7	0	0	12	0	16
	0	2	0	-2	0	0	0	0	0	0	0	0	0
	0	0	-2	0	0	0	0	0	0	0	0	0	0
	0	0	0	0	4	10	0	0	0	0	0	0	0
	0	0	0	0	0	5	0	0	0	0	0	0	0
	0	0	0	0	0	0	6	0	0	0	0	0	0
	0	0	-2	0	0	0	0	0	0	0	0	0	0
	0	0	0	0	0	0	0	0	8	0	0	0	0
	0	0	0	0	0	0	9	0	0	0	0	0	0
	0	0	0	0	0	0	0	0	0	-2	0	0	0
	0	0	0	0	0	11	0	0	0	0	0	0	0
	0	0	0	0	0	0	0	0	0	-2	0	0	0
	0	0	0	0	0	0	0	0	13	0	0	0	0
	14	0	0	0	0	0	0	0	0	0	0	0	0
	0	0	0	0	15	0	0	0	0	0	0	0	0
	0	0	0	0	0	0	0	0	0	0	0	-2	0
	0	0	0	0	0	-2	0	0	0	0	0	0	0
	
	c	digit
0	1	2
1	1	1
2	-1	2

*/
void push(char x)
{
	stack[++top] = x;
	stack[top+1] = '\0';
}

void pop()
{
	while(top!=-1)
		stack[--top]='\0';
}

int findState (int state, char x)
{
	int i;
	for(i=0; i<strlen(keywords); i++)
		if(x==keywords[i])
			return FA[state][i];
	return 0;
}

int findIdState(int state, char x)
{
	if((x>=65 && x<=90) || (x>=97 && x<=122) || x=='_')
		return idFA[state][0];
	else if (x>=48 && x<=57)
		return idFA[state][1];
	else
		return 0;
}

int opcheck(char x)
{
	if(x=='+'|| x=='-' || x=='*' || x=='/' || x=='^' || x=='%'|| x=='>' || x=='<' || x=='=')	
		return 1;
	else
		return 0;
}

int spcheck(char x)
{
	if (x==';' || x==',' || x==' ' || x==')' || x=='}' || x==']')
		return 1;
	else
		return 0;
}

int main()
{
	
	FILE * fp;
	
	int i, state=0, idstate=0, tmp;
		
	if((fp = fopen("inp3.txt", "r")) == NULL)
		printf("\nError opening the file");
	else
	{
		while(fgets(temp, 100, fp))
		{	
			pop();
			printf("\n--------------\n%s", temp);
			for(i=0; i<strlen(temp); i++)
			{		//printf("this");
				if(state == -2 && (temp[i]==' '|| temp[i]=='(' || temp[i]=='\n'))
				{	
					printf("\n%s:\tkeyword", stack);
					pop();
					state = 0;
					idstate = 0;
				}
				else if(state!=-2 && temp[i]=='(')
				{
					printf("\n%s:\tfunction call", stack);
					pop();
					state = 0;
					idstate = 0;
				}
				else if(idstate==1 && (spcheck(temp[i]) || opcheck(temp[i])))
				{
					printf("\n%s:\tidentifier", stack);
					pop();
					state = 0;
					idstate = 0;
				}
				
				else if(idstate==2 && (spcheck(temp[i]) || opcheck(temp[i])))
				{
					printf("\n%s:\tliteral", stack);
					pop();
					state = 0;
					idstate = 0;
				}
				else
				{
					if(temp[i]!='\n' && temp[i]!='\t')
						push(temp[i]);
					state = findState(state, temp[i]);
					if(idstate!=-1)
						idstate = findIdState(idstate, temp[i]);
						//printf("%d.", idstate);
				}
				
				if(opcheck(temp[i]))
				{
					printf("\n%c:\toperator", temp[i]);
					pop();
				}
				
				if(spcheck(temp[i]))
					pop();
				
				
			}
		}
	}
}
	
