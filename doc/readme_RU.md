#### <div align="center">Цели создания</div>
Существуют множество библиотек для работы с enum в C++. Каждая из них чем-то великолепна. Однако настал момент, когда для меня стали очень важным следующие моменты:
1. Интуитивно понятный синтаксис как, например, в языках Java или C#;
2. Нормальная рефлексия;
3. Декларативность;
4. Расширяемость того класса или структуры, что содержит enum (т.е. enum не является самостоятельным классом, а входит в класс, у которого могут быть другие члены, методы, структуры и т.п.);
5. Поддержка разных IDE.
6. Поддержка многопоточности при различных операция сложения/вычитания.
7. Малый размер хранимых данных в ```QqEnum``` – машинное слово в идеале.
8. Полная реентабельность.


Ещё была потребность в простоте интеграции. В итоге, получилось не совсем всё просто из-за нахождения ```QqEnum``` в библиотеке ```QqLib```. Однако, в итоге решение было принято, что ```QqEnum``` будет именно в составе ```QqLib```, т.к. её концепция мне понравилась, и я намерен развивать её дальше.

```QqLib``` разрабатывается с помощью ```QtCreator```. Изначально она была как расширение библиотеки ```Qt``` (отсюда и название – ```QqLib```). Но позже было решено отвязать её от Qt. Однако всё-равно её можно использовать совместно с Qt (в ```QqEnum``` добавятся возможности ```QStringLiteral```, если в файле ```"QqEnum/ _CompileConfig.h"``` убрать комментарий из строки ```"//#undef QQ_DONT_USE_QT"```). 
Касаемо ```QqEnum```, мне хотелось, чтобы было так (и мне за это ничего не было бы):

```C++
struct EnumStruct
{
    QQ_ENUM(EnumStruct,
        None = 0,
        One,
        Two,
        Three,
        Four)
    QQ_ENUM_INVALID_VALUE(None) // определили невалидное значение для данного типа enum
    QQ_ENUM_DEFAULT_VALUE(One) // определили значение по умолчанию для данного типа enum, чтобы при создании EnumStruct оно сразу же присваивалось.
    _myMethod01();
    _myMethod02();
};
```

#### <div align="center">Правила именования полей в QqEnum</div>
1. Все названия элементов enum идут без подчёркивания и могут начинаться как с большой буквы, так и с маленькой: ```None, One``` или ```one, two``` и т.д.
2. С подчёркивания начинаются только внутренние методы, поля, типы и т.д. ```QqEnum: _first(), _last()``` и т.п. 
3. Публичные типы ```QqEnum``` всегда начинаются со знака подчёркивания, а далее с БОЛЬШОЙ буквы (```_Enum, _Class, _Int``` и т.д.). Всё остальное – с подчёркивания и маленькой буквы.

#### <div align="center">Как начать использовать</div>
0. Ваш компилятор должен поддерживать версию C++ 17 и выше.
1. Скачайте или клонируйте репозиторий.
2. Поместите папку ```"export/QqLib"``` в удобное место, чтобы можно было подключать ```QqLib``` обычной командой ```#include```:
```#include <QqLib/QqEnum.h>```

#### <div align="center">Стиль именования файлов в библиотеке</div>
В библиотеке используются обычные h-файлы и cpp-файлы с суффиксами ".h" и ".cpp" соответственно.
Суффикс ".M.h" – означает заголовочный файл с макросами. Т.е. там всё содержимое – это макрос или макросы.

#### <div align="center">Константы и типы</div>
##### 1. Публичные.
```const bool _isQqEnum``` – указывает, что этот класс содержит методы QqEnum.
тип ```_Class``` – алиас класса.
тип ```_Enum``` – сам enum (перечисление).
тип ```_Int``` – алиас типа от которого происходит ```_Enum``` (его размер).
тип ```_``` – алиас для ```_Enum```. Необходим для нормальной работы некоторых IDE.
тип ```_Wrapper``` – алиас для ```Qq::Enum::EnumItemWrapperT<_Enum,_Int>```.
```_Iterator``` – алиас для ```Qq::Enum::IteratorT<_Class,_Enum,_Int>```.
```_IterationRange``` – алиас для ```Qq::Enum::IterationRangeT<_Class,_Enum,_Int>```.


