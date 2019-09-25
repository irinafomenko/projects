//
// Created by dobrikov on 9/24/2019.
//

#ifndef SPISOK_2_LOGGER_H
#define SPISOK_2_LOGGER_H

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

class Logger {
    std::ofstream log_file;
    Logger(char * fname) {
        std::cerr << "Opening log file." << std::endl;
        //always append to the EOF since we need to save all our logs
        std::ofstream log_file(fname, std::ios::app)
    }
    ~Logger() {
        std::cerr << "Closing log file." << std::endl;
        log_file.close();
    }
public:
    void print(char * str) {
        auto current_time = std::chrono::system_clock::now();
        if (log_file.is_open()) {
            //print time with log messages to detect when event happens
            log_file << std::ctime(&current_time) << " | " << str << std::endl;
        } else {
            std::cerr <<"Logger doesn't work!" << std::endl;
        }
    }
};

#endif //SPISOK_2_LOGGER_H
