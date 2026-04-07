#pragma once


namespace Qq::Enum
{


template <typename TEnum, typename TInt =int>
struct EatAssignT
{
    constexpr EatAssignT() noexcept
    {}

    constexpr TInt toInt() const noexcept {
        return static_cast<TInt>(value);
    }

    constexpr operator TEnum () const noexcept {
        return value;
    }

    constexpr TEnum operator = (TInt) noexcept {
        return value;
    }

    constexpr EatAssignT & operator << (TEnum value)
    {
        this->value = value;
        return *this;
    }

    TEnum value;
};


} // namespace Qq::Enum
