#include <stdio.h>
#include <stdlib.h>
#include <string.h> //library for string handling safely

typedef struct info{
    char name[20];
    char age[3];
    char address[50];
    char occupation[20];
    char monthlySal[12];
}info;

typedef struct user {
    char username[20];//the name of the string acts as a pointer for the value inside it
    char usernameCopy[20];//you must initiallize a string plus 1 of your total character for the null character(\0)
    char password[20];
    char passwordCopy[20];
    int money,topupNominal,topupNominal2;
    info userInfo;
    char transaction[10][100];
    int transactionNum;
}user;
user validUser[100];

int memberNumber = 0,memberNumberDest = 0;
int nominal;


int compare1,compare2;
char usernameAdmin[] = {"mrbank"},passwordAdmin[] = {"bankbank"};
char usernameAdminCopy[],passwordAdminCopy[];

char userInput;
int i,retry=0,newNumber=-1;
int display(char header[],char option[][20],char footer[],int manyOption);
int bankBank();

void aboutUs(),createAccount(int n),admin(),masterTopup(),listofAccounts();
int dashboard(int n);
char place[10],says[10][50];
void callMrbank(char says[][50], char place[10], int manyOption);


int main() {
    printf("\n\n\t\t\t\t|||BANK BANK|||\n");
    printf("\tMade by Anak Agung Krisna Ananda Kusuma/1806228146 on 10th May 2019\n\n\n");
    printf("\tHI! im Mr.BANK, your personal assistant. Welcome to BANK BANK!\n");
    printf("\tHere, i will help you through your activity.\n\tif you have some difficulty here, call me by pressing 9.\n");
    printf("\tEnjoy your banking experience!\n\n");
    system("pause");
    system("cls");
    userInput = -1;
    while(userInput!=0) {
        userInput = bankBank();
            switch(userInput) {
                case 1: newNumber+=1; createAccount(newNumber); break;
                case 2: {system("cls");
                         printf("\n\ninsert your member number:");
                         scanf("%d",&memberNumber);
                         dashboard(memberNumber);
                        }break;
                case 3: aboutUs(); break;
                case 9: {char says[3][50]={"press 1 if you dont have an account yet","press 2 to do some banking operation","press 3 to know more abour our company"};
                        callMrbank(says,"HOME",3);
                        } break;
                case 99: {   system("cls");
                                printf("\n\nmember #Admin\n");
                                printf("--------------------------");
                                printf("\nType in your username:");
                                scanf("%s",&usernameAdminCopy);
                                printf("Type in Your Password:");
                                scanf("%s",&passwordAdminCopy);
                                compare1 = strcmp(usernameAdmin,usernameAdminCopy);
                                compare2 = strcmp(passwordAdmin,passwordAdminCopy);
                                if(compare1 == 0 && compare2 == 0) admin();
                                if(compare1 != 0 || compare2 != 0) {
                                    printf("Last Chance to get into system!\n");
                                    printf("\nType in your username:");
                                    scanf("%s",&usernameAdminCopy);
                                    printf("Type in Your Password:");
                                    scanf("%s",&passwordAdminCopy);
                                    compare1 = strcmp(usernameAdmin,usernameAdminCopy);
                                    compare2 = strcmp(passwordAdmin,passwordAdminCopy);
                                    if(compare1 == 0 && compare2 == 0) admin();
                                    if(compare1 != 0 || compare2 != 0) {printf("You have been banned!\n"); return 0;}
                                }
                            } break;
            }
        }
    system("cls");
    printf("\nMr. BANK: Thank you for choosing bankbank. \n\t  as our company is still on development, we would appreciate your feedbacks on www.bankbankbank.com.\n\t  Have a nice day!\n\n");
    return 0;
}


void callMrbank(char says[][50], char place[10], int manyOption) {
    int i;
    printf("\n\nMr. BANK: I'm here! Since you are in %s page, you can do the followings:\n",place);
    for(i=-1;i<manyOption-1;i++) {
        printf("\t\%s\n",&says[i][50]);
    }
    printf("\n");
    system("pause");
}

