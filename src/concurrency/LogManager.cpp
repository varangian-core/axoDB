//
// Created by Yormingandr on 10/1/2023.
//
#include "LogManager.h"
#include <sstream>

namespace axodb {

    LogManager::LogManager(const std::string &logFileName) : logFileName_(logFileName) {
        logFile_.open(logFileName_, std::ios::app | std::ios::binary);
    }

    LogManager::~LogManager() {
        if (logFile_.is_open()) {
            logFile_.close();
        }
    }

    void LogManager::AppendLog(const LogRecord &record) {
        std::lock_guard<std::mutex> lock(logMutex_);
        logFile_ << record.transactionId << ","
                 << record.pageId << ","
                 << record.offset << ","
                 << record.oldValue << ","
                 << record.newValue << ","
                 << static_cast<int>(record.type) << std::endl;
    }

    std::vector<LogRecord> LogManager::ReadLogs() {
        std::vector<LogRecord> logs;
        std::ifstream inFile(logFileName_, std::ios::binary);
        std::string line;
        while (std::getline(inFile, line)) {
            std::istringstream ss(line);
            LogRecord record;
            int type;
            char delimiter;
            ss >> record.transactionId >> delimiter
               >> record.pageId >> delimiter
               >> record.offset >> delimiter
               >> record.oldValue >> delimiter
               >> record.newValue >> delimiter
               >> type;
            record.type = static_cast<LogRecord::LogType>(type);
            logs.push_back(record);
        }
        return logs;
    }

    std::set<int> LogManager::GetActiveTransactions() {
        // Placeholder implementation
        return std::set<int>();
    }

}  // namespace axodb
