#include <easyx.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <conio.h>
#include <wininet.h>

// 定义地图的大小
#define MAP_WIDTH 62
#define MAP_HEIGHT 42

// 定义像素的大小
#define PIXEL_SIZE 15

// 定义蛇的颜色
#define SNAKE_COLOR GREEN

// 定义颜色
#define BORDER_COLOR WHITE
#define FOOD RED
#define SNAKE_HEAD WHITE

// 定义蛇的移动方向
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4



// 定义蛇头的初始位置
#define SNAKE_HEAD_X 20
#define SNAKE_HEAD_Y 20
using namespace std;

int score = 0;
int speed = 80;

void drewCell(int x, int y, int color);
void delCell(int x, int y);

class food
{
private:
    int x;
    int y;
    friend class snake;
public:
    food()
    {
        srand((unsigned)time(NULL));
        x = rand() % (MAP_WIDTH - 2) + 1;
        y = rand() % (MAP_HEIGHT - 2) + 1;
    }
    void draw()
    {
        drewCell(x, y, FOOD);
    }
    void clear()
    {
        drewCell(x, y, WHITE);
    }
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
    void setX(int x)
    {
        this->x = x;
    }
    void setY(int y)
    {
        this->y = y;
    }

};
class snake
{
private:
    int x;
    int y;
    snake* next;
public:
    snake()
    {
        x = SNAKE_HEAD_X;
        y = SNAKE_HEAD_Y;
        next = NULL;
    }
    void move(int direction, food* f)
    {
        snake* p = new snake;
        p->x = this->x;
        p->y = this->y;
        switch (direction)
        {
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        }
        drewCell(x, y, SNAKE_HEAD);
        //把后面的节点都往前移动一格
        snake* q = this->next;
        while (q != NULL)
        {
            int tempX = q->x;
            int tempY = q->y;
            q->x = p->x;
            q->y = p->y;
            p->x = tempX;
            p->y = tempY;
            q = q->next;
        }
        //判断是否吃到食物
        if (isEatFood(f))
        {
            f->clear();
            do
            {
            f->setX(rand() % 40+ 1);
            f->setY(rand() % 40 + 1);
            }while (f->getX() == this->getX() && f->getY() == this->getY()||(f->getX()>40||f->getX()<=0)||(f->getY()>40||f->getY()<=0));
            f->draw();
            score += 1;
            if (score % 5 == 0)
            {
                speedUp();
            }
            snake* sn = new snake;
            sn->x = p->x;
            sn->y = p->y;
            sn->next = NULL;
            snake* t = this;
            while(t->next!=NULL)
            {
                t = t->next;
            }
            t->next = sn;
        }
        else
        {
            delCell(p->x, p->y);
        }

    }
    bool isEatSelf()
    {
        snake* p = this->next;
        while (p != NULL)
        {
            if (p->x == this->x && p->y == this->y)
            {
                return true;
            }
            p = p->next;
        }
        return false;
    }
    bool isHitWall()
    {
        if (this->x == 0 || this->x == 41 || this->y == 0 || this->y == 41)
        {
            return true;
        }
        return false;
    }
    bool isEatFood(food* f)
    {
        if (this->x == f->x && this->y == f->y)
        {
            return true;
        }
        return false;
    }
    void speedUp()
    {
        if(speed>40)speed -= 10;
    }
    void speedDown()
    {
        if(speed<80)speed += 10;
    }
    int getSpeed()
    {
        return speed;
    }
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
    snake* getNext()
    {
        return next;
    }
    void setX(int x)
    {
        this->x = x;
    }
    void setY(int y)
    {
        this->y = y;
    }
    void setNext(snake* next)
    {
        this->next = next;
    }
};



