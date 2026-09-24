#pragma once
#include <string>

namespace ip {
    class Logger {
    public:
        /**
         * @brief 로그 파일의 경로를 설정합니다.
         */
        static void setLogFile(const std::string& path);

        /**
         * @brief 처리 성공 시 로그를 기록합니다.
         * @param filterParams 사용된 필터 또는 파이프라인 정보
         * @param durationMs 처리 소요 시간(ms)
         * @param inputPath 입력 파일 경로
         * @param outputPath 출력 파일 경로
         */
        static void logSuccess(const std::string& filterParams, long long durationMs, const std::string& inputPath, const std::string& outputPath);

        /**
         * @brief 에러 발생(실패) 시 로그를 기록합니다.
         * @param filterParams 사용하려고 했던 필터 정보
         * @param errorMessage 발생한 에러 메시지
         */
        static void logFailure(const std::string& filterParams, const std::string& errorMessage);

    private:
        static std::string logFilePath;
        static std::string getCurrentTimeStr();
    };
}
