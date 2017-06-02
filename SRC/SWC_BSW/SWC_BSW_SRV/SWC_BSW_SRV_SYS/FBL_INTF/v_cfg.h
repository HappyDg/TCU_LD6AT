/* -----------------------------------------------------------------------------
  Filename:    v_cfg.h
  Description: Toolversion: 06.02.00.01.50.02.99.00.00.00
               
               Serial Number: CBD1500299
               Customer Info: Valeo Systèmes de Contrôle Moteur
                              Package: FBL Vector SLP3 - for predevelopment projects without car manufacturer specific characteristics
                              Micro: TC265
                              Compiler: Hightec 4.6.3.1
               
               
               Generator Fwk   : GENy 
               Generator Module: GenTool_GenyVcfgNameDecorator
               
               Configuration   : C:\Vector\CBD1500299_D00_Tricore\Demo\DemoFbl\Config\CBD1500299-Mod-TC265.gny
               
               ECU: 
                       TargetSystem: Hw_TricoreCpu
                       Compiler:     ANSI-C
                       Derivates:    INFINEON_TC265
               
               Channel "Channel0":
                       Databasefile: D:\usr\usage\Delivery\CBD15x\CBD1500299\D00_work\external\Demo\DemoFbl\Config\DemoFBL_Vector_SLP3.dbc
                       Bussystem:    CAN
                       Manufacturer: Vector
                       Node:         Demo

 ----------------------------------------------------------------------------- */
/* -----------------------------------------------------------------------------
  C O P Y R I G H T
 -------------------------------------------------------------------------------
  Copyright (c) 2001-2015 by Vector Informatik GmbH. All rights reserved.
 
  This software is copyright protected and proprietary to Vector Informatik 
  GmbH.
  
  Vector Informatik GmbH grants to you only those rights as set out in the 
  license conditions.
  
  All other rights remain with Vector Informatik GmbH.
 -------------------------------------------------------------------------------
 ----------------------------------------------------------------------------- */

#if !defined(__V_CFG_H__)
#define __V_CFG_H__

#ifndef VGEN_GENY
#define VGEN_GENY
#endif

#ifndef GENy
#define GENy
#endif

#ifndef SUPPLIER_CANBEDDED
#define SUPPLIER_CANBEDDED                   30
#endif

/* -----------------------------------------------------------------------------
    &&&~ General Switches
 ----------------------------------------------------------------------------- */

#ifndef V_OSTYPE_NONE
#define V_OSTYPE_NONE
#endif



/* -----------------------------------------------------------------------------
    &&&~ Processor specific
 ----------------------------------------------------------------------------- */

#ifndef C_CPUTYPE_32BIT
#define C_CPUTYPE_32BIT
#endif


#ifndef V_CPUTYPE_BITARRAY_32BIT
#define V_CPUTYPE_BITARRAY_32BIT
#endif


#ifndef C_CPUTYPE_LITTLEENDIAN
#define C_CPUTYPE_LITTLEENDIAN
#endif


#ifndef C_CPUTYPE_BITORDER_LSB2MSB
#define C_CPUTYPE_BITORDER_LSB2MSB
#endif


#ifndef V_DISABLE_USE_DUMMY_FUNCTIONS
#define V_DISABLE_USE_DUMMY_FUNCTIONS
#endif


#ifndef V_ENABLE_USE_DUMMY_STATEMENT
#define V_ENABLE_USE_DUMMY_STATEMENT
#endif


#ifndef C_COMP_GNU_TRICORE_MULTICAN
#define C_COMP_GNU_TRICORE_MULTICAN
#endif


#ifndef V_CPU_TRICORE
#define V_CPU_TRICORE
#endif

#ifndef V_COMP_GNU
#define V_COMP_GNU
#endif

#ifndef V_COMP_GNU_TRICORE
#define V_COMP_GNU_TRICORE
#endif

#ifndef V_PROCESSOR_INFINEON_TC265
#define V_PROCESSOR_INFINEON_TC265
#endif


#ifndef C_PROCESSOR_INFINEON_TC265
#define C_PROCESSOR_INFINEON_TC265
#endif




/* -----------------------------------------------------------------------------
    &&&~ Used Modules
 ----------------------------------------------------------------------------- */

#define VGEN_ENABLE_XCP
/* FBL is enabled */
#define VGEN_ENABLE_CANFBL


#ifndef kVNumberOfIdentities
#define kVNumberOfIdentities                 1
#endif

#ifndef tVIdentityMsk
#define tVIdentityMsk                        vuint8
#endif

#ifndef kVIdentityIdentity_0
#define kVIdentityIdentity_0                 (vuint8) 0
#endif

#ifndef VSetActiveIdentity
#define VSetActiveIdentity(identityLog)
#endif

#ifndef V_ACTIVE_IDENTITY_MSK
#define V_ACTIVE_IDENTITY_MSK                1
#endif

#ifndef V_ACTIVE_IDENTITY_LOG
#define V_ACTIVE_IDENTITY_LOG                0
#endif


/* -----------------------------------------------------------------------------
    &&&~ Optimization
 ----------------------------------------------------------------------------- */

#ifndef V_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define V_ATOMIC_BIT_ACCESS_IN_BITFIELD      STD_OFF
#endif

#ifndef V_ATOMIC_VARIABLE_ACCESS
#define V_ATOMIC_VARIABLE_ACCESS             16
#endif



#ifndef C_CLIENT_VECTOR
#define C_CLIENT_VECTOR
#endif



/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 200089914
      #error "The magic number of the generated file <C:\Vector\CBD1500299_D00_Tricore\Demo\DemoFbl\Appl\GenData\v_cfg.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 200089914
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __V_CFG_H__ */
