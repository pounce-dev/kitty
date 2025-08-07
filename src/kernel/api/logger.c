//
// Created by AIDAN on 5/13/2025.
//

#include "logger.h"
#include "../../util/list.h"

static klist_t handler_list = {
    0,
    0,
    sizeof(logger_handler_t*),
    0,
};

void register_logger_handler(logger_handler_t* handler) {
    klist_add(&handler_list, handler);
}

static klist_t logger_list = {
        0,
        0,
        sizeof(logger_t*),
        0,
};

void register_logger(logger_t* logger) {
    klist_add(&logger_list, logger);
}

void klog(log_message_t* log_message) {
    for (uint64_t logger_handler_index = 0; logger_handler_index < handler_list.length; logger_handler_index++) {
        logger_handler_t * logger_handler = klist_get(&handler_list, logger_handler_index);
        if (logger_handler->min_level <= log_message->level)
            logger_handler->logger_output_handler(log_message);
    }
}