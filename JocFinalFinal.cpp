#include<stdio.h>
#include<graphics.h>
#include<winbgim.h>
#include<iostream>
#include<conio.h>
#include<fstream>
#include<windowsx.h>
#define cols 8
#define rows 8
#define boardlenght 200
using namespace std;
float l;

typedef struct board
{
    float x,y;                                                  //coordonate colt stanga sus pentru fiecare celula
    int celltype;
} grid[8][8];

struct position
{
    int i, j;
} moveFrom,moveTo;

typedef struct game
{
    int piecetype;
    int nextMove;
    int gametype;
    int strategy;
    int step;
    int k;
    int LINE;
} Mainstr;

void moveFox(grid board);

void getMoveFromOnClick(int x1, int y1);

void getMoveToOnClick(int x1, int y1);

void ChooseMode();

void Hard();

void moveBotRightDiagonal(int i, int j);

void moveBotLeftDiagonal(int i, int j);

void Rules();

void ChooseDifficulty();

void BotStoopid();

void readMatrix (grid board);

void drawFox(grid board,int i,int j);

void drawDog(grid board,int i,int j);

void matrixcoord(grid board);

void drawBoard(grid board);

void menu();

bool moveIsValid (grid board, position moveFrom, position moveTo, int turn ) ;

void PlayGame();

bool didTheFoxWin(grid board);

bool didTheDogwin(grid board);

void Options();

void SaveGame();

void LoadGame();

grid board,savedBoard;
Mainstr game,save;







int main()
{
    initwindow(800, 800);
    l=(float)(getmaxx()-boardlenght)/cols;


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
    board[7][6].celltype=1;//cainele al 4-lea
}
void drawFox( grid board, int i, int j )
{
    if(game.piecetype==0)
    {
        setcolor(RED);
        circle( board[i][j].x+l/2, board[i][j].y+l/2, l/6 );
        setfillstyle(  SOLID_FILL,RED  );
        floodfill( board[i][j].x+l/2,  board[i][j].y+l/2, RED);
    }
    else if(game.piecetype==1)
    {
        setcolor(9);
        rectangle( board[i][j].x+20, board[i][j].y+20, board[i][j].x+50, board[i][j].y+50);
        setfillstyle(  SOLID_FILL,9  );
        floodfill( board[i][j].x+l/2,  board[i][j].y+l/2, 9);
    }
    else if(game.piecetype==2)
    {
        setcolor(BLUE);
        circle( board[i][j].x+l/2, board[i][j].y+l/2, l/6 );
        setfillstyle(  SOLID_FILL,BLUE  );
        floodfill( board[i][j].x+l/2,  board[i][j].y+l/2, BLUE);

    }
    else if(game.piecetype==3)
    {
        setcolor(13);
        rectangle( board[i][j].x+20, board[i][j].y+20, board[i][j].x+50, board[i][j].y+50);
        setfillstyle(  SOLID_FILL,13  );
        floodfill( board[i][j].x+l/2,  board[i][j].y+l/2, 13);
    }
}

void drawDog(grid board,int i,int j)
{

    if(game.piecetype==0)
    {
        setcolor(GREEN);
        circle( board[i][j].x+l/2, board[i][j].y+l/2, l/6 );
        setfillstyle(  SOLID_FILL,GREEN  );
        floodfill( board[i][j].x+l/2,  board[i][j].y+l/2, GREEN);
    }
    else  if(game.piecetype==1)
    {
        setcolor(10);
        rectangle( board[i][j].x+20, board[i][j].y+20, board[i][j].x+50, board[i][j].y+50);
        setfillstyle(  SOLID_FILL,10 );
        floodfill( board[i][j].x+l/2,  board[i][j].y+l/2, 10);
    }
    else  if(game.piecetype==2)
    {
        setcolor(YELLOW);
        circle( board[i][j].x+l/2, board[i][j].y+l/2, l/6 );
        setfillstyle(  SOLID_FILL,YELLOW  );
        floodfill( board[i][j].x+l/2,  board[i][j].y+l/2, YELLOW);
    }
    else if(game.piecetype==3)
    {
        setcolor(11);
        rectangle( board[i][j].x+20, board[i][j].y+20, board[i][j].x+50, board[i][j].y+50);
        setfillstyle(  SOLID_FILL,11 );
        floodfill( board[i][j].x+l/2,  board[i][j].y+l/2, 11);
    }

}

void  matrixcoord(grid board )                    //pentru fiecare patrat din tabla ,indicam coordonatele coltului stanga sus
{
    board[0][0].x=100;                                //coordonatele coltului stanga sus al tablei
    board[0][0].y=100;
    int i,j;
    for(i=0; i<8; i++)
        for(j=0; j<8; j++)                           //coordonatele coltului stanga sus  pentru fiecare patrat
        {
            board[i][j].x=board[0][0].x+j*l;
            board[i][j].y=board[0][0].y+i*l;
        }
}
void drawBoard(grid board)
{
    int i,j;
    readimagefile("drawboard.jpg",0,0,800,800);
    matrixcoord(board);
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
    setbkcolor(BLACK);
    cleardevice();
    readimagefile("vulpea.jpg",0,0,800,800);
    setbkcolor(CYAN);
    midx = getmaxx() / 2+100;
    readMatrix(board);
    settextstyle(10, HORIZ_DIR, 7);      //fontul si marimea tipul orizontal
    settextjustify(1,1);            //centrat



    while(1)
    {
        if( ismouseclick(WM_LBUTTONDOWN) )
        {
            x=mousex();
            y=mousey();
            clearmouseclick(WM_LBUTTONDOWN);


            if(x >744 && x<791 && y>0 && y<46)
                exit(0);

            if(x >508 && x<652 && y>255 && y<312)
                ChooseMode();
            if(x >485 && x<650 && y>361 && y<408)
                Options();
            if(x >504 && x<625 && y>459 && y<503)
                Rules();
        }
    }
}

