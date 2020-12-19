#include<stdio.h>
#include<graphics.h>
#include<winbgim.h>
#include<iostream>
#include<conio.h>
#define cols 8
#define rows 8
using namespace std;

float l;                                                  //latura unuei celule
typedef struct board
{
    float x,y;                                          //coordonate colt stanga sus pentru fiecare celula
    int celltype;                                    //pentru a implementa cainii si vulpea
} grid[8][8];


struct position
{
    int i, j;
} moveFrom, moveTo;



void moveFox();

void getMoveFromOnClick(int x1, int y1);

void getMoveToOnClick(int x1, int y1);

void readMatrix (grid board);

void drawFox(grid board,int i,int j);

void drawDog(grid board,int i,int j);

void matrix(grid board);

void drawBoard(grid board);

void menu();

grid board;


int main()
{


    menu();


    getch();
    closegraph();
}
void readMatrix (grid board)                //pentru teste ,urmeaza sa fie initilaizata din fisier
{
    for (int i = 0; i < cols; i++)
        for (int j = 0; j < rows; j++)
            board[i][j].celltype = 0;
    board[0][3].celltype=2;      //vulpea
    board[7][0].celltype=1;      //caine din stanga
    board[7][2].celltype=1;      //cainele al 2-lea
    board[7][4].celltype=1;      //cainele al 3-lea
    board[7][6].celltype=1;      //cainele al 4-lea
}
void drawFox( grid board, int i, int j  )
{
    setcolor(RED);
    circle( board[i][j].x+l/2, board[i][j].y+l/2, l/6 );
    setfillstyle(  SOLID_FILL,RED  );
    floodfill( board[i][j].x+l/2,  board[i][j].y+l/2, RED);
}
void drawDog(grid board,int i,int j)
{

    setcolor(GREEN);
    circle(board[i][j].x+l/2,board[i][j].y+l/2,l/6);
    setfillstyle(SOLID_FILL,GREEN);
    floodfill(board[i][j].x+l/2,board[i][j].y+l/2,GREEN);

}
void   matrix(grid board )                    //pentru fiecare patrat din tabla ,indicam coordonatele coltului stanga sus
{
    l=(float)getmaxx()/cols;                              //latura unui patratel
    //coordonatele coltului stanga sus al tablei
    board[0][0].x=0;
    board[0][0].y=0;
    //coordonatele coltului stanga sus  pentru fiecare patrat
    int i,j;
    for(i=0; i<8; i++)
        for(j=0; j<8; j++)
        {
            board[i][j].x=board[0][0].x+j*l;
            board[i][j].y=board[0][0].y+i*l;
        }
}
void drawBoard(grid board)
{
    int i,j;

    matrix( board ) ;
    for (i = 0; i < cols; i++)
    {
        for ( j = 0; j < rows; j++)
        {
            if((i+j)%2==0)
            {
                setcolor( BLACK) ;
                rectangle  (    board[i][j].x,    board[i][j].y,board[i][j].x+l,   board[i][j].y+l);
                setfillstyle (  SOLID_FILL,BLACK );
                floodfill      (  board[i][j].x+1,  board[i][j].y+1,   BLACK );
            }
            else
            {
                setcolor(WHITE);
                rectangle(board[i][j].x,board[i][j].y,board[i][j].x+l,board[i][j].y+l);
                setfillstyle(SOLID_FILL,WHITE);
                floodfill(board[i][j].x+1,board[i][j].y+1,WHITE);
            }
            if(board[i][j].celltype==2)
                drawFox(board,i,j);
            else if(board[i][j].celltype==1)
                drawDog(board,i,j);
        }

    }

    moveFox();


}

void menu()
{
    int midx,x,y;

    initwindow(800, 800);
    setbkcolor(CYAN);
    midx = getmaxx() / 2;

    settextstyle(10, HORIZ_DIR, 7);      //fontul si marimea tipul orizontal
    settextjustify(1,1);            //centrat
    outtextxy(midx, 150, "CAINII SI VULPEA");        // x si y unde se va afisa stringul "..."

    settextstyle(9, HORIZ_DIR, 6);
    setbkcolor(RED);
    outtextxy(midx, 300, "START");

    settextstyle(9, HORIZ_DIR, 6);
    setbkcolor(RED);
    outtextxy(midx, 400, " EXIT ");

    while(1)
    {
        if( ismouseclick(WM_LBUTTONDOWN) )
        {
            x=mousex();
            y=mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            if(x >240 && x<467 && y>258 && y<312)
            {
                cleardevice();
                readMatrix ( board ) ;
                drawBoard(  board );
            }
            if(x >240 && x<467 && y>358 && y<412)
                exit(0);
        }
    }
}


void moveFox()
{
    int x,y;


    while(1)
    {
        if( ismouseclick(WM_LBUTTONDOWN) )
        {
            x=mousex();
            y=mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            if( y>=0 && y<=100 && x>=300 && x<=400 )
            {
                bool gata=0;
                do
                {
                    if(ismouseclick(WM_LBUTTONUP)  )
                    {
                        x=mousex();
                        y=mousey();
                        clearmouseclick(WM_LBUTTONUP);

                        if( y>=100 && y<=200 && x>=200 && x<=300 )
                        {
                            drawFox(board, 1, 2 );
                            setcolor(WHITE);
                            setfillstyle(SOLID_FILL , WHITE );
                            circle(350,50,25);
                            floodfill(350,50,WHITE);
                             gata=1;
                        }
                    }

                }
                while(!gata);

            }

        }
    }
}

/* if( moveFrom.i>=0 && moveFrom.i<=100 && moveFrom.j>=300 && moveFrom.j<=400 )
 {
       registermousehandler(WM_LBUTTONUP, getMoveToOnClick);

       cout<<moveTo.j<<" "<<moveTo.i;


         //if( moveTo.i>=100 && moveTo.i<=200 && moveTo.j>=200 && moveTo.j<=300)

 }
}
*/



void getMoveFromOnClick(int x1, int y1)
{
    moveFrom.j=x1;
    moveFrom.i=y1;

}


void getMoveToOnClick(int x1, int y1)
{

    moveTo.j=x1;
    moveTo.i=y1;
}
