#include <iostream>
#include <memory>
#include <string>
using namespace std;

class I_LogHandler
{
    public:
        enum LogLevel{INFO, WARN, ERROR, FATAL};
        virtual shared_ptr<I_LogHandler> setNextLogHandler(shared_ptr<I_LogHandler> handler)=0;
        virtual void logMessage(int level, std::string message)=0;
};
class LoggerHandler : public I_LogHandler
{
    protected:
        shared_ptr<I_LogHandler> next_handler_;
    public:
        shared_ptr<I_LogHandler> setNextLogHandler(shared_ptr<I_LogHandler> handler) override
        {
            next_handler_ = handler;
            return handler;
        }
        void logMessage(int level, std::string message) override
        {
            if(level != LogLevel::INFO && level != LogLevel::WARN && level != LogLevel::ERROR && level != LogLevel::FATAL)
                cout << "[Message] " << message << endl;
            else
                next_handler_->logMessage(level, message);
        }
};
class InfoLoggerHandler : public LoggerHandler
{
    public:
        void logMessage(int level, std::string message) override
        {
            if(level == LogLevel::INFO)
                cout << "[INFO] " << message << endl;
            else
                next_handler_->logMessage(level, message);
        }
};
class WarnLoggerHandler : public LoggerHandler
{
    public:
        void logMessage(int level, std::string message) override
        {
            if(level == LogLevel::WARN)
                cout << "[WARN] " << message << endl;
            else
                next_handler_->logMessage(level, message);
        }
};
class ErrorLoggerHandler : public LoggerHandler
{
    public:
        void logMessage(int level, std::string message) override
        {
            if(level == LogLevel::ERROR)
                cout << "[ERROR] " << message << endl;
            else
                next_handler_->logMessage(level, message);
        }
};
class FatalLoggerHandler : public LoggerHandler
{
    public:
        void logMessage(int level, std::string message) override
        {
            if(level == LogLevel::FATAL)
                cout << "[FATAL] " << message << endl;
            else
                LoggerHandler::logMessage(level, message);
        }
};
class LogSystem : public LoggerHandler
{
    private:
        shared_ptr<LoggerHandler> default_logger_;
        shared_ptr<InfoLoggerHandler> info_logger_;
        shared_ptr<WarnLoggerHandler> warn_logger_;
        shared_ptr<ErrorLoggerHandler> error_logger_;
        shared_ptr<FatalLoggerHandler> fatal_logger_;
    public:
        LogSystem()
        {
            default_logger_ = make_shared<LoggerHandler>();
            info_logger_ = make_shared<InfoLoggerHandler>();
            warn_logger_ = make_shared<WarnLoggerHandler>();
            error_logger_ = make_shared<ErrorLoggerHandler>();
            fatal_logger_ = make_shared<FatalLoggerHandler>();
            default_logger_->setNextLogHandler(info_logger_)->setNextLogHandler(warn_logger_)->setNextLogHandler(error_logger_)->setNextLogHandler(fatal_logger_);
        }
        void LogMessage(LoggerHandler::LogLevel level, string message)
        {
            default_logger_->logMessage(level, message);
        }
};
int main()
{
    auto Logger = make_shared<LogSystem>();
    string message = "I am groot.";
    Logger->LogMessage(LogSystem::LogLevel::INFO, message);
    Logger->LogMessage(LogSystem::LogLevel::WARN, message);
    Logger->LogMessage(LogSystem::LogLevel::ERROR, message);
    Logger->LogMessage(LogSystem::LogLevel::FATAL, message);
    return 0;
}
