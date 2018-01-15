#include <stdio.h>

int main()
{
	char str[100];
	char sub[7];
	int i, len, strt, tlen, tstart;

	FILE *fp, *fp1;


	fp = fopen("inp.dat", "r");
	if (fp==NULL)
	{
		printf("Error opening the file");
	}
	else
	{
		if ((fp1=fopen("out.dat", "w"))==NULL)
		{
			
			printf("\nError opening the output file");
		}
		while (fgets(str, 100, fp)!=NULL)
		{
			if (str[0]=='H')
			{
			  for (i=1; i<=6; i++)
			    sub[i-1] = str[i];
			  sub[6]='\0';
			  sscanf(sub, "%x", &len);

			  for (i=7; i<=12; i++)
				sub[i-7] = str[i];
			  sub[6]='\0';
			  sscanf(sub, "%x", &strt);

			}

			//else if(len>0)
			{
			    	if (str[0]=='T')
			    	{
					for (i=1; i<=6; i++)
					sub[i-1] = str[i];
					sub[6]='\0';
					sscanf(sub, "%x", &tstart);

					sub[0]=str[7];
					sub[1]=str[8];
					sub[2]='\0';
					sscanf(sub, "%x", &tlen);
					
					
					

					for (i=0;i<2*tlen; i+=2)
					{
						
						fprintf(fp1, "%x\t%c%c\n", tstart, str[9+i], str[10+i]);
					tstart++;
					}


			    	}
				
				if (str[0]=='E')
					break;
				
			
			}


		}

		fclose(fp);
	}
	return 0;
}
