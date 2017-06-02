/*INSERTION_TRADOIL*/
/**********************************************************************************************************************/
/*                                                                                                                    */
/* !Layer           : BSW                                                                                             */
/*                                                                                                                    */
/* !Component       : HAL                                                                                             */
/* !Description     : IOHAL Configuration                                                                             */
/*                                                                                                                    */           
/* !File            : IOHAL_Chk.tpl                                                                                   */
/*                                                                                                                    */
/* !Scope           : Public                                                                                          */
/*                                                                                                                    */
/* !Target          : Genecode Tool                                                                                   */
/*                                                                                                                    */
/* !Vendor          : Valeo                                                                                           */
/*                                                                                                                    */
/* Coding language  : Genecode                                                                                        */
/*                                                                                                                    */
/* COPYRIGHT 2013 VALEO                                                                                               */
/* all rights reserved                                                                                                */
/*                                                                                                                    */
/**********************************************************************************************************************/
/* Dimension Informations
 * %PCMS_HEADER_SUBSTITUTION_START:%
 * The PID has this format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
 * %PID:%
 * %PCMS_HEADER_SUBSTITUTION_END:%
**********************************************************************************************************************/


/*---------------------------------------------------------------------------------------------------------------------*/
/*     order channel                                                                                                   */
/*---------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                     */
/* output first                                                                                                        */
/*                                                                                                                     */
/*---------------------------------------------------------------------------------------------------------------------*/

IOHAL_CHANNEL WHERE(DIRECTION == "INPUT") CONCATE
{
  1 INTO DIR
}

IOHAL_CHANNEL WHERE(DIRECTION == "OUTPUT") CONCATE
{
  0 INTO DIR
}

IOHAL_CHANNEL ORDERBY(DIR) CONCATE
{
  counter() INTO INDEX
}


IOHAL_CHANNEL AS iohal_channel WHERE(SIGNAL_TYP != "") CONCATE
{
  WHERE (.IOHAL_TYP AS iohal_typ WHERE(iohal_typ == iohal_channel.SIGNAL_TYP) COUNT != 1)
  {
      Error(("SIGNAL_TYP " SIGNAL_TYP " from " iohal_channel " not found"))
  }
  {.IOHAL_TYP AS iohal_typ WHERE(iohal_typ == iohal_channel.SIGNAL_TYP) {TYPE_NAME} INTO SIGNAL_TYPE_NAME }
  {.IOHAL_TYP AS iohal_typ WHERE(iohal_typ == iohal_channel.SIGNAL_TYP) {TYPE_ABBR} INTO SIGNAL_TYPE_ABBR }
}

IOHAL_CHANNEL WHERE((DIRECTION == "INPUT") and (SIGNAL_TYPE_NAME == "")) CONCATE
{
  {LINKTO{RETURN_TYP.TYPE_NAME} INTO SIGNAL_TYPE_NAME}
  {LINKTO{RETURN_TYP.TYPE_ABBR} INTO SIGNAL_TYPE_ABBR}
}

IOHAL_CHANNEL WHERE((DIRECTION == "OUTPUT") and (SIGNAL_TYPE_NAME == "")) CONCATE
{
  {LINKTO{PARAM_TYP.TYPE_NAME} INTO SIGNAL_TYPE_NAME}
  {LINKTO{PARAM_TYP.TYPE_ABBR} INTO SIGNAL_TYPE_ABBR}
}


'

/*--------------------------------------------------- end of file ----------------------------------------------------*/
