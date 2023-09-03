#include <iostream>
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
        switch (level)
        {
        case alert_level::DEBUG:
            break;
        case alert_level::TRACE:
            break;
        case alert_level::INFO:
            break;
        case alert_level::WARN:
            break;
        case alert_level::ERROR:
            exit(1);
            break;
        case alert_level::FATAL:
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
};
