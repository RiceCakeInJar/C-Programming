#include "SDL2/SDL.h"
#include <stdio.h>

/*声明*/
    /*SDL初始化*/
        SDL_Window* screen;//主窗口
        SDL_Renderer* renderer;//渲染器
        SDL_Surface* chess1_surface;
        SDL_Surface* chess2_surface;//两个棋子的表面
        SDL_Texture* chess1_texture;
        SDL_Texture* chess2_texture;//两个棋子的纹理      
    /*棋盘*/
        /*创建的3x3棋盘棋盘上只可能为3个值：0表示空，1和2分别表示玩家1和玩家2的落子*/
        int chessboard[3][3]={{0,0,0},{0,0,0},{0,0,0}};//用二维数组表示棋局情况
        int width=600,height=600;//棋盘的宽、高
        int cellWidth = 200, cellHeight = 200;//子格的尺寸(棋盘尺寸除以3)
        int chessWidth = 180, chessHeight = 180;// 棋子的尺寸
        //SDL_Rect borderRect = { 100, 100, 600, 600 };//棋盘矩形
    /*选中的落子*/
        SDL_Rect Select_Rect = { 100, 100, 200, 200 };//高亮矩形
    /*当前落子的玩家*/
        int player=1;
/*这个函数用于清洗3x3棋盘
清洗是将棋盘全部赋0*/
void ClearChessborad(int chessboard[][3]){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            chessboard[i][j]=0;
        }
    }
}

/*这个函数用于检测棋盘是否全满
返回值是0(未满)或1(已满)*/
int StalemateCheck(int chessboard[][3]){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(chessboard[i][j]==0){
                return 0;
            }
        }
    }
    return 1;
}

/*这个函数用于判定棋盘上是否出现胜方
返回值是0(无赢家)或赢家的序号（1或2）或和棋(3)*/
int WinnerCheck(int chessboard[][3]){
    if(chessboard[0][0]==1 && chessboard[1][1]==1 &&chessboard[2][2]==1){return 1;}
    else if(chessboard[0][0]==2 && chessboard[1][1]==2 && chessboard[2][2]==2){return 2;}
    else if(chessboard[0][2]==1 && chessboard[1][1]==1 && chessboard[2][0]==1){return 1;}
    else if(chessboard[0][2]==2 && chessboard[1][1]==2 && chessboard[2][0]==2){return 2;}
    else if(chessboard[0][0]==1 && chessboard[0][1]==1 && chessboard[0][2]==1){return 1;}
    else if(chessboard[0][0]==2 && chessboard[0][1]==2 && chessboard[0][2]==2){return 2;}
    else if(chessboard[1][0]==1 && chessboard[1][1]==1 && chessboard[1][2]==1){return 1;}
    else if(chessboard[1][0]==2 && chessboard[1][1]==2 && chessboard[1][2]==2){return 2;}
    else if(chessboard[2][0]==1 && chessboard[2][1]==1 && chessboard[2][2]==1){return 1;}
    else if(chessboard[2][0]==2 && chessboard[2][1]==2 && chessboard[2][2]==2){return 2;}
    else if(chessboard[0][0]==1 && chessboard[1][0]==1 && chessboard[2][0]==1){return 1;}
    else if(chessboard[0][0]==2 && chessboard[1][0]==2 && chessboard[2][0]==2){return 2;}
    else if(chessboard[0][1]==1 && chessboard[1][1]==1 && chessboard[2][1]==1){return 1;}
    else if(chessboard[0][1]==2 && chessboard[1][1]==2 && chessboard[2][1]==2){return 2;}
    else if(chessboard[0][2]==1 && chessboard[1][2]==1 && chessboard[2][2]==1){return 1;}
    else if(chessboard[0][2]==2 && chessboard[1][2]==2 && chessboard[2][2]==2){return 2;}
    else{
        if(StalemateCheck(chessboard)){return 3;}
        else{return 0;}
    }
}

/*这个函数用于绘制棋盘图形*/
void drawChessboard(SDL_Renderer* renderer)
{
    // 设置边框颜色为白色
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    // 绘制九宫格
    SDL_Rect lineRect;
    // 绘制竖直线条
    for (int i = 0; i <= 3; i++) {
        lineRect.x = 100 + i * cellWidth - 1;
        lineRect.y = 100;
        lineRect.w = 3;
        lineRect.h = height;
        SDL_RenderFillRect(renderer, &lineRect);
    }
    // 绘制水平线条
    for (int i = 0; i <= 3; i++) {
        lineRect.x = 100;
        lineRect.y = 100 + i * cellHeight - 1;
        lineRect.w = width;
        lineRect.h = 3;
        SDL_RenderFillRect(renderer, &lineRect);
    }
}


