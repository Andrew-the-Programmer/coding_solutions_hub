#include <iostream>
#include <algorithm>
#include <functional>

template <class T, class I, class Cmp = std::less<T>>
void Merge(I begin, I mid, I end, I aux, Cmp cmp = Cmp()) {
  auto i1 = begin;
  auto i2 = mid;
  auto i = 0;
  while (i1 != mid && i2 != end) {
    if (cmp(*i1, *i2)) {
      aux[i++] = *(i1++);
    } else {
      aux[i++] = *(i2++);
    }
  }
  while (i1 != mid) {
    aux[i++] = *(i1++);
  }
  for (auto it = begin; it != i2; ++it) {
    *it = *(aux++);
  }
}

template <class T, class I, class Cmp = std::less<T>>  // O(n*log(n))
void MergeSort(I begin, I end, I aux, Cmp cmp = Cmp()) {
  size_t size = end - begin;

  if (size < 2) {
    return;
  }

  auto mid = begin + size / 2;

  MergeSort<T, I, Cmp>(begin, mid, aux, cmp);
  MergeSort<T, I, Cmp>(mid, end, aux, cmp);
  Merge<T, I, Cmp>(begin, mid, end, aux, cmp);
}

template <class T = int, class I = T*, class Cmp = std::less<T>>
void Sort(I begin, I end, Cmp cmp = Cmp()) {
  I aux = new T[end - begin];

  MergeSort<T, I, Cmp>(begin, end, aux, cmp);

  delete[] aux;
}

template <class T, class S = std::istream&>
T InputResult(S stream = std::cin) {
  T value;
  stream >> value;
  return value;
}

struct SomethingWentWrong {};

template <class T>
class DynArray {
 public:
  DynArray() : capacity_(0), size_(0), data_(nullptr) {
  }
  explicit DynArray(size_t capacity) : capacity_(capacity), size_(0), data_(new T[capacity]) {
  }
  ~DynArray() {
    delete[] data_;
  }

 public:
  const T& At(size_t index) const {
    if (index < size_) {
      return data_[index];
    }
    throw std::out_of_range{""};
  }
  T& At(size_t index) {
    if (index < size_) {
      return data_[index];
    }
    throw std::out_of_range{""};
  }

  size_t Size() const {
    return size_;
  }

  void PushBack(const T& value) {
    if (size_ < capacity_) {
      data_[size_++] = value;
    } else {
      throw SomethingWentWrong{};
    }
  }

  const T* begin() const {  // NOLINT
    return data_;
  }
  T* begin() {  // NOLINT
    return data_;
  }
  const T* end() const {  // NOLINT
    return data_ + size_;
  }
  T* end() {  // NOLINT
    return data_ + size_;
  }

  template <class S = std::istream&>
  void Input(size_t size, S stream = std::cin) {
    for (size_t i = 0; i < size; ++i) {
      PushBack(InputResult<T, S>(stream));
    }
  }
  template <class S = std::ostream&>
  void Output(S stream = std::cout) {
    for (size_t i = 0; i < Size(); ++i) {
      stream << At(i);
    }
  }

 protected:
  size_t capacity_;
  size_t size_;
  T* data_;
};

struct Student {
  std::string surname;
  std::string name;

  size_t inf_points = 0;
  size_t math_points = 0;
  size_t rus_points = 0;

  Student() = default;

  Student(const std::string& surname, const std::string& name, size_t inf_points, size_t math_points, size_t rus_points)
      : surname(surname), name(name), inf_points(inf_points), math_points(math_points), rus_points(rus_points) {
  }

  size_t PointsSum() const {
    return inf_points + math_points + rus_points;
  }

  double GPA() const {
    return static_cast<double>(PointsSum()) / 3;
  }

  bool operator<(const Student& other) const {
    return GPA() < other.GPA();
  }
  bool operator==(const Student& other) const {  
    return GPA() == other.GPA();
  }
  bool operator>=(const Student& other) const {
    return !(*this < other);
  }

  friend std::ostream& operator<<(std::ostream& stream, Student& p) {
    stream << p.surname << " " << p.name << std::endl;
    return stream;
  }

  friend std::istream& operator>>(std::istream& stream, Student& p) {
    stream >> p.surname >> p.name >> p.inf_points >> p.math_points >> p.rus_points;
    return stream;
  }
};

int main() {
  size_t n = 0;
  std::cin >> n;

  DynArray<Student> students(n);

  students.Input(n);

  Sort<Student>(students.begin(), students.end(), std::greater_equal<Student>{});

  students.Output();
}