class map
{
private:
    int width;
    int height;
public:
    map(int w, int h)
    {
        width = w;
        height = h;
    }
    void manu()
    {
        IMAGE image;
        TCHAR imagePath[] = _T("R.png");
        loadimage(&image, imagePath);
        putimage(18.5*PIXEL_SIZE,4*PIXEL_SIZE, &image);
        // settextcolor(0x800000);
        // outtextxy(27*PIXEL_SIZE,10*PIXEL_SIZE,_T("贪        吃        蛇"));
        settextcolor(RED);
        outtextxy(20*PIXEL_SIZE,20*PIXEL_SIZE,_T("1.开始游戏"));
        outtextxy(27*PIXEL_SIZE,20*PIXEL_SIZE,_T("2.游戏说明"));
        outtextxy(34*PIXEL_SIZE,20*PIXEL_SIZE,_T("3.退出游戏"));
        settextcolor(YELLOW);
        outtextxy(27*PIXEL_SIZE,30*PIXEL_SIZE,_T("请按数字键选择"));
        settextcolor(WHITE);
        outtextxy(40*PIXEL_SIZE,35*PIXEL_SIZE,_T("江紫檀 2022141460178"));
        while(true)
        {
            if(GetAsyncKeyState('1') & 0x8000)
            {   
                cleardevice();
                start();
                break;
            }
            if(GetAsyncKeyState('2') & 0x8000)
            {  
                cleardevice();
                explain();
                break;
            }
            if(GetAsyncKeyState('3') & 0x8000)
            {  
                closegraph();
                exit(0);
                break;
            }
        }
    }
    void start()
    {
        setlinecolor(WHITE);
        setlinestyle(PS_SOLID | PS_ENDCAP_FLAT);

        line(1*PIXEL_SIZE, 1*PIXEL_SIZE, 41*PIXEL_SIZE, 1*PIXEL_SIZE);       // 上边界线
        line(1*PIXEL_SIZE, 1*PIXEL_SIZE, 1*PIXEL_SIZE, 41*PIXEL_SIZE);     // 左边界线
        line(1*PIXEL_SIZE, 41*PIXEL_SIZE, 41*PIXEL_SIZE, 41*PIXEL_SIZE); // 下边界线
        line(41*PIXEL_SIZE, 1*PIXEL_SIZE, 41*PIXEL_SIZE, 41*PIXEL_SIZE);   // 右边界线

        outtextxy(45*PIXEL_SIZE,5*PIXEL_SIZE,_T("得分："));
        TCHAR str[10];
        _stprintf_s(str,_T("%d"),score);
        outtextxy(48*PIXEL_SIZE,5*PIXEL_SIZE,str);
        outtextxy(45*PIXEL_SIZE,10*PIXEL_SIZE,_T("每个食物得分：1"));
        outtextxy(45*PIXEL_SIZE,15*PIXEL_SIZE,_T("不能撞墙，不能撞自己！"));
        outtextxy(45*PIXEL_SIZE,20*PIXEL_SIZE,_T("用方向键控制蛇的移动方向！"));
        outtextxy(45*PIXEL_SIZE,25*PIXEL_SIZE,_T("F1键加速，F2键减速！"));
        outtextxy(45*PIXEL_SIZE,30*PIXEL_SIZE,_T("按空格键暂停，按ESC键退出！"));
        // 初始化蛇
        snake* head = new snake;
        snake* p = new snake;
        head->setX(21);
        head->setY(20);
        p->setNext(NULL);
        head->setNext(p);
        food food;
        int direction = RIGHT;
        do
        {
            food.setX(rand() % 40+ 1);
            food.setY(rand() % 40 + 1);
        }while (food.getX() == head->getX() && food.getY() == head->getY()||(food.getX()>40||food.getX()<=0)||(food.getY()>40||food.getY()<=0));
        
        food.draw();
        head->move(direction,&food);
        while(true)
        {
            if(GetAsyncKeyState(VK_UP)&0x8000)
            {
                if(direction != DOWN)
                {
                    direction = UP;
                }
            }
            if(GetAsyncKeyState(VK_DOWN)&0x8000)
            {
                if(direction != UP)
                {
                    direction = DOWN;
                }
            }
            if(GetAsyncKeyState(VK_LEFT)&0x8000)
            {
                if(direction != RIGHT)
                {
                    direction = LEFT;
                }
            }
            if(GetAsyncKeyState(VK_RIGHT)&0x8000)
            {
                if(direction != LEFT)
                {
                    direction = RIGHT;
                }
            }
            if(GetAsyncKeyState(VK_SPACE)&0x8000)
            {
                while(true)
                {
                    if(GetAsyncKeyState(VK_SPACE)&0x8000)
                    {
                        break;
                    }
                    Sleep(50);
                }
            }
            if(GetAsyncKeyState(VK_ESCAPE)&0x8000)
            {
                exit(0);
            }
            if(GetAsyncKeyState(VK_F1)&0x8000)
            {
                head->speedUp();
            }
            if(GetAsyncKeyState(VK_F2)&0x8000)
            {
                head->speedDown();
            }
            if(head->isEatSelf()||head->isHitWall())
            {
                cleardevice();
                endgame();
            }
            head->move(direction,&food);

            //刷新得分
            delCell(48,5);  
            TCHAR str[10];
            _stprintf_s(str,_T("%d"),score);
            outtextxy(48*PIXEL_SIZE,5*PIXEL_SIZE,str);

            //恢复可能被删除的食物
            line(1*PIXEL_SIZE, 1*PIXEL_SIZE, 41*PIXEL_SIZE, 1*PIXEL_SIZE);       // 上边界线
            line(1*PIXEL_SIZE, 1*PIXEL_SIZE, 1*PIXEL_SIZE, 41*PIXEL_SIZE);     // 左边界线
            line(1*PIXEL_SIZE, 41*PIXEL_SIZE, 41*PIXEL_SIZE, 41*PIXEL_SIZE); // 下边界线
            line(41*PIXEL_SIZE, 1*PIXEL_SIZE, 41*PIXEL_SIZE, 41*PIXEL_SIZE);   // 右边界线

            Sleep(speed);
        }
        
        
    }
    void explain()
    {
        outtextxy(27*PIXEL_SIZE,10*PIXEL_SIZE,_T("游戏说明："));
        outtextxy(27*PIXEL_SIZE,15*PIXEL_SIZE,_T("1.不能撞墙，不能撞自己！"));
        outtextxy(27*PIXEL_SIZE,20*PIXEL_SIZE,_T("2.用方向键控制蛇的移动方向！"));
        outtextxy(27*PIXEL_SIZE,25*PIXEL_SIZE,_T("3.F1键加速，F2键减速！"));
        outtextxy(27*PIXEL_SIZE,30*PIXEL_SIZE,_T("4.按空格键暂停，按ESC键退出！"));
        outtextxy(27*PIXEL_SIZE,35*PIXEL_SIZE,_T("5.按空格键返回！"));
        while (true)
        {
            if(GetAsyncKeyState(VK_SPACE) & 0x8000)
            {   
                cleardevice();
                manu();
                break;
            }
        }
    }
    void endgame()
    {
        outtextxy(27*PIXEL_SIZE,10*PIXEL_SIZE,_T("游戏结束！"));
        outtextxy(27*PIXEL_SIZE,20*PIXEL_SIZE,_T("得分："));
        TCHAR str[10];
        _stprintf_s(str,_T("%d"),score);
        outtextxy(30*PIXEL_SIZE,20*PIXEL_SIZE,str);
        outtextxy(27*PIXEL_SIZE,24*PIXEL_SIZE,score);
        outtextxy(27*PIXEL_SIZE,25*PIXEL_SIZE,_T("按ESC键退出！"));
        outtextxy(27*PIXEL_SIZE,30*PIXEL_SIZE,_T("按空格键重新开始！"));
        while (true)
        {
            if(GetAsyncKeyState(VK_SPACE) & 0x8000)
            {   
                score = 0;
                speed = 80;
                cleardevice();
                start();
                break;
            }
            if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            {  
                exit(0);
                break;
            }
        }
        
    }
};



int main()
{
    initgraph(MAP_WIDTH * PIXEL_SIZE, MAP_HEIGHT * PIXEL_SIZE);
    map m(MAP_WIDTH, MAP_HEIGHT);
    m.manu();

    closegraph();
    return 0;
}

void drewCell(int x, int y, int color)
{
    setfillcolor(color);
    fillrectangle(x * PIXEL_SIZE, y * PIXEL_SIZE, (x + 1) * PIXEL_SIZE, (y + 1) * PIXEL_SIZE);

}

void delCell(int x, int y)
{
    setfillcolor(BLACK);
    clearrectangle(x * PIXEL_SIZE, y * PIXEL_SIZE, (x + 1) * PIXEL_SIZE, (y + 1) * PIXEL_SIZE);
}