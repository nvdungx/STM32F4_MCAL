/*******************************************************************************
* File:         Can.c
* Revision:
* Author:
* Date:         02.08.2019
* Description:  definition of CAN module API
*******************************************************************************/

/*
 *  Service Name...... : Can_GetVersionInfo
 *  Service ID      .. : 0x00
 *  Sync/Async........ : Synchronous
 *  Reentrancy........ : Reentrant
 *  Parameters (IN)... : None
 *  Parameters (INOUT) : versioninfo
 *  Parameters (OUT).. : None
 *  Return Value...... : None
 *  Register usage     : 
 *  Global variable    : 
 *  Description....... : This function initializes the module.
 */
FUNC(void, CAN_CODE_SLOW) Can_GetVersionInfo (
  P2VAR(Std_VersionInfoType, AUTOMATIC, CAN_APPL_DATA) versioninfo)
{
  if (versioninfo == NULL_PTR)
  {
    #ifdef DEV_ERROR_DETECT_API
    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID,
      CAN_SID_GETVERSIONINFO, CAN_E_PARAM_POINTER);
    #endif
  }
  else
  {
    versioninfo->vendorID = CAN_VENDOR_ID;
    versioninfo->moduleID = CAN_MODULE;
    versioninfo->sw_major_version = SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = SW_MINOR_VERSION;
    versioninfo->sw_patch_version = SW_PATCH_VERSION;
  }
}

void Can_Init ( )
{
  
}

void Can_DeInit (void)
{
  uint8 Luc_Count;
  for (Luc_Count = 0; Luc_Count < NUMBER_CAN_CONTROLLER; Luc_Count++)
  {
    Can_HwDeInit(Luc_Count);
  }
}

void Can_SetBaudrate ()
{

}

void Can_SetControllerMode ()
{

}


