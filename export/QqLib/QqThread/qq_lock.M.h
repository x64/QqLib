#pragma once

#include "./QqMutexGuard.h"

#ifndef QQ_LOCK_MUTEX_TYPE
    #define QQ_LOCK_MUTEX_TYPE  std::mutex
#else
    #define QQ_LOCK_MUTEX_TYPE  QMutex
#endif


#define qq_lock     if ( static QQ_LOCK_MUTEX_TYPE _qq_mutex; Qq::Thread::QqMutexGuard{ _qq_mutex } )
