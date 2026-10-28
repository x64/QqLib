#pragma once

//
// This file must be included first for all MACRO files
//

// Variadics macro:
//#define BOOST_PP_LIMIT_VARIADIC 124

# if defined _MSC_VER && _MSC_VER >= 1400 && !defined(__clang__) && (defined(__INTELLISENSE__) || (defined(__INTEL_COMPILER) && __INTEL_COMPILER >= 1700) || !(defined __EDG__ || defined __GCCXML__ || defined __PATHSCALE__ || defined __DMC__ || defined __CODEGEARC__ || defined __BORLANDC__ || defined __MWERKS__ || defined __SUNPRO_CC || defined __HP_aCC || defined __MRC__ || defined __SC__ || defined __IBMCPP__ || defined __PGI)) && (!defined(_MSVC_TRADITIONAL) || _MSVC_TRADITIONAL)
#     define QQ_PP_VARIADICS_MSVC 1
# else
#     define QQ_PP_VARIADICS_MSVC 0
# endif


#if defined _MSC_VER
    #define QQ_FULL_FUNC_SIG    __FUNCSIG__
#else
    #define QQ_FULL_FUNC_SIG    __PRETTY_FUNCTION__
#endif
