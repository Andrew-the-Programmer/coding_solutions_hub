K. Особенности волшебного багажа — База 2023 1 сем. Задание 3. Алгоритмы — Яндекс.КонтестВаше участие в соревновании завершено. Вы можете дорешивать задачи и отправлять решения вне соревнования

# K. Особенности волшебного багажа

| Ограничение времени | 0.2 секунд |
| --- | --- |
| Ограничение памяти | 64.8 Мб |
| Ввод | стандартный ввод или input.txt |
| Вывод | стандартный вывод или output.txt |

*— О, Гарри, как ты можешь быть отстающим спустя два дня после летних каникул? — спросила Гермиона с раздражением, пока закрывала за ним дверь.*

*— Я отставал задолго до каникул.*

Хогвартские школьные чемоданы, как и большинство волшебного багажа, стандартно выпускаются со встроенными увеличивающими или расширяющими чарами. Это довольно сложные чары, позволяющие в небольшом по объёму предмете или маленьком помещении держать множество вещей. Иными словами, вещь внутри становится намного больше, чем снаружи. Но у всего есть предел. Даже сильнейшие чары не позволят вам поднять вес больший MM.

Юному волшебнику перед началом учебного года необходимо собрать уйму вещей. Самый общий список включает NN предметов массой m1m1​,…,…, mNmN​ и стоимостью c1,…,cNc1​,…,cN​ соответственно. Определите имеющий наибольшую стоимость набор предметов, который можно унести в хогвартском чемодане максимальной вместимости.

## Формат ввода

В первой строке вводится натуральное число NN, не превышающее 100 и натуральное число MM, не превышающее 10000.

Во второй строке вводятся NN натуральных чисел mimi​, не превышающих 100.

В третьей строке вводятся NN натуральных чисел cici​, не превышающих 100.

## Формат вывода

Выведите номера предметов (числа от 1 до NN), которые войдут в чемодан наибольшей стоимости.

## Пример

| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| `4 6 2 4 1 2 7 2 5 1 ` | `1 3 4 ` |

Набрать здесьОтправить файл#include \<iostream>

struct DynArrayIsEmpty {};

template \<class T>
class DynArray {
protected:
DynArray(size_t size, size_t capacity, T\* data) : size\_(size), capacity\_(capacity), data\_(data) {
}

public:
DynArray() : DynArray(0, 0, nullptr) {
}
explicit DynArray(size_t capacity) : DynArray(0, capacity, new T\[capacity\]) {
}
DynArray(size_t size, const T& def_value) : DynArray(size, 2 * size, new T\[2 * size\]) {
std::fill(data\_, data\_ + size\_, def_value);
}
DynArray(const std::initializer_list\<T> list) : DynArray(list.size(), T()) {
std::copy(list.begin(), list.end(), begin());
}
DynArray(const DynArray& other) : DynArray(other.Size(), other.Capacity(), new T\[other.Capacity()\]) {
std::copy(other.begin(), other.end(), begin());
}

~DynArray() {
delete\[\] data\_;
}

public:
DynArray& operator=(const DynArray& other) {
size\_ = other.size\_;
capacity\_ = other.capacity\_;
data\_ = new T\[capacity\_\];
std::copy(other.begin(), other.end(), data\_);
return \*this;
}

protected:
bool IsInBounds(size_t index) const {
return index \< Size();
}

void ThrowIfOutOfRange(size_t index) const {
if (!IsInBounds(index)) {
throw std::out_of_range{""};
}
}

bool IsEmpty() const {
return Size() == 0;
}

void ThrowIfEmpty() const {
if (IsEmpty()) {
throw DynArrayIsEmpty{};
}
}

public:
size_t Size() const {
return size\_;
}

size_t Capacity() const {
return capacity\_;
}

const T& At(size_t index) const {
ThrowIfOutOfRange(index);
return data\_\[index\];
}

T& At(size_t index) {
ThrowIfOutOfRange(index);
return data\_\[index\];
}

const T& operator\[\](size_t index) const {
return data\_\[index\];
}

T& operator\[\](size_t index) {
return data\_\[index\];
}

void PushBack(const T& value) {
if (size\_ \< capacity\_) {
data\_\[size\_++\] = value;
}
}

const T\* begin() const { // NOLINT
return data\_;
}
T\* begin() { // NOLINT
return data\_;
}
const T\* end() const { // NOLINT
return data\_ + size\_;
}
T\* end() { // NOLINT
return data\_ + size\_;
}

template \<class I>
void Output(I begin, I end, char endl = ' ') const {
for (auto it = begin; it != end; ++it) {
std::cout \<\< \*it \<\< endl;
}
}

void Output(bool reverse = false, char endl = ' ') const {
if (reverse) {
for (auto it = end(); it != begin(); --it) {
std::cout \<\< \*(it - 1) \<\< endl;
}
} else {
Output(begin(), end(), endl);
}

// if (reverse) {
// auto begin = this->rbegin();
// auto end = this->rend();
// } else {
// auto begin = this->begin();
// auto end = this->end();
// }
// for (auto it = begin; it != end; ++it) {
// std::cout \<\< val \<\< endl;
// }
}

void Output2d() const {
for (auto val : \*this) {
val.Output();
std::cout \<\< '\\n';
}
}

void Input() {
T value = T();
for (size_t i = Size(); i \< Capacity(); ++i) {
std::cin >> value;
PushBack(value);
}
}

T Min() const {
ThrowIfEmpty();
T min = At(0);
for (size_t i = 1; i \< Size(); ++i) {
if (At(i) \< min) {
min = At(i);
}
}
return min;
}

T Max() const {
ThrowIfEmpty();
T max = 0;
for (size_t i = 0; i \< Size(); ++i) {
if (At(i) > max) {
max = At(i);
}
}
return max;
}

T Sum() const {
T sum = 0;
for (size_t i = 0; i \< Size(); ++i) {
sum += At(i);
}
return sum;
}

protected:
size_t size\_ = 0;
size_t capacity\_ = 0;
T\* data\_ = nullptr;
};

using T = size_t;
using D = DynArray\<T>;

void Solution(size_t m, size_t n, D weight, D price) {
DynArray\<D> dp(n + 1, D(m + 1, 0)); // dp\[i\]\[j\] - max price for items\[0...i\] with max weight = j.
for (size_t i = 1; i \<= n; ++i) {
for (size_t j = 1; j \<= m; ++j) {
if (j >= weight\[i - 1\]) { // can put items\[i\]
dp\[i\]\[j\] = std::max(dp\[i - 1\]\[j\], dp\[i - 1\]\[j - weight\[i - 1\]\] + price\[i - 1\]);
} else {
dp\[i\]\[j\] = dp\[i - 1\]\[j\];
}
}
}
D result(n);
for (size_t i = n; i > 0; --i) {
if (dp\[i\]\[m\] != dp\[i - 1\]\[m\]) {
result.PushBack(i);
m -= weight\[i - 1\];
}
}
result.Output(true); // reverse output
}

int main() {
size_t n = 0;
size_t m = 0;
std::cin >> n >> m;
D weight(n);
D price(n);
weight.Input();
price.Input();
Solution(m, n, weight, price);
}
