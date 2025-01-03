#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

/*宏定义*/

#define Max_Numbers 3//电话数目
#define Max_Emails 2//邮箱数目
#define MAX_CONTACT_LINE_LENGTH 500//读写文件单行长度
#define FONT "font/simkai.ttf"


/*结构体定义*/

typedef struct{
    //名字
    char name[50];
    //电话号码
    int Num_of_numbers;
    char numbers[Max_Numbers][50];
    //邮箱
    int Num_of_emails;
    char emails[Max_Emails][50];
    //备注
    char notes[100];
    //头像图片路径
    char photoPath[100];
}Contact;

typedef struct Node{
    Contact contact;
    struct Node* next;
    struct Node* prev;
}Node;

typedef struct {
    SDL_Rect rect;
    SDL_Color color;
    bool isHovered;
    bool isPressed;
}Button;


/*全局变量*/

char DefaultPhoto[100] = "photos/default.jpg";//默认头像
char User_name[50] = "Admin";//默认用户名
SDL_Window* window;//窗口
SDL_Renderer* renderer;//渲染器
TTF_Font* font;//字体与大小
SDL_Color TextColor = {0,0,0,255 };//字体颜色,默认黑色
Node* head;//联系人列表头节点（用户)
SDL_Rect eraser;//覆盖矩形
int counts = 0;

//注意：这些纹理文件是一些功能的早期设计，部分保留以作纪念
SDL_Texture* welcome_init_texture;//加载页面，当时还没有学会打印文字
SDL_Texture* init_done_texture;//用切换图片的方式来实现擦字重写
SDL_Texture* ani_1_texture;//用3个渐变图层来实现渐变专场
SDL_Texture* ani_2_texture;
SDL_Texture* ani_3_texture;


/*函数声明*/

//创建与删除联系人
Node* CreateNewContact(const char* name);
void DeleteContact(Node* head);
//电话
void AddPhoneNumber(Node* target);
void DeletePhoneNumber(Node* target);
//邮箱
void AddEmail(Node* target);
void DeleteEmail(Node* target);
//备注
void ModifyNotes(Node* target);
//读写文件
int WriteContactsToFile(const char* filename, Node* head);
Node* ReadContactsFromFile(const char* filename);
//排序（由于没有实现中文拼音功能，排序功能废弃）
void quickSort(Node* left, Node* right);
void SortContacts(Node* head);
//链表查找人名
Node* Find(Node* head,char* name);

//功能函数
void SetUser(Node* head);//注册
void DisplayCard(Node* target);//展示名片
void ChangeCard(Node* target);//修改名片
void AddContact(Node* head);//添加联系人
void ChangeContact(Node* head);//修改联系人
void FindContact(Node* head);//查找联系人
void LuckyDog(Node* head);//随机抽出联系人
void Meow();

//自定义的SDL函数
void SDL_PrintPic(SDL_Renderer* renderer,SDL_Texture* picture);
void SDL_Transition(SDL_Renderer* renderer);
void SDL_PrintText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color);
TTF_Font* ChangeFontSize(TTF_Font* font, int newSize);
void SDL_Clean(SDL_Renderer* renderer);
void SDL_Audio(const char* audioFilePath);
int SDL_Sure();
void SDL_KeyChecker();
void SDL_EnterChecker();
void SDL_EscChecker();

//主程序函数
void start();
void home();
void end();


/*Main函数*/
int main(int argc, char* argv[]) {
    // 初始化 SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL2 初始化失败: %s\n", SDL_GetError());
        return -1;
    }
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL2 初始化失败: %s\n", SDL_GetError());
        return -1;
    }
    TTF_Init();

    // 创建窗口和渲染器
    window = SDL_CreateWindow("通讯录", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1200, 700, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("窗口创建失败: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("渲染器创建失败: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    //加载字体文件
    font = TTF_OpenFont(FONT, 24);

    //加载素材文件
    SDL_Surface* welcome_init = SDL_LoadBMP("pictures/welcome_init.bmp");
    SDL_Surface* init_done = SDL_LoadBMP("pictures/init_done.bmp");
    SDL_Surface* ani_1 = SDL_LoadBMP("pictures/ani_1.bmp");
    SDL_Surface* ani_2 = SDL_LoadBMP("pictures/ani_2.bmp");
    SDL_Surface* ani_3 = SDL_LoadBMP("pictures/ani_3.bmp");
    
    welcome_init_texture = SDL_CreateTextureFromSurface(renderer,welcome_init);
    init_done_texture = SDL_CreateTextureFromSurface(renderer,init_done);
    ani_1_texture = SDL_CreateTextureFromSurface(renderer,ani_1);
    ani_2_texture = SDL_CreateTextureFromSurface(renderer,ani_2);
    ani_3_texture = SDL_CreateTextureFromSurface(renderer,ani_3);
    SDL_FreeSurface(welcome_init);
    SDL_FreeSurface(init_done);
    SDL_FreeSurface(ani_1);
    SDL_FreeSurface(ani_2);
    SDL_FreeSurface(ani_3);

    // 初始化随机数生成器
    srand(time(NULL));

    // 主程序
    start();
    home();
    end();
    return 0;
}


/*函数实现*/

Node* CreateNewContact(const char* name){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        // 内存分配失败
        return NULL;
    }
    strcpy(newNode->contact.name, name);
    newNode->contact.Num_of_numbers = 0;
    newNode->contact.Num_of_emails = 0;
    strcpy(newNode->contact.notes,"");
    newNode->next = NULL;
    newNode->prev = NULL;
    strcpy(newNode->contact.photoPath, DefaultPhoto);
    return newNode;
}

