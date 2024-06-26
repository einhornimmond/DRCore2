#include "DRCore2/DRCore2Main.h"
#include "DRCore2/Threading/DRMultithreadLogger.h"
#include "DRCore2/Manager/DRFileManager.h"

// Counter for dll use
int gCurrentNumUser = 0;
int gCurrentRun = 0;

DRMultithreadLogger DRLog;
#ifdef DEBUG
DRMultithreadLogger DRSpeedLog;
#endif


#ifdef _WIN32
#include <windows.h>
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            gCurrentNumUser++;
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            gCurrentNumUser--;
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
#endif



DRReturn Core2_init(const char* logFileName)
{
    //Logger init
    gCurrentRun++;
    DRLog.init(logFileName, true);
#ifdef PROFILING
    DRSpeedLog.init("SpeedLogger.html", false);
#endif
    LOG_INFO("Core2 init");
    DRFileManager::getSingleton().init();
    return DR_OK;
}


void Core2_exit()
{
    gCurrentRun--;
    DRFileManager::getSingleton().exit();
    LOG_INFO("Core2 exit");
#ifdef PROFILING
    DRSpeedLog.exit();
#endif
    DRLog.exit();
}
