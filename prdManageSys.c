#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define ENTER_KEY 13

const char* PRODUCT_FORMAT_IN ="%s %s %d %f %d"; //fscanf
const char* PRODUCT_FORMAT_OUT ="%s %s %d %f %d\n"; //fprintf

typedef struct{
    char name[20];
    char company[20];
    int id;
    float price;
    int quantity;
}product;

void welcome();
void login();
void menu();

void addProduct();
void deleteProduct();
void searchProduct();
void readItem();
void editItem();

int main(){
    welcome();
    login();
   //menu();
}
void welcome(){
    time_t t;
    time(&t);
    printf("\t\t\t\t%s",ctime(&t));
    printf("\n\n\n\n");
    printf("\t\t\tWELCOME TO PRODUCT MANAGEMENT SYSTEM!!");
    printf("\n\n\n\n\n\n\t\t\t Press any key to continue........\n");
    getch();
    system("cls");
}

void login(){
    int i=0,tag=0;
    char c;
    char uname[10];
    char pswrd[10];
    do{
    printf("========================LOGIN========================");
    printf("\n\t\tUSER:");
    scanf("%s",&uname);
    printf("\n\t\tPASSWORD:");
    while(i<10)
    {
        pswrd[i]=getch();
        c=pswrd[i];//p
        if(c== ENTER_KEY)break; //ENTER_KEY = '\r'
        else printf("*");
        i++;
    }
    pswrd[i]='\0';

    if(strcmp(uname,"user")==0 && strcmp(pswrd,"pass")==0){
        printf("\n\t\t\tLOGIN SUCCESSFUL!");
        getch();
        menu();
    }else
        printf("\n\t\t\tSORRY!! LOGIN UNSUCCESSFUL\n");
        getch();//holds
        tag++;
}while(tag<5);
    if(tag==5)
        printf("\nYOU HAVE ENTERED WRONG USER NAME AND PASSWORD 5 TIMES!!!\n");
        getch();//holds
}

