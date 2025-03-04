P. Itertools.Reversed — База 2024 2 сем. Задание 2. C++ — Яндекс.Контест

# P. Itertools.Reversed

| Ограничение времени | 1 секунда |
| --- | --- |
| Ограничение памяти | 64.0 Мб |
| Ввод | стандартный ввод или input.txt |
| Вывод | стандартный вывод или output.txt |

[https://gitlab.com/ibr11/cpp_psami_base_2023/-/tree/main/itertools/reversed](https://gitlab.com/ibr11/cpp_psami_base_2023/-/tree/main/itertools/reversed)

### Itertools

*Одним из минусов языка C++ является отсутствие удобного интерфейса работы с последовательностями и промежутками
значений, который, по большому счету сводится к ручному написанию циклов и работе со встроенными итераторами. С
введением библиотеки  в C++20 ситуация заметно улучшилась. В этом
цикле задач мы попытаемся решить заявленную проблему средствами C++17.*

### Reversed

Для прохода по контейнеру в обратном порядке в C++ необходимо написать подобный код:

```

for (auto it = container.rbegin(); it != container.rend(); ++it) {
    // ...
}

```

Сравните, например, с языком Python:

```

for x in reversed(container):
    # ...

```

Хотелось бы иметь подобный лаконичный код и в C++ (благо range-based for завезли в C++11):

```

for (auto&& x : reversed(container)) {
    // ...
}

```

Проблема в том, что в стандартной библиотеке (до C++20) нет сущности `reversed`, которую можно было использовать в
подобном контексте. Ну а раз так - надо ее реализовать самостоятельно!

### Детали реализации

Необходимо реализовать `Reversed` (класс или функцию), который возвращает объект некоторого класса (вам нужно его
реализовать) с определенными методами `begin` и `end`. Эти методы должны возвращать соответствующие обратные итераторы
переданного контейнера.

**Примеры:** (больше примеров см. в тестах)

```

std::vector<int> v{1, 2, 3, 4, 5};

for (int x : Reversed(v)) { ... }  // x in [5, 4, 3, 2, 1]

for (int& x : Reversed(v)) {
    x = 0;
}
// v == {0, 0, 0, 0, 0}

```

*Указание: вспомните как работает range-based for в C++*.

### Дополнительное задание 1

Поддержать обратные итераторы (см. примеры в тестах). Добавьте директиву `#define REVERSE_REVERSED_IMPLEMENTED` в файл с
решением для проверки дополнительного задания.

### Дополнительное задание 2

При наивной реализации (описанной в задании) `Reversed` не сможет работать со временными контейнерами:

```

for (auto x : Reversed(std::vector<int>{1, 2, 3, 4, 5})) { ... }  // Undefined behaviour!

```

Это связано с тем, что цикл будет работать с "висячими" (невалидными) итераторами, так как контейнер, на который они
ссылаются, будет уничтожен.

Решить эту проблему можно с помощью специализации `Reversed` на случай `rvalue` объектов. В этом случае в полях класса
необходимо сохранять не итераторы `rbegin` и `rend`, а контейнер целиком. Так мы гарантируем, что сохраненный контейнер
не будет уничтожен до выхода из цикла, и итераторы всегда будут ссылаться на живой объект.

Добавьте директиву `#define TEMPORARY_REVERSED_IMPLEMENTED` в файл с решением для проверки дополнительного задания.
