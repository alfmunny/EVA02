#include "logging.h"
#include <algorithm>
#include <iostream>
#include <sstream>

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
    //std::cout << event->getMessage() << std::endl;
    if (event->getLevel() >= m_level) {
        m_formatter->format(std::cout, event);
    }
}

class TimeItem : public LogFormatter::Item 
{
public:
    TimeItem(const std::string& fmt) : m_fmt(fmt) {
    } 
    void format(std::ostream& ss, LogEvent::ptr event) override {
        struct tm time;
        char buf[64];
        time_t t = event->getTime();
        localtime_r(&t, &time);
        strftime(buf, sizeof(buf), m_fmt.c_str(), &time);
        ss << buf;
    }

private:
    const std::string m_fmt;
};

class FileItem : public LogFormatter::Item 
{
public:
    FileItem(const std::string& fmt) : m_fmt(fmt) {}

    void format(std::ostream& ss, LogEvent::ptr event) override {
        auto depth = atoi(m_fmt.c_str());
        auto* it = event->getFile();
        for (; *it != '\n' && depth > 0; it++) {
            if (*it == '/')
                depth--;
        }
        ss << it;
    }

private:
    const std::string m_fmt;
};

class StringItem : public LogFormatter::Item 
{
public:
    StringItem(const std::string& str) : m_s(str) {}

    void format(std::ostream& ss, LogEvent::ptr) override {
        ss << m_s;
    }

private:
    const std::string m_s;
};

class LineItem : public LogFormatter::Item 
{
public:
    LineItem(const std::string& str) : m_s(str) {}

    void format(std::ostream& ss, LogEvent::ptr event) override {
        ss << event->getLine();
    }
private:
    const std::string m_s;
};

class MessageItem : public LogFormatter::Item 
{
public:
    MessageItem(const std::string& str) : m_s(str) {}

    void format(std::ostream& ss, LogEvent::ptr event) override {
        ss << event->getMessage();
    }
private:
    const std::string m_s;
};

class TabItem : public LogFormatter::Item 
{
public:
    TabItem(const std::string& str) : m_s(str) {}

    void format(std::ostream& ss, LogEvent::ptr event) override {
        ss << "\t";
    }
private:
    const std::string m_s;
};

class NewLineItem : public LogFormatter::Item 
{
public:
    NewLineItem(const std::string& str) : m_s(str) {}

    void format(std::ostream& ss, LogEvent::ptr event) override {
        ss << std::endl;
    }
private:
    const std::string m_s;
};

class LevelItem : public LogFormatter::Item 
{
public:
    LevelItem(const std::string& str) : m_s(str) {}

    void format(std::ostream& ss, LogEvent::ptr event) override {
        ss << LogLevel::toString(event->getLevel());
    }
private:
    const std::string m_s;
};

class NameItem : public LogFormatter::Item 
{
public:
    NameItem(const std::string& str) : m_s(str) {}

    void format(std::ostream& ss, LogEvent::ptr event) override {
        ss << event->getLogger()->getName();
    }
private:
    const std::string m_s;
};

std::map<char, std::function<LogFormatter::Item::ptr(const std::string&)>> LogFormatter::FORMATS = {
    {'d', [](const std::string& fmt){ return LogFormatter::Item::ptr(new TimeItem(fmt)); } },
    {'f', [](const std::string& fmt){ return LogFormatter::Item::ptr(new FileItem(fmt)); } },
    {'l', [](const std::string& fmt){ return LogFormatter::Item::ptr(new LineItem(fmt)); } },
    {'p', [](const std::string& fmt){ return LogFormatter::Item::ptr(new LevelItem(fmt)); } },
    {'m', [](const std::string& fmt){ return LogFormatter::Item::ptr(new MessageItem(fmt)); } },
    {'c', [](const std::string& fmt){ return LogFormatter::Item::ptr(new NameItem(fmt)); } },
    {'T', [](const std::string& fmt){ return LogFormatter::Item::ptr(new TabItem(fmt)); } },
    {'n', [](const std::string& fmt){ return LogFormatter::Item::ptr(new NewLineItem(fmt)); } },
};

void LogFormatter::format(std::ostream& ss, LogEvent::ptr event) {
    for (auto& item : m_items) {
        item->format(ss, event);
    }
}

void LogFormatter::init() {
    // Decode the pattern, define the format to log.

    bool found = false;
    for (auto it = m_pattern.begin(); it < m_pattern.end(); ++it) {
        if (*it == '%') {
            if (found) {
                std::cout << "parse error" << std::endl;
                break;
            } else {
                found = true;
            }
        } 
        else {
            if(found) {
                auto key = *it;
                if (FORMATS.count(key) > 0) {
                    std::stringstream fmt;
                    if (it + 1 < m_pattern.end() && *(it+1) == '{') {
                        auto fmt_found = false;
                        for (it = it+2; it < m_pattern.end(); ++it) {
                            if (*it == '}') {
                                fmt_found = found;
                                break;
                            }
                            fmt << *it;
                        }

                        if (!fmt_found) {
                            std::cout << "parse error: open {}" << std::endl;
                        }
                    }
                    m_items.push_back(FORMATS[key](fmt.str()));
                } else {
                    std::cout << "parse error" << std::endl;
                    break;
                }
                
                found = false;
            } 
            else {
                std::stringstream ss;
                for (; it < m_pattern.end(); ++it) {
                    if (*it == '%') {
                        it--; // do not skip this % for the outer loop
                        break;
                    }
                    ss << *it;
                }
                m_items.push_back(Item::ptr(new StringItem(ss.str())));
            }
        }
    }
}


}