void DeleteContact(Node* head){
    SDL_Clean(renderer);
    font = ChangeFontSize(font,50);
    SDL_PrintText(renderer,font,"删除联系人",300,200,TextColor);
    SDL_Delay(200);
    font = ChangeFontSize(font,40);
    SDL_PrintText(renderer,font,"请输入您要删除的联系人姓名，并按回车确认:",300,260,TextColor);

    bool quit = false;
    SDL_Event event;
    char name[50] = "";
    int nameLength = 0;
    Node* target;
    while (!quit) {
        // 处理事件循环
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
                break;
            }
            else if (event.type == SDL_TEXTINPUT) {
                // 获取用户输入的文本
                if (nameLength < 49) {
                    // 将输入的文本附加到用户名字符串中
                    strcat(name, event.text.text);
                    nameLength += strlen(event.text.text);
                
                    // 在屏幕上绘制用户名
                    SDL_PrintText(renderer,font,name,320,310,TextColor);
                }
            }
            else if (event.type == SDL_KEYDOWN) {
                // 检测用户按下的键
                if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
                    // 用户按下回车键，用户名输入完成
                    quit = 1;
                    break;
                }
                else if (event.key.keysym.sym == SDLK_BACKSPACE && nameLength > 0) {
                    // 用户按下退格键，删除最后一个字符
                    name[nameLength-1] = '\0';
                    nameLength--;
                    SDL_SetRenderDrawColor(renderer, 195, 195, 195, 255); //设置绘制颜色为灰色
                    eraser.x = 320;
                    eraser.y = 310;
                    eraser.w = 1380;
                    eraser.h = 50;
                    SDL_RenderFillRect(renderer, &eraser); 
                    SDL_RenderPresent(renderer);
                    SDL_PrintText(renderer,font,name,320,310,TextColor);
                    break;
                }
            }
        }
    }
    //查询递归函数
    SDL_Clean(renderer);
    target = Find(head,name);
    if(!target){
        font = ChangeFontSize(font,60);
        char* sentence = (char*)malloc(100 * sizeof(char));
        strcpy(sentence,"联系人");
        strcat(sentence,name);
        strcat(sentence,"不存在");
        SDL_PrintText(renderer,font,sentence,300,200,TextColor);
        free(sentence);
        font = ChangeFontSize(font,40);
        SDL_PrintText(renderer,font,"请检查联系人姓名是否有误",300,300,TextColor);
        SDL_Delay(3000);
        SDL_Transition(renderer);
        home();
        end();
    }
    else{
        if(!target->prev){
            SDL_Clean(renderer);
            font = ChangeFontSize(font,60);
            SDL_PrintText(renderer,font,"不可删除用户",600,300,TextColor);
            SDL_Delay(2000);
            SDL_Transition(renderer);
            home();
            end();
        }
        else{
            if(SDL_Sure()==0){
                home();
                end();
                return;
            }
            target->prev->next=target->next;
            if (target->next != NULL) {
            target->next->prev = target->prev;
            }
            free(target);
            SDL_Clean(renderer);
            SDL_PrintText(renderer,font,"删除成功！",600,300,TextColor);
            counts--;
            SDL_Delay(2000);
            SDL_Transition(renderer);
            home();
            end();
        }
    }
}

void AddPhoneNumber(Node* target) {
    font = ChangeFontSize(font,50);
    char* sentence = (char*)calloc(100,sizeof(char));
    strcpy(sentence,"为");
    strcat(sentence,target->contact.name);
    strcpy(sentence,"添加一个电话:");
    SDL_PrintText(renderer,font,sentence,300,200,TextColor);
    free(sentence);
    SDL_Delay(500);
    font = ChangeFontSize(font,40);
    SDL_PrintText(renderer,font,"请输入要添加的电话号码，并按回车确认:",300,260,TextColor);

    bool quit = false;
    SDL_Event event;
    char number[50] = "";
    int numberLength = 0;
    while (!quit) {
        // 处理事件循环
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
                break;
            }
            else if (event.type == SDL_TEXTINPUT) {
                // 获取用户输入的文本
                if (numberLength < 49) {
                    // 将输入的文本附加到用户名字符串中
                    strcat(number, event.text.text);
                    numberLength += strlen(event.text.text);
                
                    // 在屏幕上绘制用户名
                    SDL_PrintText(renderer,font,number,320,310,TextColor);
                }
            }
            else if (event.type == SDL_KEYDOWN) {
                // 检测用户按下的键
                if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
                    // 用户按下回车键，用户名输入完成
                    quit = 1;
                    break;
                }
                else if (event.key.keysym.sym == SDLK_BACKSPACE && numberLength > 0) {
                    // 用户按下退格键，删除最后一个字符
                    number[numberLength-1] = '\0';
                    numberLength--;
                    SDL_SetRenderDrawColor(renderer, 195, 195, 195, 255); //设置绘制颜色为灰色
                    eraser.x = 320;
                    eraser.y = 310;
                    eraser.w = 1380;
                    eraser.h = 50;
                    SDL_RenderFillRect(renderer, &eraser); 
                    SDL_RenderPresent(renderer);
                    SDL_PrintText(renderer,font,number,320,310,TextColor);
                    break;
                }
            }
        }
    }

    if (target == NULL) {
        return;
    }
    if (target->contact.Num_of_numbers >= Max_Numbers) {
        printf("电话号码数量已达到上限。\n");
        return;
    }

    strcpy(target->contact.numbers[target->contact.Num_of_numbers],number);
    target->contact.Num_of_numbers++;
    SDL_Clean(renderer);
    font = ChangeFontSize(font,50);
    SDL_PrintText(renderer,font,"添加成功！",500,300,TextColor);
    SDL_Delay(1000);
    SDL_Transition(renderer);
    ChangeCard(target);
    return;
}

void AddEmail(Node* target){
    font = ChangeFontSize(font,50);
    char* sentence = (char*)calloc(100,sizeof(char));
    strcpy(sentence,"为");
    strcat(sentence,target->contact.name);
    strcpy(sentence,"添加一个邮箱:");
    SDL_PrintText(renderer,font,sentence,300,200,TextColor);
    free(sentence);
    SDL_Delay(500);
    font = ChangeFontSize(font,40);
    SDL_PrintText(renderer,font,"请输入要添加的邮箱，并按回车确认:",300,260,TextColor);

    bool quit = false;
    SDL_Event event;
    char email[50] = "";
    int emailLength = 0;
    while (!quit) {
        // 处理事件循环
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
                break;
            }
            else if (event.type == SDL_TEXTINPUT) {
                // 获取用户输入的文本
                if (emailLength < 49) {
                    // 将输入的文本附加到用户名字符串中
                    strcat(email, event.text.text);
                    emailLength += strlen(event.text.text);
                
                    // 在屏幕上绘制用户名
                    SDL_PrintText(renderer,font,email,320,310,TextColor);
                }
            }
            else if (event.type == SDL_KEYDOWN) {
                // 检测用户按下的键
                if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
                    // 用户按下回车键，用户名输入完成
                    quit = 1;
                    break;
                }
                else if (event.key.keysym.sym == SDLK_BACKSPACE && emailLength > 0) {
                    // 用户按下退格键，删除最后一个字符
                    email[emailLength-1] = '\0';
                    emailLength--;
                    SDL_SetRenderDrawColor(renderer, 195, 195, 195, 255); //设置绘制颜色为灰色
                    eraser.x = 320;
                    eraser.y = 310;
                    eraser.w = 1380;
                    eraser.h = 50;
                    SDL_RenderFillRect(renderer, &eraser); 
                    SDL_RenderPresent(renderer);
                    SDL_PrintText(renderer,font,email,320,310,TextColor);
                    break;
                }
            }
        }
    }

    if (target == NULL) {
        return;
    }
    if (target->contact.Num_of_emails >= Max_Emails) {
        printf("邮箱数量已达到上限。\n");
        return;
    }

    strcpy(target->contact.emails[target->contact.Num_of_emails], email);
    target->contact.Num_of_emails++;
    SDL_Clean(renderer);
    font = ChangeFontSize(font,50);
    SDL_PrintText(renderer,font,"添加成功！",500,300,TextColor);
    SDL_Delay(1000);
    SDL_Transition(renderer);
    ChangeCard(target);
    return;
}

