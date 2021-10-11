#pragma once
#ifndef LOG_HPP
#define LOG_HPP
#include "Common.hpp"
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace cave {
	class Log {
	public:
		//TODO(Byron) Maybe move StartUp and ShutDown to private and make caller friend class
		
		static std::shared_ptr<spdlog::logger>& GetLogger() noexcept{ 
			static Log logger;
			return logger.s_logger; }

	private:
		Log() {
			spdlog::set_pattern("%^[%T] %n: %v%$");
			s_logger = spdlog::stdout_color_mt("CAVE");
		}
		Log(const Log& log) = delete;
		Log& operator=(const Log& l) = delete;
		std::shared_ptr<spdlog::logger> s_logger;
	};
}

#if NDEBUG
	#define CAVE_LOG_INFO(...)					(void(0))
	#define CAVE_LOG_ERROR(...)					(void(0))
	#define CAVE_ASSERT(expr, ...)				(void(0))
#else
	#define CAVE_LOG_INFO(...)					::cave::Log::GetLogger()->info(__VA_ARGS__)
	#define CAVE_LOG_ERROR(...)					::cave::Log::GetLogger()->error(__VA_ARGS__)
	#if WIN32
		#define CAVE_ASSERT(expr, ...)					{if(!(expr)){ \
														CAVE_LOG_ERROR(__VA_ARGS__); \
														__debugbreak(); }}
	#else
		#define CAVE_ASSERT(expr, ...)					{if(!(expr)){ \
														CAVE_LOG_ERROR(__VA_ARGS__); \
														assert(expr); }}
	#endif
												

#endif


#endif