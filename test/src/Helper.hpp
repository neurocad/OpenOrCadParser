#ifndef HELPER_HPP
#define HELPER_HPP


#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include <spdlog/spdlog.h>


namespace fs = std::filesystem;


[[maybe_unused]]
inline void configure_spdlog()
{
    spdlog::set_level(spdlog::level::off);

    spdlog::set_pattern("[%^%l%$] %v");
}


[[maybe_unused]]
inline void check_error_count(const fs::path& aFilePath, size_t aActualErrCnt, size_t aExpectedErrCnt)
{
    std::string msg;

    if(aActualErrCnt < aExpectedErrCnt)
    {
        msg = fmt::format("REDUCTION: {:>4} (actual errors) < {:>4} (expected errors) in {}",
            aActualErrCnt, aExpectedErrCnt, aFilePath.string());

        std::clog << msg << std::endl;
    }

    if(aActualErrCnt > aExpectedErrCnt)
    {
        msg = fmt::format("INCREASE:  {:>4} (actual errors) > {:>4} (expected errors) in {}",
            aActualErrCnt, aExpectedErrCnt, aFilePath.string());

        std::clog << msg << std::endl;
    }

    const fs::path logPath = fs::current_path() / "test_err_cnt.log";

    std::ofstream logFile;

    logFile.open(logPath, std::ios_base::app);

    logFile << msg;
}


#endif // HELPER_HPP