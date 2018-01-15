#include<stdio.h>
#include<string.h>
void main()
{
  FILE *fp1,*fp2,*fp3,*fp4;
  char a[20][20],b[20][20],in[90];
  int i=0,j=0,f=0;
  fp1=fopen("inp.txt","r");
  fp2=fopen("out.txt","w");
  fp3=fopen("nam.txt","w");
  fp4=fopen("def.txt","w");
  
  while(!feof(fp1))
  {fscanf(fp1,"%s",in);
  if(strcmp(in,"#define")==0)
  {
    fprintf(fp2," %s",in);
    fscanf(fp1," %s",a[i]);
    fscanf(fp1,"%s",b[i]);
    fprintf(fp2," %s %s\n",a[i],b[i]);
    fprintf(fp3," %s\n",a[i]);
    fprintf(fp4," %s\n",b[i]);
    i++;
   
 continue;
  }
 for(j=0;j<i;j++)
  {
    if(strcmp(a[j],in)==0)
      {
        fprintf(fp2," %s",b[j]);
       f=1;
     break;
      }
   }
  if(f==0)
  {
    if((strcmp(in,";")==0)||(strcmp(in,"{")==0)||(strcmp(in,"}")==0)||(strcmp(in,")")==0))
      {
         fprintf(fp2," %s\n",in);
      }
     else
      {
         fprintf(fp2," %s",in);
      }
  }f=0;
   
 }
fclose(fp1);
fclose(fp2);
fclose(fp3);
fclose(fp4);
}
