#pragma once
#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>
#include <string>
#include <memory>
#include <stdexcept>

class Logger {
private:
    static std::unique_ptr<Logger> instance;
    static std::mutex init_mtx;
    static std::mutex write_mtx;
    std::ofstream logFile;

    Logger(const std::string& filename) {
        logFile.open(filename, std::ios::trunc);
        if (!logFile.is_open()) {
            throw std::runtime_error("Failed to open log file: " + filename);
        }
        log("[Init] Logger started.");
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;


public:
    ~Logger() {
        if (logFile.is_open()) {
            log("[Shutdown] Logger closed.");
            logFile.close();
        }
    }

    static Logger* getInstance(const std::string& filename = "Test/output2.txt") {
        if (!instance) {
            std::lock_guard<std::mutex> lock(init_mtx);
            if (!instance) {
                instance = std::unique_ptr<Logger>(new Logger(filename));
            }
        }
        return instance.get();
    }

    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(write_mtx);
        if (logFile.is_open()) {
            logFile << message << std::endl;
        }
    }

};

std::unique_ptr<Logger> Logger::instance;
std::mutex Logger::init_mtx;
std::mutex Logger::write_mtx;