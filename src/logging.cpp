#include "logging.h"
#include <algorithm>
#include <iostream>

namespace eva02 {

std::string LogLevel::toString(const LogLevel::Level level) {
    switch (level) {
#define XX(level) case level: return #level;
    XX(UNKNOWN);
    XX(DEBUG);
    XX(INFO);
    XX(WARN);
    XX(ERROR);
    XX(FATAL);
#undef XX

    default: 
        return "UNKNOWN";
    }
};


Logger::Logger(const std::string& name, LogLevel::Level level)
    : m_name(name), m_level(level) {
}

void Logger::addAppender(LogAppender::ptr appender) {
    auto it = std::find(m_appenders.begin(), m_appenders.end(), appender);
    if (it == m_appenders.end()) {
        m_appenders.push_back(appender);
    }
}

void Logger::removeAppender(LogAppender::ptr appender) {
    m_appenders.remove(appender);
}

void Logger::clearAppender() {
    m_appenders.clear();
}

void Logger::log(LogLevel::Level level, LogEvent::ptr event) {
    if (level >= m_level) {
        for (auto appender : m_appenders) {
            appender->log(event);
        }
    }
}

void StdOutLogAppender::log(LogEvent::ptr event) {
    std::cout << event->getMessage() << std::endl;
}

}