void DeletePhoneNumber(Node* target) {
    int index = 0;
    int n = target->contact.Num_of_numbers;
    font = ChangeFontSize(font,50);
    char* sentence = (char*)calloc(100,sizeof(char));
    strcpy(sentence,"删除");
    strcat(sentence,target->contact.name);
    strcat(sentence,"的哪一个电话？");
    SDL_PrintText(renderer,font,sentence,300,200,TextColor);
    free(sentence);
    SDL_Delay(500);
    int y = 250;
    SDL_PrintText(renderer,font,"Number:",350,y,TextColor);
    for(int i=0;i<target->contact.Num_of_numbers;i++){
        SDL_PrintText(renderer,font,target->contact.numbers[i],520,y,TextColor);
        y+=50;
    }
    //按钮部分
    // 初始化按钮
    Button buttons[n];
    int buttonWidth = 50;
    int buttonHeight = 40;
    int startX = 900;
    int startY = 255;
    int spacing = 10;
    for (int i = 0; i < n; i++) {
        buttons[i].rect.x = startX;
        buttons[i].rect.y = startY + i * (buttonHeight + spacing);
        buttons[i].rect.w = buttonWidth;
        buttons[i].rect.h = buttonHeight;
        buttons[i].color = (SDL_Color){255, 255, 255, 255}; // 设置按钮的边框颜色为白色
        buttons[i].isHovered = false;
        buttons[i].isPressed = false;
    }

    bool quit = false;
    SDL_Event event;
    int mouseX,mouseY;
    SDL_Point mousePos;

    while (!quit) {
        // 处理事件循环
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    return;

                case SDL_MOUSEMOTION:
                    mouseX = event.motion.x;
                    mouseY = event.motion.y;
                    mousePos = (SDL_Point){mouseX, mouseY};

                    for (int i = 0; i < n; i++) {
                        if (SDL_PointInRect(&mousePos, &buttons[i].rect)) {
                            buttons[i].color = (SDL_Color){255, 0, 0, 255}; // 鼠标悬停时设置按钮的边框颜色为红色
                            buttons[i].isHovered = true;
                        } else {
                            buttons[i].color = (SDL_Color){255, 255, 255, 255}; // 恢复按钮的初始边框颜色
                            buttons[i].isHovered = false;
                        }
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    mouseX = event.button.x;
                    mouseY = event.button.y;
                    mousePos = (SDL_Point){mouseX, mouseY};

                    for (int i = 0; i < n; i++) {
                        if (SDL_PointInRect(&mousePos, &buttons[i].rect)) {
                            buttons[i].color = (SDL_Color){0, 0, 255, 255}; // 鼠标按下时设置按钮的边框颜色为蓝色
                            buttons[i].isPressed = true;
                            // 执行对应的按钮函数void AddContact(Node* head);
                            if(!SDL_Sure()){
                                DeletePhoneNumber(target);
                                return;
                            }
                            else{
                                index = i;
                                break;
                            }
                        }
                    }
                    quit = true;
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // 渲染按钮边框
        for (int i = 0; i < n; i++) {
            SDL_SetRenderDrawColor(renderer, buttons[i].color.r, buttons[i].color.g, buttons[i].color.b, buttons[i].color.a);
            SDL_RenderDrawRect(renderer, &buttons[i].rect);
        }

        SDL_RenderPresent(renderer);
    }

    if (target == NULL || index < 0 || index >= target->contact.Num_of_numbers) {
        return;  // 无效的参数或索引超出范围
    }
    // 将指定索引后面的电话号码向前移动一个位置
    for (int i = index; i < target->contact.Num_of_numbers - 1; i++) {
        strcpy(target->contact.numbers[i], target->contact.numbers[i + 1]);
    }
    // 清空最后一个电话号码并更新数量
    strcpy(target->contact.numbers[target->contact.Num_of_numbers - 1], "");
    target->contact.Num_of_numbers--;
    
    SDL_Clean(renderer);
    font = ChangeFontSize(font,50);
    SDL_PrintText(renderer,font,"删除成功！",500,300,TextColor);
    SDL_Delay(1000);
    SDL_Transition(renderer);
    ChangeCard(target);
    return;
}

void DeleteEmail(Node* target) {
    int index = 0;
    int n = target->contact.Num_of_emails;
    font = ChangeFontSize(font,50);
    char* sentence = (char*)calloc(100,sizeof(char));
    strcpy(sentence,"删除");
    strcat(sentence,target->contact.name);
    strcat(sentence,"的哪一个邮箱？");
    SDL_PrintText(renderer,font,sentence,300,200,TextColor);
    free(sentence);
    SDL_Delay(500);
    int y = 250;
    SDL_PrintText(renderer,font,"Email:",350,y,TextColor);
    for(int i=0;i<target->contact.Num_of_emails;i++){
        SDL_PrintText(renderer,font,target->contact.emails[i],520,y,TextColor);
        y+=50;
    }
    //按钮部分
    // 初始化按钮
    Button buttons[n];
    int buttonWidth = 50;
    int buttonHeight = 40;
    int startX = 900;
    int startY = 255;
    int spacing = 10;
    for (int i = 0; i < n; i++) {
        buttons[i].rect.x = startX;
        buttons[i].rect.y = startY + i * (buttonHeight + spacing);
        buttons[i].rect.w = buttonWidth;
        buttons[i].rect.h = buttonHeight;
        buttons[i].color = (SDL_Color){255, 255, 255, 255}; // 设置按钮的边框颜色为白色
        buttons[i].isHovered = false;
        buttons[i].isPressed = false;
    }

    bool quit = false;
    SDL_Event event;
    int mouseX,mouseY;
    SDL_Point mousePos;

    while (!quit) {
        // 处理事件循环
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    return;

                case SDL_MOUSEMOTION:
                    mouseX = event.motion.x;
                    mouseY = event.motion.y;
                    mousePos = (SDL_Point){mouseX, mouseY};

                    for (int i = 0; i < n; i++) {
                        if (SDL_PointInRect(&mousePos, &buttons[i].rect)) {
                            buttons[i].color = (SDL_Color){255, 0, 0, 255}; // 鼠标悬停时设置按钮的边框颜色为红色
                            buttons[i].isHovered = true;
                        } else {
                            buttons[i].color = (SDL_Color){255, 255, 255, 255}; // 恢复按钮的初始边框颜色
                            buttons[i].isHovered = false;
                        }
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    mouseX = event.button.x;
                    mouseY = event.button.y;
                    mousePos = (SDL_Point){mouseX, mouseY};

                    for (int i = 0; i < n; i++) {
                        if (SDL_PointInRect(&mousePos, &buttons[i].rect)) {
                            buttons[i].color = (SDL_Color){0, 0, 255, 255}; // 鼠标按下时设置按钮的边框颜色为蓝色
                            buttons[i].isPressed = true;
                            // 执行对应的按钮函数void AddContact(Node* head);
                            if(!SDL_Sure()){
                                DeleteEmail(target);
                                return;
                            }
                            else{
                                index = i;
                                break;
                            }
                        }
                    }
                    quit = true;
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // 渲染按钮边框
        for (int i = 0; i < n; i++) {
            SDL_SetRenderDrawColor(renderer, buttons[i].color.r, buttons[i].color.g, buttons[i].color.b, buttons[i].color.a);
            SDL_RenderDrawRect(renderer, &buttons[i].rect);
        }

        SDL_RenderPresent(renderer);
    }

    if (target == NULL || index < 0 || index >= target->contact.Num_of_emails) {
        return;  // 无效的参数或索引超出范围
    }
    // 将指定索引后面的邮箱向前移动一个位置
    for (int i = index; i < target->contact.Num_of_emails - 1; i++) {
        strcpy(target->contact.emails[i], target->contact.emails[i + 1]);
    }
    // 清空最后一个邮箱并更新数量
    strcpy(target->contact.emails[target->contact.Num_of_emails - 1], "");
    target->contact.Num_of_emails--;
    SDL_Clean(renderer);
    font = ChangeFontSize(font,50);
    SDL_PrintText(renderer,font,"删除成功！",500,300,TextColor);
    SDL_Delay(1000);
    SDL_Transition(renderer);
    ChangeCard(target);
    return;
}

void ModifyNotes(Node* target) {
    char* notes = (char*)calloc(100,sizeof(char));
    strcpy(notes,target->contact.notes);

    font = ChangeFontSize(font,50);
    char* sentence = (char*)calloc(100,sizeof(char));
    strcpy(sentence,"为");
    strcat(sentence,target->contact.name);
    strcpy(sentence,"修改备注:");
    SDL_PrintText(renderer,font,sentence,300,200,TextColor);
    free(sentence);
    SDL_Delay(500);
    font = ChangeFontSize(font,40);
    SDL_PrintText(renderer,font,"请编辑备注，并按回车确认:",300,260,TextColor);
    SDL_Delay(500);
    SDL_PrintText(renderer,font,notes,320,310,TextColor);

    bool quit = false;
    SDL_Event event;
    int notesLength = strlen(notes);
    while (!quit) {
        // 处理事件循环
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
                break;
            }
            else if (event.type == SDL_TEXTINPUT) {
                // 获取用户输入的文本
                if (notesLength < 99) {
                    // 将输入的文本附加到用户名字符串中
                    strcat(notes, event.text.text);
                    notesLength += strlen(event.text.text);
                
                    // 在屏幕上绘制用户名
                    SDL_PrintText(renderer,font,notes,320,310,TextColor);
                }
            }
            else if (event.type == SDL_KEYDOWN) {
                // 检测用户按下的键
                if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
                    // 用户按下回车键，用户名输入完成
                    quit = 1;
                    break;
                }
                else if (event.key.keysym.sym == SDLK_BACKSPACE && notesLength > 0) {
                    // 用户按下退格键，删除最后一个字符
                    notes[notesLength-1] = '\0';
                    notesLength--;
                    SDL_SetRenderDrawColor(renderer, 195, 195, 195, 255); //设置绘制颜色为灰色
                    eraser.x = 320;
                    eraser.y = 310;
                    eraser.w = 1380;
                    eraser.h = 50;
                    SDL_RenderFillRect(renderer, &eraser); 
                    SDL_RenderPresent(renderer);
                    SDL_PrintText(renderer,font,notes,320,310,TextColor);
                    break;
                }
            }
        }
    }

    if (target == NULL) {
        return;
    }

    strcpy(target->contact.notes,notes);
    SDL_Clean(renderer);
    font = ChangeFontSize(font,50);
    SDL_PrintText(renderer,font,"修改成功！",500,300,TextColor);
    SDL_Delay(1000);
    SDL_Transition(renderer);
    ChangeCard(target);
    return;
}

