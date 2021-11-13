#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace CarData {

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};

}

// Core log macros
#define CD_INFO(...)     ::CarData::Log::GetLogger()->info(__VA_ARGS__)
#define CD_TRACE(...)    ::CarData::Log::GetLogger()->trace(__VA_ARGS__)
#define CD_WARN(...)     ::CarData::Log::GetLogger()->warn(__VA_ARGS__)
#define CD_ERROR(...)    ::CarData::Log::GetLogger()->error(__VA_ARGS__)
#define CD_FATAL(...)    ::CarData::Log::GetLogger()->fatal(__VA_ARGS__)