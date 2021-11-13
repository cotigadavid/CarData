#pragma once

#include <memory>

#ifdef CD_PLATFORM_WINDOWS
#if CD_DYNAMIC_LINK
#ifdef CD_BUILD_DLL
#define CarData_API __declspec(dllexport)
#else
#define CarData_API __declspec(dllimport)
#endif
#else
#define CarData_API
#endif
#else
#error CarData only supports Windows!
#endif

#ifdef CD_DEBUG
#define CD_ENABLE_ASSERTS
#endif

#ifdef CD_ENABLE_ASSERTS
#define CD_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define CD_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define CD_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Hazel {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}