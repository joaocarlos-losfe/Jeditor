#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>

//--------------codigo relacionado a entrada sem a necessidade da tecla enter------------------------
static struct termios old, current;
void initTermios(int echo) 
{
    tcgetattr(0, &old);
    current = old;
    current.c_lflag &= ~ICANON; 
    if (echo) 
    {
        current.c_lflag |= ECHO;
    }
    else 
    {  
        current.c_lflag &= ~ECHO;
    }
    tcsetattr(0, TCSANOW, &current);
}

void resetTermios(void) 
{
    tcsetattr(0, TCSANOW, &old);
}

char getch_(int echo) 
{
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

char getch(void) 
{
    return getch_(0);
}
char getche(void) 
{
    return getch_(1);
}
//--------------------------------------

#define lh 49
#define cl 100

void generate_page(char page[lh][cl])
{
    int i=0, j=0;

    for(i=0; i<lh; i++)
    {
        for(j=0; j<cl; j++)
        {
            if(j==0 || j==cl-2)
            {
                page[i][j] = '|';
            }
            else if(i==lh-1)
            {
                page[i][j] = '_';
            }
            else
            {
                page[i][j] = ' ';
            }
        }
        page[i][cl-1] = '\0';
    }
}


int main()
{
    char page[lh][cl], chr = ' ';
    int i=0, j=0;
    int lin=0, col = 1;

    generate_page(page);

    

    while (1)
    {
        
        system("clear");
        printf("\t\t\t\t\t\t-------------------------------------------lin: %d col: %d------------------------------------------\n", lin, col-1);

        for(i=0; i<lh; i++)
        {
            printf("\t\t\t\t\t\t");
            for(j=0; j<cl; j++)
            {
                printf("%c", page[i][j]);
            }
            printf("\n");
        }

        chr = getch();

        if ((int)chr == 10 || col == 98)
        {
            lin++;
            col = 1;
        }
        else
        {
            page[lin][col] = chr;
            col++;
        }
    
    }
    
}