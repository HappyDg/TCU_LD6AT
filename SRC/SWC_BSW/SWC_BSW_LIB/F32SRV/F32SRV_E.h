/******************************************************************************/
/*                                                                            */
/* !Layer :             SRVL                                                  */
/*                                                                            */
/* !Component :         F32SRV                                                */
/* !Description :       Floating points services                              */
/*                                                                            */
/* !Module :            F32SRV                                                */
/* !Description :       External macro of the Component                       */
/*                                                                            */
/* !File :              F32SRV_E.h                                            */
/*                                                                            */
/* !Scope :             Public                                                */
/*                                                                            */
/* !Target :            All                                                   */
/*                                                                            */
/* !Vendor :            Valeo                                                 */
/*                                                                            */
/* Coding language : C                                                        */
/*                                                                            */
/* COPYRIGHT 2008 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/******************************************************************************/
/* PVCS Information                                                           */
/* $Archive::   I:/PROJETS/LIBEMB/LOG/SRV/F32SRV/LOG/F32SRV_E.h_v            $*/
/* $Revision::   1.0       $$Author::   lvoilmy    $$Date::   29 Oct 2008 10:$*/
/******************************************************************************/
/* F32SRV.0 / F32SRV_vidInit                                                  */
/* F32SRV.1 / F32SRV_bIsNan                                                   */
/******************************************************************************/

#include "F32SRV_I.h"
#include "Std_Types.h"
#include "Micro.h"


/******************************************************************************/
/* MACRO FUNCTIONS                                                            */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/* !Description : Initialize the FPU of the Renesas SH725x microcontroller    */
/* !Number : 0                                                                */
/* !Reference : V01 NT 08 06040 #2                                            */
/* !Trace_To: VEMS_R_08_06040_029.01                                          */
/* !Trace_To: VEMS_R_08_06040_030.01                                          */
/* !Trace_To: VEMS_R_08_06040_031.01                                          */
/* !Trace_To: VEMS_R_08_06040_032.01                                          */
/* !Trace_To: VEMS_R_08_06040_033.01                                          */
/* !Trace_To: VEMS_R_08_06040_034.01                                          */
/*                                                                            */
/* !LastAuthor : J. Perochon                                                  */
/******************************************************************************/
#define F32SRV_vidInit() \
   set_fpscr(F32SRV_bfFPSCR_INIT_VALUE)


/******************************************************************************/
/*                                                                            */
/* !Description : Test if the parameter is not a number                       */
/* !Number : 1                                                                */
/* !Reference : V01 NT 08 06040 #1                                            */
/* !Trace_To: VEMS_R_08_06040_001.01                                          */
/*                                                                            */
/* !LastAuthor : J. Perochon                                                  */
/******************************************************************************/
#define F32SRV_bIsNan( \
   f32Data  /* !Comment: Data to test                                       */ \
) \
   /* !Deviation: Violation of MISRA Rule 13.3. Reason : The only way to    */ \
   /*             detect NaN is to compare it with itself                   */ \
   (boolean)((f32Data != f32Data) ? (boolean)TRUE : (boolean)FALSE )




/*-------------------------------- END OF FILE -------------------------------*/