void Rules()
{
    int x,y;
    setbkcolor(BLACK);
    cleardevice();
    readimagefile("BrownPaint.jpg",0,0,800,800);

    while(1)
    {
        if( ismouseclick(WM_LBUTTONDOWN) )
        {
            x=mousex();
            y=mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            if(x >27 && x<111 && y>715 && y<784)
                menu();
        }
    }
}
void ChooseMode()
{
    int midx,x,y;
    midx = getmaxx() / 2;
    setbkcolor(BLACK);
    cleardevice();
    readimagefile("Doggo.jpg",0,0,800,800);
    while(1)
    {
        if( ismouseclick(WM_LBUTTONDOWN) )
        {
            x=mousex();
            y=mousey();
            clearmouseclick(WM_LBUTTONDOWN);



            if(x >88 && x<583 && y>209 && y<250)
            {
                readMatrix(board);
                game.nextMove=2;
                PlayGame();
            }

            if(x >51 && x<625 && y>280 && y<321)
            {
                ChooseDifficulty();
            }

            if(x >15 && x<105 && y>0 && y<74)
                menu();
            if(x >130 && x<540 && y>350 && y<390)
            {
                LoadGame();
                if(game.gametype==1)
                    PlayGame();
                else if(game.gametype==2)
                    BotStoopid();
                if( game.gametype ==3)
                    Hard() ;
            }



        }
    }

}
void ChooseDifficulty()
{
    int midx,x,y;
    midx = getmaxx() / 2;
    setbkcolor(BLACK);
    cleardevice();
    readimagefile("Doggodifficulty.jpg",0,0,800,800);



    while(1)
    {
        if( ismouseclick(WM_LBUTTONDOWN) )
        {
            x=mousex();
            y=mousey();
            clearmouseclick(WM_LBUTTONDOWN);


            if(x >293 && x<430 && y>218 && y<258)
            {
                readMatrix(board);
                game.nextMove=2;
                BotStoopid();
            }


            if(x >293 && x<430 && y>290 && y<335)
            {
                readMatrix(board);
                game.nextMove=2;
                game.strategy=0,game.step=0,game.LINE=6,game.k=0;
                Hard();
            }


            if(x >15 && x<105 && y>0 && y<74)
                ChooseMode();

        }
    }

}
void moveFox(grid board)
{
    int x,y,t,z;
    bool moveDone=0;
    if(game.piecetype==0)
        setcolor(RED);
    else if(game.piecetype==1)
        setcolor(9);
    else if (game.piecetype==2)
        setcolor(BLUE);
    else if (game.piecetype==3)
        setcolor(13);


    settextstyle (2, HORIZ_DIR, 60 );
    settextjustify(1,1);
    setbkcolor(BLACK);
    outtextxy(getmaxx()/2,l/2,"FOX     MOVES");
    while(!moveDone)
    {
        if(ismouseclick(WM_LBUTTONDOWN) )
        {
            x=mousex();
            y=mousey();
            getMoveFromOnClick(x,y);
            while(! moveDone)
            {
                if(ismouseclick(WM_LBUTTONUP))
                {
                    t=mousex();
                    z=mousey();
                    clearmouseclick(WM_LBUTTONUP);
                    getMoveToOnClick(t,z);
                    if(  moveIsValid(board, moveFrom, moveTo,game.nextMove ) )
                    {

                        drawFox(board,  moveTo.i,  moveTo.j );
                        setcolor(WHITE);
                        setfillstyle(SOLID_FILL,  WHITE );
                        circle(board[moveFrom.i][moveFrom.j].x+l/2,board[moveFrom.i][moveFrom.j].y+l/2, l/2-5);
                        floodfill(board[moveFrom.i][moveFrom.j].x+l/2,  board[moveFrom.i][moveFrom.j].y+l/2, WHITE);
                        moveDone = 1;
                    }


                    else
                    {

                        if(x>16 && x<83 && y>163  && y<253)
                        {
                            SaveGame();
                            exit(1);
                        }
                        if(x>20 && x<86 && y<119 & y>17)
                        {
                            SaveGame();
                        }
                        if(x>730 && x<774 &&y>17 && y<66)
                            exit(0);

                        else
                        {
                            break;
                            moveFox(board);
                        }
                    }
                }
                clearmouseclick(WM_LBUTTONDOWN);
            }
        }
    }
    board[moveTo.i][moveTo.j].celltype= board[moveFrom.i][moveFrom.j].celltype;
    board[moveFrom.i][moveFrom.j].celltype=0;
}