/*这个函数用于根据chessboard绘制棋盘上的棋子*/
void drawChessPieces(SDL_Renderer* renderer, int chessboard[][3], SDL_Texture* chess1, SDL_Texture* chess2)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int chessPiece = chessboard[i][j];
            if (chessPiece == 1) {
                // 绘制棋子1
                SDL_Rect chessRect = { 110+200*i, 110+200*j, chessWidth, chessHeight };
                SDL_RenderCopy(renderer, chess1, NULL, &chessRect);
                SDL_RenderPresent(renderer);
            }
            else if (chessPiece == 2) {
                // 绘制棋子2
                SDL_Rect chessRect = { 110+200*i, 110+200*j, chessWidth, chessHeight };
                SDL_RenderCopy(renderer, chess2, NULL, &chessRect);
                SDL_RenderPresent(renderer);
            }
        }
    }
}

/*这个函数用于绘制落子高亮（虚影）*/
void drawChessPiecesSelect(SDL_Renderer* renderer, SDL_Rect* select)
{
    //重新绘制棋盘的白色边框以清除上一个高亮
    drawChessboard(renderer);
    // 设置边框颜色为紫色
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 100);
    // 绘制边框
    SDL_RenderDrawRect(renderer, select);
    // 更新渲染器
    SDL_RenderPresent(renderer);
}

/*这个函数用于尝试一次落子
检查落子位置是否合法-检查落子后是否出现赢家-检查棋盘是否已满
返回值是-1(落子位置不合法)，0(落子成功但无赢家)，1或2(出现赢家1或2)，3(和棋)*/
int Try(int chessboard[][3],int x,int y,int player){
    if(chessboard[x][y]!=0){return -1;}
    else{
        chessboard[x][y]=player;
        drawChessPieces(renderer,chessboard,chess1_texture,chess2_texture);
        return WinnerCheck(chessboard);
    }
}

/*这个函数用于落子
落子后会检查棋局状态，并返回对应的代号值*/
int Move(SDL_Rect* chess_select) {
    int winner = 0;
    SDL_Event event_move;
    int validKey = 0;
    int enter = 0;
    while (!enter) {
        validKey = 0;
        while (SDL_PollEvent(&event_move)) {
            if (event_move.type == SDL_KEYDOWN) {
                switch (event_move.key.keysym.sym) {
                    case SDLK_w:
                        if (chess_select->y > 100) {
                            chess_select->y-=200;
                            validKey = 1;
                        }
                        break;
                    case SDLK_a:
                        if (chess_select->x > 100) {
                            chess_select->x-=200;
                            validKey = 1;
                        }
                        break;
                    case SDLK_s:
                        if (chess_select->y < 500) {
                            chess_select->y+=200;
                            validKey = 1;
                        }
                        break;
                    case SDLK_d:
                        if (chess_select->x < 500) {
                            chess_select->x+=200;
                            validKey = 1;
                        }
                        break;
                    case SDLK_RETURN:
                        enter = 1;
                        switch (player)
                        {
                        case 1:
                            winner=Try(chessboard,((chess_select->x)-100)/200,((chess_select->y)-100)/200,player);
                            player=2;
                            break;
                        case 2:
                            winner=Try(chessboard,((chess_select->x)-100)/200,((chess_select->y)-100)/200 ,player);
                            player=1;
                            break;                           
                        default:
                            break;
                        }
                    default:
                        break;
                }
                if (validKey){
                    drawChessboard(renderer);
                    drawChessPiecesSelect(renderer,&Select_Rect);
                }
                if (enter){
                    return winner;
                }
            }
        }
    }
    return -1;
}

