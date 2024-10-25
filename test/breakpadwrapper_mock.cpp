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

#include <../client/linux/handler/exception_handler.h>

using namespace google_breakpad;

MinidumpDescriptor::MinidumpDescriptor() : init(50)
{

}	

MinidumpDescriptor::MinidumpDescriptor(const MinidumpDescriptor& descriptor) : init(50)
{
   descIns = &descriptor;	
}	
	 	
MinidumpDescriptor::MinidumpDescriptor(const std::string) : init(50)
{
   descIns = new MinidumpDescriptor();
}	

ExceptionHandler::ExceptionHandler() : init(60)
{

}

ExceptionHandler::ExceptionHandler(ExceptionHandler & eh) : init(60)
{
   Inst = &eh; 
}

ExceptionHandler::ExceptionHandler(const MinidumpDescriptor& descriptor, void * cb, MinidumpCallback callback, void* callback_context, bool install_handler, const int server_fd) : init(50) 
{

} 

bool ExceptionHandler::AddMappingInfo(const char* name, const void* identifier, uintptr_t start_address, size_t mapping_size, size_t file_offset) 
{
   return true;	
}	
