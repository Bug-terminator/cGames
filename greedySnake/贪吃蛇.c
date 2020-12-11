/*
   Author: litang
   Description: 贪吃蛇
   Since: 2020/12/02
          08:25:19
*/

#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define bool char
#define true 1
#define false 0

/*** 光标定位 ***/
HANDLE hout;
COORD coord;

void locate(int x, int y)
{
    coord.X = y;
    coord.Y = x;
    SetConsoleCursorPosition(hout, coord);
};

/*** 隐藏光标 ***/
void hide()
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(hout, &cursor_info);
}

/*** 生成随机数 ***/
double random(double start, double end)
{
    return start + (end - start) * rand() / (RAND_MAX + 1.0);
}

/*** 定义地图的长宽，蛇的坐标，长度，方向，食物的位置 ***/
int m, n;

struct node
{
    int x, y;
} snake[1000];

int snake_length, dir;
struct node food;
int direct[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; //左右上下

/*** 输出墙 ***/
void print_wall()
{
    printf(" ");
    for (int i = 1; i <= n; i++)
        printf("-");
    printf("\n");
    for (int j = 0; j <= m - 1; j++)
    {
        printf("|");
        for (int i = 1; i <= n; i++)
            printf(" ");
        printf("|\n");
    }
    printf(" ");
    for (int i = 1; i <= n; i++)
        printf("-");
}

/*** 首次输出蛇，其中snake[0]代表头 ***/
void print_snake()
{
    locate(snake[0].x, snake[0].y);
    printf("@");
    for (int i = 1; i <= snake_length - 1; i++)
    {
        locate(snake[i].x, snake[i].y);
        printf("*");
    }
}

/*** 判断是否撞墙或者自撞 ***/
bool is_correct()
{
    if (snake[0].x == 0 || snake[0].y == 0 || snake[0].x == m + 1 || snake[0].y == n + 1)
        return false;
    for (int i = 1; i <= snake_length - 1; i++)
    {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
            return false;
    }
    return true;
}

/*** 随机生成并输出食物位置 ***/
bool print_food()
{
    srand((unsigned)time(0));
    bool e;
    //随机生成食物，不能在蛇身体上生成
    while (1)
    {
        e = true;
        int i = (int)random(0, m) + 1, j = (int)random(0, n) + 1;
        food.x = i;
        food.y = j;
        for (int k = 0; k <= snake_length - 1; k++)
        {
            if (snake[k].x == food.x && snake[k].y == food.y)
            {
                e = false;
                break;
            }
        }
        if (e)
            break;
    }
    locate(food.x, food.y);
    printf("$");
    return true;
}

/*** 蛇的前进 ***/
bool go_ahead()
{
    struct node temp;
    bool e = false;
    temp.x  = snake[snake_length - 1].x;
    temp.y  = snake[snake_length - 1].y;
    for (int i = snake_length - 1; i >= 1; i--)
        snake[i] = snake[i - 1];
    snake[0].x += direct[dir][0];
    snake[0].y += direct[dir][1];
    locate(snake[1].x, snake[1].y);
    printf("*");
    /*** 吃到了食物 ***/
    if (snake[0].x == food.x && snake[0].y == food.y)
    {
        snake_length++;
        e = true;
        snake[snake_length - 1].x = temp.x;
        snake[snake_length - 1].y = temp.y;
    }
    /*** 输出此时蛇状态 ***/
    if (!e) //去尾
    {
        locate(temp.x, temp.y);
        printf(" ");
    }
    else
        print_food();
    locate(snake[0].x, snake[0].y);
    printf("@");
    /*** 如果自撞 ***/
    if (!is_correct())
    {
        system("cls");
        printf("You lose!\n");
        printf("Length: %d\n", snake_length);
        return false;
    }
    //输出长度
    locate(m + 2, 12);
    printf("%d", snake_length);
    return true;
}

/*** 主函数 ***/
int main()
{

    printf("--------------------贪吃蛇---------------------\n");
    printf("                 祝你游戏愉快!\n");
    printf("-----------------------------------------------\n");
    Sleep(1000);
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    m = n = 24;//界面尺寸

    int hard;//难度
    hard = 1;

    /*** 数据全部初始化，包括蛇长，位置，方向 ***/
    snake_length = 5;
    char ch;
    double hard_len; //难度随长度改变
    for (int i = 0; i <= 4; i++)
    {
        snake[i].x = 1;
        snake[i].y = 5 - i;
    }
    dir = 3;
    /*** 输出初始地图，蛇与食物 ***/
    system("cls");
    hide();
    print_wall();
    print_food();
    print_snake();
    locate(m + 2, 0);
    /*** 开始游戏 ***/
    while (1)
    {
        /*** 难度随长度增加而提高 ***/
        hard_len = (double)snake_length / (double)(m * n);
        /*** 控制下一次打印的时间，越小打印越快，蛇移动越快，单位是ms ***/
        /*** 接受键盘输入的上下左右，并以此改变方向 ***/
        // 键盘上的按键按下后会有2个字节的数据，低八位存ASCII码，高八位存按键扫描码
        //键盘控制前进，优先级高于自动前进
        while (kbhit())
        {
            ch = getch(); //去除低八位
            ch = getch();
            switch (ch)
            {
            case 72: //上
                if (dir == 2 || dir == 3)
                    dir = 0;
                break;
            case 80: //下
                if (dir == 2 || dir == 3)
                    dir = 1;
                break;
            case 75: //左
                if (dir == 0 || dir == 1)
                    dir = 2;
                break;
            case 77: //右
                if (dir == 0 || dir == 1)
                    dir = 3;
                break;
            }
            /*** 键盘控制前进 ***/
            if (!go_ahead())
                return 0;
        }
        //控制蛇的移动速度，难度相关
        Sleep((int)(400 - 250 * hard) * (1 - sqrt(hard_len)));
        // 自动前进
        if (!go_ahead())
            break;
    }

    return 0;
}