// Kartikey Sharan
// 1001659433

#include <stdio.h>
void PrintBinary (int []);
void ConvertDecimalToBinary(int , int []);

int main()
{
    int input;
    int binary[7];
   
    printf("Decimal to Binary Converter.\n");
    printf("Please enter a decimal number between 0 and 255: ");
    scanf("%d",&input);
    
    while((input<0)||(input>255))
    {
        printf("You entered a number not between 0 and 255\n");
        printf("Please enter a decimal number between 0 and 255: ");
        scanf("%d",&input);
    }
    
    printf("Decimal %d converts to binary ",input);
    ConvertDecimalToBinary(input, binary);
    PrintBinary(binary);
    return 0;
}

void ConvertDecimalToBinary(int input, int binary[])
{
    int j;
   
    for (j=0; j<=7; j++)
    
    {
      
      if (input&1)
        {
        binary[j]=1;
        }
      else
        {
        binary[j]=0;
        }
        
        input= input>>1;
      
    }
}

void PrintBinary (int binary[])
{
    int k;
    for (k=7;k>=0;k--)
    
       {
        printf("%d",binary[k]);
       }
    
    printf("\n");
}



