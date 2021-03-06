#-------------------------------------------------------------------------------
.SUFFIXES:
#-------------------------------------------------------------------------------

ifeq ($(strip $(DEVKITARM)),)
$(echo "Set DEVKITARM in your environment to build for Nintendo DS.")
include Makefile-opengl
else

export GAME_ICON    := $(CURDIR)/icon.bmp

LIBNDS	:=	$(DEVKITPRO)/libnds
export GAME_TITLE	:=	Tactics DS
GAME_SUBTITLE1	:=	by Mark Holland, Victor Grau and Lluis Ulzurrun
GAME_SUBTITLE2	:=	http://github.com/Sumolari/TacticsDS

include $(DEVKITARM)/ds_rules

#-------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
# DOXY is the command to generate documentation
# DOCDIR is the path where documentation will be stored
# DOXYFILE is the file with settings for documentation the generator
# MUSIC is the path where audio files are stored
#-------------------------------------------------------------------------------
TARGET		:=	$(shell basename $(CURDIR))
BUILD		:=	build
SOURCES		:=	assets src data
INCLUDES	:=	include build
DOXY        :=  doxygen
DOCDIR      :=  doc
DOXYFILE    :=  $(DOCDIR)/Doxyfile
MUSIC       :=  maxmod_data

#-------------------------------------------------------------------------------
# options for code generation
#-------------------------------------------------------------------------------
ARCH	:=	-mthumb -mthumb-interwork

CFLAGS	:=	-g -Wall -O2\
 			-march=armv5te -mtune=arm946e-s -fomit-frame-pointer\
			-ffast-math \
			-std=gnu++0x \
			-lboost \
			-DNDS \
			$(ARCH)

CFLAGS	+=	$(INCLUDE) -DARM9
CXXFLAGS	:= $(CFLAGS) -fexceptions

ASFLAGS	:=	-g $(ARCH)
LDFLAGS	=	-specs=ds_arm9.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)

#-------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#-------------------------------------------------------------------------------
LIBS	:= -lfat -lmm9 -lnds9


#-------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level
# containing include and lib
#-------------------------------------------------------------------------------
LIBDIRS	:=	$(LIBNDS)

#-------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add
# additional rules for different file extensions
#-------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#-------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir))
export DEPSDIR	:=	$(CURDIR)/$(BUILD)

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.bin))) soundbank.bin
PNGFILES    :=  $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.png)))
export AUDIOFILES	:=	$(foreach dir,$(notdir $(wildcard $(MUSIC)/*.*)),$(CURDIR)/$(MUSIC)/$(dir))

#-------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#-------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
#-------------------------------------------------------------------------------
	export LD	:=	$(CC)
#-------------------------------------------------------------------------------
else
#-------------------------------------------------------------------------------
	export LD	:=	$(CXX)
#-------------------------------------------------------------------------------
endif
#-------------------------------------------------------------------------------

export OFILES	:=	$(PNGFILES:.png=.o) $(BINFILES:.bin=.o) \
					$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)

export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
					-I$(CURDIR)/$(BUILD)

export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)

.PHONY: $(BUILD) clean doc

#-------------------------------------------------------------------------------
$(BUILD): $(AUDIOFILES)
	@rm -f $(TARGET).nds
	@[ -d $@ ] || mkdir -p $@
	@rm -f $(BUILD)/icon.bmp
	@cp $(GAME_ICON) $(BUILD)/icon.bmp
	@make --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#-------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(TARGET).elf $(TARGET).nds $(TARGET).ds.gba $(TARGET).test

#-------------------------------------------------------------------------------
doc:
	$(DOXY) $(DOXYFILE)

doc-%:
	$(DOXY) $(DOXYFILE).$*
#-------------------------------------------------------------------------------
test:
	g++ src/tests.cpp -std=gnu++0x -o$(TARGET).test -fexceptions -DTEST
	./$(TARGET).test

#-------------------------------------------------------------------------------

else

DEPENDS	:=	$(OFILES:.o=.d)

#-------------------------------------------------------------------------------
# main targets
#-------------------------------------------------------------------------------
$(OUTPUT).nds	: 	$(OUTPUT).elf
$(OUTPUT).elf	:	$(OFILES)

#-------------------------------------------------------------------------------
# rule to build soundbank from music files
#-------------------------------------------------------------------------------
soundbank.bin : $(AUDIOFILES)
#-------------------------------------------------------------------------------
	@mmutil $^ -d -osoundbank.bin -hsoundbank.h

#-------------------------------------------------------------------------------
# GRIT rule for converting the PNG files
#-------------------------------------------------------------------------------
%.s %.h : %.png %.grit
#-------------------------------------------------------------------------------
	@grit $< -fts

#-------------------------------------------------------------------------------
%.o	:	%.bin
#-------------------------------------------------------------------------------
	@echo $(notdir $<)
	$(bin2o)

#-------------------------------------------------------------------------------
# This rule links in binary data with the .bin extension
#-------------------------------------------------------------------------------
%.bin.o	:	%.bin
#-------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)


-include $(DEPENDS)

#-------------------------------------------------------------------------------
endif
#-------------------------------------------------------------------------------

endif
