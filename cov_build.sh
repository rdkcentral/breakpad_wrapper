##########################################################################
# If not stated otherwise in this file or this component's LICENSE
# file the following copyright and licenses apply:
#
# Copyright 2024 RDK Management
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
##########################################################################

WORKDIR=`pwd`

## Build and install critical dependency
export BREAKPAD_ROOT=/usr
export BREAKPAD_INSTALL_DIR=${BREAKPAD_ROOT}/local
mkdir -p $BREAKPAD_INSTALL_DIR
cd $BREAKPAD_ROOT


git clone https://github.com/google/breakpad.git

cd $BREAKPAD_ROOT/breakpad

git clone https://chromium.googlesource.com/linux-syscall-support src/third_party/lss/

cd $WORKDIR

export INSTALL_DIR='/usr/local'
export top_srcdir=`pwd`
export top_builddir=`pwd`

autoreconf --install

export CXXFLAGS="-I${BREAKPAD_ROOT}/breakpad/src/"

./configure --prefix=${INSTALL_DIR} && make && make install
