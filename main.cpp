//
//  main.cpp
//  logger
//
//  Created by Godswill Adigwe on 11/11/2024.
//

#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <fstream>


std::string getCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t timeNow = std::chrono::system_clock::to_time_t(now);
    std::tm* timeInfo = std::localtime(&timeNow);
    std::ostringstream oss;
    oss << std::put_time(timeInfo, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

enum class LogLevel {
    Info = 1,
    Debug = 2,
    Error = 3,
};



class Logger {
public:
    LogLevel m_logLevel;
    
    Logger(): m_logLevel(LogLevel::Info){};
    
    void logtofile(const std::string message) const {
        std::ofstream outFile("log.txt", std::ios::app);
        
        if(!outFile) {
            std::cerr << "Error: Could not open the file for writing." <<std::endl;
            return;
        }
        
        std::cout << "outputting file" << std::endl;
        
        outFile << message << std::endl;
        
        outFile.close();
        
        return;
    }
    
    void logMessage(LogLevel level, const std::string& message) const {
        
        if(static_cast<int>(level) >= static_cast<int>(m_logLevel)) {
            std::ostringstream oss;
            std::string levelStr;
            
            switch (level) {
                case LogLevel::Info:
//                    std::ostringstream oss;
//                    oss << "[INFO] " << "[" << getCurrentDateTime() << "] " << message;
//                    const std::string entry = oss.str();
//                    std::cout << "[INFO] " << "[" << getCurrentDateTime() << "] " << message << std::endl;
//                    this -> logtofile(entry);
                    levelStr = "INFO";
                    break;
                    
                case LogLevel::Debug:
//                    std::cout << "[DEBUG] " << "[" << getCurrentDateTime() << "] "  << message << std::endl;
                    levelStr = "DEBUG";
                    break;
                    
                case LogLevel::Error:
//                    std::cout << "[ERROR] " << "[" << getCurrentDateTime() << "] "  << message << std::endl;
                    levelStr = "ERROR";
                    break;
            }
            
            oss << "[" << levelStr << "] " << "[" << getCurrentDateTime() << "] " << message;
            const std::string entry = oss.str();
            std::cout << entry << std::endl;
            
            this->logtofile(entry);
            
        }
    }
    
    void setLevel(LogLevel level) {
        m_logLevel = level;
    }
    
};

int main(int argc, const char * argv[]) {
    Logger logger;
    logger.logMessage(LogLevel::Info, "This is the first info message.");
    logger.logMessage(LogLevel::Debug, "This is the first Debug message.");
    logger.logMessage(LogLevel::Error, "This is first error message.");
    
//    Testing Debug
    logger.setLevel(LogLevel::Debug);
    logger.logMessage(LogLevel::Info, "This is the second info message.");
    logger.logMessage(LogLevel::Debug, "This is the second Debug message.");
    logger.logMessage(LogLevel::Error, "This is second error message.");
    
//    Testing Error
    logger.setLevel(LogLevel::Error);
    logger.logMessage(LogLevel::Info, "This is the first info message.");
    logger.logMessage(LogLevel::Debug, "This is the first Debug message.");
    logger.logMessage(LogLevel::Error, "This is first error message.");
    
    
    return 0;
}