int WriteContactsToFile(const char* filename, Node* head) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件：%s\n", filename);
        return -1;
    }
  
    // 遍历联系人链表，逐个写入文件
    Node* current = head;
    while (current != NULL) {
        fprintf(file, "%s#", current->contact.name);
        
        fprintf(file, "%d#", current->contact.Num_of_numbers);
        for (int i = 0; i < current->contact.Num_of_numbers; i++) {
            fprintf(file, "%s#", current->contact.numbers[i]);
        }

        fprintf(file, "%d#", current->contact.Num_of_emails);
        for (int i = 0; i < current->contact.Num_of_emails; i++) {
            fprintf(file, "%s#", current->contact.emails[i]);
        }
      
        fprintf(file, "%s#", current->contact.notes);
        fprintf(file, "%s", current->contact.photoPath);
        //if(current->next != NULL){
        //    fprintf(file,"\n");
        //}
        current = current->next;
    }
    fclose(file);
    return 1;
}



Node* ReadContactsFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件：%s\n", filename);
        return NULL;
    }
  
    Node* head = NULL;
    Node* tail = NULL;
    char line[256];
    counts = 0;

    // 逐行读取文件内容
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s",line);
        counts++;
        char* token = strtok(line, "#");
        // 创建新的联系人节点,同时填入姓名
        Node* newNode = CreateNewContact(token);
        
        // 读取电话号码数量
        token = strtok(NULL, "#");
        int numNumbers = atoi(token);
        newNode->contact.Num_of_numbers = numNumbers;
        
        // 读取电话号码
        for (int i = 0; i < numNumbers; i++) {
            token = strtok(NULL, "#");
            strcpy(newNode->contact.numbers[i], token);
        }
        
        // 读取电子邮件数量
        token = strtok(NULL, "#");
        int numEmails = atoi(token);
        newNode->contact.Num_of_emails = numEmails;
        
        // 读取电子邮件地址
        for (int i = 0; i < numEmails; i++) {
            token = strtok(NULL, "#");
            strcpy(newNode->contact.emails[i], token);
        }
        
        // 读取备注信息
        token = strtok(NULL, "#");
        if(token){
        strcpy(newNode->contact.notes, token);
        }
        else{
            strcpy(newNode->contact.notes,"");
        }
        
        // 读取头像图片路径
        token = strtok(NULL, "#");
        if(token){
        strcpy(newNode->contact.photoPath, token);
        }
        else{
            strcpy(newNode->contact.photoPath,"");
        }
        
        // 将节点添加到链表中
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    fclose(file);
    return head;
}

// 快速排序递归函数
void quickSort(Node* left, Node* right) {
    if (left == NULL || right == NULL || left == right || left->next == right)
        return;

    Node* i = left;
    Node* j = right;
    char pivot[50];
    strcpy(pivot, left->contact.name);

    while (i != j) {
        while (strcmp(j->contact.name, pivot) >= 0 && i != j)
            j = j->prev;

        while (strcmp(i->contact.name, pivot) <= 0 && i != j)
            i = i->next;

        if (i != j) {
            // 交换节点数据
            Contact temp = i->contact;
            i->contact = j->contact;
            j->contact = temp;
        }
    }

    // 将基准元素归位
    strcpy(left->contact.name, i->contact.name);
    strcpy(i->contact.name, pivot);

    // 递归排序左右两边的子序列
    quickSort(left, i->prev);
    quickSort(i->next, right);
}

// 排序函数
void SortContacts(Node* head) {
    if (head == NULL || head->next == NULL)
        return;

    Node* tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    quickSort(head->next, tail);
}

void SDL_PrintPic(SDL_Renderer* renderer,SDL_Texture* picture){
    //清空渲染器
    SDL_RenderClear(renderer);
    // 将纹理渲染到渲染器上
    SDL_RenderCopy(renderer, picture, NULL, NULL);
    // 刷新渲染器，更新窗口上的内容
    SDL_RenderPresent(renderer);
}//给定渲染器和图片纹理，把图片打印到屏幕上

void SDL_Transition(SDL_Renderer* renderer){
    SDL_PrintPic(renderer,ani_1_texture);
    SDL_Delay(100);
    SDL_PrintPic(renderer,ani_2_texture);
    SDL_Delay(100);
    SDL_PrintPic(renderer,ani_3_texture);
    SDL_Delay(300);
    SDL_PrintPic(renderer,ani_2_texture);
    SDL_Delay(100);
    SDL_PrintPic(renderer,ani_1_texture);
    SDL_Delay(100);
}//给定转场图片和每帧时长，实现255-0-255透明度转场

void start(){
    SDL_PrintPic(renderer,welcome_init_texture);
    head = ReadContactsFromFile("contacts.txt");
    SDL_Delay(1000);
    SDL_PrintPic(renderer,init_done_texture);
    SDL_Delay(1000);
    if(head == NULL){
        SDL_Transition(renderer);
        //注册函数
        SetUser(head);
    }
    else{
        SDL_Transition(renderer);
        //正常进入
        strcpy(User_name,head->contact.name);
    }
    return;
}

void SetUser(Node* head){
    font = ChangeFontSize(font,50);
    SDL_PrintText(renderer,font,"欢迎!请先完成注册",300,200,TextColor);
    SDL_Delay(800);
    font = ChangeFontSize(font,40);
    SDL_PrintText(renderer,font,"请输入您的用户名，并按回车确认:",300,260,TextColor);

    bool quit = false;
    SDL_Event event;
    char username[50] = "";
    int usernameLength = 0;
    while (!quit) {
        // 处理事件循环
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
                break;
            }
            else if (event.type == SDL_TEXTINPUT) {
                // 获取用户输入的文本
                if (usernameLength < 49) {
                    // 将输入的文本附加到用户名字符串中
                    strcat(username, event.text.text);
                    usernameLength += strlen(event.text.text);
                
                    // 在屏幕上绘制用户名
                    SDL_PrintText(renderer,font,username,320,310,TextColor);
                }
            }
            else if (event.type == SDL_KEYDOWN) {
                // 检测用户按下的键
                if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
                    // 用户按下回车键，用户名输入完成
                    quit = 1;
                    break;
                }
                else if (event.key.keysym.sym == SDLK_BACKSPACE && usernameLength > 0) {
                    // 用户按下退格键，删除最后一个字符
                    username[usernameLength-1] = '\0';
                    usernameLength--;
                    SDL_SetRenderDrawColor(renderer, 195, 195, 195, 255); //设置绘制颜色为灰色
                    eraser.x = 320;
                    eraser.y = 310;
                    eraser.w = 1380;
                    eraser.h = 50;
                    SDL_RenderFillRect(renderer, &eraser); 
                    SDL_RenderPresent(renderer);
                    SDL_PrintText(renderer,font,username,320,310,TextColor);
                    break;
                }
            }
        }
    }
    SDL_Clean(renderer);
    head = CreateNewContact(username);
    ChangeFontSize(font,70);
    SDL_PrintText(renderer, font, "欢迎！",380,300,TextColor);
    SDL_PrintText(renderer, font, head->contact.name,580,300,TextColor);
    SDL_Delay(1500);
    counts++;
    SDL_Transition(renderer);
}

