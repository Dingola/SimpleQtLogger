#include "SimpleQtLogger/QtFileAppenderTest.h"

#include <QFile>
#include <QTextStream>
#include <cstdio>

using namespace SimpleCppLogger;
using namespace SimpleQtLogger;

/**
 * @brief Constructs the test fixture and sets a unique test file name.
 */
QtFileAppenderTest::QtFileAppenderTest(): m_test_file_name("QtFileAppenderTest.log") {}

/**
 * @brief Destroys the test fixture and removes the test file.
 */
QtFileAppenderTest::~QtFileAppenderTest()
{
    QFile::remove(m_test_file_name);
}

/**
 * @brief Sets up the test fixture by creating a new QtFileAppender and clearing the test file.
 */
void QtFileAppenderTest::SetUp()
{
    QFile::remove(m_test_file_name);
    m_file_appender = std::make_unique<QtFileAppender>(m_test_file_name);
}

/**
 * @brief Tears down the test fixture by destroying the appender and removing the test file.
 */
void QtFileAppenderTest::TearDown()
{
    m_file_appender.reset();
    QFile::remove(m_test_file_name);
}

/**
 * @brief Helper function to read the entire content of the test file.
 * @return The file content as a std::string.
 */
auto QtFileAppenderTest::read_file_content() const -> std::string
{
    QFile file(m_test_file_name);
    std::string result;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        result = in.readAll().toStdString();
    }
    else
    {
        result = {};
    }

    return result;
}

/**
 * @brief Tests that a log message is correctly written to the file.
 */
TEST_F(QtFileAppenderTest, LogMessageIsWrittenToFile)
{
    LogMessage log_message(LogLevel::Info, "File test message");
    m_file_appender->append(log_message, std::source_location::current());

    std::string content = read_file_content();
    EXPECT_NE(content.find("File test message"), std::string::npos);
}

/**
 * @brief Tests that multiple log messages are appended to the file.
 */
TEST_F(QtFileAppenderTest, MultipleMessagesAreAppended)
{
    LogMessage msg1(LogLevel::Info, "First message");
    LogMessage msg2(LogLevel::Warning, "Second message");
    m_file_appender->append(msg1, std::source_location::current());
    m_file_appender->append(msg2, std::source_location::current());

    std::string content = read_file_content();
    EXPECT_NE(content.find("First message"), std::string::npos);
    EXPECT_NE(content.find("Second message"), std::string::npos);
}

/**
 * @brief Tests that an empty message is handled and written to the file.
 */
TEST_F(QtFileAppenderTest, LogEmptyMessage)
{
    LogMessage log_message(LogLevel::Info, "");
    m_file_appender->append(log_message, std::source_location::current());

    std::string content = read_file_content();
    EXPECT_NE(content.find("\n"), std::string::npos);
}

/**
 * @brief Tests that a very long message is handled and written to the file.
 */
TEST_F(QtFileAppenderTest, LogVeryLongMessage)
{
    std::string long_message(10000, 'X');
    LogMessage log_message(LogLevel::Info, long_message);
    m_file_appender->append(log_message, std::source_location::current());

    std::string content = read_file_content();
    EXPECT_NE(content.find(long_message), std::string::npos);
}

/**
 * @brief Tests that the file is created if it does not exist.
 */
TEST_F(QtFileAppenderTest, FileIsCreatedIfNotExists)
{
    m_file_appender.reset();

    bool removed = QFile::remove(m_test_file_name);
    EXPECT_TRUE(removed || !QFile::exists(m_test_file_name));
    EXPECT_FALSE(QFile::exists(m_test_file_name));

    m_file_appender = std::make_unique<QtFileAppender>(m_test_file_name);

    LogMessage log_message(LogLevel::Info, "Create file test");
    m_file_appender->append(log_message, std::source_location::current());

    EXPECT_TRUE(QFile::exists(m_test_file_name));
    std::string content = read_file_content();
    EXPECT_NE(content.find("Create file test"), std::string::npos);
}

/**
 * @brief Tests that the file is closed on destruction.
 */
TEST_F(QtFileAppenderTest, FileIsClosedOnDestruction)
{
    {
        auto appender = std::make_unique<QtFileAppender>(m_test_file_name);
        LogMessage log_message(LogLevel::Info, "Closed on destruction");
        appender->append(log_message, std::source_location::current());
        // File should be open here
        EXPECT_TRUE(QFile(m_test_file_name).exists());
    }
    // After destruction, file should still exist and be readable
    std::string content = read_file_content();
    EXPECT_NE(content.find("Closed on destruction"), std::string::npos);
}

/**
 * @brief Tests that a custom formatter is used.
 */
TEST_F(QtFileAppenderTest, CustomFormatterIsUsed)
{
    class CustomFormatter: public LogFormatter
    {
        public:
            auto format(const LogMessage& message,
                        const std::source_location&) const -> std::string override
            {
                return "CUSTOM: " + message.get_message();
            }
    };

    auto custom_formatter = std::make_shared<CustomFormatter>();
    QtFileAppender custom_appender(m_test_file_name, custom_formatter);

    LogMessage log_message(LogLevel::Info, "Custom format message");
    custom_appender.append(log_message, std::source_location::current());

    std::string content = read_file_content();
    EXPECT_NE(content.find("CUSTOM: Custom format message"), std::string::npos);
}
