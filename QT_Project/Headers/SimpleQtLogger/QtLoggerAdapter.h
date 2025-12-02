#pragma once

#include <QLoggingCategory>
#include <QMessageLogContext>
#include <QString>
#include <QtGlobal>

#include "ApiMacro.h"
#include "SimpleCppLogger/Logger.h"

namespace SimpleQtLogger
{
/**
 * @brief Maps a QtMsgType to the corresponding SimpleCppLogger::LogLevel.
 *
 * @param type The Qt message type (QtDebugMsg, QtInfoMsg, etc.).
 * @return The corresponding SimpleCppLogger::LogLevel.
 */
inline SIMPLEQTLOGGER_API auto map_qt_msg_type(QtMsgType type) -> SimpleCppLogger::LogLevel
{
    using namespace SimpleCppLogger;
    switch (type)
    {
    case QtDebugMsg:
        return LogLevel::Debug;
    case QtInfoMsg:
        return LogLevel::Info;
    case QtWarningMsg:
        return LogLevel::Warning;
    case QtCriticalMsg:
        return LogLevel::Error;
    case QtFatalMsg:
        return LogLevel::Fatal;
    default:
        return LogLevel::Info;
    }
}

/**
 * @brief Qt message handler that forwards messages to SimpleCppLogger.
 *
 * This function can be installed as the Qt message handler. It converts
 * Qt log messages to SimpleCppLogger log entries.
 *
 * @param type The Qt message type.
 * @param context The Qt message log context (file, line, function, category).
 * @param msg The log message.
 */
inline SIMPLEQTLOGGER_API auto qt_message_handler(QtMsgType type, const QMessageLogContext& context,
                                                  const QString& msg) -> void
{
    SimpleCppLogger::Logger::get_instance().log(map_qt_msg_type(type), msg.toStdString(),
                                                context.file, context.line, context.function,
                                                context.category);
}

/**
 * @brief Installs the Qt message handler to forward all Qt log messages to SimpleCppLogger.
 *
 * Call this function once during application initialization to enable logging redirection.
 */
inline SIMPLEQTLOGGER_API auto install_as_qt_message_handler() -> void
{
    qInstallMessageHandler(qt_message_handler);
}
}  // namespace SimpleQtLogger
