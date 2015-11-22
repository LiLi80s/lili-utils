#*************************************************************************
# Copyright Liqun LIU [liulq80s@gmail.com]
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#***************************************************************************/
headers = message_queue.h message.h actor.h socket.h mutex.h 
source = socket.cpp
lib = -lstdc++
all : $(headers) $(source) main.cpp
	cc -o maintest main.cpp $(source) $(lib)
clean : 
	rm maintest
