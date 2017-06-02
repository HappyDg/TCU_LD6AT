/**********************************************************************************************************************/
/*                                                                                                                    */
/* !Layer          : BSW                                                                                              */
/*                                                                                                                    */
/* !Component      : HAL                                                                                              */
/*                                                                                                                    */
/* !Module         : IOHAL                                                                                            */
/* !Description    : I/O hardware abstraction layer module.                                                           */
/*                                                                                                                    */
/* !File           : IOHAL.h                                                                                          */
/*                                                                                                                    */
/* !Target         : All                                                                                              */
/*                                                                                                                    */
/* !Vendor         : Valeo                                                                                            */
/*                                                                                                                    */
/* Coding language : C                                                                                                */
/*                                                                                                                    */
/* COPYRIGHT 2015 VALEO                                                                                               */
/* all rights reserved                                                                                                */
/*                                                                                                                    */
/**********************************************************************************************************************/
/* Dimension Informations
 * %PCMS_HEADER_SUBSTITUTION_START:%
 * The PID has this format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
 * %PID:%
 * %PCMS_HEADER_SUBSTITUTION_END:%
**********************************************************************************************************************/

#ifndef IOHAL_H
#define IOHAL_H

#define IOHWABS_udtWRITE_CHANNEL(snChannel, udtValue)     \
   IOHAL_vidWriteUdt_##snChannel(udtValue)

#define IOHWABS_udtREAD_CHANNEL(snChannel)                \
   IOHAL_udtRead_##snChannel()

#include "IOHAL_Api.h"

#endif /* IOHAL_H */

/*--------------------------------------------------- end of file ----------------------------------------------------*/
