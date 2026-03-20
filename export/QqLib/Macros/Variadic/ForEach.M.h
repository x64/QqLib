#pragma once


// BASED ON: https://www.scs.stanford.edu/~dm/blog/va-opt.html
// On MSVC 2017  you need to add the "/experimental:preprocessor" compiler option
// On MSVC 2019+ you need to add the "/Zc:preprocessor" compiler option


#define QP_FOREACH_PARENS ()

#define QP_FOREACH_EXPAND(...)  QP_FOREACH_EXPAND4(QP_FOREACH_EXPAND4(QP_FOREACH_EXPAND4(QP_FOREACH_EXPAND4(__VA_ARGS__))))
#define QP_FOREACH_EXPAND4(...) QP_FOREACH_EXPAND3(QP_FOREACH_EXPAND3(QP_FOREACH_EXPAND3(QP_FOREACH_EXPAND3(__VA_ARGS__))))
#define QP_FOREACH_EXPAND3(...) QP_FOREACH_EXPAND2(QP_FOREACH_EXPAND2(QP_FOREACH_EXPAND2(QP_FOREACH_EXPAND2(__VA_ARGS__))))
#define QP_FOREACH_EXPAND2(...) QP_FOREACH_EXPAND1(QP_FOREACH_EXPAND1(QP_FOREACH_EXPAND1(QP_FOREACH_EXPAND1(__VA_ARGS__))))
#define QP_FOREACH_EXPAND1(...) __VA_ARGS__

#define QQ_FOREACH(macro,...)           __VA_OPT__(QP_FOREACH_EXPAND(QP_FOREACH_HELPER(macro,__VA_ARGS__)))
#define QP_FOREACH_HELPER(macro,a1,...) macro(a1) __VA_OPT__(QP_FOREACH_AGAIN QP_FOREACH_PARENS(macro,__VA_ARGS__))

//#define QP_FOREACH(macro,...)           QP_FOREACH_EXPAND(QP_FOREACH_HELPER(macro,__VA_ARGS__))
//#define QP_FOREACH_HELPER(macro,a1,...) macro(a1) QP_FOREACH_AGAIN QP_FOREACH_PARENS(macro,__VA_ARGS__)

#define QP_FOREACH_AGAIN()              QP_FOREACH_HELPER

//
// Example: QP_FOREACH(macro, a1, a2, a3, a4) => macro(a1), macro(a2), macro(a3), macro(a4)
// Note: the last element of the macro body must be "," (comma)
//
