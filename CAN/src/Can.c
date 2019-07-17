/* Can.c: definition of CAN module API */

void Can_GetVersionInfo( Std_VersionInfoType* versioninfo)
{
  if (versioninfo == NULL_PTR)
  {
    #ifdef DEV_ERROR_DETECT_API
    (void)Det_ReportError(CAN_MODULE, CAN_ZERO, CAN_GETVERSIONINFO_ID,
      CAN_E_PARAM_POINTER);
    #endif
  }
  else
  {
    versioninfo->vendorID = NVD_VENDOR_ID;
    versioninfo->moduleID = CAN_MODULE;
    versioninfo->sw_major_version = SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = SW_MINOR_VERSION;
    versioninfo->sw_patch_version = SW_PATCH_VERSION;
  }
}

void Can_Init( )
{
  
}

void Can_DeInit( void)
{
  uint8 Luc_Count;
  for (Luc_Count = 0; Luc_Count < NUMBER_CAN_CONTROLLER; Luc_Count++)
  {
    Can_HwDeInit(Luc_Count);
  }
}

void Can_SetBaudrate()
{

}

void Can_SetControllerMode()
{

}