void menu(){
    system("cls");
    int choice;
    printf("========================MENU========================");
    printf("\n\t1. ADD PRODUCT");
    printf("\n\t2. DELETE PRODUCT");
    printf("\n\t3. SEARCH PRODUCT");
    printf("\n\t4. READ ITEMS");
    printf("\n\t5. EDIT ITEMS");
    printf("\n\t6. EXIT!");

    printf("\nEnter your choice [1-6]:");
    scanf("%d",&choice);

    switch(choice){
    case 1:
        addProduct();
        break;
    case 2:
        deleteProduct();
        break;
    case 3:
        searchProduct();
        break;
    case 4:
        readItem();
        break;
    case 5:
        editItem();
        break;
    case 6:
        printf("System Exit!");
        exit(0);
        break;
    default:
        printf("Invalid Choice!! System Exit\n");
        getch();
    }
}
void addProduct(){
    system("cls");
    int i=1;
    char ch;
    product p1,p2;
    fflush(stdin);
    printf("============ADD A PRODUCT DETAILS============\n");
    printf("\tPRODUCT NAME:");
    scanf("%s",(&p1.name));
    fflush(stdin);
    printf("\tCOMPANY NAME:");
    scanf("%s",(&p1.company));
    printf("\tPRODUCT ID:");
    scanf("%d",(&p1.id));
    printf("\tPRICE:");
    scanf("%f",(&p1.price));
    printf("\tQUANTITY:");
    scanf("%d",(&p1.quantity));

    FILE* outFile = fopen("productList.txt","a+");
    if(outFile != NULL){
        //Writing PRODUCT_FORMAT_OUT format to "productList.txt" file
        fprintf(outFile,PRODUCT_FORMAT_OUT,p1.name,p1.company,p1.id,p1.price,p1.quantity);
        fseek(outFile,0,SEEK_SET);
        fclose(outFile);
        printf("\n-------ADDED DETAILS------\n");
        printf("\tPRODUCT ID: %d\n\tPRODUCT NAME: %s\n\tCOMPANY NAME: %s\n\tPRICE:%f\n\tQUANTITY: %d\n",p1.id,p1.name,p1.company,p1.price,p1.quantity);
    }else{
        printf("File is not created!!");
    }
    getch();
    menu();

}
void deleteProduct(){
    system("cls");
    FILE *fp,*tempFile;
    product p1;
    char target[40];
    char str;
    int found;
    product p2;
    fp= fopen("productList.txt","r");
    tempFile=fopen("TempFile.txt","w+");
    printf("\n\n\t\tENTER PRODUCT NAME TO DELETE:");
    fflush(stdin);
    gets(target);
    while(fscanf(fp,PRODUCT_FORMAT_IN,p1.name,p1.company,&p1.id,&p1.price,&p1.quantity) != EOF)
    {
        if(strcmp(target,p1.name)==0)
        {
            found = 1;
        }else{
            fprintf(tempFile,PRODUCT_FORMAT_OUT,p1.name,p1.company,p1.id,p1.price,p1.quantity);
        }
    }if(!found){
        printf("\n\t\tRecord not Found!!");
    }else{
        printf("\n\t\tRecord Deleted!");
    }
    fclose(fp);fclose(tempFile);
    remove("productList.txt");
    rename("tempFile.txt","productList.txt");
    printf("\n\n\n\n\n\n\t\t\t Press any key to go to menu........\n");
    getch();
    menu();
}
void searchProduct(){
    system("cls");
    product p1;
    int flag =0;
    char target[20];
    printf("\n\n\t\tENTER PRODUCT NAME:");
    scanf("%s",target);
    FILE* fp =fopen("productList.txt","r");
    while(fscanf(fp,PRODUCT_FORMAT_IN,p1.name,p1.company,&p1.id,&p1.price,&p1.quantity)!= EOF){
        if(strcmp(target,p1.name)==0){
            flag=1;
            printf("\n-------Product Detail:-------\n");
            printf("PRODUCT ID:%d\n",p1.id);
            printf("PRODUCT NAME:%s\n",p1.name);
            printf("COMPANY NAME:%s\n",p1.company);
            printf("PRICE:%.3lf\n",p1.price);
            printf("QUANTITY:%d\n\n",p1.quantity);
        }
    }
    fclose(fp);
    if(!flag){
           printf("Product ID does not found.\n");
    }
    printf("\n\n\n\n\n\n\t\t\t Press any key to go to menu........\n");
    getch();
    menu();
}
void readItem(){
    system("cls");
    FILE* fp;
    fp = fopen("productList.txt","r+");
    //fp1 = fopen("TempList.txt","w+");
    product p1;
    if(fp == NULL){
            printf("File do not exist!");
    }else{
        printf("PRODUCT NAME COMPANY NAME PRODUCT ID\tPRICE \tQUANTITY\n");
        while(fscanf(fp,"%s %s %d %f %d",p1.name,p1.company,&p1.id,&p1.price,&p1.quantity) != EOF){
            printf(" %s\t\t%s\t\t%d\t%.3lf\t %d\n",p1.name,p1.company,p1.id,p1.price,p1.quantity);
        }fclose(fp);
    }
    printf("\n\n\n\n\n\n\t\t\t Press any key to go to menu........\n");
    getch();
    menu();
}
void editItem(){
    system("cls");
    product p1,p2;
    int id,flag = 0;
    printf("\n\n\t\tENTER PRODUCT ID TO EDIT:");
    scanf("%d",&id);
    FILE *fp,*fp1;
    fp =fopen("productList.txt","r");
    fp1 =fopen("TempFile.txt","w+");

    if(fp == NULL){
        printf("File do not exist!");
    }else{
        while(fscanf(fp,PRODUCT_FORMAT_IN,p1.name,p1.company,&p1.id,&p1.price,&p1.quantity)!= EOF){
            if(p1.id==id){
                flag=1;
                printf("\tPRODUCT NAME:");
                scanf("%s",p2.name);
                printf("\tCOMPANY NAME:");
                scanf("%s",p2.company);
                printf("\tEDIT PRODUCT ID:");
                scanf("%d",&p2.id);
                printf("\tPRICE:");
                scanf("%f",&p2.price);
                printf("\tQUANTITY:");
                scanf("%d",&p2.quantity);
                fprintf(fp1,"%s %s %d %f %d\n",p2.name,p2.company,p2.id,p2.price,p2.quantity);
                printf("\n-------NEW PRODUCT DETAILS-------\n");
                printf("\tNEW PRODUCT NAME:%s\n\tNEW COMPANY NAME:%s\n\tNEW PRODUCT ID:%d\n\tPRICE:%.3lf\n\tQUANTITY:%d\n",p2.name,p2.company,p2.id,p2.price,p2.quantity);
            }else{
                fprintf(fp1,PRODUCT_FORMAT_OUT,p1.name,p1.company,p1.id,p1.price,p1.quantity);
            }
        }
        if(!flag){
                printf("Product ID does not found.\n");
        }
    }
    fclose(fp);fclose(fp1);
    remove("productList.txt");
    rename("TempFile.txt","productList.txt");
    printf("\n\n\n\n\n\n\t\t\t Press any key to go to menu........\n");
    getch();
    menu();
}
