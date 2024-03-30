// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_LOGGING_H_
#define _GECKO_LOGGING_H_

// Includes
#include <iostream>

// Print statements
#define PUTS puts
#define PRINTF printf
#define WPRINTF wprintf

// Write a logging statement
#ifdef DEBUG
#define LOG_STATEMENT(string) PUTS("LOG: " string);
#define LOG_FORMAT_STATEMENT(string, ...) PRINTF("LOG: " string, __VA_ARGS__);
#define LOG_WFORMAT_STATEMENT(string, ...) WPRINTF("LOG: " string, __VA_ARGS__);
#define LOG_FORMAT_STATEMENT_NARGS(string) PRINTF("LOG: " string);
#define LOG_WFORMAT_STATEMENT_NARGS(string) WPRINTF("LOG: " string);
#else
#define LOG_STATEMENT
#define LOG_FORMAT_STATEMENT
#define LOG_WFORMAT_STATEMENT
#define LOG_FORMAT_STATEMENT_NARGS
#define LOG_WFORMAT_STATEMENT_NARGS
#endif

// Write an error statement
#ifdef DEBUG
#define ERROR_STATEMENT(string) PUTS("ERROR: " string);
#define ERROR_FORMAT_STATEMENT(string, ...) PRINTF("ERROR: " string, __VA_ARGS__);
#define ERROR_WFORMAT_STATEMENT(string, ...) WPRINTF("ERROR: " string, __VA_ARGS__);
#define ERROR_FORMAT_STATEMENT_NARGS(string) PRINTF("ERROR: " string);
#define ERROR_WFORMAT_STATEMENT_NARGS(string) WPRINTF("ERROR: " string);
#else
#define ERROR_STATEMENT
#define ERROR_FORMAT_STATEMENT
#define ERROR_WFORMAT_STATEMENT
#define ERROR_FORMAT_STATEMENT_NARGS
#define ERROR_WFORMAT_STATEMENT_NARGS
#endif

#endif
