#include <spdlog/spdlog.h>
#include "System/System.hpp"
#include "Config/Config.hpp"

void init_logger(const Config& config)
{
    spdlog::set_async_mode(4096);
    auto logger = spdlog::daily_logger_mt("system", config.log_path + "system.log");
    logger->flush_on(spdlog::level::err);
}

int main()
{
	const Config config;
    init_logger(config);

    System system;
    system.run();
}