##### 2. Внутренние (protected / private).
```_C``` – алиас для ```Qq::Enum::CoreT<_Class,_Enum,_Int>```.
```_D``` – алиас для ```Qq::Enum::MetadataT<_Class,_Enum,_Int>```.
```_H``` – алиас для ```Qq::Enum::Helper```.
```_EatAssign``` – алиас для ```Qq::Enum::EatAssignT<_Enum, _Int>```.


#### Поля
```static inline _D _d``` – хранит метаданные ```QqEnum```. Один для всех экземпляров класса, поэтому статический;
```Qq::Enum::Index m_index``` – хранит текущий индекс ```_Enum``` в данном экземпляре. Т.е. в объекте не хранится непосредственное значение, а лишь индекс внутри массива (вектора) значений ```_Enum```;


#### <div align="center">API</div>
##### 1. Метаданные.
```char const * _className() noexcept``` – возвращает имя класса, содержащего ```QqEnum```.
```char const * _fullClassName() noexcept``` – возвращает квалифицированное имя класса (полное).
```char const * _intTypeName() noexcept``` – возвращает название типа от которого происходит тип ```_Enum```.


##### 2. Границы.
```_Enum _first() noexcept``` – возвращает первый элемент в ```_Enum```.
```_Enum _last() noexcept``` – возвращает последний элемент в ```_Enum```.
```int _count() noexcept``` – возвращает общее количество элементов в ```_Enum```.
```_Enum _min() noexcept``` – возвращает элемент с минимальным значением в ```_Enum```.
```_Enum _max() noexcept``` – возвращает элемент с максимальным значением в ```_Enum```.


##### 3. Имена и значения.
(текущее значение задаётся через поле m_index)
```_Int _int() const noexcept``` – возвращает текущее значение как ```_Int```.
```_Enum _value() const noexcept``` – возвращает текущее значение как ```_Enum```.
```QqEnumString const & _name() const noexcept``` – возвращает ссылку на константную строку -- имя (текст, который был использован для значения при использовании макроса ```QQ_ENUM```) текущего значения.
```static QqEnumString const & _nameByValue(_Enum const e)``` – возвращает ссылку на константную строку -- имя (текст, который был использован для значения при использовании макроса ```QQ_ENUM```) переданного значения ```e```.
```static _Wrapper const & _wrapper(int index)``` – возвращает ссылку на константный объект типа ```_Wrapper```. Если ```index``` меньше нуля или больше ```_lastIndex()```, то транзитный метод бросает исключение ```std::out_of_range```.


##### 4. Списки, массивы.
```static std::vector<_Enum> const & _valueList() noexcept``` – возвращает ссылку на константный вектор содержащий список элементов _Enum. Список составляется именно в том порядке, в котором он объявлялся при использовании макроса ```QQ_ENUM```.
```static std::vector<QqEnumString> const & _nameList() noexcept``` – возвращает ссылку на константный вектор содержащий список имён (названий) ```_Enum```. Список составляется именно в том порядке, в котором он объявлялся при использовании макроса ```QQ_ENUM```.
```static std::vector<_Wrapper> const & _wrapperList() noexcept``` – возвращает ссылку на константный вектор содержащий список ```_Wrapper```. Список составляется именно в том порядке, в котором он объявлялся при использовании макроса ```QQ_ENUM```.


##### 5. Специальные значения.
```bool _isInvalid() const noexcept``` – возвращает true, если текущее значение ```m_index``` указывает на невалидное значение.
```bool _isDefault() const noexcept``` – возвращает true, если текущее значение ```m_index``` указывает на значение по-умолчанию.
```static bool _isInvalidDefined() noexcept``` – возвращает ```true```, если в данном классе определено невалидное значение через макрос ```QQ_ENUM_INVALID_VALUE```.
```static bool _isDefaultDefined() noexcept``` – возвращает ```true```, если в данном классе определено значение по умолчанию через макрос ```QQ_ENUM_DEFAULT_VALUE```.
```static _Enum _invalid()```  – возвращает то значение ```_Enum```, которое определено как невалидное. Если такое значение не определено, то транзитный метод кидает исключение ```std::out_of_range```.
```static _Enum _default()``` – возвращает то значение ```_Enum```, которое определено как по умолчанию. Если такое значение не определено, то транзитный метод кидает исключение ```std::out_of_range```.
```static QqEnumString const & _invalidName()``` – возвращает имя (название) ```_Enum```, которое определено как невалидное. Если такое значение не определено, то транзитный метод кидает исключение ```std::out_of_range```.
```static QqEnumString const & _defaultName()``` – возвращает имя (название) ```_Enum```, которое определено как по умолчанию. Если такое значение не определено, то транзитный метод кидает исключение ```std::out_of_range```.


