#include <spdlog/spdlog.h>
#include "System/System.hpp"

// Config
const std::string log_directory = "logs/";

void init_logger()
{
    spdlog::set_async_mode(4096);
    auto logger = spdlog::daily_logger_mt("system", log_directory + "system.log");
    logger->flush_on(spdlog::level::err);
}

int main()
{
    init_logger();

    System system;
    system.run();
}
