#=====================================================================================================
# Dimension Informations
# %PCMS_HEADER_SUBSTITUTION_START:%
# PID format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
# %PID:%
# %PCMS_HEADER_SUBSTITUTION_END:%
#=====================================================================================================
#
# Description : This makefile transfers files from the build folder to a package archive for "customers"
#                     Main target : T_all
#
#=====================================================================================================
#

PACKNAME = SWC_BSW
LIBRARYNAME = SWC_BSW.lib RTAOS.a
LIBHEADER = SWC_BSW_MAIN.c
ROOTDIR = ..
BUILDDIR= .
$(BUILD_PATH)

DEFINEFILE = define.mk
DEFINEFILEFROMDIR = $(addprefix $(BUILDDIR)/, $(DEFINEFILE))
-include $(DEFINEFILEFROMDIR)

#list of modules in the library that have a dictionnary. (defined by $(DEFINEFILEFROMDIR) )
MOD= $(SWC_BSW_LIBMOD) IOHAL DEVHAL

#list of objects in the library. (defined by $(DEFINEFILEFROMDIR) )
OBJS = 
LIBS = $(LIBRARYNAME) $(filter %.lib, $(SWC_BSW_LIBOBJS))

PACKDIR = $(PACKNAME)
PACKTODIR = $(PACKNAME).zip

OBJDIR=$(PACKDIR)/obj
OBJSFROMDIR      = $(addprefix $(BUILDDIR)/,$(OBJS))
OBJSTODIR        = $(addprefix $(OBJDIR)/,$(OBJS))

LIBDIR           = $(PACKDIR)/lib
LIBFROMDIR       = $(addprefix $(BUILDDIR)/, $(LIBS))
LIBTODIR         = $(addprefix $(LIBDIR)/, $(LIBS)) 

DICOFILETYPES    = donnee fonction refcdc requirements typedef
DICODONNEE       = $(addsuffix .txt,$(addprefix donnee_,$(MOD)))
DICOFONCTION     = $(addsuffix .txt,$(addprefix fonction_,$(MOD)))
DICOREFCDC       = $(addsuffix .txt,$(addprefix refcdc_,$(MOD)))
DICOREQUIREMENTS = $(addsuffix .txt,$(addprefix requirements_,$(MOD)))
DICOTYPEDEF      = $(addsuffix .txt,$(addprefix typedef_,$(MOD)))
DICO             = $(DICODONNEE) $(DICOFONCTION) $(DICOREFCDC) $(DICOREQUIREMENTS) $(DICOTYPEDEF)
DICODIR          = $(PACKDIR)/dico
DICOFROMDIR      = $(addprefix $(BUILDDIR)/, $(DICO))
DICOTODIR        = $(addprefix $(DICODIR)/, $(DICO))

DICOLIB          = $(addsuffix _$(PACKNAME).txt, $(DICOFILETYPES))
DICOLIBTODIR     = $(addprefix $(DICODIR)/,$(DICOLIB))

SRC       = SWC_BSW_MAIN.c SWC_BSW_MAIN_DEF.c SWC_BSW_MAIN.h SWC_BSW_MAIN_L.h MAIN_Msg.c MAIN_Msg.h DIO_WrapAPI.c DIO_WrapAPI.h TLE8242_wrapper.c TLE8242_wrapper.h Trim_8242_App.h Trim_8242_App.c donnee_MAIN.txt fonction_MAIN.txt refcdc_MAIN.txt requirements_MAIN.txt
SRCDIR    = $(PACKDIR)/src
SRCFROMDIR = $(addprefix $(BUILDDIR)/, $(SRC))
SRCTODIR    = $(addprefix $(SRCDIR)/, $(SRC))
SRCOBJS  = $(patsubst %.c,%.obj,$(filter %.c, $(SRCTODIR)))

INCLUDEDIR = $(PACKDIR)/include
LIBHEADERFROMDIR  = $(addprefix $(BUILDDIR)/, $(LIBHEADER))
LIBHEADERDEPTODIR = $(addprefix $(PACKDIR)/, $(addsuffix .mk, $(basename $(LIBHEADER))))
-include $(LIBHEADERDEPTODIR)
# INCLUDEDEPFROMDIR is defined by -include $(LIBHEADERDEPTODIR)
INCLUDEFROMDIR   = $(INCLUDEDEPFROMDIR) 
INCLUDETODIR = $(sort $(addprefix $(INCLUDEDIR)/, $(notdir $(INCLUDEFROMDIR))))

PROJECT = env_proj.ini compiler_opt.mk MALL.mk LinkerDef.ld convertcal.tfm geneulp.tfm SWA_BSW.ini memory_empty.int
PROJECTDIR    = $(PACKDIR)/prj
PROJECTFROMDIR = $(addprefix $(BUILDDIR)/, $(PROJECT))
PROJECTTODIR    = $(addprefix $(PROJECTDIR)/, $(PROJECT))

CFG         = *.oil
CFGDIR      = $(PACKDIR)/cfg
CFGFROMDIR  = $(addprefix $(BUILDDIR)/, $(CFG))
CFGTODIR    = $(addprefix $(CFGDIR)/, $(CFG))

BUILD_PATH =$(PACKDIR)

#************************************************** VARIABLES
# 
# AS    Program for compiling assembly files
# CC    Program for compiling C programs
# CPP  Program for running the C preprocessor, with results to standard output
# LD    Program for invoking the linker
# AR    Program for archiving object file to library
# 
# ASFLAGS   Extra flags to give to the assembler
# CFLAGS     Extra flags to give to the C compiler. 
# CPPFLAGS  Extra flags to give to the C preprocessor.
# LDFLAGS   Extra flags to give to compilers when they are supposed to invoke the linker
# ARFLAGS   Extra flags to give to archiver
# 
#**************************************************
.NOTPARALLEL:

#**************************************************
#**************************************************
LinkerFile=$(PROJECTDIR)\LinkerDef.ld

#**************************************************

INCLUDES_PATH+=

#**************************************************

COMPILER_OPT_FILE?=$(PROJECTDIR)\compiler_opt.mk
-include $(COMPILER_OPT_FILE)

#**************************************************

EXEC=SWA_BSW_DELIV

#************************************************** REGLES

.PHONY : T_clean T_objects T_dico T_cleardicomodules T_library T_main T_include T_clearincludedep T_projectfiles T_cfgfiles  T_zip T_clean T_libraryCheck

T_zip : T_objects T_include T_dico T_library T_main T_cfgfiles T_projectfiles $(PACKTODIR)
	echo End of Target  $@

$(PACKTODIR) : T_dico
	rm -f $@ 2>nul
	cmd /C "start /WAIT /MIN 7z a $@ $(PACKDIR)"
	echo move /Y $@ .. 
	move /Y $@ .. >nul

T_objects : $(OBJSTODIR)
	echo End of Target  $@

$(OBJSTODIR) : $(OBJSFROMDIR)
	install -D $(addprefix $(BUILDDIR)/,$(notdir $@)) ./$@

T_dico : $(DICOLIBTODIR) | T_cleardicomodules
	echo End of Target  $@

T_cleardicomodules : $(DICOLIBTODIR)
	rm $(DICOTODIR)
	echo End of Target  $@

$(DICOLIBTODIR) : |$(DICOTODIR)

$(DICOTODIR) : $(DICOFROMDIR)
	install -D $(addprefix $(BUILDDIR)/,$(notdir $@)) $@

$(DICODIR)/donnee_$(PACKNAME).txt : $(DICOTODIR)
	-cd $(subst /,\,$(DICODIR)) && S:\UTIL\grep -hS "|Type|Nom_module|Public|Nb_lignes|Nb_colonnes|" $(firstword $(filter donnee_%,$(DICO))) > $(notdir $@)
	-cd $(subst /,\,$(DICODIR)) && S:\UTIL\grep -hvS "|Type|Nom_module|Public|Nb_lignes|Nb_colonnes|" $(filter donnee_%,$(DICO)) >> $(notdir $@)
#	perl -pi.back -e "" $@

$(DICODIR)/fonction_$(PACKNAME).txt : $(DICOTODIR)
	-cd $(subst /,\,$(DICODIR)) && S:\UTIL\grep -hS "Nom_fonction|Release_fonction|Prototype|Num_stc|Nom_module|Public|" $(firstword $(filter fonction_%,$(DICO))) > $(notdir $@) 
	-cd $(subst /,\,$(DICODIR)) && S:\UTIL\grep -hvS "Nom_fonction|Release_fonction|Prototype|Num_stc|Nom_module|Public|" $(filter fonction_%,$(DICO)) >> $(notdir $@)
#	perl -pi.back -e "" $@

$(DICODIR)/refcdc_$(PACKNAME).txt : $(DICOTODIR)
	-cd $(subst /,\,$(DICODIR)) && S:\UTIL\grep -hS "R.f.rence_sp.cification|indice_sp.cification|intitul." $(firstword $(filter refcdc_%,$(DICO))) > $(notdir $@)
	-cd $(subst /,\,$(DICODIR)) && S:\UTIL\grep -hvS "R.f.rence_sp.cification|indice_sp.cification|intitul." $(filter refcdc_%,$(DICO)) >> $(notdir $@)
#	perl -pi.back -e "" $@

