# Copyright 2023 Comcast Cable Communications Management, LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# SPDX-License-Identifier: Apache-2.0
#

AM_CXXFLAGS = -std=c++14  -DGTEST_ENABLE -DGTEST_HAS_PTHREAD=0

AM_CFLAGS = -DGTEST_ENABLE -DGTEST_HAS_PTHREAD=0

ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = bpw_gtest.bin

bpw_gtest_bin_CPPFLAGS =  -I/usr/local/lib -I${top_srcdir}
bpw_gtest_bin_CPPFLAGS += -I${PKG_CONFIG_SYSROOT_DIR}/usr/src/googletest/googlemock/include
bpw_gtest_bin_CPPFLAGS += -I${RDK_PROJECT_ROOT_PATH}/$(GLIB_CFLAGS)

bpw_gtest_bin_SOURCES = gtest_main.cpp  breakpadwrapper_testing.cpp breakpadwrapper_mock.cpp ../breakpad_wrapper.cpp

bpw_gtest_bin_LDFLAGS = -L/usr/lib -lgmock -lgtest -lgtest_main -lgcov -lglib-2.0  -lpthread
