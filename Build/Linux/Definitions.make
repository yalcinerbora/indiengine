
#################################
# IndiEngine Common Definitions #
#################################

SHELL = /bin/sh
MAKE = make --no-print-directory
ARCHIVE = ar
MKDIR = mkdir -p

.SUFFIXES:
.SUFFIXES: .o .cpp

# Compilers
CC = gcc
CXX = g++

# Configurations
IE_RELEASE_CONF = Release
IE_DEBUG_CONF = Debug

# Cleanup Target Names
IE_CLEAN = Clean
IE_PURGE = Purge

# Test Target Name
IE_TEST = Test
IE_TEST_LIB = gtest
IE_TEST_DEPENDENCY = pthread

# Folders
IE_MAIN_FOLDER = ../..
IE_BIN_FOLDER = $(IE_MAIN_FOLDER)/Bin/Linux
IE_BUILD_FOLDER = $(IE_MAIN_FOLDER)/Build/Linux
IE_SRC_FOLDER = $(IE_MAIN_FOLDER)/Source

IE_DEBUG_FOLDER = $(addprefix $(IE_BIN_FOLDER)/, $(IE_DEBUG_CONF))
IE_RELEASE_FOLDER = $(addprefix $(IE_BIN_FOLDER)/, $(IE_RELEASE_CONF))

# Test Folders
IE_TEST_FOLDER = $(IE_MAIN_FOLDER)/Test
IE_TEST_BIN_FOLDER = $(IE_TEST_FOLDER)/Bin/Linux
IE_TEST_BUILD_FOLDER = $(IE_TEST_FOLDER)/Build/Linux
IE_TEST_LIB_FOLDER = $(IE_TEST_FOLDER)/Lib/Linux
IE_TEST_SRC_FOLDER = $(IE_TEST_FOLDER)/Source

IE_TEST_DEBUG_FOLDER = $(addprefix $(IE_TEST_BIN_FOLDER)/, $(IE_DEBUG_CONF))
IE_TEST_RELEASE_FOLDER = $(addprefix $(IE_TEST_BIN_FOLDER)/, $(IE_RELEASE_CONF))

# Libraries That Comes with the Build
IE_LIB_FOLDER = $(IE_MAIN_FOLDER)/Lib/Linux
IE_LIB_FOLDER_INCLUDE = $(IE_LIB_FOLDER)/Include
IE_LIB_FOLDER_SHARED = $(IE_LIB_FOLDER)/Bin
IE_LIB_FOLDER_STATIC = $(IE_LIB_FOLDER)/x64

# PCH Stuff (Using Windows One)
PCH_NAME = stdafx.h
COMPILED_PCH_NAME = stdafx-pch.h

DEBUG_PCH_PATH = $(IE_DEBUG_FOLDER)/stdafx-pch.h.gch
RELEASE_PCH_PATH = $(IE_RELEASE_FOLDER)/stdafx-pch.h.gch

# Common Option Flags
# Summary
# ++64-bit compile
# ++C+11 Mandatory
# ++Include Dir += Sources Dir
# ++Include Dir += Library/Include Dir
# ++Library Search Dir += Lib/Shared
# ++Library Search Dir += Lib/Static
# ++Library Search Dir += Bin/Configuration
# ++Precompiled Headers
#
# Release Specific
# ++O3
# ++Link Time Optimization
#
# Debug Specific
# ++Debug Info
# ++Define IE_DEBUG
HEADERS_INCLUDE = -I$(IE_SRC_FOLDER) -I$(IE_LIB_FOLDER_INCLUDE)
LIBRARY_INCLUDE = -L$(IE_LIB_FOLDER_STATIC) -L$(IE_LIB_FOLDER_SHARED)

CXX_FLAGS_COMMON = -m64 -std=c++11 -Wall -Wextra -MMD -fPIC -include stdafx-pch.h
CXX_FLAGS_DEBUG = -I$(IE_DEBUG_FOLDER) $(HEADERS_INCLUDE) $(CXX_FLAGS_COMMON) -g -D IE_DEBUG -Winvalid-pch
CXX_FLAGS_RELEASE = -I$(IE_RELEASE_FOLDER) $(HEADERS_INCLUDE) $(CXX_FLAGS_COMMON) -O3 -flto

# Linker Stuff
LIBRARY_INCLUDE_DEBUG = $(LIBRARY_INCLUDE) -L$(IE_DEBUG_FOLDER)
LIBRARY_INCLUDE_RELEASE = $(LIBRARY_INCLUDE) -L$(IE_RELEASE_FOLDER)

# Some rpaths For Development Last rpath is for windowslike behaviour
LD_FLAGS_COMMON = -shared-libgcc -fPIC -Wl,-rpath,$(IE_LIB_FOLDER_SHARED),-rpath,.
LD_FLAGS_DEBUG = $(LD_FLAGS_COMMON) -Wl,-rpath,$(IE_DEBUG_FOLDER)
LD_FLAGS_RELEASE = -s $(LD_FLAGS_COMMON) -Wl,-rpath,$(IE_RELEASE_FOLDER)

# Test Related Flags And Lib Directories
LIBRARY_INCLUDE_TEST = -L$(IE_TEST_LIB_FOLDER)/x64
CXX_ADDITIONAL_TEST_FLAGS = -I$(IE_TEST_LIB_FOLDER)/Include

# PCH Rules
CXX_PCH_FILTER = -include stdafx-pch.h
CXX_FLAGS_PCH_DEBUG = $(filter-out $(CXX_PCH_FILTER), $(CXX_FLAGS_DEBUG))
CXX_FLAGS_PCH_RLEASE = $(filter-out $(CXX_PCH_FILTER), $(CXX_FLAGS_RELEASE))

$(DEBUG_PCH_PATH): $(IE_SRC_FOLDER)/$(PCH_NAME)
	@echo "Compiling Debug PCH..."
	@$(CXX) $(CXX_FLAGS_PCH_DEBUG) $(IE_SRC_FOLDER)/$(PCH_NAME) -o $(DEBUG_PCH_PATH)

$(RELEASE_PCH_PATH): $(IE_SRC_FOLDER)/$(PCH_NAME)
	@echo "Compiling Release PCH..."
	@$(CXX) $(CXX_FLAGS_PCH_RLEASE) $(IE_SRC_FOLDER)/$(PCH_NAME) -o $(RELEASE_PCH_PATH)

pchClean:
	@echo "Removing PCHs..."
	@rm -f $(DEBUG_PCH_PATH)
	@rm -f $(RELEASE_PCH_PATH)

# Dependencies of PCH
-include $(IE_DEBUG_FOLDER)/stdafx-pch.h.d
-include $(IE_RELEASE_FOLDER)/stdafx-pch.h.d