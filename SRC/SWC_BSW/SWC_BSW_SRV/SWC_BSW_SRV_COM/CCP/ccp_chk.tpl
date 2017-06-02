/*INSERTION_TRADOIL*/
/******************************************************************************/
/*                                                                            */
/* !Layer           : SRVL                                                    */
/*                                                                            */
/* !Component       : CCP                                                     */
/*                                                                            */
/* !Module          : CCP_CHK                                                 */
/* !Description     : Template of CCP Configuration check file                */
/*                                                                            */
/* !File            : CCP_CHK.TPL                                             */
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
/* !Module          : CCP_CHK                                                 */
/* !Description     : Check configuration of the Component                    */
/*                                                                            */
/* !File            : CCP_CHK.RES                                             */
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
/* If DAQ list management is activated, at least one DAQ list and one event   */
/* shall be defined                                                           */
/******************************************************************************/
CCP WHERE (DAQ_LIST_SERVICES == TRUE) CONCATE
{
   WHERE (.DAQ_LIST COUNT == 0)
   {
      Error("At least one DAQ list shall be declared when DAQ list management is activated.")
   }
   WHERE (.DAQ_EVENT COUNT == 0)
   {
      Error("At least one event shall be declared when DAQ list management is activated.")
   }
}

/******************************************************************************/
/* If DAQ list management is activated, a maximum of 253 ODTs (all DAQ lists  */
/* included) can be configured                                                */
/******************************************************************************/
CCP WHERE (DAQ_LIST_SERVICES == TRUE) CONCATE
{
   WHERE (.DAQ_LIST SUM {NUMBER_OF_ODT} > 253.0)
   {
      Error("A maximum of 253 ODTs (all DAQ lists included) can be configured.")
   }
}

"No error found
"


/*-------------------------------- end of file -------------------------------*/