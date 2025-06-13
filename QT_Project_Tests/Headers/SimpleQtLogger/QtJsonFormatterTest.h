#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <source_location>
#include <string>

#include "SimpleCppLogger/LogLevel.h"
#include "SimpleCppLogger/LogMessage.h"
#include "SimpleQtLogger/QtJsonFormatter.h"

/**
 * @file QtJsonFormatterTest.h
 * @brief Test fixture for SimpleQtLogger::QtJsonFormatter and its JSON formatting functionality.
 */
class QtJsonFormatterTest: public ::testing::Test
{
    protected:
        QtJsonFormatterTest() = default;
        ~QtJsonFormatterTest() override = default;

        void SetUp() override {}
        void TearDown() override {}

        SimpleQtLogger::QtJsonFormatter m_formatter;
};