/*int checkPass(char one[5][10], char two[5][10]) {
    int i,j;
    for(i=0;i<=5;i++) {
        for(j=0;j<=10;j++) {
            if(&one[i][j] == &two[i][j]) printf("true");
            else {return 0;}
        }
    }
}*/



int bankBank() {
    system("cls");
    int value;
    char option[3][20] = {"Create an Account","Go to Dashboard","About Us"};
    value = display("|BANK BANK|",option,"Answer:",3);
    return value;
}



void balanceInfo(int y) {
    system("cls");
    printf("\n\nmember #%d\n",y);
    printf("--------------------------\n");
    printf("Balance: %d\n\n",validUser[y].money);
    system("pause");
    system("cls");
}


void transfer(int homeNum, int destNum, int y,int z) {
    int choose;
    printf("You are going to tranfer to member number #%d with owner name %s with nominal %d\n",destNum,validUser[destNum].userInfo.name,y);
    printf("Proceed?\n1. Yes\n2. Cancel\n");
    printf("Answer:");
    scanf("%d",&choose);
    if(choose == 1) {
        validUser[homeNum].money -= y;
        validUser[destNum].money += y;
        char string[10][50];
        sprintf(string[z],"Transfered to member number #%d with owner name %s with nominal %d\n\n",homeNum,validUser[destNum].userInfo.name,y);
        printf("%s",string[z]);
        strcpy(validUser[homeNum].transaction[z],string[z]);
    }
    else printf("You have canceled transfer to member number #%d with owner name %s with nominal %d\n\n",destNum,validUser[destNum].userInfo.name,y);
}


void topUp(int n) {
    system("cls");
    printf("\n\nEnter the nominal you want to insert:");
    scanf("%d",&validUser[n].topupNominal);
    validUser[n].topupNominal2 += validUser[n].topupNominal;
    printf("The balance of account with member number #%d has been Top up with %d!\n",n,validUser[n].topupNominal2);
    printf("Please wait until the system is being updated..\n\n");
    system("pause");
}


int changePass(int p) {
    int r = 0;
    printf("Insert your current password:");
    scanf("%s",validUser[p].passwordCopy);
    compare1 = strcmp(validUser[p].password,validUser[p].passwordCopy);
    while(compare1 != 0) {
        printf("\nPlease make sure your current password is correct.\n");
        printf("Insert your current password:");
        scanf("%s",validUser[p].passwordCopy);
        r += 1;
        if(r == 2){
            printf("You have reached 3 times retry. Your account is now banned!");
            return 0;
        }
        compare1 = strcmp(validUser[p].password,validUser[p].passwordCopy);
    }
    r = 0;
    printf("Insert your new password:");
    scanf("%s",validUser[p].password);
    printf("Insert your new password again:");
    scanf("%s",validUser[p].passwordCopy);
    compare1 = strcmp(validUser[p].password,validUser[p].passwordCopy);
    while(compare1 != 0) {
        printf("Please make sure your new password is the same.");
        printf("Insert your new password:");
        scanf("%s",validUser[p].password);
        printf("Insert your new password again:");
        scanf("%s",validUser[p].passwordCopy);
        compare1 = strcmp(validUser[p].password,validUser[p].passwordCopy);
    }
    printf("your password has been changed!");
    return 4;
}

