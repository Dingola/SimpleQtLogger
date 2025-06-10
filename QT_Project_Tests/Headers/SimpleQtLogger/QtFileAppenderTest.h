#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <source_location>
#include <string>

#include "SimpleCppLogger/LogAppender.h"
#include "SimpleCppLogger/LogLevel.h"
#include "SimpleCppLogger/Logger.h"
#include "SimpleQtLogger/QtFileAppender.h"

/**
 * @file QtFileAppenderTest.h
 * @brief Test fixture for SimpleQtLogger::QtFileAppender and its file logging functionality.
 */

class QtFileAppenderTest: public ::testing::Test
{
    protected:
        QtFileAppenderTest();
        ~QtFileAppenderTest() override;

        void SetUp() override;
        void TearDown() override;

        QString m_test_file_name;
        std::unique_ptr<SimpleQtLogger::QtFileAppender> m_file_appender;

        // Helper to read the file content
        auto read_file_content() const -> std::string;
};
