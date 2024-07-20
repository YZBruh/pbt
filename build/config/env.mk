# By YZBruh

# Copyright 2024 Partition Manager
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

#########################################
#                                       #
#          Configuration Flags          #
#                                       #
#         Warning: you can edit         #
#                                       #
#########################################

# speficy c compiler (cc)
PMT_CC ?= 

# speficy ar
PMT_AR ?= 

# addionital compiler flags
PMT_EXTRA_CFLAGS ?= -g 

# debugging mode (binary). it's enabling address sanitizer and source level debug information with dwarf version 5
PMT_ENABLE_DEBUG ?= 

#########################################
#########################################