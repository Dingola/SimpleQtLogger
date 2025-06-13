#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <source_location>
#include <string>

#include "ApiMacro.h"
#include "SimpleCppLogger/LogFormatter.h"

namespace SimpleQtLogger
{
/**
 * @class QtJsonFormatter
 * @brief Formats log messages as JSON objects using Qt.
 *
 * This formatter serializes log messages and their metadata (level, message, file, line, function)
 * into a compact JSON string using QJsonObject and QJsonDocument.
 */
class SIMPLEQTLOGGER_API QtJsonFormatter: public SimpleCppLogger::LogFormatter
{
    public:
        /**
         * @brief Constructs a QtJsonFormatter object.
         */
        QtJsonFormatter() = default;

        /**
         * @brief Formats the specified log message as a JSON string.
         *
         * The resulting JSON object contains the log level, message, file name, line number, and
         * function name.
         *
         * @param log_message The log message to format.
         * @param location The source location of the log message.
         * @return The formatted log message as a compact JSON string.
         */
        [[nodiscard]] auto format(
            const SimpleCppLogger::LogMessage& log_message,
            const std::source_location& location = std::source_location::current()) const
            -> std::string override;
};
}  // namespace SimpleQtLogger
