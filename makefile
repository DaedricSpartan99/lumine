################################################################################
# ESP8266 makefile
################################################################################
# PROJECT SETTIGNS
# ------------------------------------------------------------------------------
PROJNAME := lumine
GITDIR   := $(shell pwd | sed 's:/projects.*::')

## hide commands
QUIET    := 1
ifeq ($(QUIET),1)
Q := @
else
Q := 
endif

# ------------------------------------------------------------------------------
# DIRECTORIES (NAME)
# ------------------------------------------------------------------------------
## project structure
BINDIR := bin
INCDIR := include
LIBDIR := lib
OBJDIR := obj
SRCDIR := src

PROJDIRS := $(BINDIR) $(INCDIR) $(LIBDIR) $(OBJDIR)/drivers $(SRCDIR)

# ------------------------------------------------------------------------------
# TOOLCHAIN LOCATION
# ------------------------------------------------------------------------------
## sdk root (espressif)
SDK_ROOT := $(GITDIR)/esp-open-sdk/sdk
## compiler root (xtensa)
XTENSA_ROOT := $(GITDIR)/esp-open-sdk/xtensa-lx106-elf/bin
## flash tool (esptool)
ESPTOOL_ROOT := $(GITDIR)/esptool-ck

# ------------------------------------------------------------------------------
# FILES (NAME)
# ------------------------------------------------------------------------------
## source files (automated)
SOURCES  := $(wildcard $(SRCDIR)/*.c)
## objects (automated)
OBJECTS  := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
## archive file
ARCHIVE  := $(LIBDIR)/$(PROJNAME).a
## elf (esecutable and linkable format) file
BINARY   := $(BINDIR)/$(PROJNAME).elf
## compiled firmware files (final)
FW_00000 := $(BINDIR)/$(PROJNAME)_0x00000.bin 
FW_40000 := $(BINDIR)/$(PROJNAME)_0x40000.bin

## for some reason the uart/spi/i2c/... drivers aren't compiled, so we need to
## compile them by hand (see recipe `drivers`)

## driver source files (uart/spi/...) (automated)
DRIVER_SOURCES_PATH := $(SDK_ROOT)/driver_lib/driver
DRIVER_SOURCES := $(wildcard $(DRIVER_SOURCES_PATH)/*.c)
## driver objects (automated)
DRIVER_OBJECTS := $(patsubst $(DRIVER_SOURCES_PATH)/%.c,\
						$(OBJDIR)/drivers/%.o,$(DRIVER_SOURCES))
## archive file
DRIVER_ARCHIVE := $(LIBDIR)/drivers.a

# ------------------------------------------------------------------------------
# COMPILER LOCATION
# ------------------------------------------------------------------------------
## compiler, librarian, linker
CC := $(XTENSA_ROOT)/xtensa-lx106-elf-gcc
AR := $(XTENSA_ROOT)/xtensa-lx106-elf-ar
LD := $(XTENSA_ROOT)/xtensa-lx106-elf-gcc
## flash tool (using igrr/esptool-ck from github)
ESPTOOL_CK := $(ESPTOOL_ROOT)/esptool

# ------------------------------------------------------------------------------
# FLAGS / SETTINGS
# ------------------------------------------------------------------------------
# linker script file
LD_SCRIPT 	:= -T$(SDK_ROOT)/ld/eagle.app.v6.ld
# libraries used (converted with a wildcard later)
LIBRARIES 	:= c gcc hal phy pp net80211 lwip wpa main crypto driver
## linker flags
LDFLAGS   	:=  -nostdlib -Wl,--no-check-sections \
				-u call_user_start -Wl,-static \
				-L$(SDK_ROOT)/lib -L$(LIBDIR)

## C compiler flags
CFLAGS 		:= 	-I$(INCDIR) -I$(SDK_ROOT)/include \
				-I$(SDK_ROOT)/driver_lib/include \
				-Os -g -O2 -Wpointer-arith -Wundef -Werror -Wl,-EL \
				-fno-inline-functions -nostdlib -mlongcalls \
				-mtext-section-literals -D__ets__ -DICACHE_FLASH 

# ------------------------------------------------------------------------------
# RECIPES / TARGETS
# ------------------------------------------------------------------------------
.PHONY: clean dirs drivers
all: $(FW_00000) $(FW_40000)
	@printf "\nFirmware compilation completed\n\n"

## copy the data from the binary (elf file) to make it readable for the ESP8266
## for more info look on github (esptool-ck)
$(FW_00000): $(BINARY)
	@printf "Compiling firmware:\t $@\n"
	$(Q) `# quiet mode y/n` \
	$(ESPTOOL_CK) -eo $(BINARY) -bo $@ -bs .text -bs .data -bs .rodata -bc -ec

## do a raw dump (copy) of the .irom0.text section
$(FW_40000): $(BINARY)
	@printf "Compiling firmware:\t $@\n"
	$(Q) $(ESPTOOL_CK) -eo $(BINARY) -es .irom0.text $@ -ec

## create an executable and linkable file (ELF)
$(BINARY): $(ARCHIVE)
	@printf "Creating ELF file:\t $@\n"
	$(Q) $(LD) $(LDFLAGS) $(LD_SCRIPT) -Wl,--start-group \
		$(addprefix -l,$(LIBRARIES)) $(ARCHIVE) \
		-Wl,--end-group -o $@

## create archive file
$(ARCHIVE): $(OBJECTS)
	@printf "Creating archive:\t $@\n"
	$(Q) $(AR) cru $@ $^

## compile source files to objects
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c $(SOURCES) dirs drivers
	@printf "Compiling source:\t $<  =>  $@\n"
	$(Q) $(CC) $(CFLAGS) -c $< -o $@

## drivers archive for uart/spi/i2c/...
drivers: $(DRIVER_OBJECTS)
	@printf "Creating archive:\t $(DRIVER_ARCHIVE)\n"
	$(Q) $(AR) cru $(DRIVER_ARCHIVE) $^
	@printf "\nDrivers compilation completed\n\n"

## compile drivers source files
$(DRIVER_OBJECTS): $(OBJDIR)/drivers/%.o : $(DRIVER_SOURCES_PATH)/%.c $(DRIVER_SOURCES)
	@printf "Compiling driver:\t $<  =>  $@\n"
	$(Q) $(CC) $(CFLAGS) -c $< -o $@

## clean up everything
clean:
	$(Q) rm -f $(OBJECTS) $(ARCHIVE) $(BINARY) $(FW_00000) $(FW_40000) \
				$(DRIVER_OBJECTS) $(DRIVER_ARCHIVE)

## generate project sturcture
dirs:
	$(Q) mkdir -p $(PROJDIRS)
