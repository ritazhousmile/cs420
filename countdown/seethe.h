// This file is adapted from https://github.com/jnguyen1098/seethe
#ifndef SEETHE_H
#define SEETHE_H

#include <stdio.h>
#include <time.h>

/* Default level */
#ifndef LOG_LEVEL
    #define LOG_LEVEL   WARNING
#endif

/* Default output stream */
#ifndef LOG_STREAM
    #define LOG_STREAM	stderr
#endif

/* Colour customization */
#define DEBUG_COLOUR    ""
#define INFO_COLOUR     "\x1B[36m"
#define NOTICE_COLOUR   "\x1B[32;1m"
#define WARNING_COLOUR  "\x1B[33m"
#define ERROR_COLOUR    "\x1B[31m"
#define CRITICAL_COLOUR "\x1B[41;1m"

/* Do not change this. */
#define RESET_COLOUR    "\x1B[0m"

/* Formatting prefs. */
#define MSG_ENDING      "\n"
#define TIME_FORMAT     "%T"
#define BORDER          "-"

/* Enabler flags */
#define DISPLAY_COLOUR  1
#define DISPLAY_TIME    1
#define DISPLAY_LEVEL   1
#define DISPLAY_FUNC    1
#define DISPLAY_FILE    1
#define DISPLAY_LINE    1
#define DISPLAY_BORDER  1
#define DISPLAY_MESSAGE 1
#define DISPLAY_ENDING  1
#define DISPLAY_RESET   1

/* Log to screen */
#define emit_log(colour, level, file, func, line, ...) do {                    \
                                                                               \
    /* notate the time */                                                      \
    time_t raw_time = time(NULL);                                              \
    char time_buffer[80];                                                      \
    strftime(time_buffer, 80, TIME_FORMAT, localtime(&raw_time));              \
                                                                               \
    /* enable colour */                                                        \
    fprintf(LOG_STREAM, "%s", DISPLAY_COLOUR ? colour : "");                   \
                                                                               \
    /* display the time */                                                     \
    fprintf(LOG_STREAM, "%s%s",                                                \
        DISPLAY_TIME ? time_buffer : "", DISPLAY_TIME ? " " : "");             \
                                                                               \
    /* display the level */                                                    \
    fprintf(LOG_STREAM, "%10s%s",                                              \
        DISPLAY_LEVEL ? level : "", DISPLAY_LEVEL ? " " : "");                 \
                                                                               \
    /* display the function doing the logging */                               \
    fprintf(LOG_STREAM, "%s%s",                                                \
        DISPLAY_FUNC ? func : "", DISPLAY_FUNC ? " " : "");                    \
                                                                               \
    /* display the file and/or the line number */                              \
    fprintf(LOG_STREAM,                                                        \
        "%s%s%s%.d%s%s",                                                       \
        DISPLAY_FUNC && (DISPLAY_FILE || DISPLAY_LINE) ? "(" : "",             \
        DISPLAY_FILE ? file : "",                                              \
        DISPLAY_FILE && DISPLAY_LINE ? ":" : "",                               \
        DISPLAY_LINE ? line : 0,                                               \
        DISPLAY_FUNC && (DISPLAY_FILE || DISPLAY_LINE) ? ") " : "",            \
        !DISPLAY_FUNC && (DISPLAY_FILE || DISPLAY_LINE) ? " " : ""             \
    );                                                                         \
                                                                               \
    /* display message border */                                               \
    fprintf(LOG_STREAM, "%s%s",                                                \
        DISPLAY_BORDER ? BORDER : "", DISPLAY_BORDER ? " " : "");              \
                                                                               \
    /* display the callee's message */                                         \
    if (DISPLAY_MESSAGE) fprintf(LOG_STREAM, __VA_ARGS__);                     \
                                                                               \
    /* add the message ending (usually '\n') */                                \
    fprintf(LOG_STREAM, "%s", DISPLAY_ENDING ? MSG_ENDING : "");               \
                                                                               \
    /* reset the colour */                                                     \
    fprintf(LOG_STREAM, "%s", DISPLAY_RESET ? RESET_COLOUR : "");              \
    fflush(LOG_STREAM);                                                        \
                                                                               \
} while (0)

/* Level enum */
#define DEBUG       0
#define INFO        1
#define NOTICE      2
#define WARNING     3
#define ERROR       4
#define CRITICAL    5
#define SILENT      6

/* DEBUG LOG */
#if LOG_LEVEL == DEBUG
#define debug(...)                                                             \
    emit_log(                                                                  \
        DEBUG_COLOUR, "[DEBUG]", __FILE__, __func__, __LINE__, __VA_ARGS__     \
    )
#else
#define debug(...)
#endif

/* INFO LOG */
#if LOG_LEVEL <= INFO
#define info(...)                                                              \
    emit_log(                                                                  \
        INFO_COLOUR, "[INFO]", __FILE__, __func__, __LINE__, __VA_ARGS__       \
    )
#else
#define info(...)
#endif

/* NOTICE LOG */
#if LOG_LEVEL <= NOTICE
#define notice(...)                                                            \
    emit_log(                                                                  \
        NOTICE_COLOUR, "[NOTICE]", __FILE__, __func__, __LINE__, __VA_ARGS__   \
    )
#else
#define notice(...)
#endif

/* WARNING LOG */
#if LOG_LEVEL <= WARNING
#define warning(...)                                                           \
    emit_log(                                                                  \
        WARNING_COLOUR, "[WARNING]", __FILE__, __func__, __LINE__, __VA_ARGS__ \
    )
#else
#define warning(...)
#endif

/* ERROR LOG */
#if LOG_LEVEL <= ERROR
#define error(...)                                                             \
    emit_log(                                                                  \
        ERROR_COLOUR, "[ERROR]", __FILE__, __func__, __LINE__, __VA_ARGS__     \
    )
#else
#define error(...)
#endif

/* CRITICAL LOG */
#if LOG_LEVEL <= CRITICAL
#define critical(...)                                                          \
    emit_log(                                                                  \
       CRITICAL_COLOUR, "[CRITICAL]", __FILE__, __func__, __LINE__, __VA_ARGS__\
    )
#else
#define critical(...)
#endif

#endif // seethe.h
