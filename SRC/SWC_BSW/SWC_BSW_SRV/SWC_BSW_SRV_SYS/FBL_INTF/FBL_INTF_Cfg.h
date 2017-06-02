/******************************************************************************/
/* !Layer           : SRV                                                     */
/* !Component       : FBL_INTF                                                */
/* !Description     : Interface to the Flash Boot Loader                      */
/*                                                                            */
/* !File            : FBL_INTF_Cfg.h                                          */
/* !Description     :                                                         */
/*                                                                            */
/* !Reference       :                                                         */
/*                                                                            */
/* Coding language  : C                                                       */
/*                                                                            */
/* COPYRIGHT VALEO all rights reserved                                        */
/******************************************************************************/
/* Dimension Informations
 * %PCMS_HEADER_SUBSTITUTION_START:%
 * The PID has this format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
 * %PID:%
 * %PCMS_HEADER_SUBSTITUTION_END:%
 ******************************************************************************/

#ifndef FBL_INTF_CFG_H
#define FBL_INTF_CFG_H

#define RESETVECT cstart
#define FBL_PERMANENT_RESET_PTR_ADDR	0x80000440u

#endif /* FBL_INTF_CFG_H */

/*------------------------------- end of file --------------------------------*/
