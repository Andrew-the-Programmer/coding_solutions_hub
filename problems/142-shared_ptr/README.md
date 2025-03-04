C. SharedPtr — База 2024 2 сем. Задание 1. C++ — Яндекс.КонтестВаше участие в соревновании завершено. Вы можете дорешивать задачи и отправлять решения вне соревнования

# C. SharedPtr

| Ограничение времени | 1 секунда |
| --- | --- |
| Ограничение памяти | 64.0 Мб |
| Ввод | стандартный ввод или input.txt |
| Вывод | стандартный вывод или output.txt |

[https://gitlab.com/ibr11/cpp_psami_base/-/tree/main/shared_ptr](https://gitlab.com/ibr11/cpp_psami_base/-/tree/main/shared_ptr)

*Умные указатели реализуют важную идиому C++ - RAII (Resource Acquisition Is Initialization) и позволяют не заботиться о
ручном управлении памятью, так как инкапсулируют управление ресурсами посредством конструкторов и деструкторов.*

#### std::shared_ptr (C++11)

Шаблонный класс std::shared_ptr предоставляет интерфейс указателя на данные в динамической области с автоматическим
контролем своевременного выделения и удаления ресурсов. В отличие от std::unique_ptr, std::shared_ptr реализует
семантику разделяемого владения ресурсом, что означает, что у одного ресурса может быть несколько равноправных
владельцев. При этом гарантируется, что ресурс не будет освобожден пока существует хотя бы один его владелец (хотя бы
один объект std::shared_ptr указывает на ресурс). Для решения проблемы циклических ссылок в язык также введены
"слабые указатели" std::weak_ptr, которые не считаются полноценными владельцами ресурса, но из них при необходимости
можно получить "сильный указатель" std::shared_ptr на объект, если тот еще не удален.

Несмотря на то, что std::shared_ptr удобнее в использовании чем std::unique_ptr, на практике последний работает
гораздо эффективней - std::shared_ptr реализует дополнительную логику с подсчетом ссылок на объект. Поэтому
std::shared_ptr стоит использовать только тогда, когда вам действительно нужно разделяемое владение.

### Задание

Реализуйте шаблон SharedPtr - упрощенный аналог класса умного указателя с разделяемым владением.

Идея реализации: помимо самого указателя на выделенный ресурс необходимо знать число "сильных" и "слабых" ссылок на
объект. Для этого в куче выделим специальную счетчик strong_counter, который будет хранить эту информацию (при
создании нового указателя соответствующий счетчик увеличивается, при удалении - уменьшается; если число сильных ссылок
стало равно 0, то объект удаляется).

### Детали реализации

Детали обсуждались на лекции и семинарах.
Шаблонный класс SharedPtr должен поддерживать:

- Конструктор по умолчанию (создает нулевой указатель).
- Конструктор от указателя (сохраняет указатель на владеемый объект).
- Конструктор копирования и копирующее присваивание (создают новую ссылку на тот же объект).
- Перемещающий конструктор и перемещающее присваивание должны передавать владение объектом.
- Метод Reset(T\* ptr = nullptr), меняет указатель, которым владеет объект.
- Метод Swap(SharedPtr&).
- Метод Get(), возвращающий указатель на владеемый объект.
- Метод UseCount(), возвращающий число "сильных" ссылок на объект.
- Оператор разыменовывания operator\*.
- Оператор "стрелочка" operator->.
- Явный оператор приведения к bool (operator bool).

### Замечания.

- <https://en.cppreference.com/w/cpp/memory/shared_ptr>

- Решение должно состоять из одного файла shared_ptr.h

### Дополнительное задание

Реализуйте шаблон WeakPtr - аналог std::weak_ptr.
Для поддержки "слабых" ссылок (см. выше) предлагается вынести счетчик обычных (сильных) ссылок strong_count в
отдельную структуру Counter, в которую дополнительно добавить поле weak_count для подсчета количества слабых
указателей, указывающих на данный объект. Как и ранее, сам счетчик (объект Counter) должен находиться в динамической
памяти (вспомните почему), а указатель на него храниться в соответствующих объектах SharedPtr и WeakPtr. Логика
освобождения ресурса теперь следующая:

Если число сильных и слабых ссылок стало равно нулю, то удаляется и объект, и выделенный для него счетчик Counter.

Если число сильных стало равно нулю при ненулевом числе слабых, то удаляется только объект, счетчик остается жить
(то есть все сильные указатели уже "умерли", а некоторые слабые все еще ссылаются на данный счетчик).

Шаблон WeakPtr состоит из:

Аналогичных конструкторов (по умолчанию, копирования, перемещения) и операторов присваивания.

Конструктора от SharedPtr (увеличивает число "слабых" ссылок)

Метода Swap(WeakPtr&)

Метода Reset(), отвязывающего указатель от объекта

Метода UseCount(), возвращающего число "сильных" ссылок на объект

Метод Expired(), возвращающий true, если сильных ссылок на объект уже нет (объект удален)

Метод Lock(), возвращающий SharedPtr на объект (если Expired() == true, то возвращается пустой указатель)

В SharedPtr необходимо добавить конструктор от WeakPtr, который работает аналогично методу Lock(), но в случае
Expired() == true должно бросаться исключение BadWeakPtr.

### Замечания.

- <https://en.cppreference.com/w/cpp/memory/weak_ptr>

- Для проверки этой части добавьте в файл с решением (shared_ptr.h) директиву

`#define WEAK_PTR_IMPLEMENTED`
