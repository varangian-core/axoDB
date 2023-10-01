//
// Created by Yormingandr on 10/1/2023.
//

#ifndef AXODB_LOGMANAGER_H
#define AXODB_LOGMANAGER_H

#include <fstream>
#include <vector>
#include <mutex>
#include <string>

namespace axodb {

    struct LogRecord {
        int transactionId;
        int pageId;
        int offset;
        std::string oldValue;
        std::string newValue;
        enum class LogType {
            BEGIN,
            COMMIT,
            ABORT,
            UPDATE
        } type;  // Added 'type' member to the struct
    };

    class LogManager {
    public:
        LogManager(const std::string& logFileName);
        ~LogManager();

        void AppendLog(const LogRecord& record);
        std::vector<LogRecord> ReadLogs();

    private:
        std::string logFileName_;
        std::ofstream logFile_;
        std::mutex logMutex_;
    };

}  // namespace axodb

#endif //AXODB_LOGMANAGER_H
