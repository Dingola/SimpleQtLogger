#include "SimpleQtLogger/QtJsonFormatterTest.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

/**
 * @brief Helper function to parse a JSON string into a QJsonObject.
 * @param json_str The JSON string to parse.
 * @return The parsed QJsonObject.
 */
static QJsonObject parse_json(const std::string& json_str)
{
    QJsonDocument doc = QJsonDocument::fromJson(QString::fromStdString(json_str).toUtf8());
    return doc.object();
}

/**
 * @brief Tests that a log message is formatted as valid JSON.
 */
TEST_F(QtJsonFormatterTest, FormatsValidJson)
{
    SimpleCppLogger::LogMessage log_message(SimpleCppLogger::LogLevel::Info, "Json test message");
    std::string json = m_formatter.format(log_message, std::source_location::current());

    QJsonObject obj = parse_json(json);
    EXPECT_TRUE(obj.contains("level"));
    EXPECT_TRUE(obj.contains("message"));
    EXPECT_TRUE(obj.contains("file"));
    EXPECT_TRUE(obj.contains("line"));
    EXPECT_TRUE(obj.contains("function"));
}

/**
 * @brief Tests that the log level is correctly serialized.
 */
TEST_F(QtJsonFormatterTest, SerializesLogLevel)
{
    SimpleCppLogger::LogMessage log_message(SimpleCppLogger::LogLevel::Warning, "Level test");
    std::string json = m_formatter.format(log_message, std::source_location::current());

    QJsonObject obj = parse_json(json);
    EXPECT_EQ(obj["level"].toInt(), static_cast<int>(SimpleCppLogger::LogLevel::Warning));
}

/**
 * @brief Tests that the log message is correctly serialized.
 */
TEST_F(QtJsonFormatterTest, SerializesLogMessage)
{
    std::string test_message = "Hello JSON!";
    SimpleCppLogger::LogMessage log_message(SimpleCppLogger::LogLevel::Info, test_message);
    std::string json = m_formatter.format(log_message, std::source_location::current());

    QJsonObject obj = parse_json(json);
    EXPECT_EQ(obj["message"].toString().toStdString(), test_message);
}

/**
 * @brief Tests that the file name, line, and function are included in the JSON.
 */
TEST_F(QtJsonFormatterTest, SerializesSourceLocation)
{
    auto location = std::source_location::current();
    SimpleCppLogger::LogMessage log_message(SimpleCppLogger::LogLevel::Info, "Location test");
    std::string json = m_formatter.format(log_message, location);

    QJsonObject obj = parse_json(json);
    EXPECT_EQ(obj["file"].toString().toStdString(), location.file_name());
    EXPECT_EQ(obj["line"].toInt(), static_cast<int>(location.line()));
    EXPECT_EQ(obj["function"].toString().toStdString(), location.function_name());
}

/**
 * @brief Tests that an empty message is handled and serialized.
 */
TEST_F(QtJsonFormatterTest, SerializesEmptyMessage)
{
    SimpleCppLogger::LogMessage log_message(SimpleCppLogger::LogLevel::Info, "");
    std::string json = m_formatter.format(log_message, std::source_location::current());

    QJsonObject obj = parse_json(json);
    EXPECT_EQ(obj["message"].toString().toStdString(), "");
}

/**
 * @brief Tests that a very long message is handled and serialized.
 */
TEST_F(QtJsonFormatterTest, SerializesVeryLongMessage)
{
    std::string long_message(10000, 'J');
    SimpleCppLogger::LogMessage log_message(SimpleCppLogger::LogLevel::Info, long_message);
    std::string json = m_formatter.format(log_message, std::source_location::current());

    QJsonObject obj = parse_json(json);
    EXPECT_EQ(obj["message"].toString().toStdString(), long_message);
}
