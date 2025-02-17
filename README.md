# bank
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct bank_user {
    char my_name[100];
    char fa_name[100];
    char ma_name[100];
    long long int id;
    long long int pass;
};

void reg(){
 int account_create,sign_up;
    printf("account create enter 1: ");
    scanf("%d", &account_create);
    printf("account sign up 2: ");
    scanf("%d", &sign_up);
    getchar();

    if (account_create == 1) {
        struct bank_user s1;

        printf("Enter name: ");
        fgets(s1.my_name, sizeof(s1.my_name), stdin);
        printf("FATHER NAME: ");
        fgets(s1.fa_name, sizeof(s1.fa_name), stdin);
        printf("MOTHER NAME : ");
        fgets(s1.ma_name, sizeof(s1.ma_name), stdin);
        printf("Enter ID: ");
        scanf("%lld", &s1.id);
        printf("Enter PASSWRD: ");
        scanf("%lld", &s1.pass);
        printf("Name: %s", s1.my_name);
        printf("FATHER Name: %s", s1.fa_name);
        printf("MOTHER Name: %s", s1.ma_name);
        printf("ID: %lld\n", s1.id);
        printf("password: %lld\n", s1.pass);

        FILE *ptr = fopen("jibon.txt", "a+");
        fprintf(ptr,"%s %s %s %lld %lld\n\n",s1.my_name, s1.fa_name, s1.ma_name, s1.id, s1.pass);
        fclose(ptr);

    }
     else if (sign_up == 2) {
        char name[100];
        long long int password;
        struct bank_user s1;

        printf("Enter your name: ");
        scanf("%s",name);

        printf("Enter your password: ");
        scanf("%lld", &password);

        FILE *ptr = fopen("jibon.txt", "r+");

        while (fscanf(ptr, "%s %s %s %lld %lld",
                      s1.my_name, s1.fa_name, s1.ma_name, &s1.id, &s1.pass) != EOF) {

            if ((strcmp(s1.my_name, name) == 0) && (s1.pass == password)) {
                printf("Name: %s\n", s1.my_name);
                printf("Father's Name: %s\n", s1.fa_name);
                printf("Mother's Name: %s\n", s1.ma_name);
                printf("ID: %lld\n", s1.id);
                printf("Password: %lld\n", s1.pass);


            }
        }

        fclose(ptr);
    }

}



int main() {
   
    
    reg();
    
    return 0;

}



