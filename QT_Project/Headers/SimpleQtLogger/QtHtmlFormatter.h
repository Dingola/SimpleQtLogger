#pragma once

#include <QMap>
#include <QString>
#include <source_location>
#include <string>

#include "ApiMacro.h"
#include "SimpleCppLogger/LogFormatter.h"

namespace SimpleQtLogger
{
/**
 * @class QtHtmlFormatter
 * @brief Formats log messages as HTML strings with customizable colors per log level.
 *
 * This formatter serializes log messages and their metadata (level, message, file, line, function)
 * into an HTML string. Log levels are color-coded for better readability and can be customized.
 *
 * Each log entry is wrapped in a <div> with the class "log-entry". The log level, message, and meta
 * information are wrapped in <span> elements with the classes "log-level", "log-message", and
 * "log-meta" respectively. This allows for flexible styling via CSS.
 *
 * Example output:
 * @code{.html}
 * <div class="log-entry">
 *   <span class="log-level" style="color:#0066CC; font-weight:bold;">Info</span>
 *   <span class="log-message">This is an info message</span>
 *   <span class="log-meta" style="color:#888888; font-size:small;">[file.cpp:42 (function)]</span>
 * </div>
 * @endcode
 */
class SIMPLEQTLOGGER_API QtHtmlFormatter: public SimpleCppLogger::LogFormatter
{
    public:
        /**
         * @brief Constructs a QtHtmlFormatter object with default colors.
         */
        QtHtmlFormatter();

        /**
         * @brief Sets the color for a specific log level.
         * @param level The log level.
         * @param color The color as a CSS string (e.g. "#FF0000" or "red").
         */
        auto set_level_color(SimpleCppLogger::LogLevel level, const QString& color) -> void;

        /**
         * @brief Gets the color for a specific log level.
         * @param level The log level.
         * @return The color as a CSS string.
         */
        [[nodiscard]] auto get_level_color(SimpleCppLogger::LogLevel level) const -> QString;

        /**
         * @brief Formats the specified log message as an HTML string.
         *
         * The resulting HTML contains the log level, message, file name, line number, and function
         * name, with color highlighting based on the log level.
         *
         * The output uses the following CSS classes for styling:
         * - "log-entry" for the entire log entry (<div>)
         * - "log-level" for the log level (<span>)
         * - "log-message" for the log message (<span>)
         * - "log-meta" for file, line, and function information (<span>)
         *
         * @param log_message The log message to format.
         * @param location The source location of the log message.
         * @return The formatted log message as an HTML string.
         */
        [[nodiscard]] auto format(
            const SimpleCppLogger::LogMessage& log_message,
            const std::source_location& location = std::source_location::current()) const
            -> std::string override;

    private:
        QMap<SimpleCppLogger::LogLevel, QString> m_level_colors;
};
}  // namespace SimpleQtLogger
