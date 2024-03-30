// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_UTILITY_LOGGING_H_
#define _GECKO_UTILITY_LOGGING_H_

// External includes
#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>

// Internal includes
#include "Utility/Types.h"

// SpdLog function defines
#define CreateBasicLogger spdlog::basic_logger_mt<spdlog::async_factory>
#define CreateRotatingLogger spdlog::rotating_logger_mt<spdlog::async_factory>
#define CreateStdOutColorLogger spdlog::stdout_color_mt<spdlog::async_factory>
#define CreateStdErrColorLogger spdlog::stderr_color_mt<spdlog::async_factory>
#define SetDefaultLogger spdlog::set_default_logger
#define SetLoggingLevel spdlog::set_level
#define SetLoggingPattern spdlog::set_pattern
#define SetLoggingFlush spdlog::flush_every
#define WriteDebugLogEntry spdlog::debug
#define WriteInfoLogEntry spdlog::info
#define WriteErrorLogEntry spdlog::error
#define WriteWarningLogEntry spdlog::warn
#define WriteCriticalLogEntry spdlog::critical

// SpdLog type defines
#define LoggingException spdlog::spdlog_ex

// Setup logging
#ifdef DEBUG
#define SETUP_FILE_LOGGING(name, file) SetDefaultLogger(CreateBasicLogger(#name, file));
#else
#define SETUP_FILE_LOGGING(name, file)
#endif

// Write a logging statement
#ifdef DEBUG
#define LOG_STATEMENT(string) WriteInfoLogEntry(string)
#define LOG_FORMAT_STATEMENT(string, ...) WriteInfoLogEntry(string, __VA_ARGS__)
#define LOG_WFORMAT_STATEMENT(string, ...) WriteInfoLogEntry(string, __VA_ARGS__)
#define LOG_FORMAT_STATEMENT_NARGS(string) WriteInfoLogEntry(string)
#define LOG_WFORMAT_STATEMENT_NARGS(string) WriteInfoLogEntry(string)
#else
#define LOG_STATEMENT(string)
#define LOG_FORMAT_STATEMENT(string, ...)
#define LOG_WFORMAT_STATEMENT(string, ...)
#define LOG_FORMAT_STATEMENT_NARGS(string)
#define LOG_WFORMAT_STATEMENT_NARGS(string)
#endif

// Write a warning statement
#ifdef DEBUG
#define WARNING_STATEMENT(string) WriteWarningLogEntry(string)
#define WARNING_FORMAT_STATEMENT(string, ...) WriteWarningLogEntry(string, __VA_ARGS__)
#define WARNING_WFORMAT_STATEMENT(string, ...) WriteWarningLogEntry(string, __VA_ARGS__)
#define WARNING_FORMAT_STATEMENT_NARGS(string) WriteWarningLogEntry(string)
#define WARNING_WFORMAT_STATEMENT_NARGS(string) WriteWarningLogEntry(string)
#else
#define WARNING_STATEMENT(string)
#define WARNING_FORMAT_STATEMENT(string, ...)
#define WARNING_WFORMAT_STATEMENT(string, ...)
#define WARNING_FORMAT_STATEMENT_NARGS(string)
#define WARNING_WFORMAT_STATEMENT_NARGS(string)
#endif

// Write an error statement
#ifdef DEBUG
#define ERROR_STATEMENT(string) WriteErrorLogEntry(string)
#define ERROR_FORMAT_STATEMENT(string, ...) WriteErrorLogEntry(string, __VA_ARGS__)
#define ERROR_WFORMAT_STATEMENT(string, ...) WriteErrorLogEntry(string, __VA_ARGS__)
#define ERROR_FORMAT_STATEMENT_NARGS(string) WriteErrorLogEntry(string)
#define ERROR_WFORMAT_STATEMENT_NARGS(string) WriteErrorLogEntry(string)
#else
#define ERROR_STATEMENT(string)
#define ERROR_FORMAT_STATEMENT(string, ...)
#define ERROR_WFORMAT_STATEMENT(string, ...)
#define ERROR_FORMAT_STATEMENT_NARGS(string)
#define ERROR_WFORMAT_STATEMENT_NARGS(string)
#endif

#endif
