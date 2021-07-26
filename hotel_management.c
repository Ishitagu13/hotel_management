#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<conio.h>
#include<windows.h>

#define SIZE 12
#define PERDAY 7000
#define SIZ 100                         //MAX SIZE FOR STACK bd

/*int pop();
int checkYear(int);
int famount(int);

void push(int x);
void intro();
void gotoxy(int, int);
void bookrooms(int, int, int);
void checkOut(int, int, int);
void disp();
void namedisp();
void billdisp();
void lilmenu();
void rdisp(struct rest x);*/

int exists()
{
    FILE *file;
    if ((file = fopen("rooms.dat", "rb")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}


int f=0, r=11;
int rooms[SIZE]={101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112};
int top=-1;

struct rest                       //storing bill details in stack
{
    int qty, fid, p, tp;
    char fname[30];

}bd[SIZ];

struct cdet
{
    int cid, rno;
    char fnam[45], lnam[45], city[50], pno[20], email[70];
    int bdd, bmm, byyyy;
    char status[20];
    int ldd, lmm, lyyyy;
};
typedef struct cdet cust;

struct rdata
{
    int rono, amt;
    char fnam[40], lnam[40], dat[20];
};

struct dish                      //pre-initialized structure for menu display
{
    int id;
    char nm[30];
    int pri;
};

COORD coord={0,0};
void gotoxy(int x, int y)
{
    coord.X=x;
    coord.Y=y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void push(int x)                  //to push back the room no. in the cirular queue
{
    int num;
    int t, d, *r;
    r=(int *)malloc(SIZE*sizeof(int));
    FILE *file, *k;
    file=fopen("rooms.dat", "ab+");
    k=fopen("temp2.dat", "wb+");
    fread(&t,  sizeof(int), 1, file);
    fread(&d,  sizeof(int), 1, file);
    fread(r,  sizeof(int), SIZE, file);
    //printf("kkkk \n\n %d   %d", t, d);
    if((t==0 && d==SIZE-1) || (t==d+1))
    {
        printf("ERROR");
    }
    else if(t==-1 && d==-1)
    {
        t =0;
    }
    d=(d+1)%SIZE;
    *(r+d)=x;
    printf("\n\n\n\t\t\t\t THANKS FOR YOUR STAY... HOPE YOU ENJOYED IT!! PLEASE VISIT US AGAIN :):):)");
    fwrite(&t,  sizeof(int), 1, k);
    fwrite(&d,  sizeof(int), 1, k);
    fwrite(r,  sizeof(int), SIZE, k);
    //printf("kkkk \n\n %d sdsf  %d \n   kjebaf %d  %d %d", t, d, *r, *(r+3), *(r+5));
    //getch();
    fclose(k);
    fclose(file);
    free(r);
    remove("rooms.dat");
    rename("temp2.dat", "rooms.dat");
}

int pop()                          //to get the room no.
{
    FILE *file, *k;
    int t, d, *r;
    r=(int *)malloc(SIZE*sizeof(int));
    k=fopen("temp2.dat", "wb+");
    file=fopen("rooms.dat", "ab+");
    fread(&t,  sizeof(int), 1, file);
    fread(&d,  sizeof(int), 1, file);
    fread(r,  sizeof(int), SIZE, file);
    int val;
    if((t==-1 && d==-1))
    {
        printf(" SORRY NO ROOM IS AVAILABLE.......");
        val=-1;
    }
    else if(t==d)
    {
        val=*(r+t);
        t=d=-1;
    }
    else
    {
        val=*(r+t);
        t=(t+1)%SIZE;
        printf("ROOM IS AVAILABLE!!");
    }

    fwrite(&t,  sizeof(int), 1, k);
    fwrite(&d,  sizeof(int), 1, k);
    fwrite(r,  sizeof(int), SIZE, k);
    //printf("kkkk \n\n %d   %d \n fewjqw %d   %d    %d  %d   %d    %d   %d   %d    %d   %d   %d    %d", t, d, *r, *(r+1), *(r+2), *(r+3),*(r+4),*(r+5), *(r+6), *(r+7), *(r+8), *(r+9), *(r+10), *(r+11));
    fclose(file);
    fclose(k);
    remove("rooms.dat");
    rename("temp2.dat", "rooms.dat");
    free(r);
    return val;
}

struct rest searchid(struct dish a[], int x)                  //to search the id of the food element
{
    int c;
    struct rest r;
    for(c=0; c<5; c++)
    {
        if(x==a[c].id)
        {
            r.fid=x;
            strcpy(r.fname, a[c].nm);
            r.p=a[c].pri;
        }
    }
    return r;
}

void order(struct rest k)           // to order the correct quantity
 {

     int ans;
     printf("\n\n\t\t\t ENTER QUANTITY REQUIRED:");
     scanf("%d", &k.qty);
     k.tp=((k.p)*(k.qty));
     rdisp(k);
     printf("\n\n IS THE ORDER RIGHT??? (1/0):");
     scanf("%d", &ans);
     if(ans==1)
     {
         bd[++top]=k;
     }
     else
     {
         printf("\n\n NOW YOU CAN CORRECT YOUR ORDER....");
     }
     getch();
 }

 void disp()                 //FINALIZING THE ORDER
{
    int c=0, x=top;
    FILE *f;
    if(top==-1)
    {
        gotoxy(5,8);
        printf("\n\n\t\t\t\t\t\t ERROR!!!!  \n\t\t\t\t YOU HAVE NOT ORDERED ANYTHING TILL NOW!!!");
        getch();
        return;
    }
    f=fopen("restaurant.dat", "ab");
    if(!f)
    {
        return;
    }
    system("cls");
    billdisp();
    while(top>=0)
    {
        rdisp(bd[top]);
        c=c+bd[top].tp;
        top--;
    }
    printf("\n\n\t\t\t\t TOTAL PRICE=%d", c);
    struct rdata* a;
    a=(struct rdata*)malloc(sizeof(struct rdata));
    printf("\n\t ENTER ROOM NO.:");
    scanf("%d", &a->rono);
    printf("\n\t ENTER NAME: ");
    scanf("%s", a->fnam);
    scanf("%s", a->lnam);
    printf("\n\t ENTER DATE (dd-mm-yyyy):");
    scanf("%s", a->dat);
    a->amt=c;
    char d[60];
    strcpy(d, a->fnam);
    strcat(d, " ");
    strcat(d, a->lnam);
    printf("%7d %55s %15s %10d", a->rono, d, a->dat, a->amt);
    fwrite(a, sizeof(struct rdata), 1, f);
    fclose(f);
}

void namedisp()    //LIST OF ORDERS
{
    FILE * f;
    f=fopen("restaurant.dat", "ab+");
    if(!f)
    {
        return;
    }
    struct rdata* a;
    char d[60];
      printf("\n\n");
    printf("\n    ----------------------------------------------------------------------------------------------------------------\n");
    printf("\n\t\t\t\t\t\t\tORDER'S PLACED \n\n");
    printf("    ----------------------------------------------------------------------------------------------------------------\n");
    printf("\n\n      ROOM NO.\t\t\t\t\t NAME \t\t\t DATE \t\t\t AMOUNT PAID\n\n");
    a=(struct rdata*)malloc(sizeof(struct rdata));
    while(fread(a, sizeof(struct rdata), 1, f))
    {
        strcpy(d, a->fnam);
        strcat(d, " ");
        strcat(d, a->lnam);
        printf("%10d %45s %25s %25d \n", a->rono, d, a->dat, a->amt);
    }
    fclose(f);
    free(a);
}


void billdisp()                                     //displaying bill
{
    struct rest food;
    printf("\n\n \t\t\t\t\t\t\t BILL \n\n");
    printf("\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
    printf("\t     ITEM ID \t\t   ITEM NAME \t ITEM QUANTITY \t\t PRICE \t\t TOTAl PRICE\n\n");
}

void lilmenu()                                          //displaying menu
{
    printf("\n\n \t\t\t\t\t\t\t DISHES \n\n");
    printf("\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
    printf("\t\t      ITEM ID \t\t\t\t ITEM NAME \t\t\t PRICE \n\n");
}

void rdisp(struct rest x)                               //displaying item details
{
    printf(" %15d     %25s %11d %17d %18d\n", x.fid, x.fname, x.qty, x.p, x.tp);
}

void custdisp()                                     //displaying bill
{
    printf("\n\n \t\t\t\t\t\t\t DETAILS \n\n");
    printf("\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
    printf("  ROOM NO.\t NAME \t\t  PHONE NO.\t\t EMAIL \t\t  CITY \t\t DATE   \t   STATUS \n\n");
    printf("\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
}

void crdisp(cust *a)                               //displaying customer details
{
    char d[50];
    strcpy(d, a->fnam);
    strcat(d, " ");
    strcat(d, a->lnam);
    printf(" %5d %22s %13s %26s %11s %9d-%02d-%4d  %10s \n", a->rno , d, a->pno, a->email, a->city, a->bdd, a->bmm, a->byyyy, a->status);
}

void detaildisplay()                                       //to print the details of the customers
{
    FILE * f;
    cust *a;
    a=(cust *)malloc(sizeof(cust));
    f=fopen("customer.dat", "ab+");
    custdisp();
    while(fread(a, sizeof(cust), 1, f))
    {
        crdisp(a);
    }
    fclose(f);
    free(a);
}
void bookrooms(int day, int month, int year)           //FUNCTION FOR BOOKING ROOMS AND ENTEERING CUSTOMER DETAILS
{
    struct cdet *a;
    FILE * f;
    f=fopen("customer.dat", "ab+");
    a=(struct cdet*)malloc(sizeof(struct cdet));
    a->rno=pop();
    if(a->rno==-1)
    {
        return;
    }
    printf("\n\n\n\t KINDLY FILL UP THE FOLLOWING DETAILS..........");
    printf("\n\n\t\t\t FIRST NAME:");
    scanf("%s", a->fnam);
    printf("\n\t\t\t LAST NAME:");
    scanf("%s", a->lnam);
    printf("\n\t\t\t CITY:");
    scanf("%s", a->city);
    printf("\n\t\t\t PHONE NO.:");
    scanf("%s", a->pno);
    printf("\n\t\t\t EMAIL ID:");
    scanf("%s", a->email);
    strcpy( a->status, "STAYING");
    a->bdd=day;
	a->bmm=month;
	a->byyyy=year;
    a->ldd=a->lmm=a->lyyyy=0;
    crdisp(a);
    fwrite(a, sizeof(cust), 1,f);
    fclose(f);
    free(a);
}
void modify()
{
    cust *a, *b;
    FILE *t, *f;
    int k, c=0;
    char w[30], x[30], y[20], z[60], d[30];
    f=fopen("customer.dat", "ab+");
    t=fopen("temp.dat", "ab+");
    a=(cust *)malloc(sizeof(cust));
    //b=(cust *)malloc(sizeof(cust));
    if((f==NULL) || (t==NULL))
    {
        printf("ERROR...");
        return;
    }
    printf("\n\n\tENTER THE ROOM NO. OF THE CUSTOMER WHOSE DETAILS AREE TO BE MODIFIED:");
    scanf("%d", &k);
    while(fread(a, sizeof(cust), 1, f))
    {

        if(k==a->rno &&(strcmp(a->status, "STAYING")==0))
        {
            c=1;
            printf("\n\n THE ROOM DETAILS ARE:\n");
            crdisp(a);
            printf("\n\n\t ENTER FIRST NAME (enter * to retain old):");
            scanf("%s", w);
            printf("\t ENTER LAST NAME (enter * to retain old):");
            scanf("%s", x);
            printf("\t ENTER PHONE NO. (enter * to retain old):");
            scanf("%s", y);
            printf("\t ENTER EMAIL (enter * to retain old):");
            scanf("%s", z);
            printf("\t ENTER CITY (enter * to retain old):");
            scanf("%s", d);
            if(strcmp(w, "*")!=0)
            {
                strcpy(a->fnam, w);
            }
            if(strcmp(x, "*")!=0)
            {
                strcpy(a->lnam, x);
            }
            if(strcmp(y, "*")!=0)
            {
                strcpy(a->pno, y);
            }
            if(strcmp(z, "*")!=0)
            {
                strcpy(a->email, z);
            }
            if(strcmp(d, "*")!=0)
            {
                strcpy(a->city, d);
            }
            printf("\n\t NEW MODIFIED DETAILS ARE:\n");
            crdisp(a);
            fwrite(a, sizeof(cust), 1, t);
        }
        else
        {
            fwrite(a, sizeof(cust), 1, t);
        }
    }
    if(c==0)
        {
            printf("\n\t\t PLEASE CHECK THE ROOM NO. ENTERED AND RETRY!!");
        }
    fclose(f);
    fclose(t);
    remove("customer.dat");
    rename("temp.dat", "customer.dat");

    free(a);
}
int checkYear(int year)                             //to check whether a year is a leap year or not
{
    if (year % 400 == 0)
        return 1;

    if (year % 100 == 0)
        return 0;

    if (year % 4 == 0)
        return 1;
    return 0;
}

int famount(int a, int b, int c, int x, int y, int z)     //to calculate the total amount to be paid by the customer for their stay in the hotel
{
    int days=0, mm=b;
    int arr[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    days=x-a;
    while(mm!=y)
    {
        days=days+arr[mm-1];
        if(mm==12)
            mm=1;
        else
            mm++;
    }
    if((checkYear(c)==1)&& y>2)
    {
        days++;
    }
    if (days==0)
    {
        days=1;
    }
    int t;
    t=days*PERDAY;
    return t;
}

void checkOut(int day, int month, int year)                //to checkout of the room
{
    FILE * f, *t, *pp;
    cust * a, *b;
    int k;
    f=fopen("customer.dat", "ab+");
    t=fopen("temp.dat", "ab+");
    a=(struct cdet*)malloc(sizeof(struct cdet));
    if((f==NULL) || (t==NULL))
    {
        printf("ERROR...");
        return;
    }
    int x, topay;
    printf("\n\n\t ENTER YOUR ROOM NO.:");
    scanf("%d", &x);
    fflush(stdin);
    while(fread(a, sizeof(cust), 1, f))
    {

        if(x==a->rno &&(strcmp(a->status, "STAYING")==0))
        {
            printf("\n\n THE ROOM DETAILS ARE:\n");
            crdisp(a);
            //printf("%d", day);
            a->ldd=day;
            a->lmm=month;
            a->lyyyy=year;
            printf("CHECKOUT DATE: %02d-%02d-%d", a->ldd, a->lmm, a->lyyyy);
            topay=famount(a->bdd, a->bmm, a->byyyy, day, month, year);
            printf("\n\n\t YOU NEED TO PAY FO: %d", topay);
            push(a->rno);
            strcpy(a->status, "LEFT");
            fwrite(a, sizeof(cust), 1, t);
        }
        else
        {
            fwrite(a, sizeof(cust), 1, t);
        }
    }
    fclose(f);
    fclose(t);
    remove("customer.dat");
    rename("temp.dat", "customer.dat");

    free(a);
}
void intro()                       //only for intro : printing welcome
{
    system("cls");
    printf("\n\n\n\n\n\n\n\n");
    printf("                |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| \n");
    printf("                ||----------------------------------------------------------------------------|| \n");
    printf("                ||  @@      @@  @@@@@@@@   @@      @@@@@@@   @@@@@@    @@       @@   @@@@@@@@ || \n");
    printf("                ||  @@      @@  @@         @@      @@       @@    @@   @@ @   @ @@   @@       || \n");
    printf("                ||  @@  @   @@  @@@@@      @@      @@       @@    @@   @@   @   @@   @@@@@    || \n");
    printf("                ||  @@ @  @ @@  @@         @@      @@       @@    @@   @@       @@   @@       || \n");
    printf("                ||  @@      @@  @@@@@@@@   @@@@@@  @@@@@@@   @@@@@@    @@       @@   @@@@@@@@ || \n");
    printf("                ||----------------------------------------------------------------------------|| \n");
    printf("                |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| \n");
    printf("\n\n\n");
    gotoxy(40, 20);
    getch();
    system("cls");
    printf("\n\n    ----------------------------------------------------------------------------------------------------------------\n");
    printf("\n\t\t\t\t\t\t\t  ABOUT \n\n");
    printf("    ----------------------------------------------------------------------------------------------------------------\n");
    printf("\n\t\tPopularised by  films, Ooty, The  Queen of the hills is the most vengaging destination in the south of\n");
    printf(" the Himalayas. The most ideal retreat to unwind in this abode of Nilgiris, HOTEL VALENCIA is at a short distance from");
    printf("\n the  city center of Ooty. The wonderful architecture of the hotel lends an atmosphere of calm and serenity admist the");
    printf("\n verdant  Nilgiris. Shake of your ethargy and  head out for the invigorating environs of Ooty  with us. HOTEL VALENCIA");
    printf("\n is the best and finest luxury resort in the evergreen  mountains of Ooty.  Overlooking the  lush tea gardens, this 12");
    printf("\n cottage, five star resort offers panoramic views of the mountains. Come and  enjoy the serenity of the nilgiris along");
    printf("\n with magnificent luxury with us!\n\n\n");
    printf("\n\t\t\t\t\t     AMENTIES!!");
    printf("\n\t\t\t\t 1. FREE WIFI");
    printf("\n\t\t\t\t 2. CAR HIRE SERVICE");
    printf("\n\t\t\t\t 3. FITNESS CENTER");
    printf("\n\t\t\t\t 4. BONFIRE WITH GAMES");
    printf("\n\t\t\t\t 5. SPA");
    printf("\n\t\t\t\t 6. DOCTER ON CALL");
    printf("\n\t\t\t\t 7. PONY RIDING");
    printf("\n\t\t\t\t 8. POOL");
    printf("\n\t\t\t\t 9. LAUNDRY SERVICE and  much more");
    getch();

}

int main()
{
    int day, month, year;
    int choice, c1, c2, k, c, m[12];
    struct dish st[5]={101, "PANEER TIKKA", 300, 102, "CHEESE BALLS", 250, 103, "HARA BHARA KEBAB", 350, 104, "MOMOS", 160, 105, "SPRNIG ROLlS", 200};
    struct dish mc[5]={201, "DAL MAKHNI", 180, 202, "DUM ALOO", 200, 203, "KADHAI PANEER", 220, 204, "CORN CAPSICUM MASALA", 210, 205, "MALAI KOFTA", 215};
    struct dish br[5]={301, "TANDOORI ROTI", 25,  302, "RUMALI ROTI", 35, 303, "NAAM", 45, 304, "LACHCHA PARATHA", 50, 305, "MISSI ROTI", 40};
    struct dish co[5]={401, "COTTAGGE CHEESE LOAF", 150, 402, "PASTA PERI PERI", 140,  403, "QUESADILLAS", 160, 404, "TACOS", 160, 405, "STUFFED CRUST PARADISE PIZZA", 250};
    struct dish de[5]={501, "KHEER", 120, 502, "BROWNIE WITH ICECREAM", 150, 503, "GULAB JAMUN", 100, 504, "ICE CREAM", 90, 505, "HALWA IN A JAR", 80};
    struct dish be[5]={601, "TEA", 50, 602, "COFFEE", 55, 603, "COLD COFFEE", 90, 604, "SMOOTHIE", 150, 605, "LIME SODA", 100};
    //struct rest r;
    struct rest a;
    int i=0;
    char ch, p[50];
    FILE *file;
    k=exists();
    if(k==0)
    {
        file=fopen("rooms.dat", "wb");

        fwrite(&f, sizeof(int), 1, file);
        fwrite(&r, sizeof(int), 1, file);
        fwrite(rooms, sizeof(int), SIZE, file);
        fclose(file);
    }
    int c3, rr=0;
    intro();
    time_t now;
    time( &now);
    struct tm *local = localtime(&now);
    day = local->tm_mday;			// get day of month (1 to 31)
	month = local->tm_mon + 1;		// get month of year (0 to 11)
	year = local->tm_year + 1900;	// get year since 1900
	start:
	    system("cls");
	    printf("\n\n\n\n\n");
	    printf("\t\t===========================================================================================\n");
	    printf("\t\t\t\t\t\t    * * * * * * * * * \n");
        printf("\t\t\t\t\t\t    *   MAIN MENU   * \n");
        printf("\t\t\t\t\t\t    * * * * * * * * * \n");
        printf("\t\t===========================================================================================\n");
        printf("\n\n\t\t\t\t 1. ADMINISTRATOR");
        printf("\n\t\t\t\t 2. CUSTOMER");
        printf("\n\t\t\t\t 3. RESTAURANT");
        printf("\n\t\t\t\t 4. EXIT");
        printf("\n\t\t\t\t    CHOICE:");
        scanf("%d", &choice);
        switch(choice)
        {
        case 1: ad:
                    if(rr==0)
                    {
                        system("cls");                 //password is "manager"
                        gotoxy(25, 10);
                        printf(" PLEASE ENTER THE PASSWORD ");
                        ch=getch();
                        p[0]=ch;
                        for(c=0; c<7; c++)
                        {
                            printf("*");
                            ch=getch();//if(ch==char(13)) break;
                            i++;
                            p[i]=ch;
                        }
                        p[i]='\0';//printf("%s", p);
                        if(strcmpi(p,"manager")!=0)	  //password is "manager"
                        {
                                    //printf("\n\n\n");
                            gotoxy(25, 10);
                            printf("  WRONG PASSWORD ");
                            printf("\n\t\t......access denied......\t\t\n");
                            getch();
                            exit(0);
                        }
                        rr=1;
                    }
                    system("cls");
                    printf("\n\n\n\n\n\t\t\t\t\t\t MENU");
                    printf("\n\t\t============================================================================================\n");
                    printf("\n\t\t\t\t\t 1. VIEW CUSTOMER DETAILS (ROOMS)");
                    printf("\n\t\t\t\t\t 2. MODIFY CUSTOMER DETAILS");
                    printf("\n\t\t\t\t\t 3. LIST OF ORDERS PLACED");
                    printf("\n\t\t\t\t\t 4. RETURN TO MAIN MENU");
                    printf("\n\t\t\t\t\t    CHOICE:");
                    scanf("%d", &c3);
                    switch(c3)
                    {
                        case 1:
                                system("cls");
                                detaildisplay();
                                getch();
                                goto ad;

                        case 2: system("cls");
                                modify();
                                getch();
                                goto ad;
                        case 3: system("cls");
                                namedisp();
                                getch();
                                goto ad;
                        case 4: system("cls");
                                goto start;
                    }
        case 2: tk: rr=0;
                    system("cls");
                    printf("\n\n\n\n\n\t\t\t\t\t\t MENU");
                    printf("\n\t\t============================================================================================\n");
                    printf("\n\t\t\t\t\t 1. BOOK ROOMS ");
                    printf("\n\t\t\t\t\t 2. CHECKOUT ROOMS");
                    printf("\n\t\t\t\t\t 3. RETURN TO MAIN MENU");
                    printf("\n\t\t\t\t\t    CHOICE:");
                    scanf("%d", &c1);
                    switch(c1)
                    {
                        case 1: system("cls");
                                bookrooms(day, month, year);
                                getch();
                                goto tk;
                        case 2: system("cls");
                                checkOut(day, month, year);
                                getch();
                                goto tk;
                        case 3: system("cls");
                                goto start;
                    }
                    break;
        case 3: resto:
                rr=0;
                system("cls");
                printf("\n\n\n\n\n");
                printf("\t\t\t\t\t\t\t************* \n");
                printf("\t\t\t\t\t\t\t**   MENU  ** \n");
                printf("\t\t\t\t\t\t\t************* \n\n");
                printf("\t\t\t\t\t\t    1. STARTERS \n");
                printf("\t\t\t\t\t\t    2. MAIN COURSE\n");
                printf("\t\t\t\t\t\t    3. BREADS\n");
                printf("\t\t\t\t\t\t    4. CONTINENTAL\n");
                printf("\t\t\t\t\t\t    5. DESSERTS\n");
                printf("\t\t\t\t\t\t    6. BEVERAGES\n");
                printf("\t\t\t\t\t\t    7. FINALIZE YOUR ORDER \n");
                printf("\t\t\t\t\t\t    8. EXIT TO MAIN MENU\n");
                printf("\t\t\t\t\t\t       CHOICE: ");
                scanf("%d", &c2);
                switch(c2)
                {

                    case 1: system("cls");
                            lilmenu();
                            for(c=0; c<5; c++)
                            {
                                printf("%25d %40s %25d\n", st[c].id, st[c].nm, st[c].pri);
                            }
                            printf("\n\n\t\t\t ENTER CHOIOCE:");
                            scanf("%d", &c);
                            a=searchid(st, c);
                            order(a);
                            //printf("ITEM CODE OF THE YOU WANT ")
                            goto resto;
                    case 2: system("cls");
                            lilmenu();
                            for(c=0; c<5; c++)
                            {
                                printf("%25d %40s %25d\n", mc[c].id, mc[c].nm, mc[c].pri);
                            }
                            printf("\n\n\t\t\t ENTER CHOIOCE:");
                            scanf("%d", &c);
                            a=searchid(mc, c);
                            order(a);
                            //printf("ITEM CODE OF THE YOU WANT ")
                            goto resto;
                    case 3: system("cls");
                            lilmenu();
                            for(c=0; c<5; c++)
                            {
                                printf("%25d %40s %25d\n", br[c].id, br[c].nm, br[c].pri);
                            }
                            printf("\n\n\t\t\t ENTER CHOIOCE:");
                            scanf("%d", &c);
                            a=searchid(br, c);
                            order(a);
                            //printf("ITEM CODE OF THE YOU WANT ")
                            goto resto;
                    case 4: system("cls");
                            lilmenu();
                            for(c=0; c<5; c++)
                            {
                                printf("%25d %40s %25d\n", co[c].id, co[c].nm, co[c].pri);
                            }
                            printf("\n\n\t\t\t ENTER CHOIOCE:");
                            scanf("%d", &c);
                            a=searchid(co, c);
                            order(a);
                            //printf("ITEM CODE OF THE YOU WANT ")
                            goto resto;
                    case 5: system("cls");
                            lilmenu();
                            for(c=0; c<5; c++)
                            {
                                printf("%25d %40s %25d\n", de[c].id, de[c].nm, de[c].pri);
                            }
                            printf("\n\n\t\t\t ENTER CHOIOCE:");
                            scanf("%d", &c);
                            a=searchid(de, c);
                            order(a);
                            //printf("ITEM CODE OF THE YOU WANT ")
                            goto resto;
                    case 6: system("cls");
                            lilmenu();
                            for(c=0; c<5; c++)
                            {
                                printf("%25d %40s %25d\n", be[c].id, be[c].nm, be[c].pri);
                            }
                            printf("\n\n\t\t\t ENTER CHOIOCE:");
                            scanf("%d", &c);
                            a=searchid(be, c);
                            order(a);
                            goto resto;
                    case 7: system("cls");
                            disp();
                            getch();
                            goto resto;
                    case 8: goto start;

              }
        case 4: getch();
                exit(0);
        }
	return 0;

}
