/*************************************
 * 俄罗斯方块
 * 1. 游戏开始界面，显示界面
 * 2. 方块的产生,及判断方块产生的位置是否有方块，有就退出游戏
 * 3. 方块的移动，旋转，左右移动，是否能移动
 * 4. 方块到底，是否满行，产生新的方块
 * @author zhoufei
 * @date 2018-6-24
***************************************/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define UI_WIDTH 14  //显示界面的宽度
#define UI_HEIGHT 25 //界面的高度
#define WALL 1
#define BLOCK 2
#define VK_UP 72 //方向键上下左右的第二个值,方向键有两个值,第一个是224,分别是72,...
#define VK_DOWN 80
#define VK_LEFT 75
#define VK_RIGHT 77
#define TRUE 1
#define FALSE 0
void initia();                              //初始化的一些工作
void gameShow();                            /*游戏显示界面*/
void moveBlock();                           /*方块的移动*/
short isCanMoveBlock(short x, short y);     //是否能移动方块
void produceBlock();                        //产生方块
void toBottom(short x, short y);            //方块到底了之后的操作 ，bottom：底
short cur_block_coord_x, cur_block_coord_y; //当前方块的横坐标及纵坐标
//int game_arr[UI_HEIGHT][UI_WIDTH]; //游戏的界面数组
short next_blockarr[4][4];         //用来存放下一个方块的数组
short cur_boxindex, next_boxindex; //记录当前方块的下标和下一个方块的下标
int score;                         //成绩
char player_name[10] = "你大哥";   //玩家的姓名
HANDLE hOutput;
struct _game_arr
{
    short info; //用来存放游戏界面的数组
    short var;  //用来记录该数组的某个位置是否被占用 ，当方块没有移动了，
                //该位置才被占用，当移动方块是那个地方被占用就不能移动了 ,用1表示占用，0表示未占用
} game_arr[UI_HEIGHT][UI_WIDTH];
struct _block
{
    short a[4][2]; /*定义方块形状的数组，每个方块共有4个小块组成，
	 用4行2列来记录每个小方块的相对 坐标， */
    short next;    //下一个方块的号码
};
struct _block block[19] =
    {
        //初始化各个游戏方块, 总共有19总方块形状
        {1, 1, 1, 2, 1, 3, 2, 3, 1},
        {0, 2, 1, 2, 2, 2, 0, 3, 2},
        {0, 1, 1, 1, 1, 2, 1, 3, 3},
        {2, 1, 0, 2, 1, 2, 2, 2, 0},
        {1, 1, 1, 2, 0, 3, 1, 3, 5},
        {0, 1, 0, 2, 1, 2, 2, 2, 6},
        {1, 1, 2, 1, 1, 2, 1, 3, 7},
        {0, 2, 1, 2, 2, 2, 2, 3, 4},
        {1, 1, 0, 2, 1, 2, 2, 2, 9},
        {1, 1, 1, 2, 2, 2, 1, 3, 10},
        {0, 2, 1, 2, 2, 2, 1, 3, 11},
        {1, 1, 0, 2, 1, 2, 1, 3, 8},
        {1, 1, 1, 2, 2, 2, 2, 3, 13},
        {1, 2, 2, 2, 0, 3, 1, 3, 12},
        {2, 1, 1, 2, 2, 2, 1, 3, 15},
        {0, 2, 1, 2, 1, 3, 2, 3, 14},
        {1, 0, 1, 1, 1, 2, 1, 3, 17},
        {0, 2, 1, 2, 2, 2, 3, 2, 16},
        {1, 1, 2, 1, 1, 2, 2, 2, 18},
};
void main()
{
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTitle(TEXT("俄罗斯方块"));

    SMALL_RECT rc = {0, 0, UI_WIDTH * 2 + 15, UI_HEIGHT + 3}; //设置窗口大小，宽度和高度
    SetConsoleWindowInfo(hOutput, TRUE, &rc);
    srand(time(NULL));
    initia();
    //隐藏缓冲区的光标
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = 0;
    cci.dwSize = 1;
    SetConsoleCursorInfo(hOutput, &cci);

    produceBlock();
    moveBlock();
}
void initia()
{
    //初始化的一些工作
    short i, j;
    for (i = 0; i < UI_HEIGHT; i++)
    {
        for (j = 0; j < UI_WIDTH; j++)
        {
            if (i == 0 || i == UI_HEIGHT - 1)
            {
                game_arr[i][j].info = WALL;
                game_arr[i][j].var = 1;
                continue;
            } //.var=1表示该点被占用
            if (j == 0 || j == UI_WIDTH - 1)
            {
                game_arr[i][j].info = WALL;
                game_arr[i][j].var = 1;
                continue;
            }
        }
    }
    printf("\n\n\t欢迎你的到来\n\t请您输入一个昵称吧!>:");
    scanf("%s", &player_name);
    next_boxindex = rand() % 19; //第一次要随机产生两个方块
}
/*游戏显示界面*/
void gameShow()
{
    //1显示边框，空格，方块
    short i, j;
    system("cls");
    puts("\n\t\t<俄罗斯方块>");
    for (i = 0; i < UI_HEIGHT; i++)
    {
        for (j = 0; j < UI_WIDTH; j++)
        {
            if (game_arr[i][j].info == 0)
            {
                printf("＋");
                continue;
            }
            if (game_arr[i][j].info == WALL)
            {
                if (i == 0 || i == UI_HEIGHT - 1)
                    printf("－"); //画横
                else
                    printf("｜");
                continue;
            }
            if (game_arr[i][j].info == BLOCK)
                printf("▉");
        }
        if (i == 1)
            printf("  下一个方块");
        if (i >= 2 && i <= 5) //下一个方块
        {
            printf("  ");
            for (j = 0; j < 4; j++)
            {
                if (next_blockarr[i - 2][j] == 0)
                    printf("  "); //要减2，因为从i事从2开始的
                else
                    printf("▉");
            }
        }
        if (i == 10)
            printf("  玩家：%s", player_name);
        if (i == 11)
            printf("  得分：%d", score);
        if (i == UI_HEIGHT - 6)
            printf("  操作");
        if (i == UI_HEIGHT - 5)
            printf("  ↑旋转");
        if (i == UI_HEIGHT - 4)
            printf("  ←左移");
        if (i == UI_HEIGHT - 3)
            printf("  →右移");
        if (i == UI_HEIGHT - 2)
            printf("  ↓下移");
        printf("\n");
    }
}
/*每一个方块的产生*/
void produceBlock()
{
    //在游戏界面的中间放置方块
    short i, j;
    cur_boxindex = next_boxindex;
    next_boxindex = rand() % 19;            //方块的编号随机产生
    cur_block_coord_x = (UI_WIDTH - 2) / 2; //从中间落下
    cur_block_coord_y = 1;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            next_blockarr[i][j] = 0; //每次产生新的方块，都要将存放下一个方块的数组清零
    for (i = 0; i < 4; i++)
    {
        game_arr[cur_block_coord_y + block[cur_boxindex].a[i][1]][cur_block_coord_x + block[cur_boxindex].a[i][0]].info = BLOCK;
        next_blockarr[block[next_boxindex].a[i][1]][block[next_boxindex].a[i][0]] = BLOCK;
    }
    if (!isCanMoveBlock(cur_block_coord_x, cur_block_coord_y)) //产生新方块的这个地方被占用了，退出
    {
        printf("游戏结束，再接再厉！");
        getch();
        exit(0);
    }
}
/*方块的移动*/
void moveBlock()
{
    short i, j, to_bottom = FALSE;                              //到底
    short old_x = cur_block_coord_x, old_y = cur_block_coord_y; //用来记录旧的方块的位置
    short old_boxindex = cur_boxindex;                          //记录方块的下标，按上键时改变方块用
    while (1)
    {
        old_x = cur_block_coord_x, old_y = cur_block_coord_y;
        old_boxindex = cur_boxindex;
        while (kbhit()) //用户按键
        {               // getch();
            switch (getch())
            {
            case VK_UP:
                cur_boxindex = block[cur_boxindex].next;
                if (!isCanMoveBlock(cur_block_coord_x, cur_block_coord_y))
                    cur_boxindex = old_boxindex; //如果不能旋转的话要还原
                break;
            case VK_DOWN:
                for (i = 0; i < 4; i++) //一次可以下降4个
                    if (isCanMoveBlock(cur_block_coord_x, cur_block_coord_y + 1))
                        cur_block_coord_y++;
                    else
                    {
                        to_bottom = TRUE;
                        break;
                    } //到底
                break;
            case VK_LEFT:
                if (isCanMoveBlock(cur_block_coord_x - 1, cur_block_coord_y))
                    cur_block_coord_x--;
                break;
            case VK_RIGHT:
                if (isCanMoveBlock(cur_block_coord_x + 1, cur_block_coord_y))
                    cur_block_coord_x++;
                break;
            }
        }
        if (to_bottom)
        {
            if (old_x != cur_block_coord_x || old_y != cur_block_coord_y || old_boxindex != cur_boxindex)
            {
                for (i = 0; i < 4; i++)
                    game_arr[old_y + block[old_boxindex].a[i][1]][old_x + block[old_boxindex].a[i][0]].info = 0;
                for (i = 0; i < 4; i++)
                    game_arr[cur_block_coord_y + block[cur_boxindex].a[i][1]][cur_block_coord_x + block[cur_boxindex].a[i][0]].info = BLOCK;
                gameShow(); //要按键之后才刷新
            }
            to_bottom = FALSE;
            toBottom(cur_block_coord_x, cur_block_coord_y);
            gameShow(); //到底
        }
        else
        {
            if (j++ % 10 == 0) //自动下移,要放前面，
            {
                if (isCanMoveBlock(cur_block_coord_x, cur_block_coord_y + 1))
                    cur_block_coord_y++;
                else
                    to_bottom = TRUE; //到底
            }
            if (old_x != cur_block_coord_x || old_y != cur_block_coord_y || old_boxindex != cur_boxindex)
            {
                for (i = 0; i < 4; i++)
                    game_arr[old_y + block[old_boxindex].a[i][1]][old_x + block[old_boxindex].a[i][0]].info = 0;
                for (i = 0; i < 4; i++)
                    game_arr[cur_block_coord_y + block[cur_boxindex].a[i][1]][cur_block_coord_x + block[cur_boxindex].a[i][0]].info = BLOCK;
                gameShow(); //要按键之后才刷新
            }
        }
        Sleep(20);
    }
}
short isCanMoveBlock(short x, short y)
{
    //是否能移动方块
    short i;
    for (i = 0; i < 4; i++)
        if (game_arr[y + block[cur_boxindex].a[i][1]][x + block[cur_boxindex].a[i][0]].var)
            return FALSE; //如果该位置以及有方块填充，则不能移动
    return TRUE;
}
void toBottom(short x, short y)
{ //方块到底之后的操作，1.将方块的位置的状态变为1，表示被占用。2.是否满块，消行，改变状态 3.产生新的方块
    short i, j;
    for (i = 0; i < 4; i++)
        game_arr[y + block[cur_boxindex].a[i][1]][x + block[cur_boxindex].a[i][0]].var = 1;
    //2.是否满块，消行，改变状态
    for (i = UI_HEIGHT - 2; i >= 1; i--) //有两行是墙 ,从底开始往上搜
    {
        for (j = 1; j <= UI_WIDTH - 2; j++)
        {
            if (!game_arr[i][j].var)
                break;             //一行有空的就跳出这个循环 ，继续搜下一行
            if (j == UI_WIDTH - 2) //一行都满了,消行,此时第i行是满行
            {
                score += 10;
                int h, v;
                for (v = i; v >= 2; v--) //第i行开始,
                {
                    for (h = 1; h <= UI_WIDTH - 2; h++)
                    {
                        game_arr[v][h].info = game_arr[v - 1][h].info;
                        game_arr[v][h].var = game_arr[v - 1][h].var;
                    }
                } //要从底行重新,之后i--,i =  UI_HEIGHT - 2,就会出现多行一起消时有行消不了
                i = UI_HEIGHT - 1;
            }
        }
    }
    produceBlock();
}
