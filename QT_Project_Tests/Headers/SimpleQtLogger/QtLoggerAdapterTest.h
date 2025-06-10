#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <source_location>
#include <string>

#include "SimpleCppLogger/LogAppender.h"
#include "SimpleCppLogger/LogLevel.h"
#include "SimpleCppLogger/Logger.h"
#include "SimpleQtLogger/QtLoggerAdapter.h"

/**
 * @file QtLoggerAdapterTest.h
 * @brief Test fixture for SimpleQtLogger::QtLoggerAdapter and its Qt integration.
 */

class MockLogAppender: public SimpleCppLogger::LogAppender
{
    public:
        MockLogAppender(): LogAppender() {}

        MOCK_METHOD(void, internal_append,
                    (const SimpleCppLogger::LogMessage& message,
                     const std::source_location& location),
                    (override));
};

class QtLoggerAdapterTest: public ::testing::Test
{
    protected:
        QtLoggerAdapterTest() = default;
        ~QtLoggerAdapterTest() override = default;

        void SetUp() override;
        void TearDown() override;

        std::shared_ptr<MockLogAppender> m_mock_appender;
};
