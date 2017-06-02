#include "Std_Types.h"

/*********************************************************************************************/
/*Flash_trimDataBuf[index][] = {sint32 grd_grd,sint32 grd_ofs,sint32 ofs_grd,sint32 ofs_ofs};*/		
/*********************************************************************************************/
#define TLE8242_START_SEC_CALIB_UNSPECIFIED
#include "MemMap.h"
const sint32 Flash_trimDataBuf[8][4] = {{2,33612,669,446474},
								  {2,33612,669,446474},
								  {2,33612,669,446474},
								  {2,33612,669,446474},
								  {2,33612,669,446474},
								  {2,33612,669,446474},
								  {2,33612,669,446474},
								  {2,33612,669,446474}};
								  
#define TLE8242_STOP_SEC_CALIB_UNSPECIFIED
#include "MemMap.h"