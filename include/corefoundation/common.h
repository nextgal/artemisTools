/**
 * @file common.h
 * @author ryank231231
 * @brief
 * @version 0.1
 * @date 2023-02-06
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#ifndef _COMMON_H_
#define _COMMON_H_

#include <condition_variable>
#include <cstdint>
#include <cstdio>
#include <future>
#include <memory>
#include <mutex>
#include <string>
#include <string_view>
#include <utility>
#include <variant>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#endif  // _WIN32

// common data type
using u32 = uint32_t;
using i32 = int32_t;
using u64 = uint64_t;
using i64 = int64_t;
using u8 = uint8_t;
using usize = size_t;

using sharedString = std::shared_ptr<std::string>;
using uniqueString = std::unique_ptr<std::string>;
using str = std::string;
using strview = std::string_view;

#endif  //_COMMON_H_
