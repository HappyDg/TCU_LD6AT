/*INSERTION_TRADOIL*/
/******************************************************************************/
/*                                                                            */
/* !Layer           : SRVL                                                    */
/*                                                                            */
/* !Component       : CCP                                                     */
/*                                                                            */
/* !Module          : CCPUSR_CHK                                              */
/* !Description     : Template of CCP Configuration check file (user part)    */
/*                                                                            */
/* !File            : CCPUSR_CHK.TPL                                          */
/*                                                                            */
/* !Scope           : Public                                                  */
/*                                                                            */
/* !Target          : Genecode Tool                                           */
/*                                                                            */
/* !Vendor          : Valeo                                                   */
/*                                                                            */
/* Coding language  : OIL                                                     */
/*                                                                            */
/* COPYRIGHT 2009 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/******************************************************************************/
/* PVCS Information                                                           */
/* $Archive::                                                                $*/
/* $Revision::                                                               $*/
/* $Author::                                          $$Date::               $*/
/******************************************************************************/
'/***************************** <AUTO_FILE_HEADER> *****************************/
/*                                                                            */
/* !Layer           : SRVL                                                    */
/*                                                                            */
/* !Component       : CCP                                                     */
/*                                                                            */
/* !Module          : CCPUSR_CHK                                              */
/* !Description     : Check configuration of the Component (user part)        */
/*                                                                            */
/* !File            : CCPUSR_CHK.RES                                          */
/*                                                                            */
/* !Target          : All                                                     */
/*                                                                            */
/* !Vendor          : Valeo                                                   */
/*                                                                            */
/* Coding language  : C                                                       */
/*                                                                            */
/* COPYRIGHT 2009 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/**************************** </AUTO_FILE_HEADER> *****************************/
/* PVCS Information                                                           */
/* $Arc`'hive::                                                                $*/
/* $Rev`'ision::                                                               $*/
/* $Aut`'hor::                                          $$Da`'te::               $*/
/******************************************************************************/
/* Generated on `Date()' by Genecode `Version()'                       */
/******************************************************************************/

`
/******************************************************************************/
/* CHECKS                                                                     */
/******************************************************************************/
/******************************************************************************/
/* If calibration page services are activated, default calibration page       */
/* address and extension shall be defined                                     */
/******************************************************************************/
CCP WHERE (CAL_PAGE_SERVICES = TRUE) CONCATE
{
   WHERE (IsAuto(DFLT_CALIB_PAGE_ADDR))
   {
      Error("Calibration page services activated: default calibration page address shall be defined.")
   }
   WHERE (IsAuto(DFLT_CALIB_PAGE_EXTN))
   {
      Error("Calibration page services activated: default calibration page address extension shall be defined.")
   }
}


"No error found
"

/******************************************************************************/
/* COMPUTATIONS                                                               */
/******************************************************************************/


/*-------------------------------- end of file -------------------------------*/