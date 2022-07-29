#pragma once

#include <string>
#include <memory>
#include <list>

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
  %r, // r: elapse time
  %c, // c: logger name
  %t, // t: thread id
  %n, // n: new line
  %d, // d: date
  %f, // f: file
  %l, // l: line number
  %T, // T: Tab
  %F, // F: fiber id
  %N, // N: thread name

  */

class LogEvent {
public:
    using ptr = std::shared_ptr<LogEvent>;
    LogEvent(const std::string& message) : m_message(message) {};
    std::string getMessage() { return m_message; }
private:
    std::string m_message;
};

class LogAppender {
public:
    using ptr = std::shared_ptr<LogAppender>;
    virtual ~LogAppender() = default;
    virtual void log(LogEvent::ptr event) = 0;
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

class LogFormatter {

};


}
