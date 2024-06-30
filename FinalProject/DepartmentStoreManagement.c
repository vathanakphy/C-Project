#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include"data.h"
extern int ShowMainPoint(int box,char text[20][100]);
extern void gotoXY(int x,int y);
extern void setColor(int color);
extern void mainFuction(char text[100]);
extern void OptionToChoose(int number,char text[100]);
extern void headerStore();
extern void addProduct();
extern void search();
extern void update();
extern void delete();
extern void show();
extern void purches();
extern void showCustomer();
extern void sort();
extern void information();
extern void header();
extern void showOneProduct(char nameShow[100],int codeShow,float prizeShow,float discountShow,int stockShow);
int main(){
   int keyOption;
   char text1[7][100]={"Stock Management","Sale System","Employee Management Not aviable","Adminstration Not aviable"};
   char textStockManage[][100]={"Add Product","Show Product","Search ","Update ","Delete Not aviable","Sort","highest sells Not aviable","lowest sells Not aviable"};
   char textStaff[][100]={"Add Staff","Check Information","Update","Delete"};
   char textAdmin[][100]={"Change Password","Change Currency","Income","Sale Information","Customer Data"};
   char textSale[][100]={"Purches","Report"};
   start:
   system("cls");
   headerStore();
   keyOption= ShowMainPoint(4,text1);
   switch(keyOption){
      case 1:
         stockManagement:
         system("cls");
         mainFuction("Stock Management");
         keyOption=ShowMainPoint(8,textStockManage);
         switch(keyOption){
            case 1:
               system("cls");
               mainFuction("Add Product");
               addProduct();
               break;
            case 2:
               system("cls");
               mainFuction("Product");
               show();
               break;
            case 3:
               system("cls");
               mainFuction("Search Product");
               search();
               break;
            case 4:
               system("cls");
               mainFuction("Update Product");
               update();
               break;
            case 5:
               system("cls");
               mainFuction("Delete ");
               delete();
               break;
            case 6:
               system("cls");
               mainFuction("Sort Product");
               sort();
               break;
            case 7: 
               mainFuction("Most sell ");
               //need code from team mate
               break;
            case 0:
               goto start;
               break;
         }
         getch();
         goto stockManagement;
         break;
      case 2:
         system("cls");
         mainFuction("Cashir");
         keyOption=ShowMainPoint(2,textSale);
         switch(keyOption){
            case 1:
               system("cls");
               mainFuction("Purches");
               purches();
               break;
            case 2:
               mainFuction("Report");
               
               break;
         }
         break;
      case 3:
         system("cls");
         mainFuction("Employee Management");
         keyOption=ShowMainPoint(4,textStaff);
         break;
      case 4:
         system("cls");
         mainFuction("Adminstration");
         keyOption=ShowMainPoint(5,textAdmin);
         break;
      case 0:
         //This Exit Function
         exit(2);
         break;
   }
   getch();
   goto start;
   return 0;

}