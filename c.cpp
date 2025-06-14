#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <windows.h>

using namespace std;

// 屏幕尺寸
const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

// 颜色枚举
enum class Color {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHTGRAY = 7,
    DARKGRAY = 8,
    LIGHTBLUE = 9,
    LIGHTGREEN = 10,
    LIGHTCYAN = 11,
    LIGHTRED = 12,
    LIGHTMAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};

// 设置控制台文本颜色
void setTextColor(Color color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, static_cast<int>(color));
}

// 清屏函数
void clearScreen() {
    system("cls");
}

// 设置控制台窗口大小
void setConsoleSize(int width, int height) {
    char cmd[50];
    sprintf_s(cmd, "mode con cols=%d lines=%d", width, height);
    system(cmd);
}

// 画板类
class DrawingBoard {
private:
    vector<vector<char>> canvas;  // 画布
    vector<vector<Color>> colors; // 每个位置的颜色
    int cursorX, cursorY;         // 光标位置
    char currentChar;             // 当前绘制字符
    Color currentColor;           // 当前绘制颜色
    bool isDrawing;               // 是否处于绘制状态

public:
    DrawingBoard() : canvas(SCREEN_HEIGHT, vector<char>(SCREEN_WIDTH, ' ')),
                     colors(SCREEN_HEIGHT, vector<Color>(SCREEN_WIDTH, Color::WHITE)),
                     cursorX(0), cursorY(0), currentChar('*'), currentColor(Color::WHITE),
                     isDrawing(false) {}

    // 显示画布
    void display() {
        clearScreen();
        setTextColor(Color::WHITE);
        
        // 绘制顶部边框
        cout << "+";
        for (int i = 0; i < SCREEN_WIDTH; i++) cout << "-";
        cout << "+\n";

        // 绘制画布内容
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            cout << "|";
            for (int x = 0; x < SCREEN_WIDTH; x++) {
                if (x == cursorX && y == cursorY) {
                    setTextColor(Color::YELLOW);
                    cout << (isDrawing ? currentChar : 'O');
                    setTextColor(colors[y][x]);
                } else {
                    setTextColor(colors[y][x]);
                    cout << canvas[y][x];
                }
            }
            cout << "|\n";
        }

        // 绘制底部边框
        cout << "+";
        for (int i = 0; i < SCREEN_WIDTH; i++) cout << "-";
        cout << "+\n";

        // 显示当前状态
        setTextColor(Color::WHITE);
        cout << "当前位置: (" << cursorX << ", " << cursorY << ")";
        cout << "  当前字符: " << currentChar;
        cout << "  当前颜色: " << static_cast<int>(currentColor);
        cout << "  状态: " << (isDrawing ? "绘制中" : "移动中") << "\n";
        cout << "操作提示: WASD移动, 空格切换绘制/移动, C更改字符, L更改颜色, X清除, ESC退出\n";
    }

    // 绘制一个点
    void drawPoint() {
        if (isDrawing) {
            canvas[cursorY][cursorX] = currentChar;
            colors[cursorY][cursorX] = currentColor;
        }
    }

    // 清除画布
    void clearCanvas() {
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            for (int x = 0; x < SCREEN_WIDTH; x++) {
                canvas[y][x] = ' ';
                colors[y][x] = Color::WHITE;
            }
        }
    }

    // 移动光标
    void moveCursor(int dx, int dy) {
        int newX = cursorX + dx;
        int newY = cursorY + dy;

        if (newX >= 0 && newX < SCREEN_WIDTH) cursorX = newX;
        if (newY >= 0 && newY < SCREEN_HEIGHT) cursorY = newY;
        
        drawPoint();
    }

    // 更改当前字符
    void changeChar() {
        setTextColor(Color::WHITE);
        cout << "输入新的绘制字符: ";
        currentChar = _getch();
        cout << currentChar << "\n";
        system("pause");
    }

    // 更改当前颜色
    void changeColor() {
        setTextColor(Color::WHITE);
        cout << "输入新的颜色 (0-15): ";
        int color;
        cin >> color;
        cin.ignore(); // 忽略缓冲区中的换行符
        if (color >= 0 && color <= 15) {
            currentColor = static_cast<Color>(color);
        } else {
            cout << "无效的颜色值!\n";
        }
        system("pause");
    }

    // 切换绘制状态
    void toggleDrawing() {
        isDrawing = !isDrawing;
        drawPoint();
    }

    // 处理用户输入
    bool handleInput() {
        if (_kbhit()) {
            char key = _getch();
            switch (key) {
                case 'w': case 'W': moveCursor(0, -1); break;
                case 's': case 'S': moveCursor(0, 1); break;
                case 'a': case 'A': moveCursor(-1, 0); break;
                case 'd': case 'D': moveCursor(1, 0); break;
                case ' ': toggleDrawing(); break;
                case 'c': case 'C': changeChar(); break;
                case 'l': case 'L': changeColor(); break;
                case 'x': case 'X': clearCanvas(); break;
                case 27: return false; // ESC键退出
            }
        }
        return true;
    }
};

int main() {
    setConsoleSize(SCREEN_WIDTH + 3, SCREEN_HEIGHT + 5);
    DrawingBoard board;
    board.display();

    // 隐藏光标
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hOut, &cursorInfo);

    // 主循环
    while (board.handleInput()) {
        board.display();
        Sleep(50); // 减少CPU使用率
    }

    // 恢复光标
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(hOut, &cursorInfo);

    return 0;
}