void SDL_PrintText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color) {
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect destRect;

    // 创建表面
    surface = TTF_RenderUTF8_Blended(font, text, color);
    if (!surface) {
        printf("Unable to render text surface: %s\n", TTF_GetError());
        return;
    }

    // 创建纹理
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Unable to create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    // 设置绘制目标矩形
    destRect.x = x;
    destRect.y = y;
    destRect.w = surface->w;
    destRect.h = surface->h;

    // 将纹理渲染到指定位置
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    // 刷新渲染器，更新窗口上的内容
    SDL_RenderPresent(renderer);
    // 清除资源
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

TTF_Font* ChangeFontSize(TTF_Font* font, int newSize) {
    TTF_Font* newFont = NULL;
    TTF_CloseFont(font); // 关闭原字体

    // 加载新字体
    newFont = TTF_OpenFont(FONT, newSize);
    if (newFont == NULL) {
        // 处理加载字体失败的情况
        printf("Failed to load font: %s\n", TTF_GetError());
        // 返回NULL或其他适合的错误处理
    }

    return newFont;
}

void SDL_Clean(SDL_Renderer* renderer){
    eraser.h = 2000;
    eraser.w = 2000;
    eraser.x = 0;
    eraser.y = 0;
    SDL_SetRenderDrawColor(renderer, 195, 195, 195, 255); //设置绘制颜色为灰色
    SDL_RenderFillRect(renderer, &eraser); 
    SDL_RenderPresent(renderer);
}

void home() {
    SDL_Clean(renderer);
    font = ChangeFontSize(font, 60);
    SDL_PrintText(renderer, font, "接下来做点什么好捏？", 300, 80, TextColor);
    font = ChangeFontSize(font, 50);
    SDL_PrintText(renderer, font, "我的名片", 300, 180, TextColor);
    SDL_PrintText(renderer, font, "修改我的名片", 300, 240, TextColor);
    SDL_PrintText(renderer, font, "新增联系人", 300, 300, TextColor);
    SDL_PrintText(renderer, font, "修改联系人", 300, 360, TextColor);
    SDL_PrintText(renderer, font, "查找联系人", 300, 420, TextColor);
    SDL_PrintText(renderer, font, "删除联系人", 300, 480, TextColor);
    SDL_PrintText(renderer, font, "造访一位随机幸运联系人！", 300, 540, TextColor);
    SDL_PrintText(renderer, font, "听猫叫", 300, 600, TextColor);

    // 初始化按钮
    Button buttons[8];
    int buttonWidth = 50;
    int buttonHeight = 50;
    int startX = 240;
    int startY = 180;
    int spacing = 10;
    for (int i = 0; i < 8; i++) {
        buttons[i].rect.x = startX;
        buttons[i].rect.y = startY + i * (buttonHeight + spacing);
        buttons[i].rect.w = buttonWidth;
        buttons[i].rect.h = buttonHeight;
        buttons[i].color = (SDL_Color){255, 255, 255, 255}; // 设置按钮的边框颜色为白色
        buttons[i].isHovered = false;
        buttons[i].isPressed = false;
    }

    bool quit = false;
    SDL_Event event;
    int mouseX,mouseY;
    SDL_Point mousePos;

    while (!quit) {
        // 处理事件循环
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    return;

                case SDL_MOUSEMOTION:
                    mouseX = event.motion.x;
                    mouseY = event.motion.y;
                    mousePos = (SDL_Point){mouseX, mouseY};

                    for (int i = 0; i < 8; i++) {
                        if (SDL_PointInRect(&mousePos, &buttons[i].rect)) {
                            buttons[i].color = (SDL_Color){255, 0, 0, 255}; // 鼠标悬停时设置按钮的边框颜色为红色
                            buttons[i].isHovered = true;
                        } else {
                            buttons[i].color = (SDL_Color){255, 255, 255, 255}; // 恢复按钮的初始边框颜色
                            buttons[i].isHovered = false;
                        }
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    mouseX = event.button.x;
                    mouseY = event.button.y;
                    mousePos = (SDL_Point){mouseX, mouseY};

                    for (int i = 0; i < 8; i++) {
                        if (SDL_PointInRect(&mousePos, &buttons[i].rect)) {
                            buttons[i].color = (SDL_Color){0, 0, 255, 255}; // 鼠标按下时设置按钮的边框颜色为蓝色
                            buttons[i].isPressed = true;
                            // 执行对应的按钮函数void AddContact(Node* head);
                            switch (i){
                            case 0:
                                DisplayCard(head);
                                quit = true;
                                return;
                            case 1:
                                ChangeCard(head);
                                quit = true;
                                return;
                            case 2:
                                AddContact(head);
                                quit = true;
                                return;
                                break;
                            case 3:
                                ChangeContact(head);
                                quit = true;
                                return;
                                break;
                            case 4:
                                FindContact(head);
                                quit = true;
                                return;
                                break;
                            case 5:
                                DeleteContact(head);
                                quit = true;
                                return;
                                break;
                            case 6:
                                LuckyDog(head);
                                break;
                            case 7:
                                Meow();
                                break;                                
                            default:
                                break;
                            }
                        }
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // 渲染按钮边框
        for (int i = 0; i < 8; i++) {
            SDL_SetRenderDrawColor(renderer, buttons[i].color.r, buttons[i].color.g, buttons[i].color.b, buttons[i].color.a);
            SDL_RenderDrawRect(renderer, &buttons[i].rect);
        }

        SDL_RenderPresent(renderer);
    }
}

void SDL_Audio(const char* audioFilePath) {
    // 打开音频文件
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8* wavBuffer;
    if (SDL_LoadWAV(audioFilePath, &wavSpec, &wavBuffer, &wavLength) == NULL) {
        printf("Failed to load audio file: %s\n", SDL_GetError());
        return;
    }
    // 设置音频设备参数
    SDL_AudioDeviceID audioDeviceID = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    if (audioDeviceID == 0) {
        printf("Failed to open audio device: %s\n", SDL_GetError());
        SDL_FreeWAV(wavBuffer);
        return;
    }
    // 播放音频
    SDL_QueueAudio(audioDeviceID, wavBuffer, wavLength);
    SDL_PauseAudioDevice(audioDeviceID, 0);
    // 等待音频播放完毕
    while (SDL_GetQueuedAudioSize(audioDeviceID) > 0) {
        SDL_Delay(100);
    }
    // 清理资源
    SDL_CloseAudioDevice(audioDeviceID);
    SDL_FreeWAV(wavBuffer);
}

void Meow(){
    SDL_Audio("meow.wav");
    return;
}

void DisplayCard(Node* target){
    SDL_Clean(renderer);
    int y=100;
    font = ChangeFontSize(font,60);
    SDL_PrintText(renderer,font,target->contact.name,280,y,TextColor);
    y+=100;
    font = ChangeFontSize(font,40);
    SDL_PrintText(renderer,font,"Number:",350,y,TextColor);
    for(int i=0;i<target->contact.Num_of_numbers;i++){
        SDL_PrintText(renderer,font,target->contact.numbers[i],520,y,TextColor);
        y+=50;
    }
    if(!target->contact.Num_of_numbers){
        y+=50;
    }
    y+=20;
    SDL_PrintText(renderer,font,"E-mail:",350,y,TextColor);
    for(int i=0;i<target->contact.Num_of_emails;i++){
        SDL_PrintText(renderer,font,target->contact.emails[i],520,y,TextColor);
        y+=50;
    }
    if(!target->contact.Num_of_emails){
        y+=50;
    }
    y+=20;
    SDL_PrintText(renderer,font,"Notes:",350,y,TextColor);
    SDL_PrintText(renderer,font,target->contact.notes,520,y,TextColor);
    SDL_PrintText(renderer,font,"按任意键返回",900,650,TextColor);
    SDL_KeyChecker();
    SDL_Transition(renderer);
    home();
    end();
    return;   
}

void SDL_KeyChecker(){
    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN) {
                quit = true;
            }
        }
    }
    return;
}

Node* Find(Node* head,char* name){
    if(!head){
        return NULL;
    }
    else if(strcmp(head->contact.name,name)==0){
        return head;
    }
    else{
        return Find(head->next,name);
    }
}

void FindContact(Node* head){
    SDL_Clean(renderer);
    font = ChangeFontSize(font,50);
    SDL_PrintText(renderer,font,"查询联系人",300,200,TextColor);
    SDL_Delay(200);
    font = ChangeFontSize(font,40);
    SDL_PrintText(renderer,font,"请输入您要查找的联系人姓名，并按回车确认:",300,260,TextColor);

    bool quit = false;
    SDL_Event event;
    char name[50] = "";
    int nameLength = 0;
    Node* target;
    while (!quit) {
        // 处理事件循环
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
                break;
            }
            else if (event.type == SDL_TEXTINPUT) {
                // 获取用户输入的文本
                if (nameLength < 49) {
                    // 将输入的文本附加到用户名字符串中
                    strcat(name, event.text.text);
                    nameLength += strlen(event.text.text);
                
                    // 在屏幕上绘制用户名
                    SDL_PrintText(renderer,font,name,320,310,TextColor);
                }
            }
            else if (event.type == SDL_KEYDOWN) {
                // 检测用户按下的键
                if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
                    // 用户按下回车键，用户名输入完成
                    quit = 1;
                    break;
                }
                else if (event.key.keysym.sym == SDLK_BACKSPACE && nameLength > 0) {
                    // 用户按下退格键，删除最后一个字符
                    name[nameLength-1] = '\0';
                    nameLength--;
                    SDL_SetRenderDrawColor(renderer, 195, 195, 195, 255); //设置绘制颜色为灰色
                    eraser.x = 320;
                    eraser.y = 310;
                    eraser.w = 1380;
                    eraser.h = 50;
                    SDL_RenderFillRect(renderer, &eraser); 
                    SDL_RenderPresent(renderer);
                    SDL_PrintText(renderer,font,name,320,310,TextColor);
                    break;
                }
            }
        }
    }
    //查询递归函数
    SDL_Clean(renderer);
    target = Find(head,name);
    if(!target){
        font = ChangeFontSize(font,60);
        char* sentence = (char*)malloc(100 * sizeof(char));
        strcpy(sentence,"联系人");
        strcat(sentence,name);
        strcat(sentence,"不存在");
        SDL_PrintText(renderer,font,sentence,300,200,TextColor);
        free(sentence);
        font = ChangeFontSize(font,40);
        SDL_PrintText(renderer,font,"请先新建此联系人",300,300,TextColor);
        SDL_Delay(3000);
        SDL_Transition(renderer);
        home();
        end();
    }
    else{
        DisplayCard(target);
    }
}

