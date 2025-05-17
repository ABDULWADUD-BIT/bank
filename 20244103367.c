#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void display();
void reg();
void tran();
void search();
void send_money();
void withdrawal();

int choice;
struct bank_user {
    char my_name[100];
    char fa_name[100];
    char ma_name[100];
    long long int id;
    long long int pass;
    long long int balance;
};

void display() {
    printf("                                   *************YCYC BANK LIMITED*************\n");
    printf("account create enter 1:\n");
    printf("account sign in enter 2:\n");
    printf("add money enter 3:\n");
    printf("send money enter 4:\n");
    printf("search enter 5:\n");
    printf("withdrawl money enter 6:\n");
    printf("exit enter 0:\n");
    printf("option: ");
    scanf("%d", &choice);
    getchar();
}

void reg() {
    if (choice == 1) {
        struct bank_user s1;
        printf("Enter name: ");
        fgets(s1.my_name, sizeof(s1.my_name), stdin);
        s1.my_name[strcspn(s1.my_name, "\n")] = 0;

        printf("FATHER NAME: ");
        fgets(s1.fa_name, sizeof(s1.fa_name), stdin);
        s1.fa_name[strcspn(s1.fa_name, "\n")] = 0;

        printf("MOTHER NAME: ");
        fgets(s1.ma_name, sizeof(s1.ma_name), stdin);
        s1.ma_name[strcspn(s1.ma_name, "\n")] = 0;

        printf("Enter ID: ");
        scanf("%lld", &s1.id);
        printf("Enter PASSWORD: ");
        scanf("%lld", &s1.pass);
        printf("amount: ");
        scanf("%lld", &s1.balance);
        getchar();

        printf("Name: %s\n", s1.my_name);
        printf("FATHER Name: %s\n", s1.fa_name);
        printf("MOTHER Name: %s\n", s1.ma_name);
        printf("ID: %lld\n", s1.id);
        printf("password: %lld\n", s1.pass);
        printf("amount: %lld\n", s1.balance);

        FILE *ptr = fopen("ff.txt", "a");
        fprintf(ptr, "%s %s %s %lld %lld %lld\n", s1.my_name, s1.fa_name, s1.ma_name, s1.id, s1.pass, s1.balance);
        fclose(ptr);

        FILE *npp = fopen("sf.txt", "a");
        fprintf(npp, "%s %lld %lld\n", s1.my_name, s1.id, s1.balance);
        fclose(npp);
    } else if (choice == 2) {
        char name[100];
        long long int password;
        struct bank_user s1;

        printf("Enter your name: ");
        scanf("%s", name);
        printf("Enter your password: ");
        scanf("%lld", &password);
        getchar();

        FILE *ptr = fopen("ff.txt", "r");
        if (!ptr) {
            printf("Error opening file.\n");
            return;
        }

        int found = 0;
        while (fscanf(ptr, "%s %s %s %lld %lld %lld", s1.my_name, s1.fa_name, s1.ma_name, &s1.id, &s1.pass, &s1.balance) != EOF) {
            if (strcmp(s1.my_name, name) == 0 && s1.pass == password) {
                printf("Name: %s\n", s1.my_name);
                printf("Father's Name: %s\n", s1.fa_name);
                printf("Mother's Name: %s\n", s1.ma_name);
                printf("ID: %lld\n", s1.id);
                printf("Password: %lld\n", s1.pass);
                printf("ACCOUNT MONEY: %lld\n", s1.balance);
                found = 1;
            }
        }
        fclose(ptr);

        if (!found) {
            printf("Invalid name or password.\n");
        }
    }
}

void tran() {
    if (choice == 3) {
        char name[100];
        long long int id, x;
        struct bank_user s1;

        printf("Enter your name: ");
        scanf("%s", name);
        printf("Enter your id: ");
        scanf("%lld", &id);
        getchar();

        FILE *ptr = fopen("ff.txt", "r");
        FILE *temp = fopen("temp.txt", "w");
        if (!ptr || !temp) {
            printf("File error.\n");
            return;
        }

        int found = 0;
        while (fscanf(ptr, "%s %s %s %lld %lld %lld", s1.my_name, s1.fa_name, s1.ma_name, &s1.id, &s1.pass, &s1.balance) != EOF) {
            if (strcmp(s1.my_name, name) == 0 && s1.id == id) {
                found = 1;
                printf("MONEY ADD: ");
                scanf("%lld", &x);
                s1.balance += x;
                printf("Updated Balance: %lld\n", s1.balance);

                FILE *npp = fopen("sf.txt", "a");
                fprintf(npp, "%s %lld %lld\n", s1.my_name, s1.id, s1.balance);
                fclose(npp);
            }
            fprintf(temp, "%s %s %s %lld %lld %lld\n", s1.my_name, s1.fa_name, s1.ma_name, s1.id, s1.pass, s1.balance);
        }

        fclose(ptr);
        fclose(temp);

        if (!found) {
            printf("Account not found.\n");
            remove("temp.txt");
        } else {
            remove("ff.txt");
            rename("temp.txt", "ff.txt");
        }
    }
}

void search() {
    if (choice == 5) {
        char name[100];
        struct bank_user s1;

        printf("Enter your name: ");
        scanf("%s", name);
        getchar();

        FILE *ptr = fopen("ff.txt", "r");
        if (!ptr) {
            printf("Error opening file.\n");
            return;
        }

        int found = 0;
        while (fscanf(ptr, "%s %s %s %lld %lld %lld", s1.my_name, s1.fa_name, s1.ma_name, &s1.id, &s1.pass, &s1.balance) != EOF) {
            if (strcmp(s1.my_name, name) == 0) {
                printf("Name: %s\n", s1.my_name);
                printf("Father's Name: %s\n", s1.fa_name);
                printf("Mother's Name: %s\n", s1.ma_name);
                printf("ID: %lld\n", s1.id);
                printf("Password: %lld\n", s1.pass);
                printf("ACCOUNT MONEY: %lld\n", s1.balance);
                found = 1;
            }
        }
        fclose(ptr);

        if (!found) {
            printf("Account not found.\n");
        }
    }
}

void send_money() {
    if (choice == 4) {
        char sender_name[100], receiver_name[100];
        long long int sender_id, receiver_id, amount;
        struct bank_user user;

        printf("Enter Sender Name: ");
        scanf("%s", sender_name);
        printf("Enter Sender ID: ");
        scanf("%lld", &sender_id);
        printf("Enter Receiver Name: ");
        scanf("%s", receiver_name);
        printf("Enter Receiver ID: ");
        scanf("%lld", &receiver_id);
        printf("Enter Amount to Send: ");
        scanf("%lld", &amount);
        getchar();

        FILE *ptr = fopen("ff.txt", "r");
        FILE *temp = fopen("temp.txt", "w");

        if (!ptr || !temp) {
            printf("File error.\n");
            return;
        }

        int sender_found = 0, receiver_found = 0;
        long long int sender_new_bal = 0, receiver_new_bal = 0;

        while (fscanf(ptr, "%s %s %s %lld %lld %lld", user.my_name, user.fa_name, user.ma_name, &user.id, &user.pass, &user.balance) != EOF) {
            if (strcmp(user.my_name, sender_name) == 0 && user.id == sender_id) {
                if (user.balance >= amount) {
                    user.balance -= amount;
                    sender_new_bal = user.balance;
                    sender_found = 1;
                } else {
                    printf("Insufficient balance.\n");
                    fclose(ptr);
                    fclose(temp);
                    remove("temp.txt");
                    return;
                }
            } else if (strcmp(user.my_name, receiver_name) == 0 && user.id == receiver_id) {
                user.balance += amount;
                receiver_new_bal = user.balance;
                receiver_found = 1;
            }

            fprintf(temp, "%s %s %s %lld %lld %lld\n", user.my_name, user.fa_name, user.ma_name, user.id, user.pass, user.balance);
         //   printf("%s %s %s %lld %lld %lld\n", user.my_name, user.fa_name, user.ma_name, user.id, user.pass, user.balance);
         //   wadud here you can see temp file modify all data.
        }

        fclose(ptr);
        fclose(temp);

        if (!sender_found || !receiver_found) {
            printf("Sender or Receiver not found.\n");
            remove("temp.txt");
        } else {
            remove("ff.txt");
            rename("temp.txt", "ff.txt"); // here is ff file contain new data

            FILE *npp = fopen("sf.txt", "a");
            fprintf(npp, "%s %lld %lld\n", sender_name, sender_id, sender_new_bal);
            fprintf(npp, "%s %lld %lld\n", receiver_name, receiver_id, receiver_new_bal); //
            fclose(npp);

            printf("Transfer successful!\n");
            printf("Sender New Balance: %lld\n", sender_new_bal);
            printf("recever New Balance: %lld\n", receiver_new_bal);
        }
    }
}

void withdrawal(){

 if (choice == 6) {
        char name[100];
        long long int id, x;
        struct bank_user s1;

        printf("Enter your name: ");
        scanf("%s", name);
        printf("Enter your id: ");
        scanf("%lld", &id);
        getchar();

        FILE *ptr = fopen("ff.txt", "r");
        FILE *temp = fopen("temp.txt", "w");
        if (!ptr || !temp) {
            printf("File error.\n");
            return;
        }

        int found = 0;
        while (fscanf(ptr, "%s %s %s %lld %lld %lld", s1.my_name, s1.fa_name, s1.ma_name, &s1.id, &s1.pass, &s1.balance) != EOF) {
            if (strcmp(s1.my_name, name) == 0 && s1.id == id) {
                found = 1;
                printf("MONEY withdrawl: ");
                scanf("%lld", &x);
                if(s1.balance >= x){
                    s1.balance -= x;
                    printf("Updated Balance: %lld\n", s1.balance);

                    FILE *npp = fopen("sf.txt", "a");
                    fprintf(npp, "%s %lld %lld\n", s1.my_name, s1.id, s1.balance);
                    fclose(npp);
                }
                else
                    printf("not have too much money\n\n");
            }
            fprintf(temp, "%s %s %s %lld %lld %lld\n", s1.my_name, s1.fa_name, s1.ma_name, s1.id, s1.pass, s1.balance);
        }

        fclose(ptr);
        fclose(temp);

        if (!found) {
            printf("Account not found.\n");
            remove("temp.txt");
        }
        else{
            remove("ff.txt");
            rename("temp.txt", "ff.txt");
        }
    }


}





int main() {
    while (1) {
        display();
        if (choice == 0) break;
        reg();
        tran();
        search();
        send_money();
        withdrawal();
    }
    return 0;
}
