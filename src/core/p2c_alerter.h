#ifndef _P2C_ALERTER_H_
#define _P2C_ALERTER_H_

#include <iostream>
#include <fstream> // TODO: log file
#include <sstream>
enum alert_level
{
    DEBUG,
    TRACE,
    INFO,
    WARN,
    ERROR,
    FATAL
};
class p2c_alerter
{
private:
    static void _alerting(alert_level level, std::string message)
    {
        if (message.back() != '\n')
            message += '\n';
        switch (level)
        {
        case alert_level::DEBUG:
            std::cerr << "DEBUG : " << message;
            break;
        case alert_level::TRACE:
            std::cerr << "TRACE : " << message;
            break;
        case alert_level::INFO:
            std::cerr << "INFO : " << message;
            break;
        case alert_level::WARN:
            std::cerr << "WARN : " << message;
            break;
        case alert_level::ERROR:
            std::cerr << "ERROR : " << message;
            exit(1);
            break;
        case alert_level::FATAL:
            std::cerr << "FATAL : " << message;
            abort();
            break;
        default:
            break;
        }
    };

public:
    static void alerting(alert_level level) { _alerting(level, ""); };
    static void alerting(alert_level level, std::string message) { _alerting(level, message); };
    static void alerting(alert_level level, char *message)
    {
        std::string _str = message;
        _alerting(level, _str);
    };
    template <typename t>
    static void alerting(alert_level level, std::string message, t arg)
    {
        std::stringstream ss;
        ss << arg;
        std::string _str;
        ss >> _str;
        message += " " + _str;
        alerting(level, message);
    }
    template <typename t, typename... ts>
    static void alerting(alert_level level, std::string message, t arg, ts... args)
    {
        std::stringstream ss;
        ss << arg;
        std::string _str;
        ss >> _str;
        message += " " + _str;
        alerting(level, message, args...);
    }
};

#endif