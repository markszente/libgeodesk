// Copyright (c) 2024 Clarisma / GeoDesk contributors
// SPDX-License-Identifier: LGPL-3.0-only

#include <clarisma/thread/Threads.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

namespace clarisma {

namespace Threads
{
    void kill(std::thread& thread)
    {
        #ifdef _WIN32
        HANDLE hThread = reinterpret_cast<HANDLE>(thread.native_handle());
        TerminateThread(hThread, 0);
        #elif defined(__ANDROID__)
        // pthread_cancel is not available on Android
        // The thread must terminate cooperatively
        // This is a no-op on Android - threads should be designed to exit gracefully
        // via cooperative cancellation mechanisms
        (void)thread; // Suppress unused parameter warning
        #else
        pthread_t nativeThread = thread.native_handle();
        pthread_cancel(nativeThread);
        #endif
    }
}
} // namespace clarisma
