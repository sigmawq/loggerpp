//
// Created by swql on 12/23/20.
//

#ifndef LOGGER_TESTS_H
#define LOGGER_TESTS_H
#include <iostream>
#include "logger.h"
#include <chrono>
#include <memory>

void t_basic_test(){
    std::string path = "../logs-server/";
    std::string name = "test_log_1.txt";

    logger l1 { path, name };
    l1.push("This is a log ", " message");
    l1.pushp("This is",  "a log message with a label");
}

void t_insert_multiple(){
    std::string path = "../logs-server/";
    std::string name = "test_log_2_insert_multiple.txt";

    logger l1 { path, name };

    auto now = std::chrono::high_resolution_clock::now();
    unsigned long long insertions = 10e5;
    for (auto i = 0; i < insertions; i++){
        l1.push("This is a log ", " message");
    }

    auto then = std::chrono::high_resolution_clock::now();
    std::cout << insertions << " insertions in " <<
              std::chrono::duration_cast<std::chrono::milliseconds>(then - now).count() << "ms" << std::endl;
}

#endif //LOGGER_TESTS_H
