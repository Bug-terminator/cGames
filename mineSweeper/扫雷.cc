/**********************扫雷*********************/
/*******************2012-11-20******************/
 
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <queue>
using namespace std;
 
struct node
{
    int x,y;
};
 
queue<node> q;
int map[1010][1010],already[1010][1010];
int tempx,tempy,m,n,k,x0,y0,sum,l;
node temp,temp2;
int dir[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
 
bool judge()
{
    if (tempx<0 || tempx>m-1 || tempy<0 || tempy>n-1) return false;
    if (map[tempx][tempy]==-1) return false;
    if (already[tempx][tempy]==0) return false;
    return true;
}
 
void push()
{
    temp2.x=tempx;temp2.y=tempy;
    q.push(temp2);
    already[tempx][tempy]=0;
}
 
bool bfs()
{
    while (!q.empty()) q.pop();
    temp.x=x0;temp.y=y0;
    if (already[x0][y0]==0) return true;
    if (map[x0][y0]==-1) return false;
    q.push(temp);
    already[x0][y0]=0;
    while (!q.empty())
    {
        sum++;
        temp=q.front();
        if (map[temp.x][temp.y]==0)
            for (int i=0;i<=7;i++)
            {
                tempx=temp.x+dir[i][0];
                tempy=temp.y+dir[i][1];
                if (judge())
                    push();
            }
        q.pop();
    }
    return true;
}
 
void print()
{
    cout << "  ";
    for (int i=1;i<=n;i++) cout << i%10;
    cout << endl << "  ";
    for (int i=1;i<=n;i++) cout << "-";
    cout << endl;
    for (int i=0;i<=m-1;i++)
    {
        cout << (i+1)%10 << "|";
        for (int j=0;j<=n-1;j++)
        {
            switch(already[i][j])
            {
            case 0:
                if (map[i][j]==0) cout << " ";
                else
                {
                    if (map[i][j]==-1) cout << "*";
                    else cout << map[i][j];
                }
                break;
            case -1:
                cout << ".";break;
            default:
                cout << "?";
            }
        }
        cout << "|" << endl;
    }
    cout << "  ";
    for (int i=1;i<=n;i++) cout << "-";
    cout << endl;
}
 
double random(double start, double end)
{
    return start+(end-start)*rand()/(RAND_MAX + 1.0);
}
 
int judge2(int i,int j)
{
    if (i<0 || i>m-1 || j<0 || j>n-1) return 0;
    if (map[i][j]==-1) return 1;
    return 0;
}
 
void creat()
{
    srand(time(0));
    int a,b;
    memset(map,0,sizeof(map));
    memset(already,-1,sizeof(already));
    for (int i=1;i<=k;i++)
    {
        while (1)
        {
            a=(int)random(0,m);
            b=(int)random(0,n);
            if (map[a][b]==0)
            {
                map[a][b]=-1;
                break;
            }
        }
    }
    for (int i=0;i<=m-1;i++)
        for (int j=0;j<=n-1;j++)
            if (map[i][j]==0)
                for (int w=0;w<=7;w++)
                    map[i][j]+=judge2(i+dir[w][0],j+dir[w][1]);
}
 
bool del()
{
    system("cls");
    if (!bfs())
    {
        cout << "I'm sorry!" << endl << endl;
        memset(already,0,sizeof(already));
        print();
        return false;
    }
    if (sum!=m*n-k)
        cout << "Good job!" << endl << endl;
    else
    {
        cout << "Congratulations!!" << endl << endl;
        memset(already,0,sizeof(already));
    }
    print();
    return true;
}
 
int main()
{
    cout << "--------------------扫雷--------------------" << endl;
    cout << "一开始输入三个数，分别表示行数，列数以及雷数" << endl;
    cout << "然后请每次输入三个正整数，1 a b或者2 a b" << endl;
    cout << "输入1 a b代表，点击a行b列的格子" << endl;
    cout << "输入2 a b代表，在a行b列上标上旗子(做上标记)" << endl;
    cout << "--------------------------------------------" << endl;
    cin >> m >> n >> k;
    if (k>=m*n)
        cout << "ERROR!" << endl;
    else
    {
        creat();
        system("cls");
        cout << "Map created!" << endl << endl;
        print();
        sum=0;
        while (1)
        {
            if (sum==m*n-k) break;
            cin >> l >> x0 >> y0;
            x0--;y0--;
            if ((l-1)*(l-2)!=0 || x0<0 || x0>m-1 || y0<0 || y0>n-1)
            {
                system("cls");
                cout << "Input ERROR!" << endl << endl;
                print();
            }
            if (l==1)
                if (!del())
                    break;
            if (l==2)
            {
                already[x0][y0]=-already[x0][y0];
                system("cls");
                cout << "Try it!" << endl << endl;
                print();
            }
        }
    }
    system("pause");
    return 0;
}