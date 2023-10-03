//
// Created by Yormingandr on 10/1/2023.
//

#ifndef AXODB_LOGMANAGER_H
#define AXODB_LOGMANAGER_H

#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <mutex>

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
            CHECKPOINT  // Assuming you have a CHECKPOINT type
        } type;
    };

    class LogManager {
    public:
        explicit LogManager(const std::string &logFileName);
        ~LogManager();

        void AppendLog(const LogRecord &record);
        std::vector<LogRecord> ReadLogs();
        std::set<int> GetActiveTransactions();  // Declaration of the method

    private:
        std::string logFileName_;
        std::ofstream logFile_;
        std::mutex logMutex_;
    };

}  // namespace axodb

#endif //AXODB_LOGMANAGER_H
