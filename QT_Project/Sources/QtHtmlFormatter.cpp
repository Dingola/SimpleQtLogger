#include "SimpleQtLogger/QtHtmlFormatter.h"

#include <QTextDocument>
#include <QTextStream>

namespace SimpleQtLogger
{
using namespace SimpleCppLogger;

QtHtmlFormatter::QtHtmlFormatter()
{
    // Set default colors
    m_level_colors[LogLevel::Debug] = "#888888";
    m_level_colors[LogLevel::Info] = "#0066CC";
    m_level_colors[LogLevel::Warning] = "#FFA500";
    m_level_colors[LogLevel::Error] = "#FF3333";
    m_level_colors[LogLevel::Fatal] = "#B20000";
}

auto QtHtmlFormatter::set_level_color(LogLevel level, const QString& color) -> void
{
    m_level_colors[level] = color;
}

auto QtHtmlFormatter::get_level_color(LogLevel level) const -> QString
{
    return m_level_colors.value(level, "#000000");
}

auto QtHtmlFormatter::format(const SimpleCppLogger::LogMessage& log_message,
                             const std::source_location& location) const -> std::string
{
    QString html;
    QTextStream stream(&html);

    QString level_str = QString::fromStdString(SimpleCppLogger::to_string(log_message.get_level()));
    QString color = get_level_color(log_message.get_level());
    QString message = QString::fromStdString(log_message.get_message()).toHtmlEscaped();
    QString file = QString::fromUtf8(location.file_name()).toHtmlEscaped();
    QString function = QString::fromUtf8(location.function_name()).toHtmlEscaped();
    int line = static_cast<int>(location.line());

    stream << "<div class=\"log-entry\">"
           << "<span class=\"log-level\" style=\"color:" << color << "; font-weight:bold;\">"
           << level_str << "</span> "
           << "<span class=\"log-message\">" << message << "</span> "
           << "<span class=\"log-meta\" style=\"color:#888888; font-size:small;\">"
           << "[" << file << ":" << line << " (" << function << ")]"
           << "</span>"
           << "</div>";

    return html.toStdString();
}

}  // namespace SimpleQtLogger
