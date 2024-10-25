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

cd test

if [ "x$1" = "x--enable-cov" ]; then
      echo "Enabling coverage options"
      export CXXFLAGS="-g -O0 -fprofile-arcs -ftest-coverage"
      export CFLAGS="-g -O0 -fprofile-arcs -ftest-coverage"
      export LDFLAGS="-lgcov --coverage"
      ENABLE_COV=true
fi

autoreconf --install

export top_srcdir=`pwd`
mkdir ../client
mkdir ../client/linux
mkdir ../client/linux/handler
cp exception_handler.h ../client/linux/handler

#./configure --enable-gtestapp
./configure

#make -C test
make

rm -rf ../client

./bpw_gtest.bin

#### Generate the coverage report ####
if [ "$ENABLE_COV" = true ]; then
    echo "Generating coverage report"
    lcov --directory . --capture --output-file coverage.info
    lcov --remove coverage.info "${PWD}/source/test/*" --output-file coverage.info

    lcov --remove coverage.info "$HOME/usr/*" --output-file coverage.info
    lcov --remove coverage.info "/usr/*" --output-file coverage.info
fi
