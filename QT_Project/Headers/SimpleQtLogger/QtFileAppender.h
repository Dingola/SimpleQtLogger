#pragma once

#include <QFile>
#include <QString>
#include <memory>

#include "ApiMacro.h"
#include "SimpleCppLogger/LogAppender.h"
#include "SimpleCppLogger/SimpleFormatter.h"

namespace SimpleQtLogger
{
/**
 * @class QtFileAppender
 * @brief A log appender that writes log messages to a file using Qt.
 *
 * This class appends formatted log messages to a file using QFile and QTextStream.
 * It uses a provided LogFormatter to format the log messages before writing.
 */
class SIMPLEQTLOGGER_API QtFileAppender: public SimpleCppLogger::LogAppender
{
    public:
        /**
         * @brief Constructs a QtFileAppender object.
         *
         * Opens the specified file for appending log messages. If no formatter is provided,
         * a default SimpleFormatter is used.
         *
         * @param file_name The name of the file to write log messages to.
         * @param formatter The LogFormatter object to use for formatting log messages.
         */
        explicit QtFileAppender(const QString& file_name,
                                const std::shared_ptr<SimpleCppLogger::LogFormatter>& formatter =
                                    std::make_shared<SimpleCppLogger::SimpleFormatter>());

        /**
         * @brief Destroys the QtFileAppender object.
         *
         * Closes the file if it is open.
         */
        ~QtFileAppender() override;

    private:
        /**
         * @brief Appends the specified log message to the file.
         *
         * This method formats the log message using the provided formatter and writes it to the
         * file.
         *
         * @param message The log message to append to the file.
         * @param location The source location of the log message.
         */
        auto internal_append(const SimpleCppLogger::LogMessage& message,
                             const std::source_location& location) -> void override;

    private:
        QFile m_file;  ///< The file to which log messages are written.
};
}  // namespace SimpleQtLogger
