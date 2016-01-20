###################################
# IndiEngine IEInputLINUX Project #
###################################

include Definitions.make

# The Name of the Project
PROJECT_NAME = IEInputLINUX

# Project Dependencies (Other IE Projects)
PROJECT_DEPENDENCIES = IEInput

# Libraries That It Requires (External Libs)
LIBS = X11 Xi

# Sources
SRCS = \
IEInputLINUX.cpp \
IEInputLINUXDLL.cpp \
IEKeyboardLINUX.cpp \
IEMouseLINUX.cpp

# Type ("Static" "Shared" or "Exec")
PROJECT_TYPE = Shared

# Additional Flags for the compilation of these soruces (Main Flags Are Defined In Definitions.make)
CXX_ADDITIONAL_FLAGS_COMMON = -D IEINPUTLINUX_EXPORT
CXX_ADDITIONAL_FLAGS_DEBUG_ONLY =
CXX_ADDITIONAL_FLAGS_RELEASE_ONLY =

#===========================================================================#
#===========================================================================#
#===========================================================================#
# Do not Touch Below
# Generate SRC Paths
PROJECT_SRC_DIR = $(addprefix $(IE_SRC_FOLDER)/, $(PROJECT_NAME))
SRC_PATHS = $(addprefix $(PROJECT_SRC_DIR)/, $(SRCS))

# Generate Additional Flags
CXX_ADDITIONAL_FLAGS_DEBUG = $(CXX_ADDITIONAL_FLAGS_COMMON) $(CXX_ADDITIONAL_FLAGS_DEBUG_ONLY)
CXX_ADDITIONAL_FLAGS_RELEASE = $(CXX_ADDITIONAL_FLAGS_COMMON) $(CXX_ADDITIONAL_FLAGS_RELEASE_ONLY)

# Generate Target Names
PROJECT_DEBUG_TARGET = $(addsuffix $(IE_DEBUG_CONF), $(PROJECT_NAME))
PROJECT_RELEASE_TARGET = $(addsuffix $(IE_RELEASE_CONF), $(PROJECT_NAME))
PROJECT_CLEAN_TARGET = $(addsuffix $(IE_CLEAN), $(PROJECT_NAME))
PROJECT_PURGE_TARGET = $(addsuffix $(IE_PURGE), $(PROJECT_NAME))

# Intermidiate Directory
PROJECT_DEBUG_INTER_DIR = $(addprefix $(IE_DEBUG_FOLDER)/, $(PROJECT_NAME))
PROJECT_RELEASE_INTER_DIR = $(addprefix $(IE_RELEASE_FOLDER)/, $(PROJECT_NAME))

# Generate DEP Paths
DEPS = $(SRCS:.cpp=.d)
DBG_DEPS = $(addprefix $(PROJECT_DEBUG_INTER_DIR)/, $(DEPS))
REL_DEPS = $(addprefix  $(PROJECT_RELEASE_INTER_DIR)/, $(DEPS))

# Generate OBJ Paths
OBJS = $(SRCS:.cpp=.o)
DBG_OBJS = $(addprefix $(PROJECT_DEBUG_INTER_DIR)/, $(OBJS))
REL_OBJS = $(addprefix $(PROJECT_RELEASE_INTER_DIR)/, $(OBJS))

# Generate Dependency Paths
PROJECT_DEPENDENCIES_DEBUG = $(addsuffix $(IE_DEBUG_CONF), $(PROJECT_DEPENDENCIES))
PROJECT_DEPENDENCIES_RELEASE = $(addsuffix $(IE_RELEASE_CONF), $(PROJECT_DEPENDENCIES))

# Generate Lib Flags
LIB_FLAGS = $(addprefix -l, $(LIBS))

# Resolve Prerequisite
ifeq ($(PROJECT_TYPE), Static)
PROJECT_OUTPUT = lib$(PROJECT_NAME).a
PROJECT_DEBUG_COMMAND = $(ARCHIVE) cr $(IE_DEBUG_FOLDER)/$(PROJECT_OUTPUT) $(DBG_OBJS)
PROJECT_RELEASE_COMMAND = $(ARCHIVE) cr $(IE_RELEASE_FOLDER)/$(PROJECT_OUTPUT) $(REL_OBJS)
#$(info $(PROJECT_NAME) Resolved as Static Lib)
else
ifeq ($(PROJECT_TYPE), Shared)
PROJECT_OUTPUT = lib$(PROJECT_NAME).so
PROJECT_DEBUG_COMMAND = $(CXX) -shared $(LD_FLAGS_DEBUG) $(DBG_OBJS) $(LIBRARY_INCLUDE_DEBUG) $(addprefix -l, $(PROJECT_DEPENDENCIES)) $(LIB_FLAGS) -o $(IE_DEBUG_FOLDER)/$(PROJECT_OUTPUT)
PROJECT_RELEASE_COMMAND = $(CXX) -shared $(LD_FLAGS_RELEASE) $(REL_OBJS) $(LIBRARY_INCLUDE_DEBUG) $(addprefix -l, $(PROJECT_DEPENDENCIES)) $(LIB_FLAGS) -o $(IE_RELEASE_FOLDER)/$(PROJECT_OUTPUT)
#$(info $(PROJECT_NAME) Resolved as Shared Lib)
else
ifeq ($(PROJECT_TYPE), Exec)
PROJECT_OUTPUT = $(PROJECT_NAME).exec
PROJECT_DEBUG_COMMAND = $(CXX) $(LD_FLAGS_DEBUG) $(DBG_OBJS) $(LIBRARY_INCLUDE_DEBUG) $(addprefix -l, $(PROJECT_DEPENDENCIES)) $(LIB_FLAGS) -o $(IE_DEBUG_FOLDER)/$(PROJECT_OUTPUT)
PROJECT_RELEASE_COMMAND = $(CXX) $(LD_FLAGS_RELEASE) $(REL_OBJS) $(LIBRARY_INCLUDE_DEBUG) $(addprefix -l, $(PROJECT_DEPENDENCIES)) $(LIB_FLAGS) -o $(IE_RELEASE_FOLDER)/$(PROJECT_OUTPUT)
#$(info $(PROJECT_NAME) Resolved as Executable)
else
$(error Unrecognized PROJECT_TYPE...)
endif
endif
endif

