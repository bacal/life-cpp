#pragma once

#include <fmt/format.h>
#include <fmt/color.h>
#include <fmt/chrono.h>

#define LOG_INFO(...) 	    fmt::print(fg(fmt::color::azure),"[{:%H:%M:%S}] life: {}\n",fmt::localtime(std::time(nullptr)),fmt::format(__VA_ARGS__))
#define LOG_WARNING(...) 	fmt::print(fg(fmt::color::light_red),"[{:%H:%M:%S}] life: {}\n",fmt::localtime(std::time(nullptr)),fmt::format(__VA_ARGS__))
#define LOG_ERROR(...) 	    fmt::print(fg(fmt::color::crimson),"[{:%H:%M:%S}] life: {}\n",fmt::localtime(std::time(nullptr)),fmt::format(__VA_ARGS__))
#define LOG_RAW(...)		fmt::print(fg(fmt::color::light_blue),fmt::format(__VA_ARGS__))

#define LOG_ERRORQ(...) LOG_ERROR(__VA_ARGS__); return

#define LOG_FORMAT(...)		fmt::format(__VA_ARGS__)

#define LOG_FORMAT_PTR(...)	LOG_FORMAT(__VA_ARGS__).c_str()

#define LOG_FATAL(...)	 throw std::runtime_error(fmt::format("[{:%H:%M:%S}] life: {}\n",fmt::localtime(std::time(nullptr)),fmt::format(__VA_ARGS__)))