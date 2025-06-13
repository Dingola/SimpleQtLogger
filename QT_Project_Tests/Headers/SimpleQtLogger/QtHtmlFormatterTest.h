#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <source_location>
#include <string>

#include "SimpleCppLogger/LogLevel.h"
#include "SimpleCppLogger/LogMessage.h"
#include "SimpleQtLogger/QtHtmlFormatter.h"

/**
 * @file QtHtmlFormatterTest.h
 * @brief Test fixture for SimpleQtLogger::QtHtmlFormatter and its HTML formatting functionality.
 */
class QtHtmlFormatterTest: public ::testing::Test
{
    protected:
        QtHtmlFormatterTest() = default;
        ~QtHtmlFormatterTest() override = default;

        void SetUp() override {}
        void TearDown() override {}

        SimpleQtLogger::QtHtmlFormatter m_formatter;
};
