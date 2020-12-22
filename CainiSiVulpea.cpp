#include<stdio.h>
#include<graphics.h>
#include<winbgim.h>
#include<iostream>
#include<conio.h>
#define cols 8
#define rows 8
using namespace std;

float l;                                                //latura unuei celule
typedef struct board
{
    float x,y;                                          //coordonate colt stanga sus pentru fiecare celula
    int celltype;                                    //pentru a implementa cainii si vulpea
} grid[8][8];

struct position
{
    int i, j;
} moveFrom,moveTo;

int turn=1,dogsWin=0,foxWins=0;

void moveFox(grid board);

void getMoveFromOnClick(int x1, int y1);

void getMoveToOnClick(int x1, int y1);

void readMatrix (grid board);

void drawFox(grid board,int i,int j);

void drawDog(grid board,int i,int j);

void matrix(grid board);

void drawBoard(grid board);

void menu();
bool moveIsValid (grid board, position moveFrom, position moveTo, int turn ) ;

void PlayGame();
bool didTheFoxWin(grid board);
bool didTheDogwin(grid board);

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

    setcolor(BROWN);
    circle(board[i][j].x+l/2,board[i][j].y+l/2,l/6);
    setfillstyle(SOLID_FILL,BROWN);
    floodfill(board[i][j].x+l/2,board[i][j].y+l/2,BROWN);

}
void  matrixcoord(grid board )                    //pentru fiecare patrat din tabla ,indicam coordonatele coltului stanga sus
{
    l=(float)(getmaxx()-200)/cols;                              //latura unui patratel
    //coordonatele coltului stanga sus al tablei
    board[0][0].x=100;
    board[0][0].y=100;
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

    matrixcoord( board ) ;
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
                PlayGame();
            }
            if(x >240 && x<467 && y>358 && y<412)
                exit(0);
        }
    }
}


void moveFox(grid board)
{
    int x,y;
    bool moveDone=0;
    setlinestyle(0,0,6);
    setcolor(BLUE);
    line(496,0,496,30);
    setcolor(RED);
    settextstyle (2 , HORIZ_DIR, 60 );
    outtextxy(getmaxx()/2,l/2,"FOX     MOVES");
    while(!moveDone)
    {
        if( ismouseclick(WM_LBUTTONDOWN) )
        {
            x=mousex();
            y=mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            getMoveFromOnClick(x,y);
            if( board[moveFrom.i][moveFrom.j].celltype==2)
            {
                do
                {
                    if(ismouseclick(WM_LBUTTONUP)  )
                    {
                        x=mousex();
                        y=mousey();
                        clearmouseclick(WM_LBUTTONUP);
                        getMoveToOnClick(x,y);
                        if(  moveIsValid(board,moveFrom,moveTo,turn) )
                        {

                            drawFox(board, moveTo.i, moveTo.j );
                            setcolor(WHITE);
                            setfillstyle(SOLID_FILL , WHITE );
                            circle(board[moveFrom.i][moveFrom.j].x+l/2,board[moveFrom.i][moveFrom.j].y+l/2,l/4);
                            floodfill(board[moveFrom.i][moveFrom.j].x+l/2,board[moveFrom.i][moveFrom.j].y+l/2,WHITE);
                            moveDone=1;
                        }
                    }

                }
                while(!moveDone);

            }

        }
    }
    turn=2;
    board[moveTo.i][moveTo.j].celltype= board[moveFrom.i][moveFrom.j].celltype;
    board[moveFrom.i][moveFrom.j].celltype=0;
}
void moveDog(grid board)
{
    int x,y;
    bool moveDone=0;
    setcolor(BROWN);
    outtextxy(getmaxx()/2,l/2,"DOG   MOVES");
    while(!moveDone)
    {
        if( ismouseclick(WM_LBUTTONDOWN) )
        {
            x=mousex();
            y=mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            getMoveFromOnClick(x,y);
            if( board[moveFrom.i][moveFrom.j].celltype==1 )
            {
                do
                {
                    if(ismouseclick(WM_LBUTTONUP)  )
                    {
                        x=mousex();
                        y=mousey();
                        clearmouseclick(WM_LBUTTONUP);
                        getMoveToOnClick(x,y);
                        if( moveIsValid(board,moveFrom,moveTo,turn))
                        {

                            drawDog(board, moveTo.i, moveTo.j );
                            setcolor(WHITE);
                            setfillstyle(SOLID_FILL , WHITE );
                            circle(board[moveFrom.i][moveFrom.j].x+l/2,board[moveFrom.i][moveFrom.j].y+l/2,l/4);
                            floodfill(board[moveFrom.i][moveFrom.j].x+l/2,board[moveFrom.i][moveFrom.j].y+l/2,WHITE);;
                            moveDone=1;
                        }
                    }
                }while(!moveDone);

            }

        }

        }
    turn=1;
    board[moveTo.i][moveTo.j].celltype= board[moveFrom.i][moveFrom.j].celltype;
    board[moveFrom.i][moveFrom.j].celltype=0;
}
void getMoveFromOnClick(int x1, int y1)
{
    moveFrom.j=(x1-100)/l;
    moveFrom.i=(y1-100)/l;

}


