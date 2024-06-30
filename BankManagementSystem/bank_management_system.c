#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#include<windows.h>
//save data 
FILE *userData;
FILE *atmData;
FILE *bankData;
//most common use variable 
int i,j,k,atm_code,number_user=0,number_employee=0;
bool check = false,check_login,check_username,check_transfer,search_usr_bank,usd,khr,withdraw_money;
bool balance_atm,exit_atm;
int key_control;
//temp data
char temp_username[35],temp_password[35],confirm_password[35],phone_number[18];
int id_user,bank_number,id_other_user,number_incorrect,code_payment,owner_bank_number;
float transfer_money;
//call function
//bank data
struct bank{
    float exchange_rate; //1 usd = 4050 khr
    float amount_usd;
    float amount_khr;
    int total_user;
    int total_staff;
}bank,bankTemp;
//atm data
struct atm{
    float amount_usd,amount_khr;
    int number_user_deposit[30],number_user_withdraw[30],number_user_loan[30];
    char user_id[30];
    float user_deposit[30],user_withdraw[30],user_loan[30];
    char password[10];
}atm[5],atmTemp;
//stotre staff information
struct staff_information{
    char name[35],dob_month[15],id_card[18],phone[15];
    int id,dob_year,dob_day;
    float salary;
    char adress[60];
    //secure data
    char username[35],password[35];
}staff[10];
//User 
//personal data user
struct personal_data_user{
    char name[35],dob_month[15],phone[13],id_card[18];
    int dob_year,dob_day;
    float amount_usd,amount_khr;
    int id_bank_usd,id_bank_khr;
    char adress[60];
    //loan data 
    float loan_usd;
    float loan_khr;
    //secure data
    char username[35],password[35];
    //payment_data
    int payment_code;
    float payment_money;
    bool payment_account_usd;
    bool payment_account_khr;
}user[100],userTemp;
//user data;
//process security
//check username
void check_username_user(){
    check_username=true;
    for(i=0;i<number_user;i++){
        if(i==id_user){
            continue;
        }
        if(strcmp(user[id_user].username,user[i].username)==0){
            check_username=false;
            printf("\tUsername Has been Used....!\n");
            printf("\tEnter Again \n");           
        }
    }
}
//check balance to teansfer
void check_balance_transfer(){
    if(khr==true){
        if((user[id_user].amount_khr-transfer_money)>=0){
            check_transfer=true;
        }else{
            check_transfer=false;
        }
    }else if(usd==true){
        if((user[id_user].amount_usd-transfer_money)>=0){
            check_transfer=true;
        }else{
            check_transfer=false;
        }
    }
}
void check_bank_transfer(){
    if(khr==true){
        if((bank.amount_khr-transfer_money)<=0){
            check_transfer=false;
        }else{
            check_transfer=true;
        }
    }else if(usd==true){
        if((bank.amount_usd-transfer_money)<=0){
            check_transfer=false;
        }else{
            check_transfer=true;
        }
    }
}
void check_bank_number(){//need delverlope more 
    for(i=0;i<number_user;i++){
        // if(user[])
    }
}
//
void user_register(){
    id_user=number_user;
    printf("\tFirst & Last Name       : ");fflush(stdin);gets(user[number_user].name);
    printf("\tDate of Birth (d-m-y)   : ");scanf("%d-%s-%d",&user[number_user].dob_day,&user[number_user].dob_month,&user[number_user].dob_year);
    printf("\tAdress in detail        : ");fflush(stdin);gets(user[number_user].adress);
    printf("\tID National Card Number : ");scanf("%s",&user[number_user].id_card);
    printf("\tPhone Number            : ");scanf("%s",&user[number_user].phone);
    enter_username:
    printf("\tEnter Username          : ");scanf("%s",&user[id_user].username);
    check_username_user();
        if(check_username==false){
            Sleep(2000);
            goto enter_username;
        }
    secure:
    printf("\tEnter Password          : ");scanf("%s",&user[number_user].password);
    printf("\tEnter Confirm Password  : ");scanf("%s",&confirm_password);
        if(strcmp(confirm_password,user[number_user].password)!=0){
            printf("\tIncorrect Please inter Password Again\n");
            Sleep(2000);
            goto secure;
        }
    printf("\tYour Bank Account Number \n");
    srand(time(0));
    user[number_user].id_bank_usd=rand() % 9000 + 1000;
    user[number_user].id_bank_khr=rand() % 9000 + 1000;
    user[number_user].amount_usd=0;
    user[number_user].amount_khr=0;
    printf("\tCode USD  = %d \n",user[number_user].id_bank_usd);
    printf("\tCode KHR  = %d \n",user[number_user].id_bank_khr);
    number_user++;
}
void update_user_interface(){
    printf("\t=================== Mekong Bank Update User Account =================\n");
    printf("\t1. Name \n");
    printf("\t2. Date Of Birth \n");
    printf("\t3. Phone Number \n");
    printf("\t4. Change Username\n");
    printf("\t5. Change Password\n");
    printf("\t6. Update Address\n");
}
//search user acount 
void search_bank_number_account(){
    search_usr_bank=false;
    usd=false;
    khr=false;
    printf("\tEnter Bank Number : ");scanf("%d",&bank_number);
    for(i=0;i<number_user;i++){
        if((id_user==i)&&withdraw_money==false){
            continue;
        }
        if((bank_number==user[i].id_bank_usd)){
            printf("\t%s\n",user[i].name);
            printf("\tUSD %d \n",user[i].id_bank_usd);
            search_usr_bank=true;
            id_other_user=i;
            usd=true;
            break;
        }else if(bank_number==user[i].id_bank_khr){
            printf("\t%s\n",user[i].name);
            printf("\tKHR %d \n",user[i].id_bank_khr);
            search_usr_bank=true;
            id_other_user=i;
            khr=true;
            break;
        }
    }
}
void search_user_account(){
    id_user=0;
    search_usr_bank=false;
    printf("\tEnter Phone Number : ");scanf("%s",&phone_number);
    for(i=0;i<number_user;i++){
        if(strcmp(phone_number,user[i].phone)==0){
            search_usr_bank=true;
            id_user=i;
        }
    }
    if(search_usr_bank==false){
        printf("\tYou Enter Incorrect.....!\n");
    }
}
//transfer money
void transfer_interface(){
    printf("\t=================== Mekong Bank Transfer =================\n");
    printf("\t1. Transfer to Own Account \n");
    printf("\t2. Transfer to Other Account \n");
    printf("\t0. Exit\n");
}
//transfer to other account
void transfer_to_other(){
    search_bank_number_account();
    if(search_usr_bank==true){
        printf("\tEnter Money :   ");scanf("%f",&transfer_money);
        printf("\tChose Account \n");
        printf("\t1. USD %d\n",user[id_user].id_bank_usd);
        printf("\t2. KHR %d\n",user[id_user].id_bank_khr);
        printf("\t0. Exit\n");
        printf("\tChose Option : ");scanf("%d",&key_control);
            switch(key_control){
                case 1:
                    usd=true;
                    break;
                case 2:
                    khr=true;
                    break;
                case 0:
                    goto end;
                    break;
            }
        check_balance_transfer();
        if(check_transfer==true){
            if(usd==true){//need to improve more with switch bank accoiutn tupe
                user[id_user].amount_usd-=transfer_money;
                user[id_other_user].amount_usd+=transfer_money;
                printf("\tTransfer Successful\n");
                printf("\tYou Transfer %f $ \n",transfer_money);
                printf("\tTo Account %s\n",user[id_other_user].name);
                printf("\tFrom %d to %d \n",user[id_user].id_bank_usd,user[id_other_user].id_bank_usd);
            }else if(khr==true){
                user[id_user].amount_khr-=transfer_money;
                user[id_other_user].amount_khr+=transfer_money;
                printf("\tTransfer Successful\n");
                printf("\tYou Transfer %f R\n",transfer_money);
                printf("\tTo Account %s\n",user[id_other_user].name);
                printf("\tFrom %d to %d \n",user[id_user].id_bank_khr,user[id_other_user].id_bank_khr);
            }//need improve more
        }else{
            printf("\tYour Dont Have Enough Money\n");
        }
    }else{
        printf("\tAccount not found...!\n");
        }    
    end:;                                                                                                    
}
void user_login(){
    check_login=false;
    for(i=0;i<number_user;i++){
        if(strcmp(temp_username,user[i].username)==0 && strcmp(temp_password,user[i].password)==0){
            id_user=i;
            check_login=true;
        }
    }
}
void output_user_data(){
    printf("\tName            : %s\n",user[id_user].name);
    printf("\tDOB             : %d-%s-%d\b\n",user[id_user].dob_day,user[id_user].dob_month,user[id_user].dob_year);
    printf("\tAdress          : %s\n",user[id_user].adress);
    printf("\tID Card         : %s\n",user[id_user].id_card);
    printf("\tPhone           : %s\n",user[id_user].phone);
    printf("\tUSD %d        : %.2f\n",user[id_user].id_bank_usd,user[id_user].amount_usd);
    printf("\tKHR %d        : %.2f\n",user[id_user].id_bank_khr,user[id_user].amount_khr);
}
//ATM 
//atm interface prpcessing 