#### 6. Индексы.
```int_index() const noexcept``` – возвращает текущий индекс ```QqEnum```.
```int _invalidIndex() const noexcept``` – возвращает индекс элемента ```_Enum```, определённого как невалидный. Если такой элемент не определён, то возвращается ```-1```.
```int _defaultIndex() const noexcept``` – возвращает индекс элемента ```_Enum```, определённого как по умолчанию. Если такой элемент не определён, то возвращается ```-1```.
```int _firstValidIndex() const noexcept``` – возвращает первый валидный индекс (невалидный индекс всегда идёт первым). Это будет значение либо ноль, либо больше нуля.
```int _lastValidIndex() const noexcept``` – возвращает последний валидный индекс. Сейчас он всегда равен последнему индексу (```_lastIndex()```).
```int _lastIndex() const noexcept``` – возвращает последний индекс, вычисляется как ```_count() - 1```.


#### 7. Итерация.
```_Iterator _iterator() noexcept``` – возвращает итератор.
```_Iterator _iterator(int fromIndex, int toIndex) noexcept``` – возвращает объект ```_Iterator``` для диапазона индексов [```fromIndex```, ```toIndex```]. Если какой-либо индекс вне диапазона (т.е. меньше нуля или больше ```_lastIndex()```), то такой индекс будет "втиснут" в диапазон, исключение не выбрасывается. Если использовать отрицательные значения, то это рассматривается как ```_count() - индекс```.
```_Iterator _iterator(_Enum from, _Enum to) noexcept``` – возвращает объект ```_Iterator``` для диапазона индексов [```from```, ```to```].
```_IterationRange _range() noexcept``` – возвращает объект ```_IterationRange``` для всего диапазона ```_Enum```.
```_IterationRange _range(int fromIndex, int toIndex) noexcept``` – возвращает объект ```_IterationRange``` для диапазона [```fromIndex```, ```toIndex```] внутри ```_Enum```. Если ```fromIndex``` будет больше, чем ```toIndex```, то будет возвращён объект с реверсивным диапазоном.
```_IterationRange _range(_Enum from, _Enum to) noexcept``` – возвращает объект ```_IterationRange``` для диапазона [```from```, ```to```] внутри ```_Enum```. Если ```from``` будет больше, чем ```to```, то будет возвращён объект с реверсивным диапазоном.
```_IterationRange _range_r() noexcept``` – возвращает объект ```_IterationRange``` для реверсного диапазона – от конца к началу всего ```_Enum```.
```_IterationRange _range_r(int fromIndex, int toIndex) noexcept``` – возвращает объект ```_IterationRange``` для реверсного диапазона [```fromIndex```, ```toIndex```] _Enum. Важно учитывать, что ```toIndex``` должен быть меньше ```fromIndex```.


#### 8. Парсинг.
```bool _tryParse(char const * str, Class * out = nullptr, bool caseInsensitive = true) noexcept``` – возвращает true и экземпляр класса с установленным ```m_index```, находящийся в ```out```, если строка ```str``` содержит одно из имён (названий) входящих в ```_Enum```.
```Class _parse(char const * str, bool caseInsensitive = true)```  – если переданная строка содержит одно из имён (названий) ```_Enum```, то возвращает экземпляр класса с установленным m_index на соответствующий элемент ```_Enum```. В противном случае транзитный метод выкинет исключение ```Qq::Exceptions::ParseException```.


#### 9. Операторы.
```_Wrapper const & operator () (int index = Qq::Enum::Const::badIndex) const``` – возвращает константный объект ```_Wrapper``` от текущего ```m_index``` (```index``` должен быть равен ```Qq::Enum::Const::badIndex```) или же от указанного ```index```. Если ```index``` лежит вне диапазона, то транзитный метод выкидывает исключение ```std::out_of_range```.


