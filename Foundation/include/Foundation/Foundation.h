#ifndef Foundation_Foundation_NotPoco_INCLUDED
#define Foundation_Foundation_NotPoco_INCLUDED


#if !defined(API)
    #if defined (__GNUC__) && (__GNUC__ >= 4)
        #define API __attribute__ ((visibility ("default")))
    #else
        #define API
    #endif
#endif


#endif
