#include "src/logging.h"
#include <iostream>

using namespace eva02;

int main() {
    std::cout << LogLevel::toString(LogLevel::UNKNOWN) << std::endl;
    std::cout << LogLevel::toString(LogLevel::DEBUG) << std::endl;
    std::cout << LogLevel::toString(LogLevel::INFO) << std::endl;
    std::cout << LogLevel::toString(LogLevel::WARN) << std::endl;
    std::cout << LogLevel::toString(LogLevel::ERROR) << std::endl;
    std::cout << LogLevel::toString(LogLevel::FATAL) << std::endl;
    std::cout << LogLevel::toString(static_cast<LogLevel::Level>(10)) << std::endl;

    auto logger = std::make_shared<Logger>();
    auto appender = std::make_shared<StdOutLogAppender>();
    logger->addAppender(appender);
    logger->log(LogLevel::INFO, std::make_shared<LogEvent>("hello log"));
    logger->debug(std::make_shared<LogEvent>("hello log"));
    logger->info(std::make_shared<LogEvent>("hello log"));
    return 0;
}