/*这个函数用于结束游戏*/
void EndGame(int winner){
    if (winner == 1) {
        // 绘制赢家1
        SDL_Rect chessRect = { 1000, 300, chessWidth, chessHeight };
        SDL_RenderCopy(renderer, chess1_texture, NULL, &chessRect);
        SDL_RenderPresent(renderer);
    }
    else if (winner == 2) {
        // 绘制棋子2
        SDL_Rect chessRect = { 1000, 300, chessWidth, chessHeight };
        SDL_RenderCopy(renderer, chess2_texture, NULL, &chessRect);
        SDL_RenderPresent(renderer);
    }
    else if (winner == 3) {
        // 绘制平局3
        SDL_Rect chessRect_1 = { 900, 300, chessWidth, chessHeight };
        SDL_RenderCopy(renderer, chess1_texture, NULL, &chessRect_1);
        SDL_RenderPresent(renderer);
        SDL_Rect chessRect_2 = { 1100, 300, chessWidth, chessHeight };
        SDL_RenderCopy(renderer, chess2_texture, NULL, &chessRect_2);
        SDL_RenderPresent(renderer);
    }
    return;
}

/*井字棋游戏的核心部分*/
void StartGame(){
    ClearChessborad(chessboard);//开始游戏前清洗棋盘
    int flag=0;//表示当前棋局状态，初始为0(0-继续;1-1胜出;2-2胜出;3-和棋)
    while(flag==0){
        switch (flag)
        {
        case 0:
            flag=Move(&Select_Rect);
            break;
        case 1:
            flag=1;
            break;
        case 2:
            flag=2;
            break;
        case 3:
            flag=3;
            break;
        }
    }
    EndGame(flag);
}

int main( int argc, char* args[] ){
/*初始化工作*/
    SDL_Init(SDL_INIT_EVERYTHING);
    //启动SDL


    /*打开和屏幕等大的窗口*/
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);
        int win_width = DM.w;
        int win_height = DM.h;
        //获取屏幕分辨率
        screen=SDL_CreateWindow("井字棋", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,DM.w,DM.h-50, SDL_WINDOW_SHOWN);
        //打开窗口
        renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
        //生成窗口的渲染器

    /*加载棋子图片，创建表面和纹理*/
        chess1_surface = SDL_LoadBMP("chess1.bmp");
        chess2_surface = SDL_LoadBMP("chess2.bmp");
        chess1_texture = SDL_CreateTextureFromSurface(renderer, chess1_surface);
        chess2_texture = SDL_CreateTextureFromSurface(renderer, chess2_surface);

    /*给窗口设置底色（卡其色）*/
        SDL_SetRenderDrawColor(renderer, 194, 178, 128, 255);//卡其色
        //绘制背景颜色
        SDL_RenderClear(renderer);
        //清除渲染目标
        SDL_Rect rect = { 0, 0, win_width, win_height-50 };
        SDL_RenderFillRect(renderer, &rect);
        //绘制矩形
        SDL_RenderPresent(renderer);
        //更新渲染器

/*显示文字“按任意键开始游戏”*/
    SDL_Surface* imageSurface = SDL_LoadBMP("start.bmp");
    //加载文字图片
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    //创建纹理
    int imageWidth = imageSurface->w; // 图片的宽度
    int imageHeight = imageSurface->h; // 图片的高度
    int x = (win_width - imageWidth) / 2; // 矩形左上角 x 坐标
    int y = (win_height - imageHeight) / 2; // 矩形左上角 y 坐标
    SDL_Rect imageRect = {x, y, imageWidth, imageHeight};
    //设置图片位置和大小
    SDL_RenderCopy(renderer, texture, NULL, &imageRect);
    //将图片纹理绘制到渲染器
    SDL_RenderPresent(renderer);
    //更新渲染器

/*事件循环*/
    SDL_Event event;
    int isGameStarted = 0; 
    // 游戏是否已经开始
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            break;
        }
        else if (event.type == SDL_KEYDOWN) {
            if (!isGameStarted) {
                // 执行游戏开始的子程序

                isGameStarted = 1;
                //删除“按任意键开始游戏”
                SDL_RenderClear(renderer);
                SDL_RenderPresent(renderer);
                //绘制棋盘
                drawChessboard(renderer);
                SDL_RenderPresent(renderer);
                //test
                StartGame();

            }
            else {
                // 处理其他按键事件
                // ...
            }
        }
    }    

/*清理资源*/
    SDL_DestroyTexture(chess1_texture);
    SDL_DestroyTexture(chess2_texture);
    SDL_FreeSurface(chess1_surface);
    SDL_FreeSurface(chess2_surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    SDL_Quit();

    return 0;
}
