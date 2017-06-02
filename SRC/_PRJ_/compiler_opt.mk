# =========================================================================
# ==
# == Version  : 0.00
# ==
# == Fonction : compiler_opt.mk for MALL.MK
# ==
# =========================================================================
# ==
# == Historic
# ==
# ==  21/09/15 : Creation
# ==
# =========================================================================
# ==
# == Dimension Informations
# == %PCMS_HEADER_SUBSTITUTION_START:%
# == PID format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Rev>
# == %PID:%
# == %PCMS_HEADER_SUBSTITUTION_END:%
# ==
# =========================================================================

#************************************************** VARIABLES
#
# AS	Program for compiling assembly files
# CC	Program for compiling C programs
# CPP	Program for running the C preprocessor, with results to standard output
# LD    Program for invoking the linker
# AR    Program for archiving object file to library
#
# ASFLAGS	Extra flags to give to the assembler
# CFLAGS	Extra flags to give to the C compiler.
# CPPFLAGS	Extra flags to give to the C preprocessor.
# LDFLAGS	Extra flags to give to compilers when they are supposed to invoke the linker
# ARFLAGS   Extra flags to give to archiver
#
#**************************************************

COMPILER_TOOLCHAIN_PATH=S:/HIGHTEC/toolchains/tricore/v4.6.3.1
#COMPILER_TOOLCHAIN_PATH=C:/TOOLS/HIGHTEC/toolchains/tricore/v4.6.3.1

AS=$(COMPILER_TOOLCHAIN_PATH)/bin/tricore-as
CC=$(COMPILER_TOOLCHAIN_PATH)/bin/tricore-gcc
CPP=$(COMPILER_TOOLCHAIN_PATH)/bin/tricore-gcc
AR=$(COMPILER_TOOLCHAIN_PATH)/bin/tricore-ar
LD=$(COMPILER_TOOLCHAIN_PATH)/bin/tricore-ld
ELF2HEX=$(COMPILER_TOOLCHAIN_PATH)/bin/tricore-objcopy -O ihex
ELF2MOT=$(COMPILER_TOOLCHAIN_PATH)/bin/tricore-objcopy -O srec
OBJDUMP=$(COMPILER_TOOLCHAIN_PATH)/bin/tricore-objdump

#**************************************************

TARGET=-mcpu=tc27xx

PLATFORM=

COMMONS_FLAGS =

ASFLAGS = --gdwarf-2

CDEFS = -DGNU -DTRIBOARD_TC27XX -D_GNU_C_TRICORE_

CEXTRA = \
	-freorder-blocks \
	-freorder-functions \
	-fshort-double \
	-fshort-enums \
	-fthread-jumps \
	-ftree-dce

CWARN = \
	-W \
	-Wall
	#-Werror

COPTS = -x c\
	-O3 \
	-fno-common \
	-gstrict-dwarf \
	-mno-version-info \
	-nostdlib \
	-nostartfiles \
	-B $(COMPILER_TOOLCHAIN_PATH)/tricore/lib \
	-msmall=0

CPREPRO = -save-temps=obj -I .

CDEBUG = -g3

#CFLAGS = $(COPTS) $(CDEFS) $(CEXTRA) $(CWARN) $(CPREPRO) -c -MMD
CFLAGS = $(COPTS) $(CDEFS) $(CEXTRA) $(CWARN) $(CPREPRO) $(CDEBUG) -c -MMD

CPPFLAGS=

ARFLAGS= rv

LOPTS = \
	--extmap="a" \
	-L $(COMPILER_TOOLCHAIN_PATH)/tricore/lib \
	--gc-sections \
	--print-gc-sections \
	-nodefaultlibs \
	-nostartfiles

LDFLAGS = $(LOPTS) -Map=$(BUILD_PATH)/$(EXEC).map -T$(LinkerFile)

#**************************************************

INCLUDES_PATH+=

#**************************************************