int dashboard(int n) {
    printf("insert your username:");
    //        \/ you dont need the ampersand (&) to access the variable address because an array name acts as a pointer, which stores address
    scanf("%s",validUser[n].usernameCopy);
    printf("insert your password:");
    scanf("%s",validUser[n].passwordCopy);
    compare1 = strcmp(validUser[n].username,validUser[n].usernameCopy);
    compare2 = strcmp(validUser[n].password,validUser[n].passwordCopy);
    while(compare1 != 0 || compare2 != 0) {
        printf("Either your username or password is incorrect. Please re-insert your username and your password.\n");
        printf("insert your username:");
        scanf("%s",validUser[n].usernameCopy);
        printf("insert your password:");
        scanf("%s",validUser[n].passwordCopy);
        compare1 = strcmp(validUser[n].username,validUser[n].usernameCopy);
        compare2 = strcmp(validUser[n].password,validUser[n].passwordCopy);
        retry +=1;
        if(retry == 2){printf("You have reached 3 times retry. Your account is now banned!\n"); system("pause"); return 0;};
    }
    system("cls");
    int value;
    char option[4][20] = {"Transfer","TopUp","Balance info","Change password"};
    value = -1;
    while(value !=0) {
        value = display("DASHBOARD",option,"Choose your Option:",4);
            switch(value) {
                case 1: { system("cls");
                          printf("\n\nEnter the member number you want to transfer:"); //if you insert a string, system error
                          scanf("%d",&memberNumberDest);
                          while (memberNumberDest > newNumber) {
                                printf("\nmember number #%d is not registered yet\n",memberNumberDest);
                                printf("Please make sure your member number destination is correct\n");
                                printf("\nEnter the member number you want to transfer:");
                                scanf("%d",&memberNumberDest);
                            }
                          printf("Enter the nominal you want to transfer:");
                          scanf("%d",&nominal);
                          while(nominal > validUser[n].money) {
                                printf("Sorry, your balance is not enough. Please insert enough nominal to transfer:");
                                scanf("%d",&nominal);
                            }
                          transfer(n,memberNumberDest,nominal,validUser[n].transactionNum);
                          validUser[n].transactionNum ++;
                        } system("pause"); system("cls"); break;
                case 2: topUp(n); system("cls"); break;
                case 3: balanceInfo(n); break;
                case 4: changePass(n); break;
                case 9: {char says[3][50] = {"press 1 to transfer your money to your friend","press 2 to top up your balance","press 3 to check your balance"};
                        callMrbank(says,"DASHBOARD",3);}; system("cls"); break;
            }
    }

}



void aboutUs() {
    system("cls");
    char option[2][20] = {"About Us","Our Sponsors"};
    int value;
    value = -1;
    while(value!=0) {
        value = display("About Us",option,"Select option:",2);
        switch(value) {
            case 1: printf("\nOur company starts to launch at 21st of May 2019 and became successful eversince!\n\n"); system("pause"); system("cls"); break;
            case 2: printf("\nAt the moment, we have 20 sponsors but its too much to be displayed.\nyou can check on our website at www.bankbankbank.com thank you!\n\n"); system("pause"); system("cls"); break;
            case 9: {char says[2][50] = {"press 1 to know abour our company profile","press 2 to see the list of our sponsors"};
                     callMrbank(says,"ABOUT US",2);
                    } system("cls"); break;
        }
    }
}



void createAccount(int n) {
    system("cls");
    printf("\n\n\t\t\tNew Account Request Paper\n");
    printf("\t\t----------------------------------------\n");
    printf("\t\tFull name:");
    fgets(validUser[n].userInfo.name,50,stdin);
    fgets(validUser[n].userInfo.name,50,stdin);
    printf("\t\tAge:");
    fgets(validUser[n].userInfo.age,3,stdin);
    printf("\t\tAddress:");
    fgets(validUser[n].userInfo.address,50,stdin);
    fgets(validUser[n].userInfo.address,50,stdin);
    printf("\t\tOccupation:");
    fgets(validUser[n].userInfo.occupation,20,stdin);
    printf("\t\tMonthly salary:");
    fgets(validUser[n].userInfo.monthlySal,12,stdin);
    printf("\n\t\tNote: any lowercase alphabet with no space\n\t\tand less than 10 character are valid\n\t\tusername and password\n");
    printf("\n\t\tmember #%d\n",n);
    printf("\t\t--------------------------\n");
    printf("\t\tPlease enter your username:");
    scanf("%s",validUser[n].username); //scanf reads a line of string until it reaches a space.
    printf("\t\tPlease enter your password:");
    scanf("%s",validUser[n].password);
    printf("\n\t\tPlease do not forget your member number,\n\t\tusername, and password for your account\n\n");
    validUser[n].money = 0;
    system("pause");
}