# Rules
# Entry Points
$(PROJECT_DEBUG_TARGET): dirDebug $(IE_DEBUG_FOLDER)/$(PROJECT_OUTPUT)

$(PROJECT_RELEASE_TARGET): dirRelease $(IE_RELEASE_FOLDER)/$(PROJECT_OUTPUT)

$(PROJECT_CLEAN_TARGET):
	@echo "Removing $(PROJECT_DEBUG_INTER_DIR)..."
	@rm -f -r $(PROJECT_DEBUG_INTER_DIR) ; /usr/bin/test "$$?" -eq 0
	@echo "Removing $(PROJECT_RELEASE_INTER_DIR)..."
	@rm -f -r $(PROJECT_RELEASE_INTER_DIR) ; /usr/bin/test "$$?" -eq 0

$(PROJECT_PURGE_TARGET): $(PROJECT_CLEAN_TARGET)
	@echo "Removing $(IE_DEBUG_FOLDER)/$(PROJECT_OUTPUT)..."
	@rm -f $(IE_DEBUG_FOLDER)/$(PROJECT_OUTPUT)
	@echo "Removing $(IE_RELEASE_FOLDER)/$(PROJECT_OUTPUT)..."
	@rm -f $(IE_RELEASE_FOLDER)/$(PROJECT_OUTPUT)

# Directory Dependencies
dirDebug:
	@$(MKDIR) $(PROJECT_DEBUG_INTER_DIR)

dirRelease:
	@$(MKDIR) $(PROJECT_RELEASE_INTER_DIR)

# Actual File Dependencies
$(IE_DEBUG_FOLDER)/$(PROJECT_OUTPUT) : $(PROJECT_DEPENDENCIES_DEBUG) $(DBG_OBJS)
	@echo "Creating $(PROJECT_OUTPUT) in $(IE_DEBUG_CONF)..."
#	#$(error "Provide Shared Library Link Command")
	@$(PROJECT_DEBUG_COMMAND)

$(IE_RELEASE_FOLDER)/$(PROJECT_OUTPUT) : $(PROJECT_DEPENDENCIES_RELEASE) $(REL_OBJS)
	@echo "Creating $(PROJECT_OUTPUT) in $(IE_RELEASE_CONF)..."
#	#$(error "Provide Shared Library Link Command")
	@$(PROJECT_RELEASE_COMMAND)

# Compilation of Individual Files
$(DBG_OBJS): $(PROJECT_DEBUG_INTER_DIR)/%.o: $(PROJECT_SRC_DIR)/%.cpp $(DEBUG_PCH_PATH)
	@echo "Compiling $< in Debug..."
	@$(CXX) $(CXX_ADDITIONAL_FLAGS_DEBUG) $(CXX_FLAGS_DEBUG) -o $@ -c $<

$(REL_OBJS): $(PROJECT_RELEASE_INTER_DIR)/%.o: $(PROJECT_SRC_DIR)/%.cpp $(RELEASE_PCH_PATH)
	@echo "Compiling $< in Release..."
	@$(CXX) $(CXX_ADDITIONAL_FLAGS_RELEASE) $(CXX_FLAGS_RELEASE) -o $@ -c $<

-include $(DBG_DEPS)
-include $(REL_DEPS)

# Dependency Compilation
$(PROJECT_DEPENDENCIES_DEBUG):
	@$(MAKE) -f ./$(@:$(IE_DEBUG_CONF)=)/$(@:$(IE_DEBUG_CONF)=).make $@

$(PROJECT_DEPENDENCIES_RELEASE):
	@$(MAKE) -f ./$(@:$(IE_RELEASE_CONF)=)/$(@:$(IE_RELEASE_CONF)=).make $@

.PHONY: dirDebug dirRelease \
$(PROJECT_DEBUG_TARGET) \
$(PROJECT_RELEASE_TARGET) \
$(PROJECT_CLEAN_TARGET) \
$(PROJECT_PURGE_TARGET) \
$(PROJECT_DEPENDENCIES_DEBUG) \
$(PROJECT_DEPENDENCIES_RELEASE)