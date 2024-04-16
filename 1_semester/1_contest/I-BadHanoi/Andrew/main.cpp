#include <iostream>

enum Tower { first = 1, second = 2, third = 3 };

Tower RemainingTower(Tower first, Tower second) {
  return static_cast<Tower>(6 - first - second);
}

void MoveDisk(size_t index, Tower from, Tower to) {
  std::cout << index << " " << from << " " << to << "\n";
}

void StrangeHanoiSolution(size_t amount, Tower from, Tower to) {
  if (amount < 1) {
    return;
  }
  if (amount == 1) {
    if (to == Tower::second) {
      throw std::logic_error("");
    }
    MoveDisk(amount, from, to);
    return;
  }
  Tower remaining_tower = RemainingTower(from, to);
  StrangeHanoiSolution(amount - 1, from, to);
  MoveDisk(amount, from, remaining_tower);
  StrangeHanoiSolution(amount - 1, to, from);
  MoveDisk(amount, remaining_tower, to);
  StrangeHanoiSolution(amount - 1, from, to);
}

int main() {
  size_t amount = 0;
  std::cin >> amount;
  StrangeHanoiSolution(amount, Tower::first, Tower::third);
}