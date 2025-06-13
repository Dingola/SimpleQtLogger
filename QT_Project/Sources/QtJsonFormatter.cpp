#include "SimpleQtLogger/QtJsonFormatter.h"

namespace SimpleQtLogger
{

auto QtJsonFormatter::format(const SimpleCppLogger::LogMessage& log_message,
                             const std::source_location& location) const -> std::string
{
    QJsonObject obj;
    obj["level"] = static_cast<int>(log_message.get_level());
    obj["message"] = QString::fromStdString(log_message.get_message());
    obj["file"] = location.file_name();
    obj["line"] = static_cast<int>(location.line());
    obj["function"] = location.function_name();

    QJsonDocument doc(obj);
    return doc.toJson(QJsonDocument::Compact).toStdString();
}

}  // namespace SimpleQtLogger