void moveDog(grid board)
{
    int x,y,t,z;
    bool moveDone=0;
    if(game.piecetype==0)
        setcolor(GREEN);
    else if(game.piecetype==1)
        setcolor(10);
    else if(game.piecetype==2)
        setcolor(YELLOW);
    else if(game.piecetype==3)
        setcolor(11);
    settextstyle (2, HORIZ_DIR, 60 );
    settextjustify(1,1);
    outtextxy(getmaxx()/2,l/2,"DOG   MOVES");

    while(!moveDone)
    {
        if(ismouseclick(WM_LBUTTONDOWN) )
        {
            x=mousex();
            y=mousey();
            getMoveFromOnClick(x,y);
            while(! moveDone)
            {
                if(ismouseclick(WM_LBUTTONUP))
                {
                    t=mousex();
                    z=mousey();
                    clearmouseclick(WM_LBUTTONUP);
                    getMoveToOnClick(t,z);
                    if( moveIsValid(board,moveFrom,moveTo,game.nextMove))
                    {
                        drawDog(board, moveTo.i, moveTo.j );
                        setcolor(WHITE);
                        setfillstyle(SOLID_FILL, WHITE );
                        circle(board[moveFrom.i][moveFrom.j].x+l/2,board[moveFrom.i][moveFrom.j].y+l/2,l/2-5);
                        floodfill(board[moveFrom.i][moveFrom.j].x+l/2,board[moveFrom.i][moveFrom.j].y+l/2,WHITE);;
                        moveDone=1;
                    }
                    else
                    {
                        if(x>16 && x<83 && y>163  && y<253)
                        {
                            SaveGame();
                            exit(1);
                        }
                        if(x>20 && x<86 && y<119 & y>17)
                        {
                            SaveGame();
                        }
                        if(x>730 && x<774 &&y>17 && y<66)
                            exit(0);
                        else
                        {
                            break;
                            moveDog(board);
                        }
                    }
                }
                clearmouseclick(WM_LBUTTONDOWN);
            }
        }
    }
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

void BotStoopid()
{
    int x,y,i,j,click=1;
    game.gametype=2;
    setbkcolor(DARKGRAY);
    cleardevice();
    drawBoard(board);
    while(game.nextMove)
    {
        if(game.nextMove==2)
        {
            moveFox(board);
            game.nextMove=1;
        }
        if(game.nextMove==1)
        {
            int dogdrawn=0;
            bool moveDone=0;
            switch(game.piecetype)
            {
            case 0 :
                setcolor(GREEN);
                break;
            case 2:
                setcolor(YELLOW);
                break;
            }
            outtextxy(getmaxx()/2,l/2,"DOG   MOVES");
            while(!moveDone )
            {
                i=rand()%10-2;
                j=rand()%10-2;

                if(  ( board[i][j].celltype==1 && !dogdrawn)   &&   ( board[i-1][j+1].celltype==0 || board[i-1][j-1].celltype==0 )   )
                    if(  board[i-1][j+1].celltype==0 && i-1>=0  && j+1<8 && j>=0 )
                    {

                        board[i][j].celltype=0;

                        setcolor(WHITE);
                        setfillstyle(SOLID_FILL, WHITE );
                        circle(board[i][j].x+l/2,board[i][j].y+l/2,l/2-5);
                        floodfill(board[i][j].x+l/2,board[i][j].y+l/2,WHITE);

                        drawDog(board, i-1, j+1);
                        moveDone=1;
                        dogdrawn=1;
                        board[i-1][j+1].celltype=1;

                    }

                    else if(  board[i-1][j-1].celltype==0 && i-1>=0  && j-1>=0  )
                    {

                        board[i][j].celltype=0;

                        setcolor(WHITE);
                        setfillstyle(SOLID_FILL, WHITE );
                        circle(board[i][j].x+l/2,board[i][j].y+l/2,l/2-5);
                        floodfill(board[i][j].x+l/2,board[i][j].y+l/2,WHITE);


                        drawDog(board, i-1, j-1);
                        moveDone=1;
                        dogdrawn=1;
                        board[i-1][j-1].celltype=1;
                    }



            }
            game.nextMove=2;

        }
        if(didTheFoxWin(board))
        {

            click=0;
            game.nextMove =0;
            setcolor(RED);
            setbkcolor(BLACK);
            settextstyle(10, HORIZ_DIR, 9);
            outtextxy(getmaxx()/2,getmaxy()/4,"THE FOX WON!");
            setcolor(WHITE);
            settextstyle(8, HORIZ_DIR, 5);
            setbkcolor(RED);
            outtextxy(getmaxx()/2, 300, "TRY AGAIN");
            outtextxy(getmaxx()/2, 360, "MAIN MENU");
            outtextxy(getmaxx()/2, 420, "QUIT GAME");
            while(!click)
            {
                if( ismouseclick(WM_LBUTTONDOWN) )
                {
                    x=mousex();
                    y=mousey();
                    clearmouseclick(WM_LBUTTONDOWN);
                    if(x >283 && x<514 && y>270 && y<309)
                    {

                        game.nextMove=2;
                        click=1;

                        closegraph();
                        initwindow(800,800);
                        readMatrix(board);
                        BotStoopid();


                    }
                    if(x >283 && x<514 && y>330 && y<370)
                    {
                        game.nextMove=2;
                        click=1;
                        closegraph();
                        initwindow(800,800);
                        menu();


                    }
                    if(x >283 && x<514 && y>360 && y<430)
                        exit(0);
                }


            }

        }
        if(didTheDogwin(board))
        {
            click=0;
            game.nextMove =0;
            setcolor(GREEN);
            setbkcolor(BLACK);
            settextstyle(10, HORIZ_DIR, 9);
            outtextxy(getmaxx()/2,getmaxy()/4,"THE DOGS WON!");
            setcolor(WHITE);
            settextstyle(8, HORIZ_DIR, 5);
            setbkcolor(GREEN);
            outtextxy(getmaxy()/2, 300, "TRY AGAIN");
            outtextxy(getmaxy()/2, 360, "MAIN MENU");
            outtextxy(getmaxy()/2, 420, "QUIT GAME");
            while(!click)
            {
                if( ismouseclick(WM_LBUTTONDOWN) )
                {
                    x=mousex();
                    y=mousey();
                    clearmouseclick(WM_LBUTTONDOWN);
                    if(x >283 && x<514 && y>270 && y<309)
                    {

                        game.nextMove=2;
                        click=1;
                        closegraph();
                        initwindow(800,800);
                        readMatrix(board);
                        BotStoopid();



                    }
                    if(x >283 && x<514 && y>330 && y<370)
                    {
                        game.nextMove=2;
                        click=1;
                        closegraph();
                        initwindow(800,800);
                        menu();

                    }
                    if(x >283 && x<514 && y>360 && y<430)
                        exit(0);
                }


            }
        }

    }
}


void PlayGame()
{

    int x,y,click=1;
    setbkcolor(DARKGRAY);
    cleardevice();
    game.gametype=1;
    drawBoard(board);
    while(game.nextMove)
    {
        if(game.nextMove==2 )
        {
            moveFox(board);
            game.nextMove=1;
        }
        else if(game.nextMove==1 )
        {
            moveDog(board);
            game.nextMove=2;
        }
        if(didTheFoxWin(board))
        {

            click=0;
            game.nextMove =0;
            setcolor(RED);
            setbkcolor(BLACK);
            settextstyle(10, HORIZ_DIR, 9);
            outtextxy(getmaxx()/2,getmaxy()/4,"THE FOX WON!");
            setcolor(WHITE);
            settextstyle(8, HORIZ_DIR, 5);
            setbkcolor(RED);
            outtextxy(getmaxx()/2, 300, "TRY AGAIN");
            outtextxy(getmaxx()/2, 360, "MAIN MENU");
            outtextxy(getmaxx()/2, 420, "QUIT GAME");
            while(!click)
            {
                if( ismouseclick(WM_LBUTTONDOWN) )
                {
                    x=mousex();
                    y=mousey();
                    clearmouseclick(WM_LBUTTONDOWN);
                    if(x >283 && x<514 && y>270 && y<309)
                    {

                        game.nextMove=2;
                        click=1;
                        closegraph();
                        initwindow(800,800);
                        readMatrix(board);
                        PlayGame();


                    }
                    if(x >283 && x<514 && y>330 && y<370)
                    {
                        game.nextMove=2;
                        click=1;
                        closegraph();
                        initwindow(800,800);
                        menu();


                    }
                    if(x >283 && x<514 && y>360 && y<430)
                        exit(0);
                }


            }
            remove("data.bin");

        }
        if(didTheDogwin(board))
        {
            click=0;
            game.nextMove =0;
            setcolor(GREEN);
            setbkcolor(BLACK);
            settextstyle(10, HORIZ_DIR, 9);
            outtextxy(getmaxx()/2,getmaxy()/4,"THE DOGS WON!");
            setcolor(WHITE);
            settextstyle(8, HORIZ_DIR, 5);
            setbkcolor(GREEN);
            outtextxy(getmaxy()/2, 300, "TRY AGAIN");
            outtextxy(getmaxy()/2, 360, "MAIN MENU");
            outtextxy(getmaxy()/2, 420, "QUIT GAME");
            while(!click)
            {
                if( ismouseclick(WM_LBUTTONDOWN) )
                {
                    x=mousex();
                    y=mousey();
                    clearmouseclick(WM_LBUTTONDOWN);
                    if(x >283 && x<514 && y>270 && y<309)
                    {

                        game.nextMove=2;
                        click=1;
                        closegraph();
                        initwindow(800,800);
                        readMatrix(board);
                        PlayGame();



                    }
                    if(x >283 && x<514 && y>330 && y<370)
                    {
                        game.nextMove=2;
                        click=1;
                        closegraph();
                        initwindow(800,800);
                        menu();

                    }
                    if(x >283 && x<514 && y>360 && y<430)
                        exit(0);
                }


            }
            remove("data.bin");
        }
    }
}
bool moveIsValid (grid board, position moveFrom, position moveTo,int turn )
{
    if( board[moveTo.i][moveTo.j].celltype==0 )  //if the target field is free
    {
        if( turn == 2 && board[moveFrom.i][moveFrom.j].celltype==2 )  //if it's a fox & it's its game.nextMove
        {
            if((moveTo.i == moveFrom.i + 1 && moveTo.j == moveFrom.j + 1) ||
                    (moveTo.i == moveFrom.i + 1 && moveTo.j == moveFrom.j - 1) ||
                    (moveTo.i == moveFrom.i - 1 && moveTo.j == moveFrom.j + 1) ||
                    (moveTo.i == moveFrom.i - 1 && moveTo.j == moveFrom.j - 1) )
                return true;
        }
        else if(turn == 1 && board[moveFrom.i][moveFrom.j].celltype == 1 )     //if it's a dog & it's its game.nextMove
        {
            if( (moveTo.i == moveFrom.i - 1 && moveTo.j == moveFrom.j + 1) ||
                    (moveTo.i == moveFrom.i - 1 && moveTo.j == moveFrom.j - 1) )
                return true;
        }
    }
    return false;
}
bool didTheFoxWin(grid board)
{
    for(int i=0; i<rows; i++)
        if(board[7][i].celltype==2)
        {
            remove("data.bin");
            return true;
        }


    return false;
}

bool didTheDogwin(grid board)
{
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            if(
                (board[i-1][j-1].celltype==1 || i-1<0 || j-1<0)&&
                (board[i-1][j+1].celltype==1 || i-1<0 || j+1>7)&&
                (board[i+1][j-1].celltype==1 || i+1>7 || j-1<0)&&
                (board[i+1][j+1].celltype==1 || i+1>7 || j+1>7)&&
                board[i][j].celltype==2)
            {
                remove("data.bin");
                return true;
            }
    return false;
}



void Options()
{
    int x,y;
    setbkcolor(8);
    cleardevice();
    readimagefile("options.jpg",0,0,800,800);
    settextstyle(1,0,5);
    outtextxy(getmaxx()/2,200,"Alegeti tipul pieselor");
    setcolor(RED);
    settextstyle(1,3,2);
    outtextxy(500,400,"default");
    setcolor(15);
    rectangle(280,350,530,450);
    rectangle(280,450,530,550);
    rectangle(280,550,530,650);
    rectangle(280,650,530,750);

    setfillstyle(SOLID_FILL,GREEN);
    circle(350,400,40);
    floodfill(351,401,15);
    setfillstyle(SOLID_FILL,RED);
    circle(450,400,40);
    floodfill(451,401,15);

    setfillstyle(SOLID_FILL,10);
    rectangle(320,460,380,520);
    floodfill(321,461,15);
    setfillstyle(SOLID_FILL,9);
    rectangle(420,460,480,520);
    floodfill(421,461,15);

    setfillstyle(SOLID_FILL,YELLOW);
    circle(350,600,40);
    floodfill(351,601,15);
    setfillstyle(SOLID_FILL,BLUE);
    circle(450,600,40);
    floodfill(451,601,15);

    setfillstyle(SOLID_FILL,11);
    rectangle(320,660,380,720);
    floodfill(321,671,15);
    setfillstyle(SOLID_FILL,13);
    rectangle(420,660,480,720);
    floodfill(421,661,15);


    while(1)
    {
        if( ismouseclick(WM_LBUTTONDOWN) )
        {
            x=mousex();
            y=mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            if(x >0 && x<123 && y>0 && y<74)
                menu();
            if(x >280 && x<530 && y>350 && y<450)
                game.piecetype=0;
            if(x >280 && x<530 && y>450 && y<550)
                game.piecetype=1;
            if(x >280 && x<530 && y>550 && y<650)
                game.piecetype=2;
            if(x >280 && x<530 && y>650 && y<750)
                game.piecetype=3;

        }
    }
}
void SaveGame()
{
    FILE* data;
    data = fopen("data.bin", "wb+");
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            fwrite(&board[i][j], sizeof(grid), 1, data);
    fwrite(&game,sizeof(game),1,data);

    fclose(data);
}
void LoadGame()
{
    FILE* data;
    if((data = fopen("data.bin", "rb"))==0)
    {
        outtextxy(400,600,"NU EXISTA SALVARI");
        delay(1000);
        ChooseMode();
    }
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            fread(&board[i][j], sizeof(grid), 1, data);
    fread(&game,sizeof(game),1,data);
    fclose(data);
}



void Hard()
{
    int x,y,click=1,i,j,Foxi,Foxj;
    game.gametype=3;



    setbkcolor(DARKGRAY);
    cleardevice();
    drawBoard(board);
    while(game.nextMove)
    {
        if(game.nextMove==2)
          {
               moveFox(board);
               game.nextMove=1;


           }
        if(game.nextMove==1)
        {
            int moveDone=0;

            switch(game.piecetype)
            {
            case 0 :
                setcolor(GREEN);
                break;
            case 2:
                setcolor(YELLOW);
                break;
            }



            while(!moveDone )
            {

                if(game.k<4)   //  Primele 4 mutari ale cainilor valabile pentru orice situatie
                {

                    if(game.k==0)
                    { i=7; j=0;}

                    if(game.k==1)
                        {i=7;j=2;}

                    if(game.k==2)
                       {i=7;j=4;}

                    if(game.k==3)
                       {i=7;j=6;}

                    board[i][j].celltype=0;

                    setcolor(WHITE);
                    setfillstyle(SOLID_FILL, WHITE );
                    circle(board[i][j].x+l/2,board[i][j].y+l/2,l/2-5);
                    floodfill(board[i][j].x+l/2,board[i][j].y+l/2,WHITE);

                    drawDog(board, i-1, j+1);
                    board[i-1][j+1].celltype=1;
                    moveDone=1;



                    game.k++;
                }


                for(i=0; i<8; i++)             //Verifica unde se alfa vulpea
                    for(j=0; j<8; j++)
                        if(board[i][j].celltype==2)
                        {
                            Foxi=i;
                            Foxj=j;
                        }

                        if(Foxi==5 && Foxj==0 && board[6][1].celltype==0)
                            goto victory;




                if(   game.k>4  )               //verifica daca am trecut de primele 4 mutari ale cainilor
                {
                        if(game.LINE==6 && !moveDone)
                            {
                                    if( game.strategy==0 )           //strategia 0 muta cainii astfel incat sa formeze o linie
                                        {

                                                if(game.step==0){i=6;j=7;game.k=7;
                                                    if (Foxi==5 && Foxj==6)
                                                    {game.strategy=1; goto jmp;} }      //daca vulpea se afla pe diagonala stanga sarim la strategia 1

                                                        if(game.step==1)
                                                          {i=6;j=5;game.k=7;}
                                                        if(game.step==2)
                                                            {
                                                                i=6;j=3;game.k=7;
                                                                if (Foxi==5 && Foxj==2)
                                                                    {game.strategy=2; goto jmp2;}
                                                            }

                                                        if(game.step==3)
                                                          {i=6;j=1;game.k=7;}

                                                         if(game.step==4)
                                                          {i=5;j=0;game.k=8;  if(Foxi==4 && Foxj==1)game.step++;
                                                          }
                                                           if(game.step==5)
                                                          {i=5;j=2;game.k=8; if(Foxi==4 && Foxj==3)game.step++;
                                                          }
                                                           if(game.step==6)
                                                          {i=5;j=4;game.k=8; if(Foxi==4 && Foxj==5)game.step++;
                                                          }
                                                          if(game.step==7)
                                                          {i=5;j=6;game.k=8; game.LINE=4;  game.step=-1;
                                                              if(Foxi==4 && Foxj==7)
                                                                {i=4;j=5;}
                                                          }

                                                                   board[i][j].celltype=0;
                                                        if(game.k%2==0)
                                                        {
                                                            moveBotRightDiagonal(i,j);
                                                            board[i-1][j+1].celltype=1;
                                                        }
                                                        else
                                                        {
                                                            moveBotLeftDiagonal(i,j);
                                                            board[i-1][j-1].celltype=1;
                                                        }


                                                                    game.step++;
                                                                    moveDone=1;

                                         }
                                         jmp:

                                    if( game.strategy==1 )
                                        {
                                                if(game.step==0)
                                                        { i=6;j=3;  game.k=8; }
                                                if(game.step==1)
                                                        { i=6;j=7; game.k=7;  }
                                                if(game.step==2)
                                                        { i=5;j=4; game.k=7;  }
                                                if(game.step==3)
                                                        { i=6;j=5; game.k=7;  }
                                                if(game.step==4)
                                                        { i=5;j=4; game.k=8;  }
                                                if(game.step==5)
                                                    if(Foxj==7 && Foxi==4)
                                                        {i=4;j=5;moveBotRightDiagonal(i,j); goto victory2;}
                                                    else
                                                        {i=6;j=1; game.k=8;}

                                                if(game.step==6)
                                                    if(Foxj==7 && Foxi==4)
                                                        { i=4;j=5;  moveBotRightDiagonal(i,j); goto victory2; }
                                                    else
                                                        { i=5;j=2;   game.k=7; }

                                                        if(game.step==7)
                                                        {
                                                            i=5;j=6;   game.k=8;
                                                        if(Foxj==7 && Foxi==4)
                                                            {i=4;j=5;  moveBotRightDiagonal(i,j); goto victory2;}
                                                            game.strategy=0;  game.LINE=4;game.step=-1;
                                                        }

                                                        board[i][j].celltype=0;
                                                    if(game.k%2==0)                                          //daca game.k ul este par , caine trebuie mutat pe diagonala dreapta
                                                        {moveBotRightDiagonal(i,j);
                                                        board[i-1][j+1].celltype=1;}
                                                    else
                                                        {moveBotLeftDiagonal(i,j);         //altfel , trebuie mutat pe diagonala stanga
                                                        board[i-1][j-1].celltype=1;}

                                                        moveDone=1;
                                                        game.step++;
                                        }
                                            jmp2:

                                    if(game.strategy==2)
                                        {
                                                if(game.step==2)
                                                    {i=5;j=6; game.k=7; }
                                                if(game.step==3)
                                                    {i=6;j=3; game.k=7; }
                                                if(game.step==4)
                                                    {i=6;j=1; game.k=7;
                                                    if(Foxi==5&& Foxj==0)
                                                        {i=5;j=2; moveBotLeftDiagonal(i,j);  goto victory2;}
                                                     }
                                                if(game.step==5)
                                                    {i=5;j=0; game.k=8; }
                                                if(game.step==6)
                                                    {i=5;j=2; game.k=8; }
                                                if(game.step==7)
                                                    {i=4;j=5; game.k=8;  }
                                                if(game.step==8)
                                                    {i=5;j=4; game.k=8; game.strategy=0;game.step=0; game.LINE= 4;}



                                                        board[i][j].celltype=0;
                                                        if(game.k%2==0)
                                                        {
                                                            moveBotRightDiagonal(i,j);
                                                            board[i-1][j+1].celltype=1;
                                                        }
                                                        else
                                                        {
                                                            moveBotLeftDiagonal(i,j);
                                                            board[i-1][j-1].celltype=1;
                                                        }

                                                    moveDone=1;
                                                    game.step++;

                                        }
                          }

                    if(game.LINE==4 && !moveDone)
                                {
                                        if( game.strategy==0 )
                                            {

                                        if(game.step==0){i=4;j=7;
                                            if (Foxi==3 && Foxj==6)
                                                {game.strategy=1; goto strategy1;} }

                                                    if(game.step==1)
                                                        {i=4;j=5;}

                                                    if(game.step==2)
                                                        {
                                                        i=4;j=3;
                                                        if (Foxi==3 && Foxj==2)
                                                            {game.strategy=2; game.step=0 ;goto strategy2;}

                                                        }

                                                    if(game.step==3)
                                                    {i=4;j=1; game.LINE=3;game.step=-1; }


                                                        board[i][j].celltype=0;
                                                        moveBotLeftDiagonal(i,j);
                                                        moveDone=1;
                                                        board[i-1][j-1].celltype=1;
                                                        game.step++;

                                                }
                                            strategy1:
                                                  if( game.strategy==1 )
                                                    {
                                                            if(game.step==0)
                                                                    { i=4;j=3;  game.k=8; }
                                                            if(game.step==1)
                                                                    { i=4;j=7; game.k=7;  }
                                                            if(game.step==2)
                                                                    { i=3;j=4; game.k=7;  }
                                                            if(game.step==3)
                                                                    { i=4;j=5; game.k=7;  }
                                                            if(game.step==4)
                                                                    { i=3;j=4; game.k=8;  }
                                                            if(game.step==5)
                                                                if(Foxj==7 && Foxi==2)
                                                                    {i=2;j=5;moveBotRightDiagonal(i,j); goto victory2;}
                                                                else
                                                                    {i=4;j=1; game.k=8;}

                                                            if(game.step==6)
                                                            {
                                                                if(Foxj==7 && Foxi==2)
                                                                    { i=2;j=5;  moveBotRightDiagonal(i,j); goto victory2; }
                                                                else
                                                                    { i=3;j=2;   game.k=7; }
                                                            }

                                                                    if(game.step==7)
                                                                    {
                                                                         i=3;j=6;   game.k=8;
                                                                    if(Foxj==7 && Foxi==2)
                                                                        {i=2;j=5;  moveBotRightDiagonal(i,j); goto victory2;}

                                                                        }




                                                                    if(game.step==8)
                                                                          {
                                                                               if(Foxj==6)
                                                                                { i=2;j=3;game.k=8;}
                                                                            if(Foxj==4)
                                                                                { i=2;j=1;game.k=8;}
                                                                             if(Foxj==2)
                                                                                {i=2;j=5;game.k=7;}
                                                                            if(Foxj==0)
                                                                                 {i=2;j=3;game.k=7;}
                                                                          }

                                                                          if(game.step==9)
                                                                           {  i=2;j=7;game.k=7;  }

                                                                               if(game.step==10)
                                                                          {
                                                                               if(Foxj==4)
                                                                                { i=1;j=2;game.k=8;}
                                                                            if(Foxj==2)
                                                                                { i=2;j=5;game.k=7;}
                                                                             if(Foxj==0)
                                                                                {i=2;j=3;game.k=7;}
                                                                          }

                                                                            if(game.step==11)
                                                                          {i=2;j=5;game.k=7;}

                                                                          if(game.step==12)
                                                                          {
                                                                              if(Foxj==1)
                                                                                {i=2;j=1;game.k=7;}
                                                                                else
                                                                                {i=1;j=2;game.k=7;}
                                                                          }





                                                                    board[i][j].celltype=0;
                                                                if(game.k%2==0)
                                                                    {moveBotRightDiagonal(i,j);
                                                                    board[i-1][j+1].celltype=1;}
                                                                else
                                                                    {moveBotLeftDiagonal(i,j);
                                                                    board[i-1][j-1].celltype=1;}

                                                                    moveDone=1;
                                                                    game.step++;
                                                    }
                                           strategy2:

                                                if(game.strategy==2)
                                                    {
                                                       if(game.step==0)
                                                       {i=3;j=4;game.k=7;}
                                                        if(game.step==1)
                                                       {i=3;j=6;game.k=7;}

                                                       if(game.step==2)
                                                       {i=2;j=5;game.k=7;}
                                                       if(game.step==3)
                                                       {   i=4;j=3;game.k=7;}

                                                       if(game.step==4)
                                                       {i=3;j=2;game.k=7;
                                                       if(Foxi==3 && Foxj==0)
                                                          {moveBotLeftDiagonal(i,j); goto victory2;}
                                                       }
                                                       if(game.step==5)
                                                       {i=2;j=3;game.k=7;}
                                                        if(game.step==6)
                                                       {i=1;j=2;game.k=7;}




                                                                    board[i][j].celltype=0;
                                                                if(game.k%2==0)
                                                                    {moveBotRightDiagonal(i,j);
                                                                    board[i-1][j+1].celltype=1;}
                                                                else
                                                                    {moveBotLeftDiagonal(i,j);
                                                                    board[i-1][j-1].celltype=1;}

                                                                    moveDone=1;
                                                                    game.step++;





                                                    }



                               }

                   if(game.LINE==3 && !moveDone)
                    {
                                        if(game.strategy==0)
                                            {
                                                    if(game.step==0)
                                                    {
                                                        i=3;
                                                        j=0;
                                                    if (Foxi==2 && Foxj==1)
                                                            {
                                                                game.strategy=1;
                                                                goto strategia1;
                                                            }
                                                        }

                                                    if(game.step==1)
                                                        {
                                                            i=3;
                                                            j=2;
                                                        if (Foxi==2 && Foxj==3)
                                                        {game.step=0; game.strategy=2;goto strategia2;}
                                                        }
                                                    if(game.step==2)
                                                            {
                                                                i=3;
                                                                j=4;
                                                    if (Foxi==2 && Foxj==5)
                                                            {
                                                                game.strategy=2;  game.step=0;   goto strategia2;

                                                                }
                                                            }

                                                    if(game.step==3)
                                                        {
                                                            i=3;
                                                            j=6;
                                                            game.LINE=2;game.step=-1;
                                                            if(Foxi==2 && Foxj==7)
                                                            {i=2;j=5; goto victory2;}
                                                        }


                                                board[i][j].celltype=0;
                                                moveBotRightDiagonal(i,j);
                                                board[i-1][j+1].celltype=1;

                                                moveDone=1;
                                                game.step++;
                                            }
                        strategia1:
                                       if(game.strategy==1)
                                               {
                                                if(game.step==0)
                                                        { i=3;j=2;  game.k=8; }
                                                if(game.step==1)
                                                        { i=3;j=4; game.k=8;  }
                                                if(game.step==2)
                                                        { i=3;j=4; game.k=7;
                                                        if(Foxi==2 && Foxj==7)
                                                            {i=2;j=5;moveBotRightDiagonal(i,j);goto victory2;}
                                                         }
                                                if(game.step==3)
                                                        { i=2;j=3; game.k=8;  }
                                                if(game.step==4)
                                                        { i=2;j=5; game.k=8;  }


                                                        board[i][j].celltype=0;
                                                    if(game.k%2==0)
                                                        {moveBotRightDiagonal(i,j);
                                                        board[i-1][j+1].celltype=1;}
                                                    else
                                                        {moveBotLeftDiagonal(i,j);
                                                        board[i-1][j-1].celltype=1;}

                                                        moveDone=1;
                                                        game.step++;



                                               }
                         strategia2:
                                             if(game.strategy==2)
                                             {
                                                 if(game.step==0)
                                                 { i=3;j=6;game.k=7;}
                                                 if(game.step==1)
                                                 {i=3;j=2;game.k=8;}
                                                 if(game.step==2)
                                                 {i=2;j=5;game.k=8;}
                                                 if(game.step==3)
                                                 {i=3;j=4;game.k=8;}
                                                 if(game.step==4)
                                                 {i=2;j=5;game.k=7;}
                                                 if(game.step==5)
                                                 {i=1;j=4;game.k=7;}
                                                 if(game.step==6)
                                                 {i=2;j=3;game.k=7;}
                                                 if(game.step==7)
                                                 {i=1;j=2;game.k=7;goto victory2;}


                                                  board[i][j].celltype=0;
                                                    if(game.k%2==0)
                                                        {moveBotRightDiagonal(i,j);
                                                        board[i-1][j+1].celltype=1;}
                                                    else
                                                        {moveBotLeftDiagonal(i,j);
                                                        board[i-1][j-1].celltype=1;}

                                                        moveDone=1;
                                                        game.step++;



                                            }



                        }

                    if(game.LINE==2 && !moveDone)
                    {
                                  if(game.strategy==0)
                                   {
                                                  if(game.step==0)
                                                        {
                                                            i=2;j=7;game.k=7;
                                                    if(Foxi==1 && Foxj==6)
                                                            { game.strategy=1;goto line2strategy1;}
                                                        }

                                                            if(game.step==1)
                                                              {i=2;j=5;game.k=7;}
                                                         if(game.step==2)
                                                            {
                                                                i=2;j=3;game.k=7;
                                                            if(Foxi==1 && Foxj==2)
                                                               {game.strategy=2; game.step=0; goto line2strategy2;}
                                                            }

                                                         if(game.step==3)
                                                            {i=2;j=1;game.k=7;}

                                                      board[i][j].celltype=0;
                                                    if(game.k%2==0)
                                                        {moveBotRightDiagonal(i,j);
                                                        board[i-1][j+1].celltype=1;}
                                                    else
                                                        {moveBotLeftDiagonal(i,j);
                                                        board[i-1][j-1].celltype=1;}

                                                        moveDone=1;
                                                        game.step++;

                                    }

                        line2strategy1:

                                 if(game.strategy==1)
                                        {
                                            if(game.step==0)
                                            {i=2;j=3;}
                                             if(game.step==1)
                                            {i=2;j=5;}

                                            board[i][j].celltype=0;
                                            moveBotRightDiagonal(i,j);
                                            board[i-1][j+1].celltype=1;

                                            moveDone=1;
                                            game.step++;
                                        }


                             line2strategy2:
                                 if(game.strategy==2)
                                        {
                                            if(game.step==0)
                                            {i=1;j=4;}
                                             if(game.step==1)
                                            {i=2;j=3;}
                                             if(game.step==2)
                                            {i=1;j=2;}

                                            board[i][j].celltype=0;
                                            moveBotLeftDiagonal(i,j);
                                            board[i-1][j-1].celltype=1;

                                            moveDone=1;
                                            game.step++;
                                        }

                    }

                }
            if(game.k==4)game.k++;
            }
              game.nextMove=2;
        }

        if(didTheFoxWin(board))
            {
            victory:
            click=0;
             game.strategy=0;
            game.step=0;
            game.k=0;
            game.nextMove=0;
            game.LINE=6;
            setcolor(RED);
            setbkcolor(BLACK);
            settextstyle(10, HORIZ_DIR, 9);
            outtextxy(getmaxx()/2,getmaxy()/4,"THE FOX WON!");
            setcolor(WHITE);
            settextstyle(8, HORIZ_DIR, 5);
            setbkcolor(RED);
            outtextxy(getmaxx()/2, 300, "TRY AGAIN");
            outtextxy(getmaxx()/2, 360, "MAIN MENU");
            outtextxy(getmaxx()/2, 420, "QUIT GAME");
            while(!click)
            {
                if( ismouseclick(WM_LBUTTONDOWN) )
                {
                    x=mousex();
                    y=mousey();
                    clearmouseclick(WM_LBUTTONDOWN);
                    if(x >283 && x<514 && y>270 && y<309)
                    {

                        game.nextMove=2;
                        click=1;

                        closegraph();
                        initwindow(800,800);
                        readMatrix(board);
                        Hard();


                    }
                    if(x >283 && x<514 && y>330 && y<370)
                    {
                        game.nextMove=2;
                        click=1;
                        closegraph();
                        initwindow(800,800);
                        readMatrix(board);
                        menu();


                    }
                    if(x >283 && x<514 && y>360 && y<430)
                        exit(0);
                }


            }

        }
             if(didTheDogwin(board))
            {
            victory2:
            game.strategy=0;
            game.step=0;
            game.k=0;
            click=0;
            game.LINE=6;
            game.nextMove=0;
            setcolor(GREEN);
            setbkcolor(BLACK);
            settextstyle(10, HORIZ_DIR, 9);
            outtextxy(getmaxx()/2,getmaxy()/4,"THE DOGS WON!");
            setcolor(WHITE);
            settextstyle(8, HORIZ_DIR, 5);
            setbkcolor(GREEN);
            outtextxy(getmaxy()/2, 300, "TRY AGAIN");
            outtextxy(getmaxy()/2, 360, "MAIN MENU");
            outtextxy(getmaxy()/2, 420, "QUIT GAME");
            while(!click)
            {
                if( ismouseclick(WM_LBUTTONDOWN) )
                {
                    x=mousex();
                    y=mousey();
                    clearmouseclick(WM_LBUTTONDOWN);
                    if(x >283 && x<514 && y>270 && y<309)
                    {

                        game.nextMove=2;
                        click=1;
                        closegraph();
                        readMatrix(board);
                        initwindow(800,800);
                        Hard();



                    }
                    if(x >283 && x<514 && y>330 && y<370)
                    {
                        game.nextMove=2;
                        click=1;
                        closegraph();
                        initwindow(800,800);
                        readMatrix(board);
                        menu();

                    }
                    if(x >283 && x<514 && y>360 && y<430)
                        exit(0);
                }


            }
        }

    }

}

void moveBotLeftDiagonal(int i, int j)
{
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE );
    circle(board[i][j].x+l/2,board[i][j].y+l/2,l/2-5);
    floodfill(board[i][j].x+l/2,board[i][j].y+l/2,WHITE);

    drawDog(board, i-1, j-1);

}



void moveBotRightDiagonal( int i, int j)
{
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE );
    circle(board[i][j].x+l/2,board[i][j].y+l/2,l/2-5);
    floodfill(board[i][j].x+l/2,board[i][j].y+l/2,WHITE);

    drawDog(board, i-1, j+1);
}