void getMoveToOnClick(int x1, int y1)
{

    moveTo.j=(x1-100)/l;
    moveTo.i=(y1-100)/l;
}



void PlayGame()
{   setbkcolor(BLUE);
    cleardevice();
    readMatrix(board);
    drawBoard(board);

    while(turn)
    {
            if(turn==1) moveFox(board);
            else if(turn==2) moveDog(board);
            if(didTheFoxWin(board)) {
            turn =0;
            cleardevice();
            setcolor(RED);
            setbkcolor(BLACK);
            settextstyle(10, HORIZ_DIR, 7);
            outtextxy(getmaxx()/2,getmaxy()/4,"THE FOX WON!");
                    setcolor(WHITE);
                    settextstyle(8, HORIZ_DIR, 5);
                    setbkcolor(BLACK);
                    outtextxy(getmaxy()/2, 300, "TRY AGAIN");
                    outtextxy(getmaxy()/2, 360, "MAIN MENU");
                    outtextxy(getmaxy()/2, 420, "QUIT GAME");
}
            if(didTheDogwin(board))
            {
           turn =0;
            cleardevice();
            setcolor(BROWN);
            setbkcolor(BLACK);
            settextstyle(10, HORIZ_DIR, 7);
            outtextxy(getmaxx()/2,getmaxy()/4,"THE DOGS WON!");
                    setcolor(WHITE);
                    settextstyle(8, HORIZ_DIR, 5);
                    setbkcolor(BLACK);
                    outtextxy(getmaxy()/2, 300, "TRY AGAIN");
                    outtextxy(getmaxy()/2, 360, "MAIN MENU");
                    outtextxy(getmaxy()/2, 420, "QUIT GAME");
            }
}
}

bool moveIsValid (grid board, position moveFrom, position moveTo, int turn ) {
    if( board[moveTo.i][moveTo.j].celltype==0 ){ //if the target field is free
        if( turn == 1 && board[moveFrom.i][moveFrom.j].celltype==2 ){ //if it's a fox & it's its turn
            if((moveTo.i == moveFrom.i + 1 && moveTo.j == moveFrom.j + 1) ||
                (moveTo.i == moveFrom.i + 1 && moveTo.j == moveFrom.j - 1) ||
                (moveTo.i == moveFrom.i - 1 && moveTo.j == moveFrom.j + 1) ||
                (moveTo.i == moveFrom.i - 1 && moveTo.j == moveFrom.j - 1) )
                    return true;
        } else if(turn == 2 && board[moveFrom.i][moveFrom.j].celltype == 1 ) { //if it's a dog & it's its turn
            if( (moveTo.i == moveFrom.i - 1 && moveTo.j == moveFrom.j + 1) ||
                (moveTo.i == moveFrom.i - 1 && moveTo.j == moveFrom.j - 1) )
                    return true;
        }
    }
    return false;
}
bool didTheFoxWin(grid board)
{
    for(int i=0;i<rows;i++)
        if(board[7][i].celltype==2) return true;
    return false;
}

bool didTheDogwin(grid board)
{
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            if(
               (board[i-1][j-1].celltype==1 || i-1<0 || j-1<0)&&
               (board[i-1][j+1].celltype==1 || i-1<0 || j+1>7)&&
               (board[i+1][j-1].celltype==1 || i+1>7 || j-1<0)&&
               (board[i+1][j+1].celltype==1 || i+1>7 || j+1>7)&&
                board[i][j].celltype==2)
            {
                return true;
            }
    return false;
}
