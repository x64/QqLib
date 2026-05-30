#pragma once


#include "./_CompileConfig.h"
#include "./QqEnumString.h"
#include "./QqEnumStringLiteral.h"
#include "./MetadataT.h"
#include "../Exceptions/ParseException.h"


namespace Qq::Enum
{


///
/// \brief The core class for the QQ_ENUM macro.
/// All work with QqEnum should be here.
///
template <typename TClass, typename TEnum, typename TInt =int>
class CoreT
{
//
// Internal API
//
protected:

//
// Public API
//
public:

    //
    // Range API
    //

    static inline constexpr int
    toRange(int index, bool negativeIsAllow = true) noexcept
    {
        if (negativeIsAllow)
            toPositiveRange(index);

        index = std::max( 0, std::min(index, D::lastValidIndex()) );
        return index;
    }

    static inline constexpr void
    toPositiveRange(int & index) noexcept
    {
        index = index < 0
            ? D::lastValidIndex() + index +1
            : index;
    }

    //
    // \brief Searching \arg e in values and return its index. If e in not range then do throw.
    //
    static inline constexpr int
    ifEnumInNotRangeDoThrow(
        TEnum        e,
        char const * methodName)
    {
        auto it = D::eiMap().find(e);
        if (it == D::eiMap().end())
            qq_throw_l(
                std::out_of_range,
                QqEnumStringLiteral{ "The %1(as int) is not a member of enumeration %2\nMETHOD: %3" }
                    .arg(static_cast<TInt>(e))
                    .arg(D::className())
                    .arg(methodName)
                    .toLatin1()
            )

        return it->second;
    }

    // ret: if index in range then don't throws the exception
    static inline constexpr int
    ifIndexOutOfRangeDoThrow(
        int          index,
        char const * methodName,
        char const * paramName = "index")
    {
        if (D::indexInRange(index)) //-V3504
            return index;

        qq_throw_l(
            std::out_of_range,
            QqEnumStringLiteral{ "The %1 = %2 is out of range.\nMETHOD: %3" }
                .arg(paramName)
                .arg(index)
                .arg(methodName)
                .toLatin1()
        );
    }

    //
    // CTORs
    //

    static inline constexpr int
    ctor_index(int index, char const * methodName = nullptr) noexcept
    {
        return ifIndexOutOfRangeDoThrow(index, methodName ? methodName : QQ_FULL_FUNC_SIG);
    }

    static inline constexpr int
    ctor_enum(TEnum e, char const * methodName = nullptr) noexcept
    {
        return ifEnumInNotRangeDoThrow(e, methodName ? methodName : QQ_FULL_FUNC_SIG);
    }

    //
    // Assignment operators
    //

    static inline constexpr TClass &
    op_assignmentInt(TClass & c, TInt i, char const * methodName = nullptr) noexcept
    {
        return op_assignmentEnum(c, static_cast<TEnum>(i), methodName);
    }

    static inline constexpr TClass &
    op_assignmentEnum(TClass & c, TEnum e, char const * methodName = nullptr)
    {
        c.m_index = D::indexOf(e);
        if (Const::badIndex == c.m_index)
            qq_throw_l(
                std::out_of_range,
                QqEnumStringLiteral{ "The %1(as int) is not a member of enumeration %2\nMETHOD: %3" }
                    .arg(static_cast<TInt>(e))
                    .arg(D::className())
                    .arg(methodName ? methodName : QQ_FULL_FUNC_SIG)
                    .toLatin1()
            )

        return c;
    }

    static inline constexpr TClass &
    op_assignmentOther(TClass & lh, TClass const & rh, char const * methodName = nullptr) noexcept
    {
        lh.m_index = rh.m_index;
        ifIndexOutOfRangeDoThrow(lh.m_index, methodName ? methodName : QQ_FULL_FUNC_SIG);

        return lh;
    }

    //
    // ADD operators
    //

    static inline constexpr TClass &
    op_add(TClass & lh, TClass const & rh, char const * methodName = nullptr) noexcept
    {
        lh.m_index += rh.m_index;
        ifIndexOutOfRangeDoThrow(lh.m_index, methodName ? methodName : QQ_FULL_FUNC_SIG);

        return lh;
    }

    static inline constexpr TClass &
    op_add(TClass & lh, int n, char const * methodName = nullptr) noexcept
    {
        lh.m_index += n;
        ifIndexOutOfRangeDoThrow(lh.m_index, methodName ? methodName : QQ_FULL_FUNC_SIG);

        return lh;
    }

