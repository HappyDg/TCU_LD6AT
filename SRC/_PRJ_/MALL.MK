# =========================================================================
# ==
# == Version  : 0.00
# ==
# == Fonction : Software generation: makefile for make.exe
# ==            Used by mall.bat
# ==
# =========================================================================
# ==
# == Historic
# ==
# ==  21/02/12 : Creation
# ==  21/09/15 : compiler_opt.mk usage
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

-include define.mk

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
#.NOTPARALLEL:

#**************************************************

COMPILER_TOOLCHAIN_PATH=

AS=$(COMPILER_TOOLCHAIN_PATH)/as
CC=$(COMPILER_TOOLCHAIN_PATH)/cc
CPP=$(COMPILER_TOOLCHAIN_PATH)/cpp
AR=$(COMPILER_TOOLCHAIN_PATH)/ar
LD=$(COMPILER_TOOLCHAIN_PATH)/ld

#**************************************************

TARGET=

COMMONS_FLAGS=

ASFLAGS= $(COMMONS_FLAGS)

CFLAGS= $(COMMONS_FLAGS) 

LDFLAGS= $(COMMONS_FLAGS)

ARFLAGS= 

#**************************************************

LinkerFile=LinkerDef.ld

#**************************************************

INCLUDES_PATH+=

BUILD_PATH+=.

#**************************************************

COMPILER_OPT_FILE?=compiler_opt.mk
-include $(COMPILER_OPT_FILE)

#**************************************************

EXEC=SWA_BSW

BASE_BD3 = CARACTAB.BD3 CARACTER.BD3 COMMENT.BD3 ENUMERE.BD3 GROUPES.BD3 REFERENC.BD3 REVISION.BD3 REVISTAB.BD3 REV_VER.BD3 VERSIONS.BD3
EXP_BASE_TXT = caractab.txt caractab2.txt caractab3.txt caracter.txt caracter2.txt caracter3.txt comment.txt comment2.txt comment3.txt enumere.txt enumere2.txt enumere3.txt groupes.txt groupes2.txt groupes3.txt referenc.txt referenc2.txt referenc3.txt
LINK_RSLT = $(EXEC).elf $(EXEC).mot $(EXEC).hex
#************************************************** REGLES

.SUFFIXES: .exe .elf .map .mot .hex .lib .a .obj .src .inc .h .cfg .c .asm .oil .stx .tpl .obx .tpx .s .txt .VCS .dld .ld .lcf .pl .BD3

.asm.obj:
	echo Assembly $<
	if exist $*.obj del $*.obj
	if exist $*.d del $*.d
	$(AS) $(ASFLAGS) -o $(BUILD_PATH)/$*.obj $<

.c.obj:
	echo Compile $<
	if exist $*.obj del $*.obj
	if exist $*.i del $*.i
	if exist $*.d del $*.d
	if exist $*.s del $*.s
	$(CC) $(TARGET) $(CFLAGS) $(INCLUDES_PATH) -o $(BUILD_PATH)/$*.obj $< 2>$(BUILD_PATH)/$*.warn || type $(BUILD_PATH)\$*.warn && FALSE

%.lib: $(LIBOBJS)
	echo Library Generation $@
	if exist $@ del $@
	$(AR) $(ARFLAGS) $@ $($(addsuffix _LIBOBJS,$*))

$(EXEC).elf: $(EXTLIBOBJS) $(addsuffix .lib,$(LIBNAMES)) $(LinkerFile) warning.csv
	echo Link $(EXEC)
	if exist $@ del $@
	if exist $(BUILD_PATH)/$(EXEC).map del $(BUILD_PATH)\$(EXEC).map
	$(LD) -$(TARGET) $(LDFLAGS) -o $(BUILD_PATH)/$(EXEC).elf -( $(EXTLIBOBJS) $(addsuffix .lib,$(LIBNAMES)) RTAOS.a -)
	$(OBJDUMP) -d $(BUILD_PATH)/$(EXEC).elf >$(BUILD_PATH)/$(EXEC).lst

$(EXEC).mot : $(EXEC).elf
	echo Convert $(EXEC).elf To $(EXEC).mot
	$(ELF2MOT) $(BUILD_PATH)/$(EXEC).elf $(BUILD_PATH)/$(EXEC).mot

$(EXEC).hex : $(EXEC).elf
	echo Convert $(EXEC).elf To $(EXEC).hex
	$(ELF2HEX) $(BUILD_PATH)/$(EXEC).elf $(BUILD_PATH)/$(EXEC).hex

warning.csv: $(OBJS) warning.pl
	perl warning.pl
	copy /Y $@ ..\SRC\_PRJ_ >nul

#**************************************************
bd3 : $(BASE_BD3)
$(wordlist 2,$(words $(BASE_BD3)),$(BASE_BD3)): $(firstword $(BASE_BD3))
$(firstword $(BASE_BD3)): $(LINK_RSLT) $(MODSRCS) $(EXP_BASE_TXT) *.rp2 convertcal.tfm
	echo GeneBase : build $@
	rem 1) change the data length of enum type in caracter.txt caracter2.txt and caracter3.txt
	rem 2) gbase : - convertcal (convert .mot to calib.int)
	rem            - convertmap (convert .map to .map for genebase but without change because genebase will use the elf file)
	rem            - genebase   (a2l and bd3 generation with calib.int and .elf)
	rem            - perl import_rp2.pl (create Rp2ToBd3List.txt for winades )
	rem            - winades @Rp2ToBd3List.txt
	perl -pi.bak -e "s/\|1\|0\|0\|1\|0\|Enum\|/\|2\|0\|0\|1\|0\|Enum\|/;" caracter.txt
	perl -pi.bak -e "s/\|0000\|0\|1\|0\|0\|1\|0\|\-\|4\|/\|0000\|0\|2\|0\|0\|1\|0\|\-\|4\|/;" caracter2.txt
	perl -pi.bak -e "s/\|1\|0\|Enum\|/\|2\|0\|Enum\|/;" caracter3.txt
	gbase

#**************************************************
$(EXEC).INITIAL.ulp : $(EXEC).hex $(BASE_BD3) geneulp.tfm
	geneulp -all -exe $(EXEC)
	echo Copy all generated files to Parent directory
	if exist ..\build copy /Y $(EXEC)*.* .. >NUL

#**************************************************

LIST_MOD LIST_STD LIST_OIL : lists
.SECONDARY:lists
lists : LIST_$(EXEC) LIST_SWC_BSW LIST_SWC_BSW_MCAL
	echo getlist -c $(EXEC) -sw
	getlist -c $(EXEC) -sw

#************************************************** CLEAR

clear :
	if exist $(BUILD_PATH)/*.obj del $(BUILD_PATH)\*.obj
	if exist $(BUILD_PATH)/*.i del $(BUILD_PATH)\*.i
	if exist $(BUILD_PATH)/*.d del $(BUILD_PATH)\*.d
	if exist $(BUILD_PATH)/*.s del $(BUILD_PATH)\*.s
	if exist $(BUILD_PATH)/$(EXEC).map del $(BUILD_PATH)\$(EXEC).map
	if exist $(BUILD_PATH)/$(EXEC).elf del $(BUILD_PATH)\$(EXEC).elf
	if exist $(BUILD_PATH)/$(EXEC).hex del $(BUILD_PATH)\$(EXEC).hex
	if exist $(BUILD_PATH)/$(EXEC).mot del $(BUILD_PATH)\$(EXEC).mot
	if exist $(BUILD_PATH)/define.mk del $(BUILD_PATH)\define.mk
	if exist $(BUILD_PATH)/obj.mk del $(BUILD_PATH)\obj.mk
	if exist $(BUILD_PATH)/xdm.mk del $(BUILD_PATH)\xdm.mk
	if exist $(BUILD_PATH)/oil.mk del $(BUILD_PATH)\oil.mk
	if exist $(BUILD_PATH)/donnee.txt del $(BUILD_PATH)\donnee.txt
	if exist $(BUILD_PATH)/fonction.txt del $(BUILD_PATH)\fonction.txt
	if exist $(BUILD_PATH)/refcdc.txt del $(BUILD_PATH)\refcdc.txt
ifneq "$(OILSRCS)" ""
	del $(OILSRCS)
endif
ifneq "$(XDMSRCS)" ""
	del $(XDMSRCS)
endif
ifneq "$(XMLSRCS)" ""
	del $(XMLSRCS)
endif
ifneq "$(DICOSRCS)" ""
	del $(DICOSRCS)
endif
	if exist LIST_* del LIST_*

#**************************************************
.PHONY: makefile
makefile :
	make -e -s -f mall.mk makelist
	echo MakeDepOil -d oil.mk -l LIST_OIL
	makedepoil -d oil.mk -l LIST_OIL
	echo MakeDef
	makedef
	make -e -s -f mall.mk genecode
	make -e -s -f mall.mk exportbase
	perl CheckFileName.pl -dir $(BUILD_PATH)

makelist: LIST_STD LIST_MOD LIST_OIL

exportbase : donnee.txt fonction.txt refcdc.txt typedef.txt requirements.txt cfgbdd.txt

genecode : $(OILSRCS)

#**************************************************

.PHONY: comp
comp: warning.csv $(OBJS)

.PHONY: link
link : $(EXEC).elf $(EXEC).hex

#**************************************************

.PHONY: base
base: bd3

.PHONY: ulp
ulp  : $(EXEC).INITIAL.ulp

.PHONY: deliv
deliv : SWC_BSW.zip
SWC_BSW.zip : $(EXEC).INITIAL.ulp 
	make -s -j -f DELIV_BSW.mk T_clean
	make -s -j -f DELIV_BSW.mk T_zip
	make -s -j -f DELIV_BSW.mk T_libraryCheck
	rem if exist SWC_BSW\*.elf make -s -j -f DELIV_BSW.mk T_clean

#**************************************************

-include $(patsubst %.obj,%.d,$(OBJS)) 
-include oil.mk
-include txt.mk
-include port.mk
-include dio.mk

#**************************************************

