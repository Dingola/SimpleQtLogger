#include "SimpleQtLogger/QtFileAppender.h"

#include <QTextStream>

namespace SimpleQtLogger
{

/**
 * @brief Constructs a QtFileAppender object.
 *
 * Opens the specified file for appending log messages. If no formatter is provided,
 * a default SimpleFormatter is used.
 *
 * @param file_name The name of the file to write log messages to.
 * @param formatter The LogFormatter object to use for formatting log messages.
 */
QtFileAppender::QtFileAppender(const QString& file_name,
                               const std::shared_ptr<SimpleCppLogger::LogFormatter>& formatter)
    : LogAppender(formatter), m_file(file_name)
{
    m_file.open(QIODevice::Append | QIODevice::Text);
}

/**
 * @brief Destroys the QtFileAppender object.
 *
 * Closes the file if it is open.
 */
QtFileAppender::~QtFileAppender()
{
    m_file.close();
}

/**
 * @brief Appends the specified log message to the file.
 *
 * This method formats the log message using the provided formatter and writes it to the file.
 *
 * @param message The log message to append to the file.
 * @param location The source location of the log message.
 */
auto QtFileAppender::internal_append(const SimpleCppLogger::LogMessage& message,
                                     const std::source_location& location) -> void
{
    if (!m_file.isOpen())
    {
        m_file.open(QIODevice::Append | QIODevice::Text);
    }

    if (m_file.isOpen())
    {
        QTextStream out(&m_file);
        out << QString::fromStdString(m_formatter->format(message, location)) << '\n';
        out.flush();
    }
}

}  // namespace SimpleQtLogger