$(DICODIR)/requirements_$(PACKNAME).txt : $(DICOTODIR)
	-cd $(subst /,\,$(DICODIR)) && S:\UTIL\grep -hS "Name|Type|Requirement" $(firstword $(filter requirements_%,$(DICO))) > $(notdir $@)
	-cd $(subst /,\,$(DICODIR)) && S:\UTIL\grep -hvS "Name|Type|Requirement" $(filter requirements_%,$(DICO)) >> $(notdir $@)
#	perl -pi.back -e "" $@

$(DICODIR)/typedef_$(PACKNAME).txt : $(DICOTODIR)
	-cd $(subst /,\,$(DICODIR)) && S:\UTIL\grep -hS "Implement|ArgumentOrder|ItemType|Star|MasterType|ItemName|DimX|DimY|typedef_a_supprimer|Validation|Module|Public|Kind_of_export" $(firstword $(filter typedef_%,$(DICO))) > $(notdir $@)
	-cd $(subst /,\,$(DICODIR)) && S:\UTIL\grep -hvS "Implement|ArgumentOrder|ItemType|Star|MasterType|ItemName|DimX|DimY|typedef_a_supprimer|Validation|Module|Public|Kind_of_export" $(filter typedef_%,$(DICO)) >> $(notdir $@)
#	perl -pi.back -e "" $@

T_library :  $(LIBTODIR)
	echo End of Target  $@

$(LIBTODIR) : $(LIBFROMDIR)
	install -D $(addprefix $(BUILDDIR)/,$(notdir $@)) $@

T_main : $(SRCTODIR)
	echo End of Target  $@

$(SRCTODIR) : $(SRCFROMDIR)
	install -D $(addprefix $(BUILDDIR)/,$(notdir $@)) $@

T_include : $(INCLUDETODIR) | T_clearincludedep
	echo End of Target  $@

T_clearincludedep : $(INCLUDETODIR)
	rm -rf $(LIBHEADERDEPTODIR) $(LIBHEADERDEPTODIR)~

$(INCLUDETODIR) : $(INCLUDEFROMDIR) | $(INCLUDEDIR) $(LIBHEADERDEPTODIR) 
	-install -C $(filter %$(notdir $@),$(INCLUDEFROMDIR)) --target-directory=$(INCLUDEDIR)

$(LIBHEADERDEPTODIR) : $(LIBHEADERFROMDIR) | $(PACKDIR)
#	gnucpp -MM -I ./ -I $(BUILDDIR) $(INCLUDES_PATH) -D_GNU_C_TRICORE_ $(LIBHEADERFROMDIR) > $@
	gnucpp -M -nostdinc -I $(BUILDDIR) $(INCLUDES_PATH) -D_GNU_C_TRICORE_ $(LIBHEADERFROMDIR) > $@
	perl -pi~ -e "s/^[^\s].*\:/INCLUDEDEPFROMDIR = /" $@

T_projectfiles : $(PROJECTTODIR)
	echo End of Target  $@

$(PROJECTTODIR) : $(PROJECTFROMDIR) | $(PROJECTDIR)
	install -D  $(filter %$(notdir $@),$(PROJECTFROMDIR)) --target-directory=$(PROJECTDIR)

T_cfgfiles : $(CFGTODIR)
	echo End of Target  $@

$(CFGTODIR) : $(CFGFROMDIR) | $(CFGDIR)
	install -D  $(filter %$(notdir $@),$(CFGFROMDIR)) --target-directory=$(CFGDIR)

$(PACKDIR) :
	-mkdir $(subst /,\,$@) 2>nul

$(INCLUDEDIR) : $(PACKDIR)
	-mkdir $(subst /,\,$@) 2>nul

$(PROJECTDIR) : 
	-mkdir $(subst /,\,$@) 2>nul

$(CFGDIR) : 
	-mkdir $(subst /,\,$@) 2>nul

c : T_clean
T_clean :
	rm -r -f ./$(PACKDIR)

T_libraryCheck : $(SRCOBJS)
	echo $(LD) -$(TARGET) $(LDFLAGS) $(SRCOBJS) $(LIBTODIR) -o $(PACKDIR)\$(EXEC).elf
	$(LD) -$(TARGET) $(LDFLAGS) $(SRCOBJS) $(LIBTODIR) RTAOS.a -o $(PACKDIR)\$(EXEC).elf
	echo End of Target  $@

$(SRCOBJS) : $(SRCTODIR)
	echo $(CC) $(TARGET) $(CFLAGS) -I ./$(INCLUDEDIR) -o $@ $(filter %$(addsuffix .c, $(basename $(notdir $@))), $(SRCTODIR))
	$(CC) $(TARGET) $(CFLAGS) -I ./$(INCLUDEDIR) -o $@ $(filter %$(addsuffix .c, $(basename $(notdir $@))), $(SRCTODIR))
	echo End of Target  $(notdir $@)

