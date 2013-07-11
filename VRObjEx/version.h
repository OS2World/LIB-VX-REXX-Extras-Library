
#define DLLNAME "VROBJEX"

#define MINIMUM_VXREXX_LEVEL 210
#define LEVEL_ERRORMSG "This object library requires VX-REXX version 2.10 or higher."
#define LEVEL_TITLE "VROBJEX Object Library"

#define VERSION 112
#define VERSION_STRING "1.12"

#define VersionEntry _VROBJEX_VERSION_INFO_

#ifdef MAKELIB
#define SomInit    VROBJEX_SOMInitModule
#define SomUninit  VROBJEX_SOMUninitModule
#else
#define SomInit    SOMInitModule
#define SomUninit  SOMUninitModule
#endif

