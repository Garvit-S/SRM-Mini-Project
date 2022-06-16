#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h> 
#include <string.h>

int main()
{
    FILE *fp, *ft;
    char another, choice;
    struct emp
    {
        char name[40];
        char id[40];
        int age; 
        float bs;
    };

    struct emp e;
    char empname[40];
    char stdid[40];
    long int recsize;
    fp = fopen("EMP.DAT","rb+");
    if(fp == NULL)
    {
        fp = fopen("EMP.DAT","wb+");
        if(fp == NULL)
        {
            printf("Cannot open file");
            exit(1);
        }
    }
    recsize = sizeof(e);
    while(1)
    {
        system("cls");
        printf("1. Add Record"); 
        printf("\n2. List Records"); 
        printf("\n3. Modify Records"); 
        printf("\n4. Delete Records");
        printf("\n5. Exit"); 
        printf("\nYour Choice: "); 
        fflush(stdin); 
        choice  = getche();
        switch(choice)
        {
        case '1': 
            system("cls");
            fseek(fp,0,SEEK_END);

            another = 'y';
            while(another == 'y') 
            {
                printf("\nEnter Student ID: ");
                scanf("%s",e.id);
                printf("\nEnter Name: ");
                scanf("%s",e.name);
                printf("\nEnter Age: ");
                scanf("%d", &e.age);
                printf("\nEnter Marks: ");
                scanf("%f", &e.bs);

                fwrite(&e,recsize,1,fp); 

                printf("\nAdd another record(y/n) ");
                fflush(stdin);
                another = getche();
            }
            break;
        case '2':
            system("cls");
            rewind(fp); 
            while(fread(&e,recsize,1,fp)==1)
            {
                printf("\n%s %s %d %.2f",e.id,e.name,e.age,e.bs);
            }
            getch();
            break;

        case '3':
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("\nEnter the Student ID to modify: ");
                scanf("%s", stdid);
                rewind(fp);
                while(fread(&e,recsize,1,fp)==1) 
                {
                    if(strcmp(e.id,stdid) == 0) 
                    {
                        printf("\nEnter modified Marks: ");
                        scanf("%f",&e.bs);
                        fseek(fp,-recsize,SEEK_CUR); 
                        fwrite(&e,recsize,1,fp); 
                        break;
                    }
                }
                printf("\nModify another record(y/n)");
                fflush(stdin);
                another = getche();
            }
            break;
        case '4':
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("\nEnter Student ID to delete: ");
                scanf("%s",stdid);
                ft = fopen("Temp.dat","wb"); 
                rewind(fp); 
                while(fread(&e,recsize,1,fp) == 1) 
                {
                    if(strcmp(e.id,stdid) != 0)  
                    {
                        fwrite(&e,recsize,1,ft);
                    }
                }
                fclose(fp);
                fclose(ft);
                remove("EMP.DAT"); 
                rename("Temp.dat","EMP.DAT"); 
                fp = fopen("EMP.DAT", "rb+");
                printf("Delete another record(y/n)");
                fflush(stdin);
                another = getche();
            }
            break;
        case '5':
            fclose(fp);  
            exit(0); 
        }
    }
    return 0;
}