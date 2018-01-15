#include <stdio.h>
#include <string.h>

char *terminals = "$+*a";


char findPrecedence(char top, char inp)
{
	int i, j;
	for(i=0; i<strlen(terminals); i++)
		if(terminals[i]==top)
			break;
	
	for(j=0; j<strlen(terminals); j++)
		if(terminals[j]==inp)
			break;
			
	if((j==0 && i==0) || (i==3 && j==3))
		return '-';
	else if (i>=j)
		return '>';
	else
		return '<';
}

void insert_between(char *x, char item)
{
	int i;
	for(i=strlen(x)+1; i>0; i--)
		x[i]=x[i-1];
	*(x+1) = item;
}

void shift(char *x)
{
	int i, j;
	for(j=0; j<3; j++)
		for(i=0; i<strlen(x); i++)
			*(x+i)=*(x+i+1);
}

int main()
{
	char input[20], ptr;
	int i, j, converted=0, error=0;
	
	printf("Precedence Table\n---------- -----\n\t");
	for(i=0; i<strlen(terminals); i++)
		printf("%c\t", terminals[i]);
	printf("\n");
	for(i=0; i<strlen(terminals); i++)
	{
		printf("%c\t", terminals[i]);
		for(j=0; j<strlen(terminals); j++)
			printf("%c\t", findPrecedence(terminals[i], terminals[j]));
		printf("\n");
	}
		
	
	printf("\nEnter the input string starting and ending with $ : ");
	scanf("%s", input);
	
	while(!error)
	{
		
		if(input[0]=='$' && input[1]=='$')
		{
			printf("\nSuccess");
			break;
		}
	
		for(i=0; i<strlen(input)-1; i+=2)
		{
			if(findPrecedence(input[i], input[i+1])=='-')
			{
				printf("\nError");
				error=1;
				break;
			}
			if(input[i+1]=='>' || input[i+1]=='<')
				continue;
			insert_between(&input[i], findPrecedence(input[i], input[i+1]));
		}
		
		if(error)
			break;
		
		printf("\n%s", input);
	
		if(!converted)
		{
			for(i=0; i<strlen(input); i++)
				input[i] = (input[i]=='a')?'E':input[i];
			printf("\n%s", input);
			converted = 1;
		}
		
	
		for(i=1; i<strlen(input)-1; i++)
		{
			if(input[i-1]=='<' && input[i+1]=='>')
				shift(&input[i-1]);
		}
	
		printf("\n%s", input);
		
	}
	printf("\n");
}
	
