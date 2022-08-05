#pragma once

#include <string>
#include <memory>
#include <list>
#include <ctime>
#include <string_view>
#include <iostream>
#include <map>
#include <vector>
#include <functional>

namespace eva02 {

class LogLevel {
public:
    enum Level {
        UNKNOWN,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL
    };
    static std::string toString(const LogLevel::Level level);
};

/**

  "%d{%Y-%m-%d %a %H:%M:%S}%T%f{5}%T%l%T[%p]%T[%c]%T%m%n";

  Every pattern has also has sub format in {}

  %m, // m: message
  %p, // p: level
  %c, // c: logger name
  %d, // d: date
  %f, // f: file __FILE__
  %l, // l: line number __LINE__

  %n, // n: new line
  %T, // T: Tab

  ---------------

  %t, // t: thread id 
  %N, // N: thread name

  %r, // r: elapse time
  %F, // F: fiber id

  */

class Logger;

class LogEvent {
public:
    using ptr = std::shared_ptr<LogEvent>;
    LogEvent(const std::shared_ptr<Logger> logger, const std::string& message
            , const LogLevel::Level level, const char* file, const int32_t line
            , const time_t time)
        : m_logger(logger)
        , m_message(message)
        , m_level(level)
        , m_file(file) 
        , m_line(line)
        , m_time(time) {

    };

public:
    const std::string getMessage() const { return m_message; }
    const LogLevel::Level getLevel() const { return m_level; }
    const std::shared_ptr<Logger> getLogger() const { return m_logger; } // name, logger level
    const time_t getTime() const { return m_time; }
    const char* getFile() const { return m_file; }
    const int32_t getLine() const { return m_line; }

private:
    const std::shared_ptr<Logger> m_logger;
    const std::string m_message;
    const LogLevel::Level m_level;
    const char* m_file;
    const int32_t m_line;
    const time_t m_time;
};


class LogFormatter {

public:
    using ptr = std::shared_ptr<LogFormatter>;

    LogFormatter(const std::string& pattern)
        : m_pattern(pattern) {
            init();
        }

    void format(std::ostream& ss, LogEvent::ptr event);
    void init();

    class Item {
    public:
        using ptr = std::shared_ptr<Item>;
        //virtual std::string format(LogEvent::ptr event) = 0;
        virtual ~Item() = default;
        virtual void format(std::ostream&, LogEvent::ptr event) = 0;
    };

    //"%d%T%f%T%l%T%p%T%m%n[*9()]";
    static std::map<char, std::function<Item::ptr(const std::string&)>> FORMATS;
private:
    std::string m_pattern;
    std::vector<Item::ptr> m_items;
};

class LogAppender {
public:
    LogAppender(const std::string& pattern = "%d{%Y-%m-%d %a %H:%M:%S}%T%f{5}%T%l%T[%p]%T[%c]%T%m%n") 
        : m_formatter(std::make_shared<LogFormatter>(pattern)) {
    }
    using ptr = std::shared_ptr<LogAppender>;
    virtual ~LogAppender() = default;
    virtual void log(LogEvent::ptr event) = 0;

    LogLevel::Level getLevel() { return m_level; }
    void setLevel(LogLevel::Level level) { m_level = level; }

protected:
    LogFormatter::ptr m_formatter;
    LogLevel::Level m_level = LogLevel::DEBUG;
};

class StdOutLogAppender : public LogAppender {
public:
    void log(LogEvent::ptr event) override;
};


class Logger {
public:
    using ptr = std::shared_ptr<Logger>;
    Logger() = default;
    Logger(const std::string& name, LogLevel::Level level);

    void addAppender(LogAppender::ptr appender);
    void removeAppender(LogAppender::ptr appender);
    void clearAppender();

    std::string getName() const { return m_name; }
    inline LogLevel::Level getLevel() const { return m_level; }
    inline void setLevel(const LogLevel::Level level) { m_level = level; }

    void log(LogLevel::Level level, LogEvent::ptr event);

    inline void debug(LogEvent::ptr event) { log(LogLevel::DEBUG, event); }
    inline void info(LogEvent::ptr event) { log(LogLevel::INFO, event); }
    inline void warn(LogEvent::ptr event) { log(LogLevel::WARN, event); }
    inline void error(LogEvent::ptr event) { log(LogLevel::ERROR, event); }
    inline void fatal(LogEvent::ptr event) { log(LogLevel::FATAL, event); }

private:
    std::string m_name = "root";
    LogLevel::Level m_level = LogLevel::DEBUG;
    std::list<LogAppender::ptr> m_appenders;
};



}