##### 9.1. Операторы присваивания.
```Class & operator = (Int enumAsInt)``` – используется, чтобы присвоить ```m_index```, то значение которое соответствует условию, что ```static_cast<_Enum>(enumAsInt)``` входит в диапазон ```_Enum```. Если нет, то транзитный метод выкинет исключение ```std::out_of_range```.
```Class & operator = (_Enum e)``` – используется чтобы присвоить значение `e` текущему экземпляру ```Class```.
```Class & operator = (Class const & other)``` – оператор присваивания другого экземпляра.

##### 9.2. Операторы сравнения.
```friend bool operator == (Class const & lh, Class const & rh) noexcept``` – возвращает ```true```, если ```lh.m_index == rh.m_index```.
```friend bool operator != (Class const & lh, Class const & rh) noexcept``` – возвращает ```true```, если ```lh.m_index != rh.m_index```.
```friend bool operator == (Class const & c, _Enum e) noexcept``` – возвращает ```true```, если у ```c._value() == e```.
```friend bool operator != (Class const & c, _Enum e) noexcept``` – возвращает ```true```, если у ```c._value() != e```.

```friend bool operator > (Class const & lh, Class const & rh) noexcept``` – возвращает ```true```, если ```lh._value() > rh._value()```.
```friend bool operator > (Class const & c, _Int i) noexcept``` – возвращает ```true```, если ```c._int() > i```.
```friend bool operator > (_Int i, Class const & c) noexcept``` – возвращает ```true```, если ```i > c._int()```.
```friend bool operator > (Class const & c, _Enum e) noexcept``` – возвращает ```true```, если ```c._value() > e```.
```friend bool operator > (_Enum e, Class const & c) noexcept``` – возвращает ```true```, если ```e > c._value()```.

```friend bool operator < (Class const & lh, Class const & rh) noexcept``` – возвращает ```true```, если ```lh._value() < rh._value()```.
```friend bool operator < (Class const & c, _Int i) noexcept``` – возвращает ```true```, если ```c._int() < i```.
```friend bool operator < (_Int i, Class const & c) noexcept``` – возвращает ```true```, если ```i < c._int()```.
```friend bool operator < (Class const & c, _Enum e) noexcept``` – возвращает ```true```, если ```c._value() < e```.
```friend bool operator < (_Enum e, Class const & c) noexcept``` – возвращает ```true```, если ```e < c._value()```.

```friend bool operator >= (Class const & lh, Class const & rh) noexcept``` – возвращает ```true```, если ```lh._value() >= rh._value()```.
```friend bool operator >= (Class const & c, _Int i) noexcept``` – возвращает ```true```, если ```c._int() >= i```.
```friend bool operator >= (_Int i, Class const & c) noexcept``` – возвращает ```true```, если ```i >= c._int()```.
```friend bool operator >= (Class const & c, _Enum e) noexcept``` – возвращает ```true```, если ```c._value() >= e```.
```friend bool operator >= (_Enum e, Class const & c) noexcept``` – возвращает ```true```, если ```e >= c._value()```.

```friend bool operator <= (Class const & lh, Class const & rh) noexcept``` – возвращает ```true```, если ```lh._value() <= rh._value()```.
```friend bool operator <= (Class const & c, _Int i) noexcept``` – возвращает ```true```, если ```c._int() <= i```.
```friend bool operator <= (_Int i, Class const & c) noexcept``` – возвращает ```true```, если ```i <= c._int()```.
```friend bool operator <= (Class const & c, _Enum e) noexcept``` – возвращает ```true```, если ```c._value() <= e```.
```friend bool operator <= (_Enum e, Class const & c) noexcept``` – возвращает ```true```, если ```e <= c._value()```.

##### 9.3. Операторы сложения.
```friend Class operator + (Class const & lh, Class const & rh)``` – возвращает экземпляр ```Class```, в котором будет сумма ```lh.m_index+rh.m_index```. Если ```lh.m_index+rh.m_index``` меньше нуля или больше ```Class::_lastIndex()```, то транзитный метод выкинет исключение ```std::out_of_range```.
```friend Class operator + (Class const & c, int n)``` – возвращает новый экземпляр ```Class```, в котором будет сумма ```c.m_index+n```. Если ```c.m_index+n``` будет меньше нуля или больше ```_lastIndex()```, то транзитный метод выкинет исключение ```std::out_of_range```.
```friend Class operator + (int n, Class const & c)``` – возвращает новый экземпляр ```Class```, в котором будет сумма ```c.m_index+n```. Если ```c.m_index+n``` меньше нуля или больше ```_lastIndex()```, то транзитный метод выкинет исключение ```std::out_of_range```.
```Class & operator += (int n)``` – возвращает текущий экземпляр, в котором ```m_index``` уже увеличен на ```n```. Если ```m_index``` будет меньше нуля или больше ```_lastIndex()```, то транзитный метод выкинет исключение ```std::out_of_range```.
```Class & operator += (Class const & other)``` – возвращает текущий экземпляр, в котором ```m_index``` уже увеличен на ```other.m_index```. Если сумма ```m_index+other.m_index``` будет больше ```Class::_lastIndex()```, то транзитный метод выкинет исключение ```std::out_of_range```.

##### 9.4. Операторы вычитания.
```friend Class operator - (Class & lh, Class const & rh)``` – экземпляр ```Class```, в котором будет разница ```lh.m_index–rh.m_index```. Если ```lh.m_index–rh.m_index``` меньше нуля или больше ```Class::_lastIndex()```, то транзитный метод выкинет исключение ```std::out_of_range```.
```friend Class operator – (Class const & c, int n)``` – возвращает новый экземпляр ```Class```, в котором будет разница ```c.m_index–n```. Если значение будет меньше нуля или больше ```Class::_lastIndex()```, тогда транзитный метод выкинет исключение ```std::out_of_range```.
```friend Class operator – (int n, Class const & c)``` – возвращает новый экземпляр ```Class```, в котором будет разница ```n– c.m_index```. Если значение будет меньше нуля или больше ```Class::_lastIndex()```, тогда транзитный метод выкинет исключение ```std::out_of_range```.
```Class & operator –= (int n)``` – возвращает текущий экземпляр, в котором ```m_index``` уже уменьшен на ```n```. Если разница ```n-m_index``` будет меньше нуля или больше ```_lastIndex()```, то транзитный метод выкинет исключение ```std::out_of_range```.
```Class & operator –= (Class const & other)``` – возвращает текущий экземпляр, в котором ```m_index``` уже уменьшен на ```other.m_index```. Если ```m_index–other.m_index``` будет меньше нуля или больше ```_lastIndex()```, то транзитный метод выкинет исключение ```std::out_of_range```.

##### 9.5. Операторы инкремента и декремента.
```Class & operator ++ ()``` – выполняет префиксный инкремент ```m_index``` на единицу. Если ```m_index``` будет меньше нуля или больше ```_lastIndex()```, то транзитный метод выкинет исключение ```std::out_of_range```.
```Class & operator ++ (int)``` – выполняет постфиксный инкремент ```m_index``` на единицу. Если ```m_index``` будет меньше нуля или больше ```_lastIndex()```, то транзитный метод выкинет исключение ```std::out_of_range```.
```Class & operator -- ()``` – выполняет префиксный декремент ```m_index``` на единицу. Если ```m_index``` будет меньше нуля или больше ```_lastIndex()```, то транзитный метод выкинет исключение ```std::out_of_range```.
```Class & operator -- (int)``` – выполняет постфиксный декремент ```m_index``` на единицу. Если ```m_index``` будет меньше нуля или больше ```_lastIndex()```, то транзитный метод выкинет исключение ```std::out_of_range```.


#### <div align="center">Примеры</div>
##### 1. Объявление структуры или класса.
Объявление ```QqEnum```-структуры:
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

##### 2. Итераторы.
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

Вывод:
```
value: 1
name: Mercury
asInt: 1
isInvalid: 0
isDefault: 0
iter3->index(): 6
iter3->name(): Jupiter
```

##### 3. Итерации и EnumItemWrapperT (_Wrapper).
Концепция ```EnumItemWrapperT``` (суффикс ```T``` – означает, что это шаблонный класс/структура) заключается в том, что при компиляции макроса ```QQ_ENUM```. Создаётся константный массив, содержащий все необходимые данные об элементах ```_Enum```. При работе с экземпляром ```EnumItemWrapperT```, почти всегда Вы будете работать со ссылкой на константный объект экземпляра ```EnumItemWrapperT```.
###### Основные методы EnumItemWrapperT:
```_Enum value() const``` – возвращает значение ```_Enum```, которое содержит.
```QqEnumString const & name() const``` – возвращает ссылку на константное имя ```_Enum```, которое содержит.
```int index() const``` – возвращает значение ```m_index```.
```TInt asInt() const``` – возвращает ```value()``` в значении ```TInt```, т.е. вызов ```asInt()``` эквивалентно выражению ```static_cast<TInt>(value())```.
```bool isInvalid() const``` – возвращает ```true```, если значение ```value()``` является невалидным.
```bool isDefault() const``` – возвращает ```true```, если значение ```value()``` назначено по-умолчанию.

В следующем примере показано как работать с итератором и ```_Wrapper``` (алиас для ```EnumItemWrapperT```).
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
        cout << w.name()TO_STD_STRING << " = " << w.asInt()<< "\t, isDefault: " << w.isDefault() << ", isInvalid: " << w.isInvalid() << endl;
    } 
}
```

Вывод:
```
Unknown = -1    , isDefault: 0, isInvalid: 1
Sun = 0 , isDefault: 1, isInvalid: 0
Mercury = 1, isDefault: 0, isInvalid: 0
Venus = 2       , isDefault: 0, isInvalid: 0
Earth = 3       , isDefault: 0, isInvalid: 0
Mars = 4        , isDefault: 0, isInvalid: 0
```

Т.е. методы ```_range()``` и ```_range_r()``` возвращают объект ```Qq::Enum::IterationRange```, у которого есть методы ```begin()``` и ```end()``` для выполнения цикла ```for(... : ...)```.

##### 4. qq_lock 
Макрос для использования критический секций на основе мьютекса. Пример использования. Допустим, необходимо обеспечить эксклюзивное исполнение какого-либо кода. Для этого можно использовать ```qq_lock```:
```C++
#include <QqLib/QqThread/qq_lock.M.h>
...
void func() {
    qq_lock m_x += 1;
}
или 
void func2()
{
    qq_lock
    {
        m_x = getValue();
        m_x = x * 2;
    }
}
```

##### 5. qq_trow_l
```qq_trow_l(EXCEPTION,TEXT)``` – макрос для того, чтобы выводить в ```std::err``` ```TEXT``` с последующим выбросом исключения ```EXCEPTION```, передавая ```TEXT, в конструктор исключения.


#### Папки и файлы
##### Папка src
- ```src/``` – здесь файлы для подключения компонентов ```QqLib``` через ```#include``` (например, ```QqEnum```: ```#include <QqLib/QqEnum.h>```)
- ```src/Exceptions/``` – файлы Исключений библиотеки (```Qq::Enum::Exceptions::*```).
- ```src/Helpers/``` – файлы всяких Helper-ов библиотеки. 
- ```src/Macros/``` – файлы макросов библиотеки.
- ```src/QqEnum/``` – файлы для работы QqEnum.
- ```src/QqThread/``` – файлы для работы с потоками.
- ```src/Utils/``` – файлы различных утилитарных макросов, функций, классов и т.д.
- ```src/Core/``` – файлы ядра библиотеки ```QqLib```.

##### Папка doc
В ней содержится документация.

##### Папка examples
Папка с примерами.

##### Папка export
Сюда ложатся файлы, которые копируются из src скриптом ```tools/copy_to_export/copy_to_export.py```. Этот скрипт выполняется (должен выполняться) после каждой компиляции проекта.

##### Папка tests
Здесь файлы тестов для ```QTest```.

##### Папка tools
Здесь различные полезные инструменты для библиотеки.
```tools/copy_to_export/``` – здесь файлы для того, чтобы копировать файлы из папки ```src``` в папку ```export```.

##### Файл src/QqEnum/_CompileConfig.h
Предназначен для управления компиляцией. Сейчас главная задача этого файла – это возможность задавать будет ли использоваться ```Qt``` и как компилируется ```QqEnumString```.
