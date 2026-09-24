#include "Logger.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace ip {

    std::string Logger::logFilePath = "process.log"; // 기본 로그 파일명

    void Logger::setLogFile(const std::string& path) {
        if (!path.empty()) {
            logFilePath = path;
        }
    }

    std::string Logger::getCurrentTimeStr() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm tm_buf;
#if defined(_WIN32) || defined(_WIN64)
        localtime_s(&tm_buf, &now_time);
#else
        localtime_r(&now_time, &tm_buf);
#endif
        std::ostringstream oss;
        oss << std::put_time(&tm_buf, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    void Logger::logSuccess(const std::string& filterParams, long long durationMs, const std::string& inputPath, const std::string& outputPath) {
        std::ofstream ofs(logFilePath, std::ios_base::app);
        if (ofs.is_open()) {
            ofs << "[" << getCurrentTimeStr() << "] [SUCCESS] "
                << "Filter: " << filterParams << " | "
                << "Time: " << durationMs << " ms | "
                << "In: " << inputPath << " | "
                << "Out: " << outputPath << "\n";
        } else {
            std::cerr << "Warning: Could not open log file: " << logFilePath << "\n";
        }
    }

    void Logger::logFailure(const std::string& filterParams, const std::string& errorMessage) {
        std::ofstream ofs(logFilePath, std::ios_base::app);
        if (ofs.is_open()) {
            ofs << "[" << getCurrentTimeStr() << "] [FAILED]  "
                << "Filter: " << (filterParams.empty() ? "None" : filterParams) << " | "
                << "Error: " << errorMessage << "\n";
        } else {
            std::cerr << "Warning: Could not open log file: " << logFilePath << "\n";
        }
    }

} // namespace ip
