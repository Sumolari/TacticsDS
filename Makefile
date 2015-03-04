ifeq ($(strip $(DEVKITARM)),)
include Makefile-opengl
else
include Makefile-nds
endif