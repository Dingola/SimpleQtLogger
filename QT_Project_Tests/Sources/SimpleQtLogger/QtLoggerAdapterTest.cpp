#include "SimpleQtLogger/QtLoggerAdapterTest.h"

#include <QMessageLogContext>
#include <QString>
#include <QtGlobal>

using namespace SimpleCppLogger;
using namespace SimpleQtLogger;

/**
 * @brief Sets up the test fixture by clearing appenders and adding a mock appender.
 */
void QtLoggerAdapterTest::SetUp()
{
    m_mock_appender = std::make_shared<MockLogAppender>();
    Logger::get_instance().clear_appenders();
    Logger::get_instance().add_appender(m_mock_appender);
    Logger::get_instance().set_log_level(LogLevel::Debug);
}

/**
 * @brief Tears down the test fixture by clearing appenders.
 */
void QtLoggerAdapterTest::TearDown()
{
    Logger::get_instance().clear_appenders();
    m_mock_appender.reset();
}

/**
 * @brief Tests that map_qt_msg_type maps all QtMsgType values correctly.
 */
TEST_F(QtLoggerAdapterTest, MapQtMsgType)
{
    EXPECT_EQ(map_qt_msg_type(QtDebugMsg), LogLevel::Debug);
    EXPECT_EQ(map_qt_msg_type(QtInfoMsg), LogLevel::Info);
    EXPECT_EQ(map_qt_msg_type(QtWarningMsg), LogLevel::Warning);
    EXPECT_EQ(map_qt_msg_type(QtCriticalMsg), LogLevel::Error);
    EXPECT_EQ(map_qt_msg_type(QtFatalMsg), LogLevel::Fatal);
    EXPECT_EQ(map_qt_msg_type(static_cast<QtMsgType>(9999)), LogLevel::Info);
}

/**
 * @brief Tests that qt_message_handler forwards messages to the logger.
 */
TEST_F(QtLoggerAdapterTest, QtMessageHandlerForwardsMessage)
{
    EXPECT_CALL(*m_mock_appender, internal_append(::testing::_, ::testing::_))
        .WillOnce([](const LogMessage& log_message, const std::source_location&) {
            EXPECT_EQ(log_message.get_level(), LogLevel::Info);
            EXPECT_EQ(log_message.get_message(), "Qt test message");
        });

    QMessageLogContext context;
    qt_message_handler(QtInfoMsg, context, QStringLiteral("Qt test message"));
}

/**
 * @brief Tests that qt_message_handler handles empty messages.
 */
TEST_F(QtLoggerAdapterTest, QtMessageHandlerHandlesEmptyMessage)
{
    EXPECT_CALL(*m_mock_appender, internal_append(::testing::_, ::testing::_))
        .WillOnce([](const LogMessage& log_message, const std::source_location&) {
            EXPECT_EQ(log_message.get_message(), "");
        });

    QMessageLogContext context;
    qt_message_handler(QtInfoMsg, context, QString());
}

/**
 * @brief Tests that qt_message_handler handles very long messages.
 */
TEST_F(QtLoggerAdapterTest, QtMessageHandlerHandlesLongMessage)
{
    std::string long_message(10000, 'Q');
    EXPECT_CALL(*m_mock_appender, internal_append(::testing::_, ::testing::_))
        .WillOnce([&](const LogMessage& log_message, const std::source_location&) {
            EXPECT_EQ(log_message.get_message(), long_message);
        });

    QMessageLogContext context;
    qt_message_handler(QtInfoMsg, context, QString::fromStdString(long_message));
}

/**
 * @brief Tests that qt_message_handler maps Qt log levels to SimpleCppLogger log levels.
 */
TEST_F(QtLoggerAdapterTest, QtMessageHandlerMapsLogLevels)
{
    struct LevelPair {
            QtMsgType qt_type;
            LogLevel cpp_level;
    };
    LevelPair levels[] = {{QtDebugMsg, LogLevel::Debug},
                          {QtInfoMsg, LogLevel::Info},
                          {QtWarningMsg, LogLevel::Warning},
                          {QtCriticalMsg, LogLevel::Error},
                          {QtFatalMsg, LogLevel::Fatal}};

    for (const auto& pair: levels)
    {
        EXPECT_CALL(*m_mock_appender, internal_append(::testing::_, ::testing::_))
            .WillOnce([expected_level = pair.cpp_level](const LogMessage& log_message,
                                                        const std::source_location&) {
                EXPECT_EQ(log_message.get_level(), expected_level);
            });

        QMessageLogContext context;
        qt_message_handler(pair.qt_type, context, QStringLiteral("Level test"));
        ::testing::Mock::VerifyAndClearExpectations(m_mock_appender.get());
    }
}

/**
 * @brief Tests that install_as_qt_message_handler installs the handler (smoke test).
 */
TEST_F(QtLoggerAdapterTest, InstallAsQtMessageHandler)
{
    EXPECT_NO_THROW(install_as_qt_message_handler());
}
