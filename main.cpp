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

std::variant<std::streampos, std::nullptr_t> getFileSize (const std::string filepath) {
    
    std::ifstream file(filepath, std::ios::binary);
    
    if(!file) {
        std::cerr << "Error opening file!" << std::endl;
        return nullptr;
    }
    
    // move the file pointer to the end
    
    file.seekg(0, std::ios::end);
    
    std::streampos fileSize = file.tellg();
    
    std::cout << "File size: " << fileSize << " bytes" << std::endl;
    
    file.close();
    
    return fileSize;
    
}

int extractNumberBetweenGAndDot(const std::string& path) {
    size_t gPos = path.find('g');
    size_t dotPos = path.find('.', gPos);
    
    if (gPos != std::string::npos && dotPos != std::string::npos && gPos < dotPos) {
        std::string numberStr = path.substr(gPos + 1, dotPos - gPos - 1);
        return std::stoi(numberStr);
    }
    
    return -1;
}



class Logger {
public:
    LogLevel m_logLevel;
    
    Logger(): m_logLevel(LogLevel::Info){};
    
    void logtofile(const std::string message, const std::string path) const {
        std::ofstream outFile(path, std::ios::app);
        
        
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
            std::streampos sizeOfFile;
            int numlogs;
            std::ostringstream newpath;
            
            switch (level) {
                case LogLevel::Info:
                    levelStr = "INFO";
                    break;
                    
                case LogLevel::Debug:
                    levelStr = "DEBUG";
                    break;
                    
                case LogLevel::Error:
                    levelStr = "ERROR";
                    break;
            }
            
            oss << "[" << levelStr << "] " << "[" << getCurrentDateTime() << "] " << message;
            const std::string entry = oss.str();
            std::cout << entry << std::endl;
            
            std::string path = "log0.txt";
            
            std::variant<std::streampos, std::nullptr_t> size = getFileSize(path);
            
            if(std::holds_alternative<std::streampos>(size)){
                
               sizeOfFile  = std::get<std::streampos>(size);
                
            }else{
                std::cerr << "Failed to retrieve file size." << std::endl;
            }
            
//            while(sizeOfFile > 1000) {
                
                if(sizeOfFile > 1000) {
                    numlogs = extractNumberBetweenGAndDot(path);
                    
                    std::cout << numlogs << std::endl;
                    
                    newpath << "log" << numlogs+1 << ".txt";
                    
                    path = newpath.str();
                    
                    std::cout << path << std::endl;
                    
//                    std::variant<std::streampos, std::nullptr_t> size = getFileSize(newpath.str());
//
//                    if(std::holds_alternative<std::streampos>(size)){
//
//                        sizeOfFile  = std::get<std::streampos>(size);
//
//                    }else{
//                        std::cerr << "Failed to retrieve file size." << std::endl;
//                    }
//
                    std::cout << "greater than 1000" << std::endl;
                    
                }else{
                    std::cout << "less than 1000" << std::endl;
                }
//            }
           
            
            this->logtofile(entry, path);
            
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
