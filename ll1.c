#include <stdio.h>
#include <string.h>

char *input_symbols="a+*()$";
char *nonterminals="ESTRF";
char stack[10];
int top=-1;
char table[5][6][4] =
	{	"TS", "", "", "TS", "", "",
		"", "+TS", "", "", "C", "C",
		"FR", "", "", "FS", "", "",
		"", "C", "*FR", "", "C", "C",
		"a", "", "", "(E)", "", ""
	};

void push(char x)
{
	stack[++top]=x;
	stack[top+1]='\0';
}

void pop()
{
	if(top!=-1)
		stack[top--]='\0';
}

int find(char non_terminal, char terminal)
{
	int i, j, k;
	
	for(i=0; i<strlen(nonterminals); i++)
		if(non_terminal==nonterminals[i])
			break;
	for(j=0; j<strlen(input_symbols); j++)
		if(terminal==input_symbols[j])
			break;
	
	if(i!=strlen(nonterminals) && j!=strlen(input_symbols) && strlen(table[i][j])!=0)
	{
		printf("\tM[%c, %c]: ", non_terminal, terminal);
		pop();
		if(table[i][j][0]!='C')
		{
			for(k=strlen(table[i][j])-1; k>=0; k--)
				push(table[i][j][k]);
			printf("%c->%s", non_terminal, table[i][j]);
		}
		else
			printf("%c->Epsilon", non_terminal);
		return 0;
	}
	
	printf("\tReject\n\nInvalid input string.\n");
	return 1;
}

int main()
{
	int error=0, ptr=0, i, j;
	char input[20];
	
	push('$');
	push('E');
	printf("\nEnter the input string: ");
	scanf("%s", input);
	
	printf("\nParsing Table\n-------------\n\t");
	for(i=0; i<strlen(input_symbols); i++)
		printf("%c\t", input_symbols[i]);
		
	printf("\n");
	
	for(i=0; i<strlen(nonterminals); i++)
	{
		printf("%c", nonterminals[i]);
		for(j=0; j<strlen(input_symbols); j++)
		{
		
			printf("\t");
			if(strlen(table[i][j])!=0)
			{
				printf("%c->", nonterminals[i]);
				if(table[i][j][0]!='C')
					printf("%s", table[i][j]);
				else
					printf("Ep");
			}
		}
		printf("\n");
	}
	
	printf("\nStack\tInput\tAction\n");
	printf("-----\t-----\t------\n");
	while(error!=1)
	{
		printf("%s\t%s", stack, &input[ptr]);
		if(stack[top]=='$' && input[ptr]=='$')
		{
			printf("\tAccept\n\nValid input string.\n");
			break;
		}

		
		if(stack[top]==input[ptr])
		{
			printf("\tPop %c, advance ptr", stack[top]);
			ptr++;
			pop();
		}
		else
		{
			error = find(stack[top], input[ptr]);
		}
		printf("\n");
	}
}	
	
	
