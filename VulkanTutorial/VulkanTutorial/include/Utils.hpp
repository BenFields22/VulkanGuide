#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#ifdef _WIN32
#include <windows.h>
enum Color {
    RED = 12,
    GREEN = 10,
    BLUE = 11,
    YELLOW = 14,
    MAGENTA = 13,
    WHITE = 15
};

class Logger{
private:
    std::string loggerId;
    int loggerFlag;
    int loggerColor;
public:
    Logger(std::string id, int logFlag, int color);
    ~Logger();
    void print(std::string text);
};
#else
enum Color {
    RED = 31,
    GREEN = 32,
    BLUE = 34,
    YELLOW = 33,
    MAGENTA = 35,
    CYAN = 36,
    WHITE=37
    };

class Logger {
private:
    std::string loggerId;
    int loggerFlag;
    std::string loggerColor;
public:
    Logger(std::string id, int logFlag, int color);
    ~Logger();
    void print(std::string text);
};
#endif


class CheckPoint {
private:
    std::vector<std::string> checkPoints;
    int num;
public:
    CheckPoint() {
        num = -1;
    }
    ~CheckPoint() {

    }
    void note(std::string s) {
        num = num + 1;
        checkPoints.push_back(s);
    }

    void dumpLog(int i) {
        std::ofstream myfile;
        myfile.open("AppLog.txt");
        for (int i = 0; i <= num; i++) {
            myfile <<"["<<i<<"]:"<< checkPoints[i] << "\n";
        }
        myfile.close();
        // _WIN32 = we're in windows
        #ifdef _WIN32
        if(i)system("notepad AppLog.txt");
        #else
        if (i)system("open -a TextEdit AppLog.txt");
        #endif
    }

    std::string getLastCheckPoint() {
        return checkPoints[num];
    }
};


#endif // !UTILS_H

