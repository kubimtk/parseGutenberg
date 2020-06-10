//
// Created by Wolfgang Kubisiak on 09.06.20.
//

#ifndef PARSEGUTENBERG_KKKLOGGER_H
#define PARSEGUTENBERG_KKKLOGGER_H

#include <string>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

//#define Log(logLevel, s) if(loglevel >= 2) { KKKLogger.LogITso(logLevel, s); }

class KKKLogger {
    //the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

    static const int LError = 0;
    static const int LLocalError = 1;
    static const int LWarning = 2;
    static const int LRInfo = 3;
    static const int LInfo = 4;
    static const int LFine = 5;
    static const int LFiner = 6;
    static const int LFinest = 7;


    static void LogITso(int logmode, const std::string& s, std::string colorString="") {
        if(logmode<=LogLevel) {
            auto now = std::chrono::system_clock::now();
            auto in_time_t = std::chrono::system_clock::to_time_t(now);

            std::stringstream ss;
            ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");

            std::string msg = colorString + "KKK: " + ss.str() + " " + s + RESET;
            if(logmode==LError) {
                std::cerr << msg << std::endl;
            } else {
                std::cout << msg << std::endl;
            }
        }
    }

public:
    static int LogLevel;
    static void Error(const std::string& s) { LogITso(LError, "(Error): " + s, RED); }
    static void Warning(const std::string& s) { LogITso(LWarning, "(Warning): " + s, CYAN); }
    static void Info(const std::string& s) { LogITso(LInfo, "(Info): " + s, YELLOW); }
    static void Fine(const std::string& s) { LogITso(LFine, "(Fine): " + s, BLUE); }
};

int KKKLogger::LogLevel=LInfo;

#endif //PARSEGUTENBERG_KKKLOGGER_H