void ChangeCard(Node* target){
    SDL_Clean(renderer);
    int y=100;
    font = ChangeFontSize(font,60);
    SDL_PrintText(renderer,font,target->contact.name,150,y,TextColor);
    y+=100;
    font = ChangeFontSize(font,40);
    SDL_PrintText(renderer,font,"Number:",200,y,TextColor);
    for(int i=0;i<target->contact.Num_of_numbers;i++){
        SDL_PrintText(renderer,font,target->contact.numbers[i],350,y,TextColor);
        y+=50;
    }
    if(!target->contact.Num_of_numbers){
        y+=50;
    }
    y+=20;
    SDL_PrintText(renderer,font,"E-mail:",200,y,TextColor);
    for(int i=0;i<target->contact.Num_of_emails;i++){
        SDL_PrintText(renderer,font,target->contact.emails[i],350,y,TextColor);
        y+=50;
    }
    if(!target->contact.Num_of_emails){
        y+=50;
    }
    y+=20;
    SDL_PrintText(renderer,font,"Notes:",200,y,TextColor);
    SDL_PrintText(renderer,font,target->contact.notes,350,y,TextColor);

    //选择按钮部分
    SDL_PrintText(renderer,font,"添加电话",900,150,TextColor);
    SDL_PrintText(renderer,font,"删除电话",900,230,TextColor);
    SDL_PrintText(renderer,font,"添加邮箱",900,310,TextColor);
    SDL_PrintText(renderer,font,"删除邮箱",900,390,TextColor);
    SDL_PrintText(renderer,font,"修改备注",900,470,TextColor);
    SDL_PrintText(renderer,font,"退出",900,550,TextColor);
    // 初始化按钮
    Button buttons[6];
    int buttonWidth = 50;
    int buttonHeight = 50;
    int startX = 840;
    int startY = 145;
    int spacing = 30;
    for (int i = 0; i < 6; i++) {
        buttons[i].rect.x = startX;
        buttons[i].rect.y = startY + i * (buttonHeight + spacing);
        buttons[i].rect.w = buttonWidth;
        buttons[i].rect.h = buttonHeight;
        buttons[i].color = (SDL_Color){255, 255, 255, 255}; // 设置按钮的边框颜色为白色
        buttons[i].isHovered = false;
        buttons[i].isPressed = false;
    }

    bool quit = false;
    SDL_Event event;
    int mouseX,mouseY;
    SDL_Point mousePos;

    while (!quit) {
        // 处理事件循环
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    return;

                case SDL_MOUSEMOTION:
                    mouseX = event.motion.x;
                    mouseY = event.motion.y;
                    mousePos = (SDL_Point){mouseX, mouseY};

                    for (int i = 0; i < 6; i++) {
                        if (SDL_PointInRect(&mousePos, &buttons[i].rect)) {
                            buttons[i].color = (SDL_Color){255, 0, 0, 255}; // 鼠标悬停时设置按钮的边框颜色为红色
                            buttons[i].isHovered = true;
                        } else {
                            buttons[i].color = (SDL_Color){255, 255, 255, 255}; // 恢复按钮的初始边框颜色
                            buttons[i].isHovered = false;
                        }
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    mouseX = event.button.x;
                    mouseY = event.button.y;
                    mousePos = (SDL_Point){mouseX, mouseY};

                    for (int i = 0; i < 6; i++) {
                        if (SDL_PointInRect(&mousePos, &buttons[i].rect)) {
                            buttons[i].color = (SDL_Color){0, 0, 255, 255}; // 鼠标按下时设置按钮的边框颜色为蓝色
                            buttons[i].isPressed = true;
                            // 执行对应的按钮函数void AddContact(Node* head);
                            switch (i){
                            case 0:
                                SDL_Clean(renderer);
                                if(target->contact.Num_of_numbers<Max_Numbers){
                                    AddPhoneNumber(target);
                                }
                                else{
                                    SDL_PrintText(renderer,font,"添加失败!电话号码数已达到上限",300,300,TextColor);
                                    SDL_Delay(1000);
                                    ChangeCard(target);
                                }
                                return;
                            case 1:
                                SDL_Clean(renderer);
                                if(target->contact.Num_of_numbers>0){
                                    DeletePhoneNumber(target);
                                }
                                else{
                                    SDL_PrintText(renderer,font,"可怜的家伙一个电话也没有QAQ",300,300,TextColor);
                                    SDL_Delay(1000);
                                    ChangeCard(target);
                                }
                                return;
                            case 2:
                                SDL_Clean(renderer);
                                if(target->contact.Num_of_emails<Max_Emails){
                                    AddEmail(target);
                                }
                                else{
                                    SDL_PrintText(renderer,font,"添加失败!邮箱数已达到上限",300,300,TextColor);
                                    SDL_Delay(1000);
                                    ChangeCard(target);
                                }
                                return;
                                break;
                            case 3:
                                SDL_Clean(renderer);
                                if(target->contact.Num_of_emails>0){
                                    DeleteEmail(target);
                                }
                                else{
                                    SDL_PrintText(renderer,font,"可怜的家伙一个邮箱也没有QAQ",300,300,TextColor);
                                    SDL_Delay(1000);
                                    ChangeCard(target);
                                }
                                return;
                                break;
                            case 4:
                                SDL_Clean(renderer);
                                ModifyNotes(target);
                                return;
                                break;     
                            case 5:
                                home();
                                end();
                                return;
                            default:
                                break;
                            }
                        }
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // 渲染按钮边框
        for (int i = 0; i < 6; i++) {
            SDL_SetRenderDrawColor(renderer, buttons[i].color.r, buttons[i].color.g, buttons[i].color.b, buttons[i].color.a);
            SDL_RenderDrawRect(renderer, &buttons[i].rect);
        }

        SDL_RenderPresent(renderer);
    }
    return;   
}

void AddContact(Node* head){
    SDL_Clean(renderer);
    Node* newcontact;
    font = ChangeFontSize(font,50);
    SDL_PrintText(renderer,font,"新建联系人",300,200,TextColor);
    SDL_Delay(500);
    font = ChangeFontSize(font,40);
    SDL_PrintText(renderer,font,"请输入要新建的联系人的姓名，并按回车确认:",300,260,TextColor);

    bool quit = false;
    SDL_Event event;
    char name[50] = "";
    int nameLength = 0;
    while (!quit) {
        // 处理事件循环
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
                break;
            }
            else if (event.type == SDL_TEXTINPUT) {
                // 获取用户输入的文本
                if (nameLength < 49) {
                    // 将输入的文本附加到用户名字符串中
                    strcat(name, event.text.text);
                    nameLength += strlen(event.text.text);
                
                    // 在屏幕上绘制用户名
                    SDL_PrintText(renderer,font,name,320,310,TextColor);
                }
            }
            else if (event.type == SDL_KEYDOWN) {
                // 检测用户按下的键
                if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
                    // 用户按下回车键，用户名输入完成
                    quit = 1;
                    break;
                }
                else if (event.key.keysym.sym == SDLK_BACKSPACE && nameLength > 0) {
                    // 用户按下退格键，删除最后一个字符
                    name[nameLength-1] = '\0';
                    nameLength--;
                    SDL_SetRenderDrawColor(renderer, 195, 195, 195, 255); //设置绘制颜色为灰色
                    eraser.x = 320;
                    eraser.y = 310;
                    eraser.w = 1380;
                    eraser.h = 50;
                    SDL_RenderFillRect(renderer, &eraser); 
                    SDL_RenderPresent(renderer);
                    SDL_PrintText(renderer,font,name,320,310,TextColor);
                    break;
                }
            }
        }
    }
    
    newcontact = CreateNewContact(name);
    if(!head->next){
        head->next=newcontact;
        newcontact->prev=head;
    }
    else{
        newcontact->prev = head;
        newcontact->next = head->next;
        head->next->prev = newcontact;
        head->next = newcontact;
    }
    SDL_Clean(renderer);
    font = ChangeFontSize(font,50);
    SDL_PrintText(renderer,font,"添加成功！",500,300,TextColor);
    counts++;
    SDL_Delay(1000);
    SDL_Transition(renderer);
    ChangeCard(newcontact);
    return;
}