void listofAccounts(int x) {
    system("cls");
    int i,j;
    for(i=0;i<=x;i++) {
        printf("\n\t\t\tmember #%d\n",i);
        printf("\t\t\t--------------------------\n");
        printf("\t\t\tOwnername:\t%s\n",validUser[i].userInfo.name);
        printf("\t\t\tAge\t :\t%s\n",validUser[i].userInfo.age);
        printf("\t\t\tAddress  :\t%s\n",validUser[i].userInfo.address);
        printf("\t\t\tOccupation:\t%s\n",validUser[i].userInfo.occupation);
        printf("\t\t\tMonthly salary:\t%s\n",validUser[i].userInfo.monthlySal);
        printf("\t\t\tBalance  :\t%d\n",validUser[i].money);
        printf("\t\t\tTopup history:\t%d\n\n",validUser[i].topupNominal2);
        for(j=0;j<=validUser[i].transactionNum;j++) {
            printf("\t\t\tTransfer history:%s\n\n",validUser[i].transaction[j]);
        }
    }
    system("pause");
}


void updateSystem() {
    system("cls");
    int n,k=0;
    char updatePass[15],updatePass2[15] = {"systemUpdate"};
    printf("\t\t\tTopup transaction list\n");
    printf("\t\t--------------------------------------\n");
    for(n=0;n<=newNumber;n++) {
        if(validUser[n].topupNominal2 > 0) {
            k+=1;
            printf("\t\t%d. member number #%d with owner name %s\n\t\t   has done topup transaction with nominal %d\n\n",k,n,validUser[n].userInfo.name,validUser[n].topupNominal2);
        }
    }
    printf("\t\t--------------------------------------\n");
    printf("\t\tEnter the password to update the system:");
    scanf("%s",updatePass);
    compare1 = strcmp(updatePass,updatePass2);
    while(compare1 != 0) {
        printf("\t\tPlease make sure the password is correct.\n");
        printf("\t\tEnter the password to update the system:");
        scanf("%s",updatePass);
        compare1 = strcmp(updatePass,updatePass2);
    }
    for(n=0;n<=newNumber;n++) {
        validUser[n].money += validUser[n].topupNominal2;
        validUser[n].topupNominal2 -= validUser[n].topupNominal2;
    }
    printf("\t\tThe system has been updated!\n\n");
    system("pause");
}


void admin() {
    system("cls");
    char option[2][20] = {"List of accounts","Update system"};
    int value;
    value = -1;
    while (value!=0) {
        system("cls");
        value = display("AdminDashboard",option,"Select Admin option:",2);
        switch(value) {
            case 1: listofAccounts(newNumber); break;
            case 2: updateSystem();break;
            case 9: printf("\nYour an admin, you know what to do!\n"); system("pause"); system("cls"); break;
        }
    }
}


int display(char header[],char option[][20],char footer[],int manyOption) {
    int i;
    int input;
    printf("\n\n\t\t\t\t%s\n",header);
    printf("\t\t\t--------------------------\n");
    for(i=-1;i<manyOption-1;i++) {
        printf("\t\t\t[%d]: %s\n",i+2,&option[i][20]);
    }
    printf("\t\t\t\n\t\t\t[9]: Call Mr.BANK\n");
    printf("\t\t\t[0]: Go to previous page/Exit\n");
    printf("\t\t\t--------------------------\n");
    printf("\t\t\t%s",footer);
    scanf("%d",&input);
    while(input <0 || input > 99) {
        printf("\t\t\tPlease select the list above:");
        scanf("%d",&input);
    }
    return input;
}
