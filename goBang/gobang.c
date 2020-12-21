
/*
   Author: litang
   Description: gobang
   Since: 2020/12/21
          22:06:29
*/

#include<stdio.h>
#include<windows.h>
 
int main()
{
 
    int i,j;//表示棋盘横纵坐标
    /*************************************************
    *
    *绘制表格需要的字符:┌ ┬ ┐├ ┼ ┤└ ┴ ┘│─●○
    *数组的值0表示黑棋，1表示白棋，2表示该位置没有棋
    *
    */
    int qipan[20][20];
    int color=0;//0表示黑棋(圆圈)，1表示白棋
    int iTemp = 0,jTemp = 0,countTemp = 0;
    int colorFlag = 0;
    char op;
 
again:
 
    for(i=0;i<20;i++)
        for(j=0;j<20;j++)
            qipan[i][j]=2;
 
    while(1)
    {
        printf("请输入棋子位置（棋盘大小为20*20),如2,2: ");
        scanf("%d,%d", &i,&j);
 
        if(i<1 || i >20 || j<1 || j>20)
        {
            printf("输入的位置超出了棋盘的范围，请重新输入！\n");
            continue;
        }
 
        if((2 != qipan[i-1][j-1]))
        {
            printf("提示：该位置已经有棋子了!\n");
            fflush(stdin);
            continue;
        }
 
        color=(color+1)%2;//获取棋盘棋子属性
        qipan[i-1][j-1]=color;//将该位置棋子属性给棋盘
 
        //根据棋盘对应位置属性，绘制最新状态的棋盘，一行行绘制，边缘特别处理
        for(i=1;i<=20;i++)
        {
            //第一行
            if(i==1)
            {
                //第一列
                if(qipan[i-1][0]==1)
                    printf("●");
                if(qipan[i-1][0]==0)
                    printf("○");
                if(qipan[i-1][0]==2)
                    printf("┌ ");
 
                //第2-19列
                for(j=2;j<=19;j++)
                {
                    if(qipan[i-1][j-1]==1)
                        printf("●");
                    if(qipan[i-1][j-1]==0)
                        printf("○");
                    if(qipan[i-1][j-1]==2)
                        printf("┬ ");
                }
 
                //第20列
                if(qipan[i-1][j-1]==1)
                    printf("●");
                if(qipan[i-1][j-1]==0)
                    printf("○");
                if(qipan[i-1][j-1]==2)
                    printf("┐ ");
 
                    printf("\n");
            }
 
            //第2-19行
            if(i<=19 && i>=2)
            {
                //第一列
                if(qipan[i-1][0]==1)
                    printf("●");
                if(qipan[i-1][0]==0)
                    printf("○");
                if(qipan[i-1][0]==2)
                    printf("├ ");
 
                //第2-19列
                for(j=2;j<=19;j++)
                {
                    if(qipan[i-1][j-1]==1)
                        printf("●");
                    if(qipan[i-1][j-1]==0)
                        printf("○");
                    if(qipan[i-1][j-1]==2)
                        printf("┼ ");
                }
 
                //第20列
                if(qipan[i-1][j-1]==1)
                    printf("●");
                if(qipan[i-1][j-1]==0)
                    printf("○");
                if(qipan[i-1][j-1]==2)
                    printf("┤ ");
 
                    printf("\n");
            }
 
            //第20行
            if(i==20)
            {
                if(qipan[i-1][0]==1)
                    printf("●");
                if(qipan[i-1][0]==0)
                    printf("○");
                if(qipan[i-1][0]==2)
                    printf("└ ");
 
                for(j=2;j<=19;j++)
                {
                    if(qipan[i-1][j-1]==1)
                        printf("●");
                    if(qipan[i-1][j-1]==0)
                        printf("○");
                    if(qipan[i-1][j-1]==2)
                        printf("┴ ");
                }
 
                if(qipan[i-1][j-1]==1)
                    printf("●");
                if(qipan[i-1][j-1]==0)
                    printf("○");
                if(qipan[i-1][j-1]==2)
                    printf("┘ ");
 
                    printf("\n");
            }
 
        }
 
        //判断输赢
        for(i=0;i<20;i++)
        {
            for(j=0;j<20;j++)
            {
                //count = 0;
                //如果检测到该有棋子，则检查与该棋子有关的是否可以赢
                if(2 != qipan[i][j] )
                {
                    colorFlag = qipan[i][j];
                    countTemp = 1;
                    iTemp = i;
                    jTemp = j;
 
                    //该棋子横向上是否可以赢
                    while((++jTemp<20 )&&( 5 != countTemp ))
                    {
                        if(colorFlag == qipan[i][jTemp])
                        {
                            countTemp++;
                            if(5 == countTemp)
                            {
                                if(0 == colorFlag)
                                {
                                    printf("黑棋赢了!\n");
                                }
                                else if(1 == colorFlag)
                                {
                                    printf("白棋赢了!\n");
                                }
                                goto whileEnd;
                            }
                        }
                        else
                        {
                            countTemp = 0;
                            break;
                        }
                    }
 
                    //纵向可以赢
                    iTemp = i;
                    jTemp = j;
                    countTemp = 1;
                    while((++iTemp<20 )&&(5 !=countTemp))
                    {
                        if(colorFlag == qipan[iTemp][j])
                        {
                            countTemp++;
                            if(5 == countTemp)
                            {
                                if(0 == colorFlag)
                                {
                                    printf("黑棋赢了!\n");
                                }
                                else if(1 == colorFlag)
                                {
                                    printf("白棋赢了!\n");
                                }
                                goto whileEnd;
                            }
                        }
                        else
                        {
                            countTemp= 0;
                            break;
                        }
 
                    }
 
                    //斜向,从左上到右下方向检查
                    iTemp = i;
                    jTemp = j;
                    countTemp = 1;
                    while((++iTemp<20 )&&(++jTemp<20 )&&(5 !=countTemp))
                    {
                        if(colorFlag == qipan[iTemp][jTemp])
                        {
                            countTemp++;
                            if(5 == countTemp)
                            {
                                if(0 == colorFlag)
                                {
                                    printf("黑棋赢了!\n");
                                }
                                else if(1 == colorFlag)
                                {
                                    printf("白棋赢了!\n");
                                }
                                goto whileEnd;
                            }
                        }
                        else
                        {
                            countTemp = 0;
                            break;
                        }
                    }
 
                    //斜向,从右上到左下方向检查
                    iTemp = i;
                    jTemp = j;
                    countTemp = 1;
                    while((++iTemp>=0 )&&(--jTemp>=0)&&(5 !=countTemp))
                    {
                        if(colorFlag == qipan[iTemp][jTemp])
                        {
                            countTemp++;
                            if(5 == countTemp)
                            {
                                if(0 == colorFlag)
                                {
                                    printf("黑棋赢了!\n");
                                }
                                else if(1 == colorFlag)
                                {
                                    printf("白棋赢了!\n");
                                }
                                goto whileEnd;
                            }
                        }
                        else
                        {
                            countTemp = 0;
                            break;
                        }
                    }
 
                }
 
            }
 
        }
 
    }
whileEnd:
    printf("重新开始，还是退出?重新开始请按y/Y,退出请按任意键:");
    fflush(stdin);
    op = getchar();
 
    if(('y' == op) ||( 'Y' == op))
    {
        system("cls");
        printf("已经重新开始了，请输入第一颗棋子的坐标:\n\n\n");
        goto again;
    }
 
}