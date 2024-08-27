#include <cinttypes>

#include <cstring>
#include <iostream>

struct SomethingWentWrong {};

template <class T>
struct DequeNode {

  using Node = DequeNode;

  Node* next;
  Node* past;
  T value;

  DequeNode(Node* next, Node* past, const T& value) : next(next), past(past), value(value) {
  }

  ~DequeNode() {
    if (past && next) {
      past->next = next;
      next->past = past;
    } else if (past) {
      past->next = nullptr;
    } else if (next) {
      next->past = nullptr;
    }
  }

  Node* Front() {
    if (next) {
      return next->Front();
    }
    return this;
  }

  Node* Back() {
    if (past) {
      return past->Back();
    }
    return this;
  }

  static size_t Distance(const Node* first, const Node* second) {
    if (!first || !second) {
      return -1;
    }
    size_t count = 0;
    for (auto cur = first; cur; cur = cur->next) {
      if (cur == second) {
        return count;
      }
      ++count;
    }
    count = 0;
    for (auto cur = first; cur; cur = cur->past) {
      if (cur == second) {
        return count;
      }
      ++count;
    }
    return -1;
  }

  Node* Closest() {
    Node* return_ptr = nullptr;
    if (past) {
      return_ptr = past;
    } else if (next) {
      return_ptr = next;
    }
    return return_ptr;
  }

  Node* PushNext(const T& value) {
    if (next) {
      return nullptr;
    }
    return (next = new Node(nullptr, this, value));
  }

  Node* PushFront(const T& value) {
    return (Front()->PushNext(value));
  }

  Node* PushPast(const T& value) {
    if (past) {
      return nullptr;
    }
    return (past = new Node(this, nullptr, value));
  }

  Node* PushBack(const T& value) {
    return (Back()->PushPast(value));
  }

  Node* Pop() {
    Node* return_ptr = Closest();
    delete this;
    return return_ptr;
  }

  Node* PopFront() {
    return Front()->Pop();
  }

  Node* PopBack() {
    return Back()->Pop();
  }
};

struct DequeIsEmpty {};

template <class T>
class Deque {
 public:
  using Node = DequeNode<T>;

  Deque() : front_(nullptr), back_(nullptr), size_(0) {
  }
  ~Deque() {
    Clear();
  }

 protected:
  void IncreaseSize() {
    ++size_;
  }

  void DecreaseSize() {
    --size_;
  }

  void ThrowIfDequeIsEmpty() const {
    if (IsEmpty()) {
      throw DequeIsEmpty{};
    }
  }

  void TestIfAllGood() const {
    if (size_ == 0) {
      if (front_ || back_) {
        throw SomethingWentWrong{};
      }
    } else {
      if (Node::Distance(back_, front_) != size_ - 1) {
        throw SomethingWentWrong{};
      }
    }
  }

 public:
  bool IsEmpty() const {
    return size_ == 0;
  }

 public:
  void PushFront(const T& value) {
    if (IsEmpty()) {
      back_ = front_ = new Node(nullptr, nullptr, value);
    } else {
      front_ = front_->PushNext(value);
    }
    IncreaseSize();
  }

  void PushBack(const T& value) {
    if (IsEmpty()) {
      back_ = front_ = new Node(nullptr, nullptr, value);
    } else {
      back_ = back_->PushPast(value);
    }
    IncreaseSize();
  }

  void PopFront() {
    ThrowIfDequeIsEmpty();
    front_ = front_->Pop();
    DecreaseSize();
    if (size_ == 0) {
      back_ = nullptr;
    }
  }

  void PopBack() {
    ThrowIfDequeIsEmpty();
    back_ = back_->Pop();
    DecreaseSize();
    if (size_ == 0) {
      front_ = nullptr;
    }
  }

  void Clear() {
    while (!IsEmpty()) {
      PopFront();
    }
  }

  const T& Front() const {
    ThrowIfDequeIsEmpty();
    return front_->value;
  }

  const T& Back() const {
    ThrowIfDequeIsEmpty();
    return back_->value;
  }

  size_t Size() const {
    return size_;
  }

  void Log(std::ostream& ostream = std::cout) const {
    for (auto cur = back_; cur; cur = cur->next) {
      ostream << cur->value << " ";
    }
    ostream << std::endl;
  }

 protected:
  Node* front_;
  Node* back_;
  size_t size_;
};

template <class T, class S = std::istream&>
T Input(S stream = std::cin) {
  T value = T();
  stream >> value;
  return value;
}

using T = int;

int main() {
  auto k = Input<size_t>();

  Deque<T> deque;

  std::string command;

  for (size_t count = 0; count < k; ++count) {
    std::cin >> command;
    if (command == "exit") {
      std::cout << "bye\n";
      return 0;
    }
    if (command == "push_front") {
      deque.PushFront(Input<T>());
      std::cout << "ok\n";
    } else if (command == "push_back") {
      deque.PushBack(Input<T>());
      std::cout << "ok\n";
    } else if (command == "pop_front") {
      try {
        std::cout << deque.Front() << std::endl;
        deque.PopFront();
      } catch (DequeIsEmpty) {
        std::cout << "error" << std::endl;
      }
    } else if (command == "pop_back") {
      try {
        std::cout << deque.Back() << std::endl;
        deque.PopBack();
      } catch (DequeIsEmpty) {
        std::cout << "error" << std::endl;
      }
    } else if (command == "front") {
      try {
        std::cout << deque.Front() << std::endl;
      } catch (DequeIsEmpty) {
        std::cout << "error" << std::endl;
      }
    } else if (command == "back") {
      try {
        std::cout << deque.Back() << std::endl;
      } catch (DequeIsEmpty) {
        std::cout << "error" << std::endl;
      }
    } else if (command == "size") {
      std::cout << deque.Size() << std::endl;
    } else if (command == "clear") {
      deque.Clear();
      std::cout << "ok\n";
    }
  }
  return 0;
}