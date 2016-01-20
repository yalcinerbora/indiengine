##############################
# Indie Engine Main Makefile #
##############################

include Definitions.make

# Add New Projects Here
PROJECT_NAMES = \
IEUtility \
IEInput \
IEInputLINUX \
IERenderer \
IESystem \
IERendererGL \
IEFileLoaders \
Exec

# Project Configuration Targets
PROJECT_NAMES_DEBUG = $(addsuffix $(IE_DEBUG_CONF), $(PROJECT_NAMES))
PROJECT_NAMES_RELEASE = $(addsuffix $(IE_RELEASE_CONF), $(PROJECT_NAMES))
PROJECT_NAMES_CLEAN = $(addsuffix $(IE_CLEAN), $(PROJECT_NAMES))
PROJECT_NAMES_PURGE = $(addsuffix $(IE_PURGE), $(PROJECT_NAMES))

# Target Definitions 
#	all: 					Both Release and Debug Builds Are Compiled
#	allDebug: 				Only Debug Build Are Compiled
#	allRelease:				Only Release Build Are Compiled
#	clean:					Cleans Intermidiate Files (Libraries and Executabes Remains Intact)
#	purge:					Cleans Intermidiate Files and Actual Outputs
#
#	$(ProjectName):			Builds The Project (w/e its output is) with both configurations
#	$(ProjectName)Debug:	Builds The Project (w/e its output is) with Debug configurations
#	$(ProjectName)Release:	Builds The Project (w/e its output is) with Release configurations
#	$(ProjectName)Clean:	Cleans Projects Intermidiate Files (Actual Output Remains Intact)
#	$(ProjectName)Purge:	Cleans Projects Intermidiate Files and Its Actual Output

# Generic Rules
all: $(PROJECT_NAMES) Testall

allDebug: $(PROJECT_NAMES_DEBUG) TestallDebug

allRelease: $(PROJECT_NAMES_RELEASE) TestallRelease

clean: pchClean $(PROJECT_NAMES_CLEAN) Testclean

purge: pchClean $(PROJECT_NAMES_PURGE) Testpurge

# Directory Dependencies
dirDebug:
	@$(MKDIR) $(IE_DEBUG_FOLDER)

dirRelease:
	@$(MKDIR) $(IE_RELEASE_FOLDER)

# Project Matching Rules
$(PROJECT_NAMES): %: %Debug %Release

$(PROJECT_NAMES_DEBUG): dirDebug
	@echo "=================$(@:$(IE_DEBUG_CONF)=) $(IE_DEBUG_CONF)================="
	@$(MAKE) -f ./$(@:$(IE_DEBUG_CONF)=)/$(@:$(IE_DEBUG_CONF)=).make $@

$(PROJECT_NAMES_RELEASE): dirRelease
	@echo "================$(@:$(IE_RELEASE_CONF)=) $(IE_RELEASE_CONF)=============="
	@$(MAKE) -f ./$(@:$(IE_RELEASE_CONF)=)/$(@:$(IE_RELEASE_CONF)=).make $@
		
$(PROJECT_NAMES_CLEAN):
	@echo "=================$(@:$(IE_CLEAN)=) Clean================="
	@$(MAKE) -f ./$(@:$(IE_CLEAN)=)/$(@:$(IE_CLEAN)=).make $@

$(PROJECT_NAMES_PURGE):
	@echo "=================$(@:$(IE_PURGE)=) Purge================="
	@$(MAKE) -f ./$(@:$(IE_PURGE)=)/$(@:$(IE_PURGE)=).make $@

# Test Matching Rules
# Directly Pass It To the IETests.Make
Test%:
	@$(MAKE) -f ../../Test/Build/Linux/IETests.make $@

# All of The Targets Specified In this Makefile is a Phony!
.PHONY : all allDebug allRelease clean purge dirDebug dirRelease \
$(PROJECT_NAMES) \
$(PROJECT_NAMES_DEBUG) \
$(PROJECT_NAMES_RELEASE) \
$(PROJECT_NAMES_CLEAN) \
$(PROJECT_NAMES_PURGE)
