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

#ifndef CLIENT_LINUX_HANDLER_EXCEPTION_HANDLER_H_
#define CLIENT_LINUX_HANDLER_EXCEPTION_HANDLER_H_

#include <stdexcept>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace std;
using  ::testing::_;
using  ::testing::Return;
using  ::testing::StrEq;
using  ::testing::SetArgPointee;
using  ::testing::DoAll;
#include <iostream>
#include <stdexcept>

typedef struct {
  uint32_t data1;
  uint16_t data2;
  uint16_t data3;
  uint8_t  data4[8];
} MDGUID;  /* GUID */

namespace google_breakpad {
	
class MinidumpDescriptor {
 public:
  int getMiniDumpFileSize() ;
  void dump(const std::string& file_path, void* buffer) ;
  MinidumpDescriptor();
  MinidumpDescriptor(int);
  MinidumpDescriptor(const std::string );
  MinidumpDescriptor(const MinidumpDescriptor& descriptor);  
  MinidumpDescriptor& operator=(const MinidumpDescriptor& descriptor);
  protected:
  const MinidumpDescriptor  *descIns;
  int init;
};

typedef bool (*MinidumpCallback)(const MinidumpDescriptor& descriptor,
                                   void* context,
                                   bool succeeded);

class ExceptionHandler {
public:
    bool AddMappingInfo(const char* name, const void* identifier, uintptr_t start_address, size_t mapping_size, size_t file_offset) ;
    ExceptionHandler();
    ExceptionHandler(ExceptionHandler &);
    ExceptionHandler& operator=(const ExceptionHandler& descriptor);
    ExceptionHandler(const MinidumpDescriptor& descriptor,
		   void * cb,
                   MinidumpCallback callback,
                   void* callback_context,
                   bool install_handler,
                   const int server_fd) ;
protected :
   ExceptionHandler *Inst; 
   int init;    
};

}  // namespace google_breakpad

#endif
