#pragma once


//
// Consts for m_wrappers.m_index
//

namespace Qq::Enum::Const
{


enum Mask : int
{
    invlaidValueMask  = 0x00ff0000,
    defaultValueMask  = 0x0000ff00,
    indexMask         = 0x000000ff
};

enum Shift : int
{
    invalidValueShift = 16,
    defaultValueShift = 8
};



} // namespace Qq::Enum::Const