//process in atm
void withdraw(){
    withdraw_money=true;
    search_bank_number_account();
    if(search_usr_bank==true){
        printf("\tEnter Money : ");scanf("%f",&transfer_money);
        printf("\tChose Account \n");
        printf("\t1. USD %d\n",user[id_user].id_bank_usd);
        printf("\t2. KHR %d\n",user[id_user].id_bank_khr);
        printf("\t0. Exit\n");
        printf("\tChose Option : ");scanf("%d",&key_control);
            switch(key_control){
                case 1:
                    usd=true;
                    check_balance_transfer();
                    // check_balance_atm();
                    break;
                case 2:
                    khr=true;
                    check_balance_transfer();
                    //check_balance_atm();
                    break;
                case 0:
                    goto end;
                    break;;
            }
            if(check_transfer==true){
                number_incorrect=0;
                enter_password:
                printf("\tEnter Password : ");scanf("%s",&confirm_password);
                    if(strcmp(confirm_password,user[id_other_user].password)==0){
                        //improve loading animetion 
                        if(usd==true){
                            user[id_other_user].amount_usd-=transfer_money;
                            atm[atm_code].amount_usd-=transfer_money;
                            //improve more detail
                        }else if(khr==true){
                            user[id_other_user].amount_khr-=transfer_money;
                            atm[atm_code].amount_khr-=transfer_money;
                            //need imrove when link with bank
                        }
                        printf("\tWithdraw Successful......!\n");
                        printf("\tTake it %.2f \n",transfer_money);
                    }else{
                        printf("\tPassword Incorrect \n");
                        printf("\tEnter Again\n");
                        Sleep(3000);
                        number_incorrect+=1;
                        if(number_incorrect>=3){
                            printf("\t More Incorrect Try Again \n");
                            goto end;
                        }
                        goto enter_password;
                    }   
            }else{
                printf("\tYou Dont Have Enough Money.....!\n");
            }
    }
    end:;
};
void deposit(){
    khr=false;
    usd=false;
    check_transfer=false;
    search_user_account();
    if(search_usr_bank==true){
        check_transfer=true;
        printf("\tChose Account \n");
        printf("\t1. USD %d\n",user[id_user].id_bank_usd);
        printf("\t2. KHR %d\n",user[id_user].id_bank_khr);
        printf("\t0. Exit\n");
        printf("\tChose Option : ");scanf("%d",&key_control);
            switch(key_control){
                case 1:
                    usd=true;
                    break;
                case 2:
                    khr=true;
                    break;
                case 0:
                    goto end;
                    break;;
            }
            if(check_transfer==true){
                number_incorrect=0;
                enter_password:
                printf("\tEnter Password : ");scanf("%s",&confirm_password);
                    if(strcmp(confirm_password,user[id_user].password)==0){
                        //improve loading animetion 
                        if(usd==true){
                            printf("\tEnter Money : $");scanf("%f",&transfer_money);
                            user[id_user].amount_usd+=transfer_money;
                            atm[atm_code].amount_usd+=transfer_money;
                            //improve more detail
                        }else if(khr==true){
                            printf("\tEnter Money : R");scanf("%f",&transfer_money);
                            user[id_user].amount_khr+=transfer_money;
                            atm[atm_code].amount_khr+=transfer_money;
                            //need imrove when link with bank
                        }
                        printf("\tDeposit Successful......!\n");
                        printf("\tCheck Your Balance\n");
                        printf("\tYour Money %.2f \n",transfer_money);
                    }else{
                        printf("\tPassword Incorrect \n");
                        printf("\tEnter Again\n");
                        Sleep(3000);
                        number_incorrect+=1;
                        if(number_incorrect>=3){
                            printf("\t More Incorrect Try Again \n");
                            goto end;
                        }
                        goto enter_password;
                    }   
            }else{
                printf("\tSomething Wrong.....!\n");
            }
    }
    end:;
}
void replenishment(){
    printf("\tEnter Paswword : ");scanf("%s",&confirm_password);
        if(strcmp(confirm_password,atm[atm_code].password)==0){
            printf("\tChose Account \n");
            printf("\t1. USD \n");
            printf("\t2. KHR \n");
            printf("\t0. Exit\n");
            printf("\tChose Option : ");scanf("%d",&key_control);
                switch(key_control){
                    case 1:
                        usd=true;                    
                        printf("\tEnter Money : $ ");scanf("%f",&transfer_money);
                        //need to check with bank total money 
                        check_bank_transfer();
                        if(check_transfer==true){
                            bank.amount_usd-=transfer_money;
                            atm[atm_code].amount_usd+=transfer_money;
                            printf("\tDeposit to ATM Success\n");
                            printf("\tYou Deposit %.2f to ATM\n",transfer_money);
                        }else{
                            printf("\tDeposit Unsuceess\n");
                        }
                        break;
                    case 2:
                        khr=true;
                        printf("\tEnter Money : R ");scanf("%f",&transfer_money);
                        check_bank_transfer();
                        if(check_transfer==true){
                            bank.amount_khr-=transfer_money;
                            atm[atm_code].amount_khr+=transfer_money;
                            printf("\tDeposit to ATM Success\n");
                            printf("\tYou Deposit %.2f to ATM\n",transfer_money);
                        }else{
                            printf("\tDeposit Unsuceess\n");
                        }
                        break;
                    case 0:
                        goto end;
                        break;
                }
            printf("\tPassword Incorrect");
            //more improve to exit or enter again
        }
        printf("\tPress any key Exit\n");
        end:;
}
void atm_interface(){
    printf("\t1. Deposit\n"); 
    printf("\t2. Withdraw\n");
    printf("\t3. Replenishment\n");//only use by staff 
    printf("\t0. Exit\n");
    printf("\tChose Option : ");scanf("%d",&key_control);
        switch(key_control){
            case 1:
                system("cls");
                printf("\t=================== Mekong Bank ATM =================\n");
                deposit();
                break;
            case 2:
                system("cls");
                printf("\t=================== Mekong Bank ATM =================\n");
                withdraw();
                break;
            case 3:
                system("cls");
                printf("\t=================== Mekong Bank ATM =================\n");
                replenishment();
                break;
            case 0:
                exit_atm=true;
                break;
        }
}
//payment function
void create_payment(){
    user[id_user].payment_account_khr=false;
    user[id_user].payment_account_usd=false;
    printf("\tChose Type of money\n");
    printf("\t1. USD \n");
    printf("\t2. KHR \n");
    printf("\t0. Exit\n");
    printf("\tChose Option : ");scanf("%d",&key_control);
    switch(key_control){
        case 1:
            user[id_user].payment_account_usd=true;
            printf("\tEnter Money : $ ");scanf("%f",&transfer_money);
            srand(time(0));
            user[id_user].payment_code= rand() % 900000 + 100000;
            user[id_user].payment_money=transfer_money;
            printf("\tPayment Code = %d \n",user[id_user].payment_code);
            printf("\tMoney to payment = %.2f $\n",user[id_user].payment_money);
            break;
        case 2:
            user[id_user].payment_account_khr=true;
            printf("\tEnter Money : R ");scanf("%f",&transfer_money);
            srand(time(0));
            user[id_user].payment_code= rand() % 900000 + 100000;
            user[id_user].payment_money=transfer_money;
            printf("\tPayment Code = %d \n",user[id_user].payment_code);
            printf("\tMoney to payment = %.2f R\n",user[id_user].payment_money);
            break;
        case 0:
            break;
    }
}
void pay_money(){
    check=false;
    printf("\tEnter Payment Code : ");scanf("%d",&code_payment);
    for(i=0;i<number_user;i++){
        if(code_payment==user[i].payment_code){
            id_other_user=i;
            printf("\tPayment Found\n");
            printf("\t%s\n",user[id_other_user].name);
            if(user[id_other_user].payment_account_usd==true){
                printf("\tUSD %d : %.2f $\n",user[id_other_user].id_bank_usd,user[id_other_user].payment_money);
            }else if(user[id_other_user].payment_account_khr==true){
                printf("\tKHR %d : %.2f R\n",user[id_other_user].id_bank_khr,user[id_other_user].payment_money);
            }
            printf("\n\tChose Account \n");
            printf("\t1. USD \n");
            printf("\t2. KHR \n");
            printf("\t0. Exit\n");
            printf("\tChose Option : ");scanf("%d",&key_control);
            switch(key_control){
                case 1:
                    usd=true;
                    owner_bank_number=user[id_user].id_bank_usd;
                    if(user[id_other_user].payment_account_usd==true){
                        transfer_money = user[id_other_user].payment_money;
                    }else if(user[id_other_user].payment_account_khr==true){
                        transfer_money = user[id_other_user].payment_money/bank.exchange_rate;
                    }
                    check_balance_transfer();
                    break;
                case 2:
                    khr=true;
                    owner_bank_number=user[id_user].id_bank_khr;
                    if(user[id_other_user].payment_account_usd==true){
                        transfer_money = user[id_other_user].payment_money*bank.exchange_rate;
                    }else if(user[id_other_user].payment_account_khr==true){
                        transfer_money = user[id_other_user].payment_money;
                    }
                    check_balance_transfer();
                    break;
                case 0:
                    goto end;
                    break;
            }
            if(check_transfer==true){
                printf("\tPayment Success\n");
                printf("\tYou Pay to %s\n",user[id_other_user].name);
                if(user[id_other_user].payment_account_usd==true){
                    printf("\tFrom %d to %d\n",owner_bank_number,user[id_other_user].id_bank_usd);
                    if(usd==true){
                        user[id_user].amount_usd-=transfer_money;
                    }else if(khr==true){
                        user[id_user].amount_khr-=transfer_money;
                    }
                    printf("\tPayment %.2f \n",user[id_other_user].payment_money);
                    user[id_other_user].amount_usd+=user[id_other_user].payment_money;
                    user[id_other_user].payment_money=0;
                    user[id_other_user].payment_code=0;
                }else if(user[id_other_user].payment_account_khr==true){
                    printf("\tFrom %d to %d\n",owner_bank_number,user[id_other_user].id_bank_khr);
                    if(usd==true){
                        user[id_user].amount_usd-=transfer_money;
                    }else if(khr==true){
                        user[id_user].amount_khr-=transfer_money;
                    }
                    printf("\tPayment %.2f \n",user[id_other_user].payment_money);
                    user[id_other_user].amount_khr+=user[id_other_user].payment_money;
                    user[id_other_user].payment_money=0;
                    user[id_other_user].payment_code=0;
                    }
                }else{
                printf("\tPayment Unsuccess\n");
            }
            check=true;
        }
    }
    if(check==false){
        printf("\tCode Payment Not Found\n");
    }
    end:;
}
//loan function in bank 
void loan(){
    printf("\t=================== Mekong Bank Loan =================\n");//loan in bank need to use id user indteat id other user
    printf("\tChose Type money\n");
}
int main(){
    //load data 
    userData=fopen("UserData.bin","rb");
    atmData=fopen("atmData.bin","rb");
    bankData=fopen("bankData.bin","rb");
    number_user=0;
    while(fread(&userTemp,sizeof(struct personal_data_user),1,userData)){
        user[number_user]=userTemp;
        number_user++;
    }
    i=0;
    while(fread(&atmTemp,sizeof(struct atm),1,atmData)){
        atm[i]=atmTemp;
        i++;
    }
    fwrite(&bankTemp,sizeof(struct bank),1,bankData);
    bank=bankTemp;
    fclose(userData);
    fclose(atmData);
    fclose(bankData);
    //start bank program
    start:
    withdraw_money=false;
    exit_atm=false;
    system("cls");
    printf("\t=================== Mekong Bank =================\n");
    printf("\t1. ATM \n");
    printf("\t2. User Account \n");
    printf("\t3. Adminstration \n");
    printf("\t0. Exit \n");
    printf("\t Chose Option : ");scanf("%d",&key_control);
        switch(key_control){
            //ATM
            case 1:{
            atm_location:
            system("cls");
            printf("\t=================== Mekong Bank ATM =================\n");
            //need function in every atm
            printf("\t1. Sensok\n");
            printf("\t2. Toul Kork\n");
            printf("\t3. 7 Makara\n");
            printf("\t4. Chory Chongva\n");
            printf("\t0. Exit\n");
            printf("\t Chose Option : ");scanf("%d",&key_control);
                switch(key_control){
                    case 1:
                        atm_code=key_control;
                        strcpy(atm[atm_code].password,"1234abcd");
                        system("cls");
                        printf("\t=================== Mekong Bank ATM =================\n");
                        atm_interface();
                        if(exit_atm==true){
                            goto atm_location;
                        }
                        break;
                    case 2:
                        atm_code=key_control;
                        strcpy(atm[atm_code].password,"1234abcd");
                        system("cls");
                        printf("\t=================== Mekong Bank ATM =================\n");
                        atm_interface();
                        if(exit_atm==true){
                            goto atm_location;
                        }
                        break;
                    case 3:
                        atm_code=key_control;
                        strcpy(atm[atm_code].password,"1234abcd");
                        system("cls");
                        printf("\t=================== Mekong Bank ATM =================\n");
                        atm_interface();
                        break;
                    case 4:
                        atm_code=key_control;
                        strcpy(atm[atm_code].password,"1234abcd");
                        system("cls");
                        printf("\t=================== Mekong Bank ATM =================\n");
                        atm_interface();
                        if(exit_atm==true){
                            goto atm_location;
                        }
                        break;
                    case 0:
                        goto start;
                        break;
                    default:
                    printf("\tPlease Input Number in list\n");
                    Sleep(3000);
                        break;
                }
                getch();
                goto atm_location;
                break;}
            case 2:{
            //User Account
            user_interface:
            system("cls");
            printf("\t=================== Mekong Bank User Account =================\n");
            printf("\t1. Login\n");
            printf("\t2. Register\n");
            printf("\t0. Exit\n");
            printf("\t Chose Option : ");scanf("%d",&key_control);
                switch(key_control){
                    case 1:{
                        system("cls");
                        printf("\t=================== Mekong Bank User Account =================\n");
                        printf("\tEnter Username : ");scanf("%s",&temp_username);
                        printf("\tEnter Password : ");scanf("%s",&temp_password);
                        //process of login
                        user_login();
                        if(check_login==true){
                            printf("\tLogin Success....!\n");
                            _sleep(2000);
                            user_account:
                            system("cls");
                            //user accont inteface
                            printf("\t=================== Mekong Bank User Account =================\n");
                            printf("\t1. Check My Information\n");
                            printf("\t2. Check Wallete\n");
                            printf("\t3. Teansfer Money\n");//have 2 function (1 transfer to own account and 2 transfer to other account) after payment need enter pwd to sucess
                            printf("\t4. Loan\n");//have 2 function pay and take and build policy to take loan from your own money
                            printf("\t5. Update Data \n");//need update security to update datat
                            printf("\t6. Payment\n");
                            printf("\t0. Exit\n");
                            printf("\t Chose Option : ");scanf("%d",&key_control);
                                switch(key_control){
                                    case 1:
                                        system("cls");
                                        printf("\t=================== Mekong Bank User Account =================\n");
                                        output_user_data();
                                        getch();
                                        break;
                                    case 2:
                                        system("cls");
                                        printf("\t=================== Mekong Bank User Account =================\n");
                                        printf("\t USD %d = %.2f \n",user[id_user].id_bank_usd,user[id_user].amount_usd);
                                        printf("\t KHR %d = %.2f \n",user[id_user].id_bank_khr,user[id_user].amount_khr);
                                        printf("\t=================== Loan =================\n");
                                        printf("\t USD  = %.2f \n",user[id_user].loan_usd);
                                        printf("\t KHR  = %.2f \n",user[id_user].loan_khr);
                                        getch();
                                        break;
                                    case 3:
                                        system("cls");
                                        transfer_interface();
                                        printf("\tChose Option : ");scanf("%d",&key_control);
                                            switch(key_control){
                                                case 1:
                                                    //transfer to own account
                                                    system("cls");
                                                    printf("\t=================== Mekong Bank Transfer =================\n");
                                                    printf("\t1. Transfer USD to KHR\n");
                                                    printf("\t2. Transfer KHR to USD\n");
                                                    printf("\t3. Exit\n");
                                                    printf("\tChose Option : ");scanf("%d",&key_control);
                                                        switch(key_control){
                                                            case 1:
                                                                system("cls");
                                                                printf("\t=================== Transfer USD to KHR =================\n");
                                                                printf("\tEnter Money : ");scanf("%f",&transfer_money);
                                                                //check transfer by enter code and check you wallet is enough or not
                                                                usd=true;
                                                                check_balance_transfer();
                                                                if(check_transfer==true){
                                                                    user[id_user].amount_usd-=transfer_money;
                                                                    user[id_user].amount_khr+=(transfer_money*bank.exchange_rate);
                                                                    printf("\tTransfer Successful\n");
                                                                    printf("\tYou Transfer %f\n",transfer_money);
                                                                    printf("\tFrom %d to %d \n",user[id_user].id_bank_usd,user[id_user].id_bank_khr);
                                                                }else{
                                                                    printf("\tTransfer not success\n");
                                                                }
                                                                printf("\tPress any key Exit \n");
                                                                getch();
                                                                break;
                                                            case 2:
                                                                system("cls");
                                                                printf("\t=================== Transfer KHR to USD =================\n");
                                                                printf("\tEnter Money : ");scanf("%f",&transfer_money);
                                                                //check transfer by enter code and check you wallet is enough or not
                                                                khr=true;
                                                                check_balance_transfer();
                                                                if(check_transfer==true){
                                                                    user[id_user].amount_khr-=transfer_money;
                                                                    user[id_user].amount_usd+=(transfer_money/bank.exchange_rate);
                                                                    printf("\tTransfer Successful\n");
                                                                    printf("\tYou Transfer %f\n",transfer_money);
                                                                    printf("\tFrom %d to %d \n",user[id_user].id_bank_khr,user[id_user].id_bank_usd);
                                                                }else{
                                                                    printf("\tTransfer not success\n");
                                                                    printf("\tMoney Not Enough\n");
                                                                }
                                                                printf("\tPress any key Exit \n");
                                                                getch();
                                                                break;
                                                            case 0:
                                                                goto user_account;
                                                                break;
                                                        }
                                                    break;
                                                case 2:
                                                    system("cls");
                                                    printf("\t=================== Transfer KHR to USD =================\n");
                                                    transfer_to_other();
                                                    //transfer to other account
                                                    printf("\tPress any Exit");
                                                    getch();
                                                    break;
                                                case 0:
                                                    break;
                                            }
                                        break;
                                    case 4:
                                        break;
                                    case 5:
                                        update_user:
                                        system("cls");
                                        update_user_interface();
                                        printf("\t0. Exit\n");
                                        printf("\t Chose Option : ");scanf("%d",&key_control);
                                            switch(key_control){
                                                case 1:
                                                    system("cls");
                                                    printf("\t=================== Mekong Bank Update User Account =================\n");
                                                    printf("\tName : ");fflush(stdin);gets(user[id_user].name);
                                                    puts("\tPress any key Exit");
                                                    getch();
                                                    break;
                                                case 2:
                                                    system("cls");
                                                    printf("\t=================== Mekong Bank Update User Account =================\n");
                                                    printf("\tDate Of Birth : ");scanf("%d-%s-%d",&user[id_user].dob_day,&user[id_user].dob_month,&user[id_user].dob_year);
                                                    puts("\tPress any key Exit");
                                                    getch();
                                                    break;
                                                case 3:
                                                    system("cls");
                                                    printf("\t=================== Mekong Bank Update User Account =================\n");
                                                    printf("\tPhone Number : ");scanf("%s",&user[id_user].phone);
                                                    puts("\tPress any key Exit");
                                                    getch();
                                                    break;
                                                case 4:
                                                    system("cls");
                                                    printf("\t=================== Mekong Bank Update User Account =================\n");
                                                    enter_username:
                                                    printf("\tNew Username          : ");scanf("%s",&user[id_user].username);
                                                    check_username_user();
                                                        if(check_username==false){
                                                            goto enter_username;
                                                        }
                                                    puts("\tPress any key Exit");
                                                    getch();
                                                    break;
                                                case 5:
                                                    system("cls");
                                                    printf("\t=================== Mekong Bank Update User Account =================\n");
                                                    secure_update:
                                                    printf("\tNew Password      : ");scanf("%s",&user[id_user].password);
                                                    printf("\tConfirm Password  : ");scanf("%s",&confirm_password);
                                                        if(strcmp(confirm_password,user[id_user].password)!=0){
                                                            printf("\tIncorrect Please inter Password Again\n");
                                                            Sleep(3000);
                                                            goto secure_update;
                                                        }
                                                    puts("\tPress any key Exit");
                                                    getch();
                                                    break;
                                                case 6:
                                                    system("cls");
                                                    printf("\t=================== Mekong Bank Update User Account =================\n");
                                                    printf("\tAddress : ");fflush(stdin);gets(user[id_user].adress);
                                                    puts("\tPress any key Exit");
                                                    getch();
                                                    break;
                                                case 0:
                                                    goto user_account;
                                                    break;
                                            }
                                            goto update_user;
                                        break;
                                    case 6:
                                    //user_payment
                                        system("cls");
                                        printf("\t=================== Mekong Bank Payment =================\n");
                                        printf("\t1. Create Payment\n");
                                        printf("\t2. Pay Money\n");
                                        printf("\t0. Exit");
                                        printf("\tChose Option : ");scanf("%d",&key_control);
                                            switch(key_control){
                                                case 1:
                                                    system("cls");
                                                    printf("\t=================== Mekong Bank Create Payment =================\n");
                                                    create_payment();
                                                    getch();
                                                    break;
                                                case 2:
                                                    system("cls");
                                                    printf("\t=================== Mekong Bank Pay Money =================\n");
                                                    pay_money();
                                                    getch();
                                                    break;
                                                case 0:
                                                    goto user_account;
                                                    break;
                                            }
                                        break;
                                    case 0:
                                        goto start;
                                        break;
                                    default:
                                        printf("\tPlease Input Number in list\n");
                                        Sleep(3000);
                                        break;
                                }
                                goto user_account;
                        }else{
                            printf("\t Login Unsuccess...!\n");
                            printf("\t Try Again\n");
                            _sleep(3000);
                            goto user_interface;
                        }
                        break;}
                    case 2:
                        //regisgter
                        system("cls");
                        printf("\t=================== Mekong Bank User Account =================\n");
                        user_register();
                        printf("\tPress any Key to Exit");
                        getch();
                        goto user_interface;
                        break;
                }
                break;}
            case 3:{
            // adminstration control bank
            //ass password
                adminstration:
                system("cls");
                printf("\t=================== Mekong Bank Adminstration =================\n");
                printf("\t1 . Loan\n");
                printf("\t2 . Withdraw\n");
                printf("\t3 . Deposit\n");
                printf("\t4 . Seaerch\n");
                printf("\t5 . Show all user\n");
                printf("\t6 . Update\n");
                printf("\t7 . Delete Information\n");
                printf("\t7 . Add Staff\n");
                printf("\t8 . Check Staff Information\n");
                printf("\t0 . Exit\n");
                printf("\tChoose : ");scanf("%d",&key_control);
                switch(key_control){
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        system("cls");
                        printf("\t=================== Mekong Bank Search Data =================\n");
                        search_user_account();
                        if(search_usr_bank==true){
                            output_user_data();
                        }
                        getch();
                        break;
                    case 5:
                        system("cls");
                        printf("\t=================== Mekong Bank Show User =================\n");
                        for(i=0;i<number_user;i++){
                            id_user=i;
                            printf("\t<==============================================>\n");
                            output_user_data();
                            printf("\t<==============================================>\n\n");
                        }
                        getch();
                        break;
                    case 6:
                        system("cls");
                        printf("\t=================== Mekong Bank Update User Account =================\n");
                        search_user_account();
                        if(search_usr_bank){
                            output_user_data();
                            update_user_interface();
                            printf("\tChoose : ");scanf("%d",&key_control);
                            switch(key_control){
                                case 1:
                                    system("cls");
                                    printf("\t=================== Mekong Bank Update User Account =================\n");
                                    printf("\tName : ");fflush(stdin);gets(user[id_user].name);
                                    puts("\tPress any key Exit");
                                    getch();
                                    break;
                                case 2:
                                    system("cls");
                                    printf("\t=================== Mekong Bank Update User Account =================\n");
                                    printf("\tDate Of Birth : ");scanf("%d-%s-%d",&user[id_user].dob_day,&user[id_user].dob_month,&user[id_user].dob_year);
                                    puts("\tPress any key Exit");
                                    getch();
                                    break;
                                case 3:
                                    system("cls");
                                    printf("\t=================== Mekong Bank Update User Account =================\n");
                                    printf("\tPhone Number : ");scanf("%s",&user[id_user].phone);
                                    puts("\tPress any key Exit");
                                    getch();
                                    break;
                                case 4:
                                    system("cls");
                                    printf("\t=================== Mekong Bank Update User Account =================\n");
                                    enter_username_again:
                                    printf("\tNew Username    : ");scanf("%s",&user[id_user].username);
                                    check_username_user();
                                    if(check_username==false){
                                        goto enter_username_again;
                                    }   
                                    puts("\tPress any key Exit");
                                    getch();
                                    break;
                                case 5:
                                    system("cls");
                                    printf("\t=================== Mekong Bank Update User Account =================\n");
                                    secure_update_again:
                                    printf("\tNew Password      : ");scanf("%s",&user[id_user].password);
                                    printf("\tConfirm Password  : ");scanf("%s",&confirm_password);
                                        if(strcmp(confirm_password,user[id_user].password)!=0){
                                            printf("\tIncorrect Please inter Password Again\n");
                                            Sleep(3000);
                                            goto secure_update_again;
                                        }
                                    puts("\tPress any key Exit");
                                    getch();
                                    break;
                                case 6:
                                    system("cls");
                                    printf("\t=================== Mekong Bank Update User Account =================\n");
                                    printf("\tAddress : ");fflush(stdin);gets(user[id_user].adress);
                                    puts("\tPress any key Exit");
                                    getch();
                                    break;
                                case 0:
                                    goto adminstration;
                                    break;
                                }
                        }else{
                            printf("\nSearch Not Found.....!\n");
                        }
                        break;
                    case 7:
                        break;
                    case 0:
                        break;
                }
                break;}
            case 0:
                userData=fopen("UserData.bin","wb");
                atmData=fopen("atmData.bin","wb");
                bankData=fopen("bankData.bin","wb");
                for(i=0;i<number_user;i++){
                    userTemp=user[i];
                    fwrite(&userTemp,sizeof(struct personal_data_user),1,userData);
                }
                for(i=0;i<5;i++){
                    atmTemp=atm[i];
                    fwrite(&atmTemp,sizeof(struct atm),1,atmData);
                }
                bank=bankTemp;
                fwrite(&bankTemp,sizeof(struct bank),1,bankData); 
                fclose(userData);
                fclose(atmData);
                fclose(bankData);
                return 0;
                break;
            default:
                printf("\tPlease Input Number in list\n");
                Sleep(3000);
                break;
        }
    goto start;
    return 0;
}