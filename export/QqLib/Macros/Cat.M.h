#pragma once


#define QQ_PP_CAT(a, b) QP_PP_CAT_I(a, b)

#define QP_PP_CAT_I(a, b) QP_PP_CAT_II(~, a ## b) //~ #define QP_PP_CAT_I(a, b) a ## b

#define QP_PP_CAT_II(p, res) res
