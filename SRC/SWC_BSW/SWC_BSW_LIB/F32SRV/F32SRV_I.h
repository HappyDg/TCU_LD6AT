/******************************************************************************/
/*                                                                            */
/* !Layer :             SRVL                                                  */
/*                                                                            */
/* !Component :         F32SRV                                                */
/* !Description :       Floating points services                              */
/*                                                                            */
/* !Module :            F32SRV                                                */
/* !Description :       Internal macro of the Component                       */
/*                                                                            */
/* !File :              F32SRV_I.h                                            */
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
/* $Archive::   I:/PROJETS/LIBEMB/LOG/SRV/F32SRV/LOG/F32SRV_I.h_v            $*/
/* $Revision::   1.0       $$Author::   lvoilmy    $$Date::   29 Oct 2008 10:$*/
/******************************************************************************/
/* !CompReq : FLOAT                                                           */
/******************************************************************************/



/******************************************************************************/
/* DEFINES                                                                    */
/******************************************************************************/
#define F32SRV_f32MIN_NORMALIZED_VALUE       1.1754943508222876e-38f
#define F32SRV_f32_ARE_INT_MIN_VALUE         8388608.0f  /* 8388608.0f = 2^23 */
#define F32SRV_f32UINT32_OVERFLOW_VALUE      4294967296.0f
#define F32SRV_f32SINT32_OVERFLOW_VALUE      2147483648.0f

/* FPSCR register defines                                                     */
#define F32SRV_bfFPSCR_ROUND_TO_NEAREST        0x00000000
#define F32SRV_bfFPSCR_INVALID_IT_DISABLE      0x00000000
#define F32SRV_bfFPSCR_DIV_BY_0_IT_DISABLE     0x00000000
#define F32SRV_bfFPSCR_OVERFLOW_IT_DISABLE     0x00000000
#define F32SRV_bfFPSCR_UNDERFLOW_IT_DISABLE    0x00000000
#define F32SRV_bfFPSCR_INEXACT_IT_DISABLE      0x00000000
#define F32SRV_bfFPSCR_DENORM_AS_ZERO          0x00040000

/* FPSCR register init value                                                  */
#define F32SRV_bfFPSCR_INIT_VALUE   F32SRV_bfFPSCR_ROUND_TO_NEAREST     |  \
                                    F32SRV_bfFPSCR_INVALID_IT_DISABLE   |  \
                                    F32SRV_bfFPSCR_DIV_BY_0_IT_DISABLE  |  \
                                    F32SRV_bfFPSCR_OVERFLOW_IT_DISABLE  |  \
                                    F32SRV_bfFPSCR_UNDERFLOW_IT_DISABLE |  \
                                    F32SRV_bfFPSCR_INEXACT_IT_DISABLE   |  \
                                    F32SRV_bfFPSCR_DENORM_AS_ZERO



/*-------------------------------- END OF FILE -------------------------------*/
