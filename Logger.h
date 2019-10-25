//
// Created by dobrikov on 9/24/2019.
//

#ifndef SPISOK_2_LOGGER_H
#define SPISOK_2_LOGGER_H

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <cstring>
#include <mutex>

class Logger {
private:
    std::mutex mutex;
    const char * comment;
public:
    std::ofstream log_file;
    Logger(const char * fname) {
        //std::cerr << "Opening log file." << std::endl;
        //always append to the EOF since we need to save all our logs
        log_file.open(fname, std::ios::app);
    }
    Logger(const char * fname, const char * cmt) {
        comment = cmt;
        //std::cerr << "Opening log file." << std::endl;
        //always append to the EOF since we need to save all our logs
        log_file.open(fname, std::ios::app);
    }
    ~Logger() {
        //std::cerr << "Closing log file." << std::endl;
        log_file.close();
    }
    void print(std::string str) {
        auto current_time = std::chrono::system_clock::now();
        time_t now = std::chrono::system_clock::to_time_t(current_time);
        /*----------костыль для символа новой строки----------*/
        std::string t = std::ctime(&now);
        t [t.std::string::length() - 1]= 0;
        /*----------------------------------------------------*/
        mutex.lock();
        if (log_file.is_open())
        {
            if(comment != NULL)
            {
                //print time with log messages to detect when event happens
                log_file << t << " | " << comment << " | " << str << std::endl;
            }
            else
            {
                //print time with log messages to detect when event happens
                log_file << t << " | " << str << std::endl;
            }
        } else {
            std::cerr <<"Logger doesn't work!" << std::endl;
        }
        mutex.unlock();
    }
};

#endif //SPISOK_2_LOGGER_H
