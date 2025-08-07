//
// Created by AIDAN on 5/13/2025.
//

#ifndef KITTY_LOGGER_H
#define KITTY_LOGGER_H

typedef struct logger {
    char* logger_name; // The name of the logger, usually the process.
} logger_t;

enum log_level {
    DEBUG = 0,
    INFO = 1,
    WARN = 2,
    ERROR = 3,
    FATAL = 4
};

typedef struct log_message {
    logger_t* logger;
    enum log_level level;
    char* log_message;
} log_message_t;


typedef void (*logger_output_handler)(log_message_t* log_message);

typedef struct logger_handler {
    logger_output_handler logger_output_handler;
    enum log_level min_level; // the minimum level that the message must be to be logged (inclusive).
} logger_handler_t;

/*
 * Registers a logger (Input to the logger mechanism).
 */
void register_logger(logger_t* logger);

/*
 * Registers a logger_handler (Output of the logger mechanism).
 */
void register_logger_handler(logger_handler_t* handler);

/*
 * Logs a message to all the available logger handlers.
 */
void klog(log_message_t* log_message);

#endif //KITTY_LOGGER_H
