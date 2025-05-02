/*
 * Copyright 2023 Comcast Cable Communications Management, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <signal.h>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../client/linux/handler/exception_handler.h"
#include "../breakpad_wrapper.h"
using namespace std;

class BreakpadAddMappingInfoTest : public ::testing::Test {
 protected:
  virtual void SetUp() { }
  virtual void TearDown() { }
};

class BreakpadExceptionHandlerTest : public ::testing::Test {
 //MockExceptionHandler* excHandler;    
  virtual void SetUp() { }
  virtual void TearDown() { }	
};	


TEST_F(BreakpadAddMappingInfoTest, PositiveTest) {
  // Valid inputs
  char name[] = "my_breakpad";
  char identifier[] = "my_ Identifier";
  size_t identifier_length = strlen(identifier);
  uintptr_t start_address = 0x12345678;
  size_t mapping_size = 100;
  size_t file_offset = 0;

  breakpad_AddMappingInfo(name, identifier, identifier_length, start_address, mapping_size, file_offset);
}

TEST_F(BreakpadAddMappingInfoTest, NegativeTest1) {
  // Invalid name
  char name[] = "";
  char identifier[] = "my_Identifier";
  size_t identifier_length = strlen(identifier);
  uintptr_t start_address = 0x12345678;
  size_t mapping_size = 100;
  size_t file_offset = 0;

  EXPECT_NO_THROW(breakpad_AddMappingInfo(name, identifier, identifier_length, start_address, mapping_size, file_offset));
}

TEST_F(BreakpadAddMappingInfoTest, NegativeTest2) {
  // Invalid identifier
  char name[] = "my_breakpad";
  char identifier[] = "";
  size_t identifier_length = 0;
  uintptr_t start_address = 0x12345678;
  size_t mapping_size = 100;
  size_t file_offset = 0;

  EXPECT_NO_THROW(breakpad_AddMappingInfo(name, identifier, identifier_length, start_address, mapping_size, file_offset));
}

TEST_F(BreakpadAddMappingInfoTest, NegativeTest3) {
  // Invalid start address
  char name[] = "my_breakpad";
  char identifier[] = "my_ Identifier";
  size_t identifier_length = strlen(identifier);
  uintptr_t start_address = 0x12345679;  // One byte overflow
  size_t mapping_size = 100;
  size_t file_offset = 0;

  EXPECT_NO_THROW(breakpad_AddMappingInfo(name, identifier, identifier_length, start_address, mapping_size, file_offset));
}

TEST_F(BreakpadAddMappingInfoTest, NegativeTest4) {
  // Invalid mapping size
  char name[] = "my_breakpad";
  char identifier[] = "my_ Identifier";
  size_t identifier_length = strlen(identifier);
  uintptr_t start_address = 0x12345678;
  size_t mapping_size = 0;  // Zero mapping size
  size_t file_offset = 0;

  EXPECT_NO_THROW(breakpad_AddMappingInfo(name, identifier, identifier_length, start_address, mapping_size, file_offset));
}


TEST_F(BreakpadAddMappingInfoTest, NegativeTest5) {
  // Invalid file offset
  char name[] = "my_breakpad";
  char identifier[] = "my_ Identifier";
  size_t identifier_length = strlen(identifier);
  uintptr_t start_address = 0x12345678;
  size_t mapping_size = 100;
  size_t file_offset = -1;  // Negative file offset

  EXPECT_NO_THROW(breakpad_AddMappingInfo(name, identifier, identifier_length, start_address, mapping_size, file_offset));
}

TEST_F(BreakpadAddMappingInfoTest, NegativeTest6) {
  // Null pointer for name
  char* name = nullptr;
  char identifier[] = "my_ Identifier";
  size_t identifier_length = strlen(identifier);
  uintptr_t start_address = 0x12345678;
  size_t mapping_size = 100;
  size_t file_offset = 0;

  EXPECT_NO_THROW(breakpad_AddMappingInfo(name, identifier, identifier_length, start_address, mapping_size, file_offset));
}

TEST_F(BreakpadAddMappingInfoTest, NegativeTest7) {
  // Null pointer for identifier
  char name[] = "my_breakpad";
  char* identifier = nullptr;
  size_t identifier_length = 0;
  uintptr_t start_address = 0x12345678;
  size_t mapping_size = 100;
  size_t file_offset = 0;

  EXPECT_NO_THROW(breakpad_AddMappingInfo(name, identifier, identifier_length, start_address, mapping_size, file_offset));
}

TEST_F(BreakpadAddMappingInfoTest, NegativeTest8) {
  // Both name and identifier are empty strings
  char name[] = "";
  char identifier[] = "";
  size_t identifier_length = 0;
  uintptr_t start_address = 0x12345678;
  size_t mapping_size = 100;
  size_t file_offset = 0;

  EXPECT_NO_THROW(breakpad_AddMappingInfo(name, identifier, identifier_length, start_address, mapping_size, file_offset));
}

TEST_F(BreakpadExceptionHandlerTest, PositiveTest2) {
 // call and make sure that  ExeceptionHandler is getting called.  
  breakpad_ExceptionHandler();
}
