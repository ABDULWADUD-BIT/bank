#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void reg();
void tran();
void display();
void send_money();
void search();
int choice;
int call = 1;
struct bank_user {
    char my_name[100];
    char fa_name[100];
    char ma_name[100];
    long long int id;
    long long int pass;
    long long int blance;

};

struct add_money{
    char my_name[100];
    long long int id;
    long long int money;

};
void display(){

printf("                                   *************YCYC BANK LIMITED*************                ");
printf("\n");
printf("account create enter 1: ");
printf("\n");
printf("account sign in 2: ");
printf("\n");
printf("add money enter 3: ");
printf("\n");
printf("send money enter 4 :");
printf("\n");
printf("serach enter 5 : \n");
printf("option : ");
scanf("%d",&choice);
getchar();
}

void reg(){



    if (choice == 1) {
        struct bank_user s1;
        printf("Enter name: ");
        fgets(s1.my_name, sizeof(s1.my_name), stdin);//scanf use on console
        printf("FATHER NAME: ");
        fgets(s1.fa_name, sizeof(s1.fa_name), stdin);
        printf("MOTHER NAME : ");
        fgets(s1.ma_name, sizeof(s1.ma_name), stdin);
        printf("Enter ID: ");
        scanf("%lld", &s1.id);
        printf("Enter PASSWRD: ");
        scanf("%lld", &s1.pass);
        printf("amount  :");
        scanf("%lld",&s1.blance);
        printf("Name: %s", s1.my_name);
        printf("FATHER Name: %s", s1.fa_name);
        printf("MOTHER Name: %s", s1.ma_name);
        printf("ID: %lld\n", s1.id);
        printf("password: %lld\n", s1.pass);
        printf("amount : %lld\n",s1.blance);
        FILE *ptr = fopen("ff.txt", "a+");
        fprintf(ptr,"%s %s %s %lld %lld %lld\n\n",s1.my_name, s1.fa_name, s1.ma_name, s1.id, s1.pass,s1.blance);//write in file

        fclose(ptr);

        FILE *npp = fopen("sf.txt", "a+");
        fprintf(npp,"%s   %lld    %lld\n\n",s1.my_name,s1.id,s1.blance);

        fclose(npp);

    }
    else if (choice == 2) {
        char name[100];
        long long int password;
        struct bank_user s1;

        printf("Enter your name: ");
        scanf("%s",name);

        printf("Enter your password: ");
        scanf("%lld", &password);

        FILE *ptr = fopen("ff.txt", "r+");

        while (fscanf(ptr, "%s %s %s %lld %lld %lld",
                      s1.my_name, s1.fa_name, s1.ma_name, &s1.id, &s1.pass,&s1.blance) != EOF) {

            if ((strcmp(s1.my_name, name) == 0) && (s1.pass == password)) {
                printf("Name: %s\n", s1.my_name);
                printf("Father's Name: %s\n", s1.fa_name);
                printf("Mother's Name: %s\n", s1.ma_name);
                printf("ID: %lld\n", s1.id);
                printf("Password: %lld\n", s1.pass);
                printf("ACCOUNT MONEY : %lld\n",s1.blance);

            }

        }


        fclose(ptr);
    }
        tran();
        call++;
}
void tran(){

if(call == 1){
    struct bank_user s1;
    char name[100];

    long long int id,x;

    if(choice == 3){
        printf("Enter your name: ");
        scanf("%s",name);
        printf("Enter your  id: ");
        scanf("%lld", &id);
        getchar();
         FILE *ptr = fopen("ff.txt", "a+");
           while (fscanf(ptr, "%s %s %s %lld %lld %lld",
                      s1.my_name, s1.fa_name, s1.ma_name, &s1.id, &s1.pass,&s1.blance) != EOF) {

            if ((strcmp(s1.my_name, name) == 0) && (s1.id == id)) {
                    FILE *npp = fopen("sf.txt", "a+");
                     FILE *ptr = fopen("ff.txt", "a+");
                    struct add_money p1;
                    p1.my_name[100] = name[100];
                    p1.id =  s1.id;
                    p1.money = s1.blance;
                    printf("MONEY ADD :");
                    scanf("%lld",&x);
                    p1.money = p1.money + x;
                    s1.blance = p1.money;
                    printf("account money: %lld\n",p1.money);
                    fprintf(npp,"%s   %lld    %lld\n\n",s1.my_name,p1.id,p1.money);
                    fprintf(ptr,"%s   %lld    %lld\n\n",s1.my_name,s1.id,s1.blance);
                    fclose(npp);
            }


            }

    }

    else if(choice ==4){
         struct bank_user s2;
         char name_2[100];
         long long int iid,a,b;
        printf("Enter your sender name: ");
        scanf("%s",name);
        printf("Enter your sender  id: ");
        scanf("%lld", &id);
        getchar();
        printf("Enter your reciver name: ");
        scanf("%s",name_2);
        printf("Enter your sender  id: ");
        scanf("%lld", &iid);
        scanf("%lld",&x);
        printf("amount : %lld",x);
        getchar();
        FILE *ptr = fopen("ff.txt", "a+");
        FILE *npp = fopen("sf.txt", "a+");
           while (fscanf(ptr, "%s %s %s %lld %lld",
                      s1.my_name, s1.fa_name, s1.ma_name, &s1.id, &s1.pass) != EOF) {
                if ((strcmp(s1.my_name, name) == 0) && (s1.id == id)) {


                     while (fscanf(ptr, "%s %s %s %lld %lld", s2.my_name, s2.fa_name, s2.ma_name, &s2.id, &s2.pass) != EOF) {
                                if ((strcmp(s2.my_name, name_2) == 0) && (s1.id == iid)){

                                        s1.blance -= x;
                                        s2.blance += x;
                                        printf("lld  lld   lld\n",s1.blance,s2.blance,x);
                                }

                            }

                      }

            }


    }
    }

}

void search(){
    if(choice == 5){
           char name[100];
        long long int password;
        struct bank_user s1;

        printf("Enter your name: ");
        scanf("%s",name);


        FILE *ptr = fopen("ff.txt", "a+");

        while (fscanf(ptr, "%s %s %s %lld %lld %lld",
                      s1.my_name, s1.fa_name, s1.ma_name, &s1.id, &s1.pass,&s1.blance) != EOF) {

            if ((strcmp(s1.my_name, name) == 0)) {
                printf("Name: %s\n", s1.my_name);
                printf("Father's Name: %s\n", s1.fa_name);
                printf("Mother's Name: %s\n", s1.ma_name);
                printf("ID: %lld\n", s1.id);
                printf("Password: %lld\n", s1.pass);
                printf("ACCOUNT MONEY : %lld\n",s1.blance);

            }


        }


        fclose(ptr);
    }

}




int main() {
    display();
    reg();
    tran();
    search();
  //  send_money();


    return 0;
}