    //
    // ADD & assignment operators
    //

    static inline constexpr int
    op_add_assignment(int index, int n, char const * methodName = nullptr) noexcept
    {
        index += n;
        return ifIndexOutOfRangeDoThrow(index, methodName ? methodName : QQ_FULL_FUNC_SIG);
    }

    //
    // INC operator (only prefix)
    //

    static inline constexpr int
    op_inc(int index, char const * methodName = nullptr) noexcept
    {
        ++index;
        return ifIndexOutOfRangeDoThrow(index, methodName ? methodName : QQ_FULL_FUNC_SIG);
    }

    //
    // SUB operators
    //

    static inline constexpr TClass &
    op_sub(TClass & lh, TClass const & rh, char const * methodName = nullptr) noexcept
    {
        lh.m_index -= rh.m_index;
        ifIndexOutOfRangeDoThrow(lh.m_index, methodName ? methodName : QQ_FULL_FUNC_SIG);

        return lh;
    }

    static inline constexpr TClass &
    op_sub/*_asFriend*/(TClass & lh, int n, char const * methodName = nullptr) noexcept
    {
        lh.m_index -= n;
        ifIndexOutOfRangeDoThrow(lh.m_index, methodName ? methodName : QQ_FULL_FUNC_SIG);

        return lh;
    }

    //
    // ADD & assignment operators
    //

    static inline constexpr int
    op_sub_assignment(int index, int n, char const * methodName = nullptr) noexcept
    {
        index -= n;
        return ifIndexOutOfRangeDoThrow(index, methodName ? methodName : QQ_FULL_FUNC_SIG);
    }

    //
    // DEC operator (only prefix)
    //

    static inline constexpr int
    op_dec(int index, char const * methodName = nullptr) noexcept
    {
        --index;
        return ifIndexOutOfRangeDoThrow(index, methodName ? methodName : QQ_FULL_FUNC_SIG);
    }

    //
    // Comparsion operators
    //
    static inline constexpr bool
    op_compare(int index, TEnum e, char const * methodName = nullptr) noexcept
    {
        return index == ifEnumInNotRangeDoThrow(e, methodName ? methodName : QQ_FULL_FUNC_SIG);
    }


    //
    // Other
    //
    static constexpr int
    findNameIndex(char const * nameStr, bool caseInsensitive = true)
    {
        if (not nameStr) return -1;

        int index   = -1;
        int counter = 0;

    #ifdef QQ_DONT_USE_QT
        using H = Qq::Helpers::Main;
        std::string sFind{
            caseInsensitive
                ? H::toLower(H::trim(nameStr))
                : H::trim(nameStr)
        };

        for(auto const & name : D::nameList())
        {
            if (caseInsensitive)
            {
                std::string lowName{ name };
                if (sFind == H::toLower(lowName))
                {
                    index = counter;
                    break;
                }
            }
            else
            {
                if (sFind == name)
                {
                    index = counter;
                    break;
                }
            }

            ++counter;
        }
    #else
        QString sFind = QString{ nameStr }.trimmed();
        sFind = not caseInsensitive ? sFind : sFind.toLower();

        for(auto const & name : D::nameList())
        {
            if (caseInsensitive)
                if (sFind == name.toLower())
                {
                    index = counter;
                    break;
                }
            else
            {
                if (sFind == name)
                {
                    index = counter;
                    break;
                }
            }

            ++counter;
        }
    #endif

        return index;
    }

    static constexpr bool
    tryParse(
        char const * name,
        TClass     * out             = nullptr,
        bool         caseInsensitive = true
    )
        noexcept
    {
        int idx = findNameIndex(name, caseInsensitive);

        if (idx == Const::badIndex) return false;

        if (out) out->m_index = idx;

        return true;
    }

    static constexpr TClass
    parse(char const * name, bool caseInsensitive = true)
    {
        int idx = findNameIndex(name, caseInsensitive);

        if (idx == Const::badIndex)
            qq_throw_l(
                Qq::Exceptions::ParseException,
                QqEnumStringLiteral{ "The string '%1' was not found in the list of names of the '%2' enum when parsing.\nMETHOD: %3" }
                    .arg(name)
                    .arg(D::className())
                    .arg(QQ_FULL_FUNC_SIG)
                    .toLatin1()
            );

        TClass res{ idx };

        return res;
    }

//
// Using-synonyms
//
private:
    using D = MetadataT<TClass,TEnum,TInt>;
};


} // namespace Qq::Enum
