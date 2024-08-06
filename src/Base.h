#pragma once

#include <memory>

#include <iostream>
#include <string>
#include <functional>

#ifdef DEBUG
#else
#define DEBUGBREAK()
#endif


#define EXPAND_MACRO(x) x
#define STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

template<typename T>
using Scope = std::unique_ptr<T>;
template<typename T, typename ... Args>
constexpr Scope<T> CreateScope(Args&& ... args)
{
  return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... args)
{
  return std::make_shared<T>(std::forward<Args>(args)...);
}

