#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stdbool.h>
#include<windows.h>
char spToMidle[40]="                                    ";
char moreToMidle[40]="                  ";
char tempSpace[30];
void setColor(int color) {
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void gotoXY(int x, int y) {
   COORD coord;
   coord.X = x;
   coord.Y = y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void headerStore(){
   setColor(1);//blue 
   printf("\n%s┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",spToMidle);
   printf("\n%s┃                                                                ┃",spToMidle);
   printf("\n%s┃                       Department Store                         ┃",spToMidle);
   printf("\n%s┃                                                                ┃",spToMidle);
   printf("\n%s┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n",spToMidle);
   setColor(7);//reset
}
// frrom this x 72 , y 6
void mainFuction(char text[100]){
   setColor(1);//blue 
   printf("\n%s┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",spToMidle);
   printf("\n%s┃                                                                   ┃",spToMidle);
   printf("\n%s┃                     %-26s                    ┃",spToMidle,text);
   printf("\n%s┃                                                                   ┃",spToMidle);
   printf("\n%s┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n",spToMidle);
   setColor(7);//reset
}
void showOneProduct(char nameShow[100],int codeShow,float prizeShow,float discountShow,int stockShow){
   setColor(1);//blue 
   // strcpy(tempSpace,spToMidle);
   // strcat(spToMidle,moreToMidle);
   char sevenSpace[9]="      ";
   printf("\n%s%s┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",sevenSpace,spToMidle);
   printf("\n%s%s┃  %-15s %-39s ┃",sevenSpace,spToMidle,"Name     : ",nameShow);
   printf("\n%s%s┃  %-15s %-39d ┃",sevenSpace,spToMidle,"Code     : ",codeShow);
   printf("\n%s%s┃  %-15s %-39.0f ┃",sevenSpace,spToMidle,"Prize    : ",prizeShow);
   printf("\n%s%s┃  %-15s %-39.0f ┃",sevenSpace,spToMidle,"Discount : %",discountShow);
   printf("\n%s%s┃  %-15s %-39d ┃",sevenSpace,spToMidle,"Stock    :   ",stockShow);
   printf("\n%s%s┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛",sevenSpace,spToMidle);
   setColor(2);
   // strcpy(spToMidle,tempSpace);

}
void choose(){
   strcpy(tempSpace,spToMidle);
   strcat(spToMidle,moreToMidle);
   printf("\n%s┏━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",spToMidle);
   printf("\n%s┃ 0 . Exit                  ┃",spToMidle);
   printf("\n%s┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛",spToMidle);
   printf("\n%s┏━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",spToMidle);
   printf("\n%s┃ Choose  :                 ┃",spToMidle);
   printf("\n%s┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛",spToMidle);
   strcpy(spToMidle,tempSpace);
   setColor(7);//reset
}
void OptionToChoose(int number,char text[100]){
   setColor(2);//blue 
   strcpy(tempSpace,spToMidle);
   strcat(spToMidle,moreToMidle);
   printf("\n%s┏━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",spToMidle);
   printf("\n%s┃ %-d . %-22s┃",spToMidle,number,text);
   printf("\n%s┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛",spToMidle);
   strcpy(spToMidle,tempSpace);
}
int ShowMainPoint(int box,char text[20][100]){
   int key,yAxis=11+(box*3);
   char bufferKey[8];
   for(int i=0;i<box;i++){
      OptionToChoose(i+1,text[i]);
   }
   choose();
   gotoXY(72,yAxis);printf("");scanf("%s",&bufferKey);
   key=atoi(bufferKey);
   return key;
}
void inputBox(char text[100]){
   setColor(2);//blue 
   strcpy(tempSpace,spToMidle);//add 4 space to midle
   strcat(spToMidle,"      ");
   printf("\n%s┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",spToMidle);
   printf("\n%s┃  %-55s ┃",spToMidle,text);
   printf("\n%s┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛",spToMidle);
   strcpy(spToMidle,tempSpace);
   setColor(7);//blue 
}