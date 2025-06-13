#include "SimpleQtLogger/QtHtmlFormatterTest.h"

#include <QRegularExpression>
#include <QString>

/**
 * @brief Helper function to check if a substring exists in the HTML output.
 * @param html The HTML string.
 * @param substring The substring to search for.
 * @return True if substring is found, false otherwise.
 */
static bool html_contains(const std::string& html, const std::string& substring)
{
    return (html.find(substring) != std::string::npos);
}

/**
 * @brief Tests that a log message is formatted as valid HTML with expected structure.
 */
TEST_F(QtHtmlFormatterTest, FormatsValidHtml)
{
    SimpleCppLogger::LogMessage log_message(SimpleCppLogger::LogLevel::Info, "Html test message");
    std::string html = m_formatter.format(log_message, std::source_location::current());

    EXPECT_TRUE(html_contains(html, "<div"));
    EXPECT_TRUE(html_contains(html, "class=\"log-entry\""));
    EXPECT_TRUE(html_contains(html, "class=\"log-level\""));
    EXPECT_TRUE(html_contains(html, "class=\"log-message\""));
    EXPECT_TRUE(html_contains(html, "class=\"log-meta\""));
    EXPECT_TRUE(html_contains(html, "Html test message"));
}

/**
 * @brief Tests that the log level is correctly colorized and labeled.
 */
TEST_F(QtHtmlFormatterTest, SerializesLogLevelWithColor)
{
    SimpleCppLogger::LogMessage log_message(SimpleCppLogger::LogLevel::Warning, "Level color test");
    std::string html = m_formatter.format(log_message, std::source_location::current());

    EXPECT_TRUE(html_contains(html, "Warning"));
    EXPECT_TRUE(html_contains(html, "color:#FFA500"));
}

/**
 * @brief Tests that the log message is correctly HTML-escaped.
 */
TEST_F(QtHtmlFormatterTest, EscapesHtmlInMessage)
{
    std::string test_message = "<b>bold & test</b>";
    SimpleCppLogger::LogMessage log_message(SimpleCppLogger::LogLevel::Info, test_message);
    std::string html = m_formatter.format(log_message, std::source_location::current());

    // Should not contain raw <b> or & but their HTML-escaped equivalents
    EXPECT_FALSE(html_contains(html, "<b>"));
    EXPECT_TRUE(html_contains(html, "&lt;b&gt;bold &amp; test&lt;/b&gt;"));
}

/**
 * @brief Tests that the file name, line, and function are included in the HTML.
 */
TEST_F(QtHtmlFormatterTest, SerializesSourceLocation)
{
    auto location = std::source_location::current();
    SimpleCppLogger::LogMessage log_message(SimpleCppLogger::LogLevel::Info, "Location test");
    std::string html = m_formatter.format(log_message, location);

    EXPECT_TRUE(html_contains(html, location.file_name()));
    EXPECT_TRUE(html_contains(html, std::to_string(location.line())));
    EXPECT_TRUE(html_contains(html, location.function_name()));
}

/**
 * @brief Tests that an empty message is handled and included in the HTML.
 */
TEST_F(QtHtmlFormatterTest, SerializesEmptyMessage)
{
    SimpleCppLogger::LogMessage log_message(SimpleCppLogger::LogLevel::Info, "");
    std::string html = m_formatter.format(log_message, std::source_location::current());

    // The log-message span should still be present, even if empty
    EXPECT_TRUE(html_contains(html, "class=\"log-message\"></span>"));
}

/**
 * @brief Tests that a very long message is handled and included in the HTML.
 */
TEST_F(QtHtmlFormatterTest, SerializesVeryLongMessage)
{
    std::string long_message(10000, 'H');
    SimpleCppLogger::LogMessage log_message(SimpleCppLogger::LogLevel::Info, long_message);
    std::string html = m_formatter.format(log_message, std::source_location::current());

    EXPECT_TRUE(
        html_contains(html, long_message.substr(0, 100)));  // Check a substring for performance
}

/**
 * @brief Tests that custom colors can be set for log levels.
 */
TEST_F(QtHtmlFormatterTest, CustomLevelColorIsUsed)
{
    m_formatter.set_level_color(SimpleCppLogger::LogLevel::Error, "#123456");
    SimpleCppLogger::LogMessage log_message(SimpleCppLogger::LogLevel::Error, "Custom color test");
    std::string html = m_formatter.format(log_message, std::source_location::current());

    EXPECT_TRUE(html_contains(html, "color:#123456"));
}