void ChangeContact(Node* head){
    SDL_Clean(renderer);
    font = ChangeFontSize(font,50);
    SDL_PrintText(renderer,font,"修改联系人",300,200,TextColor);
    SDL_Delay(200);
    font = ChangeFontSize(font,40);
    SDL_PrintText(renderer,font,"请输入您要修改的联系人姓名，并按回车确认:",300,260,TextColor);

    bool quit = false;
    SDL_Event event;
    char name[50] = "";
    int nameLength = 0;
    Node* target;
    while (!quit) {
        // 处理事件循环
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
                break;
            }
            else if (event.type == SDL_TEXTINPUT) {
                // 获取用户输入的文本
                if (nameLength < 49) {
                    // 将输入的文本附加到用户名字符串中
                    strcat(name, event.text.text);
                    nameLength += strlen(event.text.text);
                
                    // 在屏幕上绘制用户名
                    SDL_PrintText(renderer,font,name,320,310,TextColor);
                }
            }
            else if (event.type == SDL_KEYDOWN) {
                // 检测用户按下的键
                if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
                    // 用户按下回车键，用户名输入完成
                    quit = 1;
                    break;
                }
                else if (event.key.keysym.sym == SDLK_BACKSPACE && nameLength > 0) {
                    // 用户按下退格键，删除最后一个字符
                    name[nameLength-1] = '\0';
                    nameLength--;
                    SDL_SetRenderDrawColor(renderer, 195, 195, 195, 255); //设置绘制颜色为灰色
                    eraser.x = 320;
                    eraser.y = 310;
                    eraser.w = 1380;
                    eraser.h = 50;
                    SDL_RenderFillRect(renderer, &eraser); 
                    SDL_RenderPresent(renderer);
                    SDL_PrintText(renderer,font,name,320,310,TextColor);
                    break;
                }
            }
        }
    }
    //查询递归函数
    SDL_Clean(renderer);
    target = Find(head,name);
    if(!target){
        font = ChangeFontSize(font,60);
        char* sentence = (char*)malloc(100 * sizeof(char));
        strcpy(sentence,"联系人");
        strcat(sentence,name);
        strcat(sentence,"不存在");
        SDL_PrintText(renderer,font,sentence,300,200,TextColor);
        free(sentence);
        font = ChangeFontSize(font,40);
        SDL_PrintText(renderer,font,"请先新建此联系人",300,300,TextColor);
        SDL_Delay(3000);
        SDL_Transition(renderer);
        home();
        end();
    }
    else{
        ChangeCard(target);
    }
}

void LuckyDog(Node* head){
    int randomNumber = 0 + rand() % (counts - 1 + 1);
    Node* target = head;
    while(randomNumber){
        target = target->next;
        randomNumber--;
    }
    DisplayCard(target);
    return;
}

void SDL_EnterChecker(){
    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
                quit = true;
            }
        }
    }
    return;
}

void SDL_EscChecker(){
    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            
            else if (event.key.keysym.sym == SDLK_ESCAPE){
                quit = true;
            }
        }
    }
    return;
}

void end(){
    WriteContactsToFile("contacts.txt",head);
    // 清理资源
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(0);
}

#include <SDL2/SDL.h>

int SDL_Sure() {
    // 创建窗口
    SDL_Window* window = SDL_CreateWindow("Sure?", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 300, 150, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("无法创建窗口: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // 创建渲染器
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("无法创建渲染器: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // 清空渲染器
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // 创建确定按钮
    SDL_Rect yesButtonRect = {50, 70, 80, 40};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &yesButtonRect);
    font = ChangeFontSize(font,30);
    SDL_PrintText(renderer,font,"确定",60,75,TextColor);

    // 创建取消按钮
    SDL_Rect noButtonRect = {170, 70, 80, 40};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &noButtonRect);
    SDL_PrintText(renderer,font,"取消",180,75,TextColor);

    // 更新渲染器
    SDL_RenderPresent(renderer);
    // 处理事件循环
    int result = -1;  // 默认返回值为异常情况
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            result = 0;  // 用户关闭窗口，返回取消
            break;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX = event.button.x;
            int mouseY = event.button.y;
            if (mouseX >= yesButtonRect.x && mouseX < (yesButtonRect.x + yesButtonRect.w) &&
                mouseY >= yesButtonRect.y && mouseY < (yesButtonRect.y + yesButtonRect.h)) {
                result = 1;  // 用户点击确定按钮，返回确定
                break;
            }
            else if (mouseX >= noButtonRect.x && mouseX < (noButtonRect.x + noButtonRect.w) &&
                     mouseY >= noButtonRect.y && mouseY < (noButtonRect.y + noButtonRect.h)) {
                result = 0;  // 用户点击取消按钮，返回取消
                break;
            }
        }
    }

    // 清理资源
    SDL_DestroyWindow(window);
    return result;
}
