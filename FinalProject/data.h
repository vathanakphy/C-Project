#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stdbool.h>
#include<windows.h>
#include"interface.h"
#define MAX_SIZE 300
FILE *file;
FILE *DataCustomer;
FILE *tempData;
FILE *storeData;
struct product{
   int code,stock;
   char name[50];
   float prize,discount;
}bufferProduct[200],tempBufferStruct;
struct Customer{
   float paymentFee,total,productDiscount[30];
   char product[30][100],phoneNumber[20];
   int qty[30],numberProduct;
   float prize[30],discount;
   int day,year,hour,min;
   char month[20];
};
struct Date{
   int day,year,hour,min;
   char month[20];
}CurtentDate;
struct Store{
   float income;
   int totalProductSold,totalCustomer,totalMemberShip;
}store,tempStore;
struct product myProduct;
struct Customer tempCustomerData;
int tempCode;
int keyControl;
int numberProduct;
int defaultYAsis=5;
int defaultXAsisForChoose=72;
bool check,checkName;
char fourSpace[5]="    ";
char midlePossition[100]="                                        ";
void search();
char  buffername[50];
//from inteface.h
extern void gotoXY(int x, int y);
extern void mainFuction(char text[100]);
extern void inputBox(char text[100]);
extern void showOneProduct(char nameShow[100],int codeShow,float prizeShow,float discountShow,int stockShow);
//
void animetion(){
   printf("%s",midlePossition);
   for(int i=0;i<10;i++){
      printf("#");
      _sleep(200);
   }
   printf("\t\t\tSuccess!");
}
void getCurentDate(){
   time_t t = time(NULL);
   struct tm date = *localtime(&t);
   int tempMonth;
   char month[12][20]={"January","Febuary","March","April","May","June","July","Augest","September","Octerber","November","Decmeber"};
   tempMonth=date.tm_mon+1;
   strcpy(CurtentDate.month,month[tempMonth]);
   CurtentDate.year=date.tm_year+1900;
   CurtentDate.day=date.tm_mday;
   CurtentDate.hour=date.tm_hour;
   CurtentDate.min=date.tm_min;
}
void header(){
   setColor(2);//blue 
   printf("\n%s%s  ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",fourSpace,spToMidle);
   printf("\n%s%s  ┃  %-4s  %-20s %-9s %-8s %-9s ┃",fourSpace,spToMidle,"Code","Name","Prize","Dsicount","Stock");
   printf("\n%s%s  ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛",fourSpace,spToMidle);
   setColor(1);//blue 
}
void headerOrderProduct(){
   setColor(2);//blue 
   gotoXY(80+30,defaultYAsis+3);printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
   gotoXY(80+30,defaultYAsis+1+3);printf("┃ %-19s%-8s %-7s   %-8s┃","Name","Prize","Discount","Qty");
   // gotoXY(80,defaultYAsis+9);printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
   setColor(1);//blue 
}
void addProduct(){
   struct product myProduct;
   check=true;
   //tempdata 
   int stock,code;char name[100];float prize,discount;
   inputBox("Name     : ");
   inputBox("Prize    : ");
   inputBox("Stock    : ");
   inputBox("Discount : ");
   inputBox("Code     : ");
   fflush(stdin);
   gotoXY(55,defaultYAsis+3);gets(name);
   gotoXY(55,defaultYAsis+6);scanf("%f",&prize);
   gotoXY(55,defaultYAsis+9);scanf("%d",&stock);
   gotoXY(55,defaultYAsis+12);scanf("%f",&discount);
   inputCode:
   gotoXY(55,defaultYAsis+15);scanf("%d",&code);
   file=fopen("DataProduct.bin","rb");
   while((fread(&myProduct,sizeof(struct product),1,file))){
      if(code==myProduct.code){
         check=false;
         gotoXY(55,defaultYAsis+17);printf("Code has been used......!");
         gotoXY(55,defaultYAsis+18);printf("Enter Code Again");
         _sleep(1500);
         goto inputCode;
      }else{
         check=true;
      }
   }
   fclose(file);
   file=fopen("DataProduct.bin","ab");
   if(check==true){
      myProduct.code=code;
      strcpy(myProduct.name,name);
      myProduct.prize=prize;
      myProduct.stock=stock;   
      myProduct.discount=discount;   
   }
   int check=0;
   check=fwrite(&myProduct,sizeof(struct product),1,file);
   if(check){
      gotoXY(55,defaultYAsis+19);printf("Success!!");
   }else{
      gotoXY(55,defaultYAsis+19);printf("\nError");
   }
   fclose(file);
}
extern void show(){
   struct product myProduct;
   numberProduct=0;
   header();
   setColor(2);//blue 
   file=fopen("DataProduct.bin","rb");
   printf("\n%s%s  ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",fourSpace,spToMidle);
   while(fread(&myProduct,sizeof(struct product),1,file)){
      numberProduct+=1;
      printf("\n%s%s  ┃  %-4d   %-20s %-9.0f %-8.2f %-9d┃",fourSpace,spToMidle,myProduct.code,myProduct.name,myProduct.prize,myProduct.discount,myProduct.stock);
   }
   printf("\n%s%s  ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n",fourSpace,spToMidle);;
   fclose(file);
   setColor(7);//reset
}
void search(){
   tempCode=0;
   setColor(9);//blue 
   check=false;
   fflush(stdin);
   printf("%s1 . Search By Name \n",midlePossition);
   printf("%s2 . Search By Code\n",midlePossition);
   printf("%s0 . Exit\n",midlePossition);
   printf("%sChoose : ",midlePossition);scanf("%d",&keyControl);
   switch(keyControl){
      case 1:
         printf("%sEnter Name : ",midlePossition);fflush(stdin);gets(buffername);
         break;
      case 2:
         printf("%sEnter Code : ",midlePossition);scanf("%d",&tempCode);
         break;
      case 0:
         goto end;
         break;
   }
      file=fopen("DataProduct.bin","rb");
      rewind(file);
      setColor(2);//blue 
      struct product myProduct;
         while(fread(&myProduct,sizeof(struct product),1,file)){
            if(strcmpi(buffername,myProduct.name)==0 || tempCode==myProduct.code){
               check=true;
               printf("\n%sSearch Product Found....!",midlePossition);
               showOneProduct(myProduct.name,myProduct.code,myProduct.prize,myProduct.discount,myProduct.stock);
               check=true;
               break;
            }
         }
         if(check==false){
            printf("\n%sNot Found.....!\n",midlePossition);
         }
         end:;
         printf("\n%sPress any key Exit\n,",midlePossition);
      setColor(1);
      fclose(file);
      return 1;
}
extern void update(){
   check=false;
   int checkUpdate=0,bufferCode=0;
   fflush(stdin);
   char name[100];int code,stock;float prize,discount;
   inputBox("Name or Code    :");
   gotoXY(defaultXAsisForChoose-10,defaultYAsis+3);gets(buffername);
      bufferCode=atoi(buffername);
      file=fopen("DataProduct.bin","rb+");
      rewind(file);
      struct product myProduct;
         while(fread(&myProduct,sizeof(struct product),1,file)){
            if(strcmpi(buffername,myProduct.name)==0 || bufferCode==myProduct.code){
               check=true;
               showOneProduct(myProduct.name,myProduct.code,myProduct.prize,myProduct.discount,myProduct.stock);
               printf("\n%s▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄ update ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n",midlePossition);
               printf("%s1 . Name\n",midlePossition);
               printf("%s2 . Prize\n",midlePossition);
               printf("%s3 . Stock\n",midlePossition);
               printf("%s4 . Discount\n",midlePossition);
               printf("%sChose : ",midlePossition);scanf("%d",&keyControl);
               switch(keyControl){
                  case 1:
                     fflush(stdin);
                     printf("\n\n%sNew Name : ",midlePossition);gets(name);
                     strcpy(myProduct.name,name);
                     break;
                  case 2:
                     printf("\n\n%sNew Prize : ",midlePossition);scanf("%f",&prize);
                     myProduct.prize=prize;
                     break;
                  case 3:
                     printf("\n\n%sAdd Stock : ",midlePossition);scanf("%d",&stock);
                     myProduct.stock+=stock;
                     break;
                  case 4:
                     printf("\n\n%sEdit Discount : ",midlePossition);scanf("%f",&discount);
                     myProduct.discount=discount;
                     break;
               }
               fseek(file,-sizeof(myProduct),SEEK_CUR);
               checkUpdate=fwrite(&myProduct,sizeof(struct product),1,file);
               if(file!=NULL){        
                  animetion();
               }else {
                  setColor(4);
                  printf("%s\tError",midlePossition);
                  setColor(1);
               }
               fclose(file);
               break;
            }
         }
         if(check==false){
            printf("\n%sNot Found.....!\n",midlePossition);
         }
         printf("\n%sPress any key Exit\n",midlePossition);
   fclose(file);
}
extern void delete(){//imporve deelete deta in c
   search();
   char tempKey[5];
   bool success=false;
   struct product myProduct;
   file=fopen("DataProduct.bin","rb");
   if(file==NULL){
      printf("\n%sError Can not Open file...!",midlePossition);
      exit(2);
   }
   if(check==true){
      printf("%sType OK to delete : ",midlePossition);scanf("%s",tempKey);
      if(strcmpi(tempKey,"ok")==0){
         int numebrProduct=0;
         while(fread(&myProduct,sizeof(struct product),1,file)){
            if((strcmpi(buffername,myProduct.name)==0) || (tempCode==myProduct.code)){
               continue;
            }else{
               bufferProduct[numebrProduct]=myProduct;
               numebrProduct++;
            }
         }
         //process delete
         fclose(file);
         file=fopen("DataProduct.bin","wb");
         for(int i=0;i<numebrProduct;i++){
            fwrite(&bufferProduct[i],sizeof(struct product),1,file);
         }
         if(file!=NULL){
            animetion();
         }else{
            printf("%sError Can not Delete File",midlePossition);
         }
         fclose(file);
      }
   }
}
bool checkPhoneNumberCustomer(char phoneNumberCustomer[25]){
   DataCustomer=fopen("Customer.bin","rb");
   bool check=false;
   struct Customer customer;
   rewind(DataCustomer);
   while(fread(&customer,sizeof(struct Customer),1,DataCustomer)){
      if(strcmpi(phoneNumberCustomer,customer.phoneNumber)==0 && (strcmpi(phoneNumberCustomer,"0")!=0)){
         check=true;
         break;
      }else{
         check=false;
      }
   }
   fclose(DataCustomer);
   return check;
}
float discountForCustomer(char phone[20],float payment){
   float discount;
   struct Customer customer;
   struct product myProduct;
   if(checkPhoneNumberCustomer(phone)==true){
      if(payment<=100000.00){
         discount=0.05*100;
      }else{
         discount=0.08*100;
      }
   }
   if(checkPhoneNumberCustomer(phone)==false){
      discount=0.00;
   }
   return discount;
}
extern void purches(){
   struct Customer customer;
   struct product myProduct;
   struct Store store;
   // struct product myProduct;
   int number=0,bufferCode=0,qty[30],i;
   float payment=0;
   start:
   system("cls");
   mainFuction("Purches");
   inputBox("Enter Code : ");
   inputBox("Press 0 For Finish and - 1 for Cancle");
   show();
   if(number>=1){
      gotoXY(80+40,defaultYAsis);printf("\tYour Order");
      gotoXY(80+30,defaultYAsis+1);printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫");
      headerOrderProduct();
      gotoXY(80+30,defaultYAsis+2+3);printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫");
      for(i=0;i<number;i++){
         gotoXY(80+30,defaultYAsis+3+3+i);printf("┃ %-19s%-8.0f %-7.0f   %-8d ┃",customer.product[i],customer.prize[i],customer.productDiscount[i],customer.qty[i]);
      }
      // gotoXY(80+30,defaultYAsis+i+3+3);printf("┃                payemnt > %-20.f <              ┃",payment);
      gotoXY(80+30,defaultYAsis+i+3+3);printf("┃  %25s %-19.0f ┃","Payment = ",payment);
      gotoXY(80+30,defaultYAsis+i+4+3);printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
   };
   printf("");
   gotoXY(57,defaultYAsis+3);scanf("%d",&bufferCode);
   if(bufferCode==0){
      goto end;
   }else if(bufferCode==-1){
      file=fopen("DataProduct.bin","rb+");
      if(file==NULL){
         printf("\nError Can not Open file...!");
         exit(2);
      }
      number-=1;
      while(fread(&myProduct,sizeof(struct product),1,file)){
         if(strcmpi(myProduct.name,customer.product[number])==0){
            myProduct.stock+=qty[number];
            payment-=customer.prize[number]*qty[number];
            fseek(file,-sizeof(myProduct),SEEK_CUR);
            fwrite(&myProduct,sizeof(struct product),1,file);
            fclose(file);
         }
      }
      
   }
   file=fopen("DataProduct.bin","rb+");
   if(file==NULL){
      printf("\nError Can not Open file...!");
      exit(2);
   }
   while(fread(&myProduct,sizeof(struct product),1,file)){
      if(bufferCode==myProduct.code){
         checkName=true;
         showOneProduct(myProduct.name,myProduct.code,myProduct.prize,myProduct.discount,myProduct.stock);
         gotoXY(55-12,defaultYAsis+3);printf("Enter Qty :            ");gotoXY(57,defaultYAsis+3);scanf("%d",&qty[number]);
         myProduct.stock-=qty[number];
         payment+=(myProduct.prize*qty[number]);
         customer.prize[number]=myProduct.prize*((100-myProduct.discount)/100);
         strcpy(customer.product[number],myProduct.name);
         customer.productDiscount[number]=myProduct.discount;
         for(int i=0;i<number;i++){
            if(strcmp(customer.product[i],myProduct.name)==0){
               customer.qty[i]+=qty[number];
               checkName=false;
               break;
            }
         }
         fseek(file,-sizeof(myProduct),SEEK_CUR);
         fwrite(&myProduct,sizeof(struct product),1,file);
         if(checkName==false){
            number+=0;
         }else{
            customer.qty[number]=qty[number];
            number+=1;
         }
         fclose(file);
         break;
      } 
   } 
   goto start;
   end:;
      customer.numberProduct=number;
      customer.paymentFee=payment;
      customer.total=payment;
      getCurentDate();
      customer.day=CurtentDate.day;
      customer.year=CurtentDate.year;
      strcpy(customer.month,CurtentDate.month);
      customer.hour=CurtentDate.hour;
      customer.min=CurtentDate.min;
      //prinit receipt need create new
      system("cls");
      printf("\n===================================================\n");
      printf("Enter Phone Number : ");scanf("%s",customer.phoneNumber);
      printf("====================Store==========================\n\n");
      printf("==================Your Order=======================\n");
      printf("Date %d - %s - %d ",customer.day,customer.month,customer.year);
      printf("\t\tTime %d : %d \n",customer.hour,customer.min);
      printf("%-15s %-5s %-8s\n","Name","Qty","Prize");
      for(int i=0;i<number;i++){
         printf("%-15s %-5d %-8.0f\n",customer.product[i],customer.qty[i],customer.prize[i]);
      }
      printf("\n============== > Total %0.f\n\n",customer.total);
      customer.discount=discountForCustomer(customer.phoneNumber,customer.paymentFee);
      printf("\n============== > discount %0.f %%\n\n",customer.discount);
      customer.paymentFee*=((100-customer.discount))/100;
      printf("\n==============Payemnt %0.f\n\n",customer.paymentFee);
      printf("==================Thank You =====================\n");
      DataCustomer=fopen("Customer.bin","ab");
      fwrite(&customer,sizeof(struct Customer),1,DataCustomer);
      fclose(DataCustomer);
      storeData=fopen("storeData.bin","rb+");
      fread(&store,sizeof(struct Store),1,storeData);
      tempStore=store;
      tempStore.income+=payment;
      tempStore.totalCustomer+=1;
      tempStore.totalProductSold+=customer.numberProduct;
      if(strcmp(customer.phoneNumber,"0")!=0 && customer.discount==0){
         tempStore.totalMemberShip+=1;
      }//need to impre more lv use algorithm nis sin
      store=tempStore;
      fseek(storeData,-sizeof(store),SEEK_CUR);
      fwrite(&store,sizeof(struct Store),1,storeData);
      fclose(storeData);
}
void showCustomer(){
   system("cls");
   struct Customer customer;
   DataCustomer=fopen("Customer.bin","rb");
   if(DataCustomer==NULL){
      printf("Cnnot Open File....!");
   }
   rewind(DataCustomer);
   printf("\n================== Customer ====================\n");
   while(fread(&customer,sizeof(struct Customer),1,DataCustomer)){
      printf("<==============Customer Recipt=============>\n");
      printf("Date %d - %s - %d ",customer.day,customer.month,customer.year);
      printf("\t\tTime %d : %d \n",customer.hour,customer.min);
      printf("Phone Number : %s\n",customer.phoneNumber);
      printf("Number of Product : %d\n",customer.numberProduct);
      printf("Product Type \n");
      printf("%-15s %-6s %-10s\n","Name","Qty","Prize");
      for(int i=0;i<customer.numberProduct;i++){
         printf("%-15s %-6d %-8.0f\n",customer.product[i],customer.qty[i],customer.prize[i]);
      }
      printf("\n=============== > Total %0.f <\n",customer.total);
      printf("\n=============== > discount %0.f %% < \n",customer.discount);
      printf("\n<============== > Payment %0.f <\n",customer.paymentFee);
   }  
   fclose(DataCustomer);
}
void sort(){
   struct product myProduct;
   int numberProduct=0,i,j;
   file=fopen("DataProduct.bin","rb");
   if(file==NULL){
      printf("ERROR.....!");
   }
   while(fread(&myProduct,sizeof(struct product),1,file)){
      bufferProduct[numberProduct]=myProduct;
      numberProduct++;
   }
   char textForSorting[][100]={"Sort By Name","Sort By Type"};
   fclose(file);
   keyControl=ShowMainPoint(2,textForSorting);
   switch(keyControl){
      case 1:
         for(i=0;i<numberProduct;i++){
            for(j=i+1;j<numberProduct;j++){
               if(strcmpi(bufferProduct[i].name,bufferProduct[j].name)>0){
                  tempBufferStruct=bufferProduct[i];
                  bufferProduct[i]=bufferProduct[j];
                  bufferProduct[j]=tempBufferStruct;
               }
            }
         }
         break;
      case 2:
         for(i=0;i<numberProduct;i++){
            for(j=i+1;j<numberProduct;j++){
               if(bufferProduct[i].code>bufferProduct[j].code){
                  tempBufferStruct=bufferProduct[i];
                  bufferProduct[i]=bufferProduct[j];
                  bufferProduct[j]=tempBufferStruct;
               }
            }
         }
         break;
   }
   remove("DataProduct.bin");
   file=fopen("DataProduct.bin","wb");
   if(file==NULL){
      printf("Eorro Canot create file");
   }
   for(int i=0;i<numberProduct;i++){
      myProduct=bufferProduct[i];
      fwrite(&myProduct,sizeof(struct product),1,file);   
   }
   fclose(file);
   show();
}
void information(){
   system("cls");
   struct Store store;
   storeData=fopen("storeData.bin","rb");
   if(storeData==NULL){
      printf("Error Cannot open file......!\n");
      exit(2);
   }
   fread(&store,sizeof(struct Store),1,storeData);
   printf("================== Store Information ====================\n");
   getCurentDate();
   printf("Date %d - %s - %d \n",CurtentDate.day,CurtentDate.month,CurtentDate.year);
   printf("Balance           : %.0f R \n",store.income);
   printf("Product Sold out  : %d \n",store.totalProductSold);
   printf("Total Customer    : %d \n",store.totalCustomer);
   printf("Total Membership  : %d \n",store.totalMemberShip);
   fclose(storeData);
   printf("\n 1 . Check Detail \n");
   printf(" 0 . exit \n");
   printf("Choose : ");scanf("%d",&keyControl);
   switch(keyControl){
      case 1:
         showCustomer();
      break;
   }
}
char* comfirmPassword() {
   char tempChar[50]="",tempCpass[50]="";
   static char cpass[50];
   int ascii,i=0;
   printf("Enter Password : ");
   while(1){
      tempChar[i]=getch();
      ascii=tempChar[i];
      if(ascii==13){
         break; 
      }else if((ascii==8) && (i>=0)){
         printf("\b \b");
         tempCpass[i]=tempCpass[i+1];
         i--;
      }else{
         printf("*");
         strcpy(tempCpass,tempChar);
         i++;
      }
   }
   sprintf(cpass, "%s", tempCpass);
   return cpass;
}
