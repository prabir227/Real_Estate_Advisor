#include <stdio.h>
#include <string.h>
void insert()
{
    int P_id, bhk, price;
    char Desired_Area[10], locality[40], P_name[50];
    char query[200];
    printf("Enter property id:");
    scanf("%d", &P_id);
    printf("Enter area of your property:");
    scanf("\n");
    scanf("%[^\n]%*c",&Desired_Area);
    printf("Enter number of BHK:");
    scanf("%d", &bhk);
    printf("ENter locality of your property:");
    scanf("\n");
    scanf("%[^\n]%*c",locality);
    printf("Enter name of your property:");
    scanf("\n");
    scanf("%[^\n]%*c",P_name);
    printf("Enter price of ypur property:");
    scanf("%d", &price);
    }
void main(){
    // char var1[10];
    // char var2[20];
    // char var3[20];
    // printf("Enter number: ");
    // gets(var1);
    // printf("ENter another number");
    // gets(var2);
    // printf("\n%s\n",var3);
    insert();
}