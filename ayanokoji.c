#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void display();
void reg();
void tran();
void search();
void send_money();

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
        s1.my_name[strcspn(s1.my_name, "\n")] = 0; // Remove newline
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
        if (ptr == NULL) {
            printf("Error opening file.\n");
            return;
        }

        int found = 0;
        while (fscanf(ptr, "%s %s %s %lld %lld %lld", s1.my_name, s1.fa_name, s1.ma_name, &s1.id, &s1.pass, &s1.balance) == 6) {
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
        if (ptr == NULL || temp == NULL) {
            printf("Error opening file.\n");
            if (ptr) fclose(ptr);
            if (temp) fclose(temp);
            return;
        }

        int found = 0;
        while (fscanf(ptr, "%s %s %s %lld %lld %lld", s1.my_name, s1.fa_name, s1.ma_name, &s1.id, &s1.pass, &s1.balance) == 6) {
            if (strcmp(s1.my_name, name) == 0 && s1.id == id) {
                found = 1;
                printf("MONEY ADD: ");
                scanf("%lld", &x);
                s1.balance += x;
                printf("account money: %lld\n", s1.balance);

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
        if (ptr == NULL) {
            printf("Error opening file.\n");
            return;
        }

        int found = 0;
        while (fscanf(ptr, "%s %s %s %lld %lld %lld", s1.my_name, s1.fa_name, s1.ma_name, &s1.id, &s1.pass, &s1.balance) == 6) {
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
        struct bank_user sender, receiver;

        printf("Enter sender name: ");
        scanf("%s", sender_name);
        printf("Enter sender ID: ");
        scanf("%lld", &sender_id);
        printf("Enter receiver name: ");
        scanf("%s", receiver_name);
        printf("Enter receiver ID: ");
        scanf("%lld", &receiver_id);
        printf("Enter amount to send: ");
        scanf("%lld", &amount);
        getchar();

        FILE *ptr = fopen("ff.txt", "r");
        FILE *temp = fopen("temp.txt", "w");
        if (ptr == NULL || temp == NULL) {
            printf("Error opening file.\n");
            if (ptr) fclose(ptr);
            if (temp) fclose(temp);
            return;
        }

        int sender_found = 0, receiver_found = 0;
        while (fscanf(ptr, "%s %s %s %lld %lld %lld", sender.my_name, sender.fa_name, sender.ma_name, &sender.id, &sender.pass, &sender.balance) == 6) {
            if (strcmp(sender.my_name, sender_name) == 0 && sender.id == sender_id) {
                sender_found = 1;
                if (sender.balance >= amount) {
                    sender.balance -= amount;
                } else {
                    printf("Insufficient balance.\n");
                    fclose(ptr);
                    fclose(temp);
                    remove("temp.txt");
                    return;
                }
            } else if (strcmp(sender.my_name, receiver_name) == 0 && sender.id == receiver_id) {
                receiver_found = 1;
                sender.balance += amount;
            }
            fprintf(temp, "%s %s %s %lld %lld %lld\n", sender.my_name, sender.fa_name, sender.ma_name, sender.id, sender.pass, sender.balance);
        }
        fclose(ptr);
        fclose(temp);

        if (!sender_found || !receiver_found) {
            printf("Sender or receiver not found.\n");
            remove("temp.txt");
        } else {
            remove("ff.txt");
            rename("temp.txt", "ff.txt");

            FILE *npp = fopen("sf.txt", "a");
            fprintf(npp, "%s %lld %lld\n", sender_name, sender_id, sender.balance);
            fprintf(npp, "%s %lld %lld\n", receiver_name, receiver_id, sender.balance);
            fclose(npp);

            printf("Transfer successful. Sender balance: %lld\n", sender.balance);
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
    }
    return 0;
}
