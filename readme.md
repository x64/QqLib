#### <div align="center">Goals of Creation<div>
There are many libraries for working with enums in C++. Each of them offers excellent features. However, there came a point when the following aspects became especially important to me:
1. Intuitive syntax, similar to, for example, Java or C#;
2. Normal reflection;
3. Declarativity;
4. Extensibility of the class or structure that contains the enum (i.e., the enum is not a standalone class, but is part of a class that can have other members, methods, structures, etc.);
5. Support for different IDEs.
6. Multithreading support for various addition/subtraction operations.
7. Small data storage size in ```QqEnum``` – ideally, a single machine word.
8. Complete reusability.

There was also a need for ease of integration. Ultimately, it wasn't entirely straightforward due to ```QqEnum``` being in the ```QqLib``` library. However, it was ultimately decided that QqEnum would be part of ```QqLib```, as I liked the concept and intend to develop it further.
```QqLib``` is developed using ```QtCreator```. Initially, it was an extension of the ```Qt``` library (hence the name – ```QqLib```). However, it was later decided to decouple it from ```Qt```. However, it can still be used with ```Qt``` (```QStringLiteral``` capabilities will be added to ```QqEnum``` if you remove the comment from the line "```//#undef QQ_DONT_USE_QT```" in the "```QqEnum/_CompileConfig.h```" file).
Regarding ```QqEnum```, I wanted it to be like this (and I wouldn't have to face any penalties for it):

```C++
struct EnumStruct
{
    QQ_ENUM(EnumStruct,
        None = 0,
        One,
        Two,
        Three,
        Four)
    QQ_ENUM_INVALID_VALUE(None) // defined an invalid value for this enum type.
    QQ_ENUM_DEFAULT_VALUE(One) // defined a default value for this enum type so that it is assigned immediately when the EnumStruct is created.
    _myMethod01();
    _myMethod02();
};
```

#### <div align="center">Rules for naming fields in QqEnum</div>
1. All enum element names are without underscores and can begin with either a capital or lowercase letter: ```None```, ```One```, ```one```, ```two```, etc.
2. Only internal methods, fields, types, etc. begin with an underscore: ```QqEnum``` (```_first()```, ```_last()```, etc.).
3. Public ```QqEnum``` types always begin with an underscore and then a CAPITAL letter (```_Enum```, ```_Class```, ```_Int```, etc.). Everything else begins with an underscore and a lowercase letter.

#### <div align="center">How to start using</div>
Download or clone the repository. Place the "```export/QqLib```" directory in a convenient location so you can include ```QqLib``` with the standard ```#include``` command: ```#include <QqLib/QqEnum.h>```

#### <div align="center">File naming style in the library</div>
The library uses regular ```.h``` and ```.cpp``` files with the suffixes "```.h```" and "```.cpp```" respectively.
The suffix "```.M.h```" denotes a header file with macros. This means that everything in it is a macro or macros.

#### <div align="center">Constants and types</div>
##### 1. Public.
```const bool _isQqEnum``` – indicates that this class contains ```QqEnum``` methods.
```_Class``` – class alias.
```_Enum``` – the enum itself (an enumeration).
```_Int``` – alias of the type from which ```_Enum``` derives (its size).
```_``` – alias for ```_Enum```. Required for proper operation of some IDEs.
```_Wrapper``` – alias for ```Qq::Enum::EnumItemWrapperT<_Enum,_Int>```.
```_Iterator``` – alias for ```Qq::Enum::IteratorT<_Class,_Enum,_Int>```.
```_IterationRange``` – alias for ```Qq::Enum::IterationRangeT<_Class,_Enum,_Int>```.

##### 2. Internal (protected / private)
```_C``` – alias for ```Qq::Enum::CoreT<_Class,_Enum,_Int>```.
```_D``` – alias for ```Qq::Enum::MetadataT<_Class,_Enum,_Int>```.
```_H``` – alias for ```Qq::Enum::Helper```.
```_EatAssign – alias for Qq::Enum::EatAssignT<_Enum, _Int>```.


#### <div align="center">Fields</div>
```static inline _D _d``` – stores ```QqEnum``` metadata. It's the same for all instances of the class, so it's static;
```Qq::Enum::Index m_index``` – stores the current index of ```_Enum``` in the current instance. This means the object doesn't store the actual value, but only the index within the array (vector) of ```_Enum``` values;


#### <div align="center">API</div>
##### 1. Metadata.
```char const * _className() noexcept``` – returns the name of the class containing ```QqEnum```.
```char const * _fullClassName() noexcept``` – returns the fully qualified name of the class.
```char const * _intTypeName() noexcept``` – returns the name of the type from which ```_Enum``` is derived.

##### 2. Boundaries.
```_Enum _first() noexcept``` – returns the first element in ```_Enum```.
```_Enum _last() noexcept``` – returns the last element in ```_Enum```.
```int _count() noexcept``` – returns the total number of elements in ```_Enum```.
```_Enum _min() noexcept``` – returns the element with the minimum value in ```_Enum```.
```_Enum _max() noexcept``` – returns the element with the maximum value in ```_Enum```.

##### 3. Names and values.
(The current value is specified through the ```m_index``` field)
```_Int _int() const noexcept``` – returns the current value as an ```_Int```.
```_Enum _value() const noexcept``` – returns the current value as an ```_Enum```.
```QqEnumString const & _name() const noexcept``` – returns a reference to a constant string – the name (the text that was used for the value when using the ```QQ_ENUM``` macro) of the current value.
```static QqEnumString const & _nameByValue(_Enum const e)``` – returns a reference to a constant string – the name (the text that was used for the value when using the ```QQ_ENUM``` macro) of the passed value ```e```.
```static _Wrapper const & _wrapper(int index)``` – returns a reference to a constant object of type ```_Wrapper```. If index is less than zero or greater than ```_lastIndex()```, the transitive method throws an ```std::out_of_range``` exception.

##### 4. Lists, arrays.
```static std::vector<_Enum> const & _valueList() noexcept``` – returns a reference to a constant vector containing a list of ```_Enum``` elements. The list is constructed in the order in which it was declared using the ```QQ_ENUM``` macro.
```static std::vector<QqEnumString> const & _nameList() noexcept``` – returns a reference to a constant vector containing a list of ```_Enum``` names. The list is constructed in the order in which it was declared using the ```QQ_ENUM``` macro.
```static std::vector<_Wrapper> const & _wrapperList() noexcept``` – returns a reference to a constant vector containing a ```_Wrapper``` list. The list is constructed in the order in which it was declared using the ```QQ_ENUM``` macro.

##### 5. Special values.
```bool _isInvalid() const noexcept``` – returns true if the current ```m_index``` value points to an invalid value.
```bool _isDefault() const noexcept``` – returns true if the current ```m_index``` value points to the default value.
```static bool _isInvalidDefined() noexcept``` – returns true if an invalid value is defined in this class via the ```QQ_ENUM_INVALID_VALUE``` macro.
```static bool _isDefaultDefined() noexcept``` – returns true if a default value is defined in this class via the ```QQ_ENUM_DEFAULT_VALUE``` macro.
```static _Enum _invalid()``` – returns the ```_Enum``` value defined as invalid. If such a value is undefined, the transitive method throws an ```std::out_of_range``` exception.
```static _Enum _default()``` – returns the default ```_Enum``` value. If this value is undefined, the transitive method throws an ```std::out_of_range``` exception.
```static QqEnumString const & _invalidName()``` – returns the name of the ```_Enum``` defined as invalid. If this value is undefined, the transitive method throws an ```std::out_of_range``` exception.
```static QqEnumString const & _defaultName()``` – returns the default ```_Enum``` name. If this value is undefined, the transitive method throws an ```std::out_of_range exception```.

##### 6. Indexes.
```int_index() const noexcept``` – returns the current index of the ```QqEnum```.
```int _invalidIndex() const noexcept``` – returns the index of the ```_Enum``` element defined as invalid. If no such element is defined, ```-1``` is returned.
```int _defaultIndex() const noexcept``` – returns the index of the ```_Enum``` element defined as default. If no such element is defined, ```-1``` is returned.
```int _firstValidIndex() const noexcept``` – returns the first valid index (the invalid index always comes first). This will be either zero or greater than zero.
```int _lastValidIndex() const noexcept``` – returns the last valid index. Currently, this is always equal to the last index (```_lastIndex()```).
```int _lastIndex() const noexcept``` – returns the last index, calculated as ```_count() - 1```.

##### 7. Iteration.
```_Iterator _iterator() noexcept``` – returns an iterator.
```_Iterator _iterator(int fromIndex, int toIndex) noexcept``` – returns an ```_Iterator``` object for the index range [```fromIndex```, ```toIndex```]. If any index is out of range (i.e., less than zero or greater than ```_lastIndex()```), that index will be "squeezed" into the range; no exception is thrown. Negative values are treated as ```_count()``` indexes.
```_Iterator _iterator(_Enum from, _Enum to) noexcept``` – returns an ```_Iterator``` object for the index range [```from```, ```to```].
```_IterationRange _range() noexcept``` – returns an ```_IterationRange``` object for the entire ```_Enum``` range. 
```_IterationRange _range(int fromIndex, int toIndex) noexcept``` – returns an ```_IterationRange``` object for the range [```fromIndex```, ```toIndex```] within ```_Enum```. If ```fromIndex``` is greater than ```toIndex```, a reversed range object is returned.
```_IterationRange _range(_Enum from, _Enum to) noexcept``` – returns an ```_IterationRange``` object for the range [```from```, ```to```] within ```_Enum```. If from is greater than to, a reversed range object is returned.
```_IterationRange _range_r() noexcept``` – returns an ```_IterationRange``` object for the reversed range – from the end to the beginning of the entire ```_Enum```.
```_IterationRange _range_r(int fromIndex, int toIndex) noexcept``` – returns an ```_IterationRange``` object for the reverse range [```fromIndex```, ```toIndex```] of ```_Enum```. It is important to note that ```toIndex``` must be less than ```fromIndex```.

##### 8. Parsing.
```bool _tryParse(char const * str, Class * out = nullptr, bool caseInsensitive = true) noexcept``` – returns true and the class instance with the specified ```m_index```, located in out, if the string str contains one of the names (titles) included in ```_Enum```.
```Class _parse(char const * str, bool caseInsensitive = true)``` – if the passed string contains one of the names (titles) of ```_Enum```, returns the class instance with ```m_index``` set to the corresponding ```_Enum``` element. Otherwise, the transitive method throws a ```Qq::Exceptions::ParseException``` exception. 


##### 9. Operators.
```_Wrapper const & operator () (int index = Qq::Enum::Const::badIndex) const``` – returns a constant ```_Wrapper``` object from the current ```m_index``` (index must be equal to ```Qq::Enum::Const::badIndex```) or from the specified index. If index is out of range, the transitive method throws an ```std::out_of_range``` exception.

###### 9.1 Assignment operators.
```Class & operator = (_Int enumAsInt)``` – used to assign ```m_index``` the value that satisfies the condition that ```static_cast<_Enum>(enumAsInt)``` is within the range of ```_Enum```. If not, the transitive method throws an ```std::out_of_range``` exception.
```Class & operator = (_Enum e)``` – used to assign the value `e` to the current ```Class``` instance.
```Class & operator = (Class const & other)``` – assignment operator for another instance.

###### 9.2 Comparison operators.
```friend bool operator == (Class const & lh, Class const & rh) noexcept``` – returns ```true``` if ```lh.m_index == rh.m_index```.
```friend bool operator != (Class const & lh, Class const & rh) noexcept``` – returns ```true``` if ```lh.m_index != rh.m_index```.
```friend bool operator == (Class const & c, _Enum e) noexcept``` – returns ```true``` if ```c._value() == e```.
```friend bool operator != (Class const & c, _Enum e) noexcept``` – returns ```true``` if ```c._value() != e```.

```friend bool operator > (Class const & lh, Class const & rh) noexcept``` – returns ```true``` if ```lh._value() > rh._value()```.
```friend bool operator > (Class const & c, _Int i) noexcept``` – returns ```true``` if ```c._int() > i```.
```friend bool operator > (_Int i, Class const & c) noexcept``` – returns ```true``` if ```i > c._int()```.
```friend bool operator > (Class const & c, _Enum e) noexcept``` – returns ```true``` if ```c._value() > e```.
```friend bool operator > (_Enum e, Class const & c) noexcept``` – returns ```true``` if ```e > c._value()```.

```friend bool operator < (Class const & lh, Class const & rh) noexcept``` – returns ```true``` if ```lh._value() < rh._value()```.
```friend bool operator < (Class const & c, _Int i) noexcept``` – returns ```true``` if ```c._int() < i```.
```friend bool operator < (_Int i, Class const & c) noexcept``` – returns ```true``` if ```i < c._int()```.
```friend bool operator < (Class const & c, _Enum e) noexcept``` – returns ```true``` if ```c._value() < e```.
```friend bool operator < (_Enum e, Class const & c) noexcept``` – returns ```true``` if ```e < c._value()```.

```friend bool operator >= (Class const & lh, Class const & rh) noexcept``` – returns ```true``` if ```lh._value() >= rh._value()```.
```friend bool operator >= (Class const & c, _Int i) noexcept``` – returns ```true``` if ```c._int() >= i```.
```friend bool operator >= (_Int i, Class const & c) noexcept``` – returns ```true``` if ```i >= c._int()```.
```friend bool operator >= (Class const & c, _Enum e) noexcept``` – returns ```true``` if ```c._value() >= e```.
```friend bool operator >= (_Enum e, Class const & c) noexcept``` – returns ```true``` if ```e >= c._value()```.

```friend bool operator <= (Class const & lh, Class const & rh) noexcept``` – returns ```true``` if ```lh._value() <= rh._value()```.
```friend bool operator <= (Class const & c, _Int i) noexcept``` – returns ```true``` if ```c._int() <= i```.
```friend bool operator <= (_Int i, Class const & c) noexcept``` – returns ```true``` if ```i <= c._int()```.
```friend bool operator <= (Class const & c, _Enum e) noexcept``` – returns ```true``` if ```c._value() <= e```. 
```friend bool operator <= (_Enum e, Class const & c) noexcept``` – returns ```true``` if ```e <= c._value()```.

###### 9.3 Addition operators.
```friend Class operator + (Class const & lh, Class const & rh)``` – returns a ```Class``` instance containing the sum of ```lh.m_index + rh.m_index```. If ```lh.m_index + rh.m_index``` is less than zero or greater than ```Class::_lastIndex()```, the transitive method throws an ```std::out_of_range``` exception.
```friend Class operator + (Class const & c, int n)``` – returns a new ```Class``` instance containing the sum of ```c.m_index + n```. If ```c.m_index + n``` is less than zero or greater than ```_lastIndex()```, the transitive method throws an ```std::out_of_range``` exception.
```friend Class operator + (int n, Class const & c)``` – returns a new ```Class``` instance containing the sum of ```c.m_index + n```. If ```c.m_index + n``` is less than zero or greater than ```_lastIndex()```, the transitive method throws an ```std::out_of_range exception```.
```Class & operator += (int n)``` – returns the current instance with ```m_index``` already incremented by ```n```. If ```m_index``` is less than zero or greater than ```_lastIndex()```, the transitive method will throw an ```std::out_of_range``` exception.
```Class & operator += (Class const & other)``` – returns the current instance with ```m_index``` already incremented by ```other.m_index```. If the sum of ```m_index + other.m_index``` is greater than ```Class::_lastIndex()```, the transitive method will throw an ```std::out_of_range``` exception.

###### 9.4 Subtraction operators.
```friend Class operator - (Class & lh, Class const & rh)``` – the ```Class``` instance containing the difference ```lh.m_index – rh.m_index```. If ```lh.m_index – rh.m_index``` is less than zero or greater than ```Class::_lastIndex()```, the transitive method will throw an ```std::out_of_range``` exception.
```friend Class operator – (Class const & c, int n)``` – returns a new ```Class``` instance containing the difference ```c.m_index – n```. If the value is less than zero or greater than ```Class::_lastIndex()```, the transitive method will throw an ```std::out_of_range``` exception.
```friend Class operator – (int n, Class const & c)``` – returns a new ```Class``` instance containing the difference ```n – c.m_index```. If the value is less than zero or greater than ```Class::_lastIndex()```, the transitive method will throw an ```std::out_of_range``` exception.
```Class & operator –= (int n)``` – returns the current instance, with ```m_index``` decremented by ```n```. If the difference between ```n``` and ```m_index``` is less than zero or greater than ```_lastIndex()```, the transitive method will throw an ```std::out_of_range``` exception.
```Class & operator –= (Class const & other)``` – returns the current instance, with ```m_index``` already decremented by ```other.m_index```. If ```m_index – other.m_index``` is less than zero or greater than ```_lastIndex()```, the transitive method will throw an ```std::out_of_range``` exception.

###### 9.5 Increment and Decrement Operators.
```Class & operator ++ ()``` – prefix increments ```m_index``` by one. If ```m_index``` is less than zero or greater than ```_lastIndex()```, the transitive method throws an ```std::out_of_range``` exception.
```Class & operator ++ (int)``` – postfix increments ```m_index``` by one. If ```m_index``` is less than zero or greater than ```_lastIndex()```, the transitive method throws an ```std::out_of_range``` exception.
```Class & operator -- ()``` – prefix decrements ```m_index``` by one. If ```m_index``` is less than zero or greater than ```_lastIndex()```, the transitive method throws an ```std::out_of_range``` exception.
```Class & operator -- (int)``` – postfix decrements ```m_index``` by one. If ```m_index``` is less than zero or greater than ```_lastIndex()```, the transitive method throws an ```std::out_of_range``` exception.


#### <div align="center">Examples</div>
##### 1. Declaring a structure or class.
Declaring a ```QqEnum``` structure:
```C++
struct SolarSystemObject
{
    QQ_ENUM( SolarSystemObject,
        Unknown = -1,
        Sun = 0,

        // Planets:
        Mercury,
        Venus,
        Earth,
        Mars,
        Jupiter,
        Saturn,
        Uranus,
        Neptune,
        
        // Moons:
        Moon,
        Deimos,
        Phobos,
        // Jupiter's moons - Galilean moons:
        Io,
        Europa,
        Ganymede,
        Callisto,
        // Saturn's moons – Big Seven:
        Titan,
        Rhea,
        Iapetus,
        Dione,
        Tethys,
        Enceladus,
        Mimas,
        // Uranu's moons – Big Five:
        Titania,
        Oberon,
        Ariel,
        Umbriel,
        Miranda,
        // Neptune's moons:
        Triton,
        Nereid,
        Larissa,
        Proteus,
        Despina,
        Galatea,
        Thalassa,
        Naiad,
        Halimede,
        Sao,
        Laomedeia,
        Neso,
        Psamathe,
        Hippocamp,
        S_2002_N_5,
        S_2021_N_1,
        Moons_end = S_2021_N_1
    );
    QQ_ENUM_INVALID_VALUE(Unknown);
    QQ_ENUM_DEFAULT_VALUE(Sun);
};
```
##### 2. Iterators.
```C++
void Iterator_example_02()
{
    using namespace std;
    SolarSystemObject::_Iterator iter1, iter2{ 4 }, iter3;
    iter1 += 2;
    cout << "value: "       << iter1->value()
         << "\nname: "      << iter1->name()
         << "\nasInt: "     << iter1->asInt()
         << "\nisInvalid: " << iter1->isInvalid()
         << "\nisDefault: " << iter1->isDefault()
         << endl;

    iter3 = iter1+iter2;
    cout << "iter3->index(): " << iter3->index() << endl;
    cout << "iter3->name(): "  << iter3->name()  << endl;
}
```

Printed:
```
value: 1
name: Mercury
asInt: 1
isInvalid: 0
isDefault: 0
iter3->index(): 6
iter3->name(): Jupiter
```

##### 3. Iterations and EnumItemWrapperT(_Wrapper).
The concept of ```EnumItemWrapperT``` (the T suffix denotes that it is a template class/struct) is that when the ```QQ_ENUM``` macro is compiled, a constant array is created containing all the necessary data about the ```_Enum``` elements. When working with an ```EnumItemWrapperT``` instance, you will almost always be working with a reference to the constant ```EnumItemWrapperT``` instance object.

###### Main methods of ```EnumItemWrapperT```:
```_Enum value() const``` – returns the value of the ```_Enum``` it contains.
```QqEnumString const & name() const``` – returns a reference to the constant name of the ```_Enum``` it contains.
```int index() const``` – returns the ```m_index``` value.
```TInt asInt() const``` – returns ```value()``` as a ```TInt``` value, i.e., calling ```asInt()``` is equivalent to the expression ```static_cast<TInt>(value())```.
```bool isInvalid() const``` – returns ```true``` if ```value()``` is invalid.
```bool isDefault() const``` – returns ```true``` if ```value()``` is assigned by default.

The following example shows how to work with an iterator and ```_Wrapper``` (an alias for ```EnumItemWrapperT```).
```C++
void IteratorWrapper_example()
{
    using namespace std;

    SolarSystemObject e1{ SolarSystemObject::Mercury };

    //for (SolarSystemObject::_Wrapper const & w : e1._range(5)) // Prints all _Enum elements but skip first 5 elements
    //for (SolarSystemObject::_Wrapper const & w : e1._range(-5)) // Prints last _Enum elements
    for (SolarSystemObject::_Wrapper const & w : e1._range(0,5)) // Prints first 5 _Enum elements
    //for (SolarSystemObject::_Wrapper const & w : e1._range_r(0,5)) // Prints first 5 _Enum elements in reverse order
    {
        cout << w.name() << " = " << w.asInt()<< "\t, isDefault: " << w.isDefault() << ", isInvalid: " << w.isInvalid() << endl;
    } 
}
```

Printed:
```
Unknown = -1    , isDefault: 0, isInvalid: 1
Sun = 0 , isDefault: 1, isInvalid: 0
Mercury = 1, isDefault: 0, isInvalid: 0
Venus = 2       , isDefault: 0, isInvalid: 0
Earth = 3       , isDefault: 0, isInvalid: 0
Mars = 4        , isDefault: 0, isInvalid: 0
```

That is, the ```_range()``` and ```_range_r()``` methods return a ```Qq::Enum::IterationRange``` object, which has ```begin()``` and ```end()``` methods for executing the ```for(... : ...)``` loop.

##### 4. qq_lock.
A macro for using mutex-based critical sections. Example usage: Let's say you need to ensure exclusive execution of some code. For this, you can use ```qq_lock```:
```C++
#include <QqLib/QqThread/qq_lock.M.h>
...
void func() {
    qq_lock m_x += 1;
}
```
or
```C++
void func2()
{
    qq_lock
    {
        m_x = getValue();
        m_x = x * 2;
    }
}
```

##### 5. qq_trow_l.
```qq_trow_l(EXCEPTION,TEXT)``` – a macro for outputting ```TEXT``` to ```std::err``` and then throwing an exception ```EXCEPTION```, passing ```TEXT``` to the exception constructor.

#### Directories and files
##### ```src``` directory
- ```src/``` – files for including QqLib components via ```#include``` (e.g., ```QqEnum```: ```#include <QqLib/QqEnum.h>```)
- ```src/Exceptions/``` – library Exception files (```Qq::Enum::Exceptions::*```).
- ```src/Helpers/``` – files for various library Helpers.
- ```src/Macros/``` – library macro files.
- ```src/QqEnum/``` – files for working with QqEnum.
- ```src/QqThread/``` – files for working with threads.
- ```src/Utils/``` – files for various utility macros, functions, classes, etc.
- ```src/Core/``` – files for the core QqLib library.

##### ```doc``` directory
It contains documentation.

##### ```examples``` directory
Directory с примерами.

##### ```export``` directory
Files copied from src by the ```tools/copy_to_export/copy_to_export.py``` script are placed here. This script is (must be) executed after each project compilation.

##### ```tests``` directory
Here are the test files for ```QTest```.

##### ```tools``` directory
Here are various useful tools for the library.
```tools/copy_to_export/``` – these are files for copying files from the src folder to the export folder.

##### ```src/QqEnum/_CompileConfig.h``` file
Designed to control compilation. Currently, the main purpose of this file is to specify whether ```Qt``` will be used and how ```QqEnumString``` is compiled. 
