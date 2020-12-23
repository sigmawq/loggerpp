// Tests

#include <iostream>
#define LOGGER_TO_COUT
#include "logger.h"
#include <memory>

int main() {
    logger log { "/home/swql/CLionProjects/logger/logs-server/"};
    log.pushp("A", "B", 35);
    log.push("HELLLL", "I AM SO TIRED");
    return 0;
}
