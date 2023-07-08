#include<stdio.h>
#include<string.h>
char prod[3][15]={"A->aBa","B->bB","B->@"};
char table[2][3][3]={  {"aBa"," "," "}, {"@","bB"," "} };
int size[2][3]={3,0,0,1,2,0},n;
char s[20],stack[20];

void display(int i,int j)
{
   int k;
   for(k=0;k<=i;k++)
     printf("%c",stack[k]);
   printf(" \t");
   for(k=j;k<n;k++)
      printf("%c",s[k]);
   printf("\n");
}

void main()
{
   int i,j,k,row,col,flag=0;
   printf("\nThe grammar is:\n");
   for(i=0;i<3;i++)
      printf("%s\n",prod[i]);
   printf("\nPredictive parsing table is \n\n"); 
   printf("\ta\tb\t$\n"); 
   printf("----------------\n");
   for(i=0;i<2;i++)
   {
      if(i==0)
        printf("A  ");
      else 
         printf("\nB  ");
      for(j=0;j<3;j++)
      {
        printf("\t%s",table[i][j]);
      }
   }
   printf("\nEnter the input string:");
   scanf("%s",s);
   strcat(s,"$");
   n=strlen(s);
   stack[0]='$';
   stack[1]='A';
   i=1;
   j=0;
   printf("\nStack \tInput");
   printf("\n---------------\n");
   while(1)
   {
      if(stack[i]==s[j])
      {
        i--;
        j++;
        if(stack[i]=='$' && s[j]=='$')
        {
           printf("$   $\nSuccess\n");  
           break;
        }
        else if(stack[i]=='$' && s[j]!='$')
        {
           printf("ERROR\n");      
           break;
        }
        display(i,j);
      }
      switch(stack[i])
      {
         case 'A':row=0;    
                       break;
         case 'B':row=1;   
                       break;
      }
      switch(s[j])
      {
         case 'a':col=0;   
                      break;
         case 'b':col=1;   
                      break;
         case '$':col=2;   
                      break;
      }
    //   if(table[row][col][0]=='\0')
    //   {
    //       printf("ERROR\n");   
    //       break;
    //   }
      if(table[row][col][0]=='@')
      {
         i--;
         display(i,j);
      }
      else
      {
         for(k=size[row][col]-1;k>=0;k--)
         {
            stack[i]=table[row][col][k];
            i++;
         }
         i--;
         display(i,j);   
      }
   }  
}

/* output

The grammar is:
A->aBa
B->bB
B->@

Predictive parsing table is 

        a       b       $
----------------
A       aBa              
B       @       bB       
Enter the input string:abba

Stack   Input
---------------
$aBa    abba$
$aB     bba$
$aBb    bba$
$aB     ba$
$aBb    ba$
$aB     a$
$a      a$
$   $
Success

*/