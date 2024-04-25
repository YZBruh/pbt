# By YZBruh

# Copyright 2024 YZBruh - Partition Manager
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

# sources
SRCS := \
	$(SOURCE_DIR)/$(TARGET).c \
	$(SOURCE_DIR)/error.c     \
	$(SOURCE_DIR)/checkers.c  \
	$(SOURCE_DIR)/listpart.c  \
	$(SOURCE_DIR)/flash.c     \
	$(SOURCE_DIR)/backup.c    \
	$(SOURCE_DIR)/format.c    \
	$(SOURCE_DIR)/docs.c

# only the reason why the resource list is available is that:
# construction of a code was made with a different make sub-process in the old compilation logic. And then the built files were saved. And the main structure was created. But no longer needs it. According to new logic...