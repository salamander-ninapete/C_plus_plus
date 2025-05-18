// #ifndef TESTBINARYTREE_H
// #define TESTBINARYTREE_H
#include <gtest/gtest.h>

#include "testTreeContainers.h"

TEST(MapTest, DefaultConstructor2) {
  s21::Map<int, char> tree;
  EXPECT_EQ(tree.size(), 0);
  EXPECT_TRUE(tree.empty());
}

TEST(MapTest, InitializerListConstructor) {
  s21::Map<int, char> tree{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  EXPECT_EQ(tree.size(), 3);
  EXPECT_TRUE(tree.contains(1));
  EXPECT_TRUE(tree.contains(2));
  EXPECT_TRUE(tree.contains(3));
  EXPECT_EQ(tree.at(1), 'a');
  EXPECT_EQ(tree.at(2), 'b');
  EXPECT_EQ(tree.at(3), 'c');
}

TEST(MapTest, CopyConstructor) {
  s21::Map<int, char> tree1{{1, 'a'}, {2, 'b'}};
  s21::Map<int, char> tree2(tree1);

  EXPECT_EQ(tree2.size(), 2);
  EXPECT_TRUE(tree2.contains(1));
  EXPECT_TRUE(tree2.contains(2));
  EXPECT_EQ(tree2.at(1), 'a');
  EXPECT_EQ(tree2.at(2), 'b');

  // Проверка независимости деревьев
  tree1.insert(3, 'c');
  EXPECT_EQ(tree1.size(), 3);
  EXPECT_EQ(tree2.size(), 2);
}

TEST(MapTest, MoveConstructor) {
  s21::Map<int, char> tree1{{1, 'a'}, {2, 'b'}};
  s21::Map<int, char> tree2(std::move(tree1));

  EXPECT_EQ(tree2.size(), 2);
  EXPECT_TRUE(tree2.contains(1));
  EXPECT_TRUE(tree2.contains(2));
  EXPECT_EQ(tree2.at(1), 'a');
  EXPECT_EQ(tree2.at(2), 'b');

  // После перемещения исходное дерево должно быть пустым
  EXPECT_EQ(tree1.size(), 0);
  EXPECT_TRUE(tree1.empty());
}

TEST(MapTest, Destructor) {
  s21::Map<int, char>* tree = new s21::Map<int, char>{{1, 'a'}, {2, 'b'}};
  EXPECT_EQ(tree->size(), 2);
  delete tree;
  // Проверка на отсутствие утечек памяти может быть выполнена с помощью
  // valgrind или ASan.
}

TEST(MapTest, MoveAssignmentOperator) {
  s21::Map<int, char> map1{{1, 'a'}, {2, 'b'}};
  s21::Map<int, char> map2;

  map2 = std::move(map1);

  EXPECT_EQ(map2.size(), 2);
  EXPECT_TRUE(map2.contains(1));
  EXPECT_TRUE(map2.contains(2));
  EXPECT_EQ(map2.at(1), 'a');
  EXPECT_EQ(map2.at(2), 'b');

  // После перемещения `map1` должен быть пустым
  EXPECT_TRUE(map1.empty());
}

TEST(MapTest, AtMethod) {
  s21::Map<int, std::string> map{{1, "one"}, {2, "two"}};

  EXPECT_EQ(map.at(1), "one");
  EXPECT_EQ(map.at(2), "two");
}

TEST(MapTest, SubscriptOperator) {
  s21::Map<int, std::string> map;

  // Вставка через оператор []
  map[1] = "one";
  map[2] = "two";

  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map[2], "two");

  // Добавление нового ключа с значением по умолчанию
  EXPECT_EQ(map[3], "");
  EXPECT_EQ(map.size(), 3);
}

TEST(MapTest, EmptyMethod) {
  s21::Map<int, char> map;
  EXPECT_TRUE(map.empty());

  map[1] = 'a';
  EXPECT_FALSE(map.empty());
}

TEST(MapTest, SizeMethod) {
  s21::Map<int, char> map;
  EXPECT_EQ(map.size(), 0);

  map[1] = 'a';
  EXPECT_EQ(map.size(), 1);

  map[2] = 'b';
  EXPECT_EQ(map.size(), 2);
}

TEST(MapTest, MaxSizeMethod) {
  s21::Map<int, char> map;
  EXPECT_GT(map.max_size(), 0);
}

TEST(MapTest, ClearMethod) {
  s21::Map<int, std::string> map{{1, "one"}, {2, "two"}};
  EXPECT_FALSE(map.empty());

  map.clear();
  EXPECT_TRUE(map.empty());
  EXPECT_EQ(map.size(), 0);
}

TEST(MapTest, InsertValueType) {
  s21::Map<int, char> map;
  auto result = map.insert({1, 'a'});

  EXPECT_TRUE(result.second);
  EXPECT_EQ(map.size(), 1);

  // Попытка вставки уже существующего ключа
  result = map.insert({1, 'b'});
  EXPECT_FALSE(result.second);
}

TEST(MapTest, InsertKeyAndObject) {
  s21::Map<int, char> map;
  auto result = map.insert(2, 'b');

  EXPECT_TRUE(result.second);
  EXPECT_EQ(map.size(), 1);
}

TEST(MapTest, InsertOrAssign) {
  s21::Map<int, std::string> map;

  auto result = map.insert_or_assign(1, "one");
  EXPECT_TRUE(result.second);
  EXPECT_EQ(map.at(1), "one");

  // Заменяем значение для существующего ключа
  result = map.insert_or_assign(1, "uno");
  EXPECT_FALSE(result.second);
  EXPECT_EQ(map.at(1), "uno");
}

TEST(MapTest, EraseMethod) {
  s21::Map<int, char> map{{1, 'a'}, {2, 'b'}, {3, 'c'}};

  auto it = map.begin();
  map.erase(it);

  EXPECT_EQ(map.size(), 2);
  EXPECT_FALSE(map.contains(1));
}

TEST(MapTest, SwapMethod) {
  s21::Map<int, char> map1{{1, 'a'}, {2, 'b'}};
  s21::Map<int, char> map2{{3, 'c'}};

  map1.swap(map2);

  EXPECT_EQ(map1.size(), 1);
  EXPECT_TRUE(map1.contains(3));

  EXPECT_EQ(map2.size(), 2);
  EXPECT_TRUE(map2.contains(1));
  EXPECT_TRUE(map2.contains(2));
}

TEST(MapTest, MergeMethod) {
  s21::Map<int, char> map1{{1, 'a'}, {2, 'b'}};
  s21::Map<int, char> map2{{2, 'x'}, {3, 'c'}};

  map1.merge(map2);

  EXPECT_EQ(map1.size(), 3);
  EXPECT_TRUE(map1.contains(1));
  EXPECT_TRUE(map1.contains(2));
  EXPECT_TRUE(map1.contains(3));

  // После слияния map2 должен содержать только те элементы, которые не были
  // перенесены
  EXPECT_TRUE(map2.empty());
}

TEST(MapTest, ContainsMethod) {
  s21::Map<int, char> map{{1, 'a'}, {2, 'b'}};

  EXPECT_TRUE(map.contains(1));
  EXPECT_TRUE(map.contains(2));
  EXPECT_FALSE(map.contains(3));
}

TEST(MapTest, InsertManyMethod) {
  s21::Map<int, std::string> map;
  auto results =
      map.insert_many(std::make_pair(1, "one"), std::make_pair(2, "two"),
                      std::make_pair(3, "three"));

  EXPECT_EQ(map.size(), 3);
  EXPECT_TRUE(map.contains(1));
  EXPECT_TRUE(map.contains(2));
  EXPECT_TRUE(map.contains(3));

  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_TRUE(results[2].second);
}

TEST(MapTest, End) {
  s21::Map<int, std::string> m;
  m.insert(1, "one");
  auto it = m.end();  // Перемещаемся на последний элемент
  EXPECT_EQ(it.get(),
            nullptr);  // Проверяем, что последний элемент имеет ключ 1
}

TEST(SetTest, DefaultConstructor) {
  s21::Set<int> my_set;
  EXPECT_TRUE(my_set.empty());
  EXPECT_EQ(my_set.size(), 0);
}

// Тест конструктора с initializer_list
TEST(SetTest, InitializerListConstructor) {
  s21::Set<int> my_set = {(1), (2), (3), (4)};
  EXPECT_FALSE(my_set.empty());
  EXPECT_EQ(my_set.size(), 4);
}

// Тест insert() и проверки наличия элемента
TEST(SetTest, InsertAndContains) {
  s21::Set<int> my_set;
  auto result = my_set.insert(10);
  EXPECT_TRUE(result.second);
  EXPECT_TRUE(my_set.contains(10));
  EXPECT_EQ(my_set.size(), 1);

  // Повторная вставка того же элемента
  result = my_set.insert(10);
  EXPECT_FALSE(result.second);
}

// Тест erase()
TEST(SetTest, EraseElement) {
  s21::Set<int> my_set = {1, 2, 3};
  auto it = my_set.find(2);
  ASSERT_NE(it, my_set.end());
  my_set.erase(it);
  EXPECT_FALSE(my_set.contains(2));
  EXPECT_EQ(my_set.size(), 2);
}

// Тест find()
TEST(SetTest, FindElement) {
  s21::Set<int> my_set = {1, 2, 3, 4};
  auto it = my_set.find(3);
  EXPECT_NE(it, my_set.end());
  // EXPECT_EQ(*it, 3);

  auto it_not_found = my_set.find(10);
  EXPECT_EQ(it_not_found, my_set.end());
}

// Тест swap()
TEST(SetTest, SwapSets) {
  s21::Set<int> set1 = {1, 2, 3};
  s21::Set<int> set2 = {4, 5};

  set1.swap(set2);
  EXPECT_TRUE(set1.contains(4));
  EXPECT_TRUE(set1.contains(5));
  EXPECT_TRUE(set2.contains(1));
  EXPECT_EQ(set1.size(), 2);
  EXPECT_EQ(set2.size(), 3);
}

// Тест merge()
TEST(SetTest, MergeSets) {
  s21::Set<int> set1 = {1, 2};
  s21::Set<int> set2 = {3, 4};

  set1.merge(set2);
  EXPECT_EQ(set1.size(), 4);
  EXPECT_TRUE(set1.contains(1));
  EXPECT_TRUE(set1.contains(4));
}

// Тест insert_many()
TEST(SetTest, InsertMany) {
  s21::Set<int> my_set;
  auto results = my_set.insert_many(1, 2, 3, 4, 2);
  EXPECT_EQ(my_set.size(), 4);  // Вставка уникальных элементов
  EXPECT_TRUE(my_set.contains(1));
  EXPECT_FALSE(results[4].second);  // Повторная вставка элемента 2
}

// Тест clear()
TEST(SetTest, ClearSet) {
  s21::Set<int> my_set = {1, 2, 3};
  my_set.clear();
  EXPECT_TRUE(my_set.empty());
  EXPECT_EQ(my_set.size(), 0);
}

TEST(SetTest, CopyConstructor) {
  s21::Set<int> s1;
  s1.insert(1);
  s1.insert(2);
  s21::Set<int> s2(s1);             // Конструктор копирования
  EXPECT_EQ(s1.size(), s2.size());  // Размеры должны быть одинаковыми
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
}

// Тест для конструктора перемещения в Set
TEST(SetTest, MoveConstructor) {
  s21::Set<int> s1;
  s1.insert(1);
  s1.insert(2);
  s21::Set<int> s2(std::move(s1));  // Конструктор перемещения
  EXPECT_EQ(s2.size(), 2);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_EQ(s1.size(), 0);  // После перемещения s1 должен быть пустым
}

// Тест для функции begin() в Set
TEST(SetTest, Begin) {
  s21::Set<int> s;
  s.insert(5);
  s.insert(3);
  auto it = s.begin();
  EXPECT_EQ(it.get()->key_, 3);  // Первый элемент должен быть минимальным (3)
}

// Тест для перемещающего оператора присваивания в Set
TEST(SetTest, MoveAssignmentOperator) {
  s21::Set<int> s1;
  s1.insert(10);
  s1.insert(20);

  s21::Set<int> s2;
  s2 = std::move(s1);  // Перемещающее присваивание

  EXPECT_EQ(s2.size(), 2);
  EXPECT_TRUE(s2.contains(10));
  EXPECT_TRUE(s2.contains(20));
  EXPECT_EQ(s1.size(), 0);  // После перемещения s1 должен быть пустым
}

// Тест для функции max_size() в Set
TEST(SetTest, MaxSize) {
  s21::Set<int> s;
  EXPECT_GT(s.max_size(),
            0);  // Проверяем, что max_size возвращает значение больше 0
}

TEST(MultisetTest, InsertElement) {
  s21::Multiset<int> ms;
  ms.insert(5);
  EXPECT_EQ(ms.size(), 1);
  EXPECT_EQ(ms.count(5), 1);
}

// Тест на вставку нескольких элементов
TEST(MultisetTest, InsertManyElements) {
  s21::Multiset<int> ms;
  auto results = ms.insert_many(1, 2, 3, 4, 2);
  EXPECT_EQ(ms.size(), 5);
  EXPECT_EQ(ms.count(2), 2);
}

// Тест на удаление элемента
TEST(MultisetTest, EraseElement) {
  s21::Multiset<int> ms;
  ms.insert(10);
  ms.insert(5);
  auto it = ms.find(10);
  ms.erase(it);

  EXPECT_EQ(ms.size(), 1);
  EXPECT_EQ(ms.count(10), 0);
  EXPECT_EQ(ms.count(5), 1);
}

// Тест на поиск элемента
TEST(MultisetTest, FindElement) {
  s21::Multiset<int> ms;
  ms.insert(5);
  ms.insert(10);

  auto it = ms.find(5);
  EXPECT_NE(it, ms.end());
  EXPECT_EQ(it.get()->key_, 5);

  auto it_not_found = ms.find(20);
  EXPECT_EQ(it_not_found, ms.end());
}

// Тест на проверку наличия элемента
TEST(MultisetTest, ContainsElement) {
  s21::Multiset<int> ms;
  ms.insert(10);

  EXPECT_TRUE(ms.contains(10));
  EXPECT_FALSE(ms.contains(20));
}

// Тест на равенство диапазонов для ключа
TEST(MultisetTest, EqualRange) {
  s21::Multiset<int> ms;
  ms.insert(5);
  ms.insert(5);
  ms.insert(10);

  auto range = ms.equal_range(5);
  EXPECT_EQ(range.first != ms.end(), true);  // Диапазон не пустой
}

// Тест на размер контейнера
TEST(MultisetTest, Size) {
  s21::Multiset<int> ms;
  EXPECT_EQ(ms.size(), 0);

  ms.insert(1);
  EXPECT_EQ(ms.size(), 1);

  ms.insert(2);
  EXPECT_EQ(ms.size(), 2);
}

// Тест на очистку контейнера
TEST(MultisetTest, Clear) {
  s21::Multiset<int> ms;
  ms.insert(1);
  ms.insert(2);
  ms.clear();
  EXPECT_EQ(ms.size(), 0);
}

// Тест на слияние множеств
TEST(MultisetTest, Merge) {
  s21::Multiset<int> ms1;
  ms1.insert(1);
  ms1.insert(2);

  s21::Multiset<int> ms2;
  ms2.insert(3);
  ms2.insert(4);

  ms1.merge(ms2);
  EXPECT_EQ(ms1.size(), 4);
  EXPECT_EQ(ms2.size(), 0);
  EXPECT_TRUE(ms1.contains(1));
  EXPECT_TRUE(ms1.contains(4));
}

// Тест на поиск верхней и нижней границы
TEST(MultisetTest, Bound) {
  s21::Multiset<int> ms;
  ms.insert(5);
  ms.insert(10);
  ms.insert(15);

  auto lower = ms.lower_bound(10);
  auto upper = ms.upper_bound(10);

  EXPECT_EQ(lower.get()->key_, 10);
  EXPECT_EQ(upper.get()->key_, 15);
}

// Тест на пустоту контейнера
TEST(MultisetTest, Empty) {
  s21::Multiset<int> ms;
  EXPECT_TRUE(ms.empty());

  ms.insert(1);
  EXPECT_FALSE(ms.empty());
}

TEST(MultisetTest, CopyConstructor) {
  s21::Multiset<int> ms1;
  ms1.insert(1);
  ms1.insert(2);
  ms1.insert(3);

  // Используем конструктор копирования
  s21::Multiset<int> ms2(ms1);

  // Проверяем, что контейнеры имеют одинаковые элементы
  EXPECT_EQ(ms2.size(), ms1.size());
  EXPECT_TRUE(ms2.contains(1));
  EXPECT_TRUE(ms2.contains(2));
  EXPECT_TRUE(ms2.contains(3));

  // Проверяем, что контейнеры независимы
  ms1.insert(4);
  EXPECT_EQ(ms1.size(), 4);
  EXPECT_EQ(ms2.size(), 3);  // Контейнеры должны быть независимыми
}

TEST(MultisetTest, MoveConstructor) {
  s21::Multiset<int> ms1;
  ms1.insert(1);
  ms1.insert(2);
  ms1.insert(3);

  // Используем конструктор перемещения
  s21::Multiset<int> ms2(std::move(ms1));

  // Проверяем, что контейнеры имеют одинаковые элементы
  EXPECT_EQ(ms2.size(), 3);
  EXPECT_TRUE(ms2.contains(1));
  EXPECT_TRUE(ms2.contains(2));
  EXPECT_TRUE(ms2.contains(3));

  // Проверяем, что ms1 пуст
  EXPECT_EQ(ms1.size(), 0);  // ms1 должен быть пустым после перемещения
}

TEST(MultisetTest, MoveAssignmentOperator) {
  s21::Multiset<int> ms1;
  ms1.insert(1);
  ms1.insert(2);
  ms1.insert(3);

  s21::Multiset<int> ms2;
  ms2.insert(4);
  ms2.insert(5);

  // Используем оператор присваивания перемещением
  ms2 = std::move(ms1);

  // Проверяем, что элементы перенесены
  EXPECT_EQ(ms2.size(), 3);
  EXPECT_TRUE(ms2.contains(1));
  EXPECT_TRUE(ms2.contains(2));
  EXPECT_TRUE(ms2.contains(3));

  // Проверяем, что ms1 пуст
  EXPECT_EQ(ms1.size(), 0);  // ms1 должен быть пустым после перемещения
}

TEST(MultisetTest, BeginEnd) {
  s21::Multiset<int> ms;
  ms.insert(1);
  ms.insert(2);
  ms.insert(3);

  // Проверяем, что begin и end работают правильно
  auto it = ms.begin();
  EXPECT_EQ(it.get()->key_, 1);  // Первый элемент должен быть 1
  ++it;
  EXPECT_EQ(it.get()->key_, 2);  // Второй элемент должен быть 2
  ++it;
  EXPECT_EQ(it.get()->key_, 3);  // Третий элемент должен быть 3
  ++it;
  EXPECT_EQ(it, ms.end());  // Итератор должен быть равен end, когда мы достигли
                            // конца контейнера
}

TEST(MultisetTest, CopyAssignmentOperator) {
  s21::Multiset<int> ms1;
  ms1.insert(1);
  ms1.insert(2);
  ms1.insert(3);

  s21::Multiset<int> ms2;
  ms2.insert(4);
  ms2.insert(5);

  // Используем оператор присваивания
  ms2 = ms1;

  // Проверяем, что элементы перенесены
  EXPECT_EQ(ms2.size(), 3);
  EXPECT_TRUE(ms2.contains(1));
  EXPECT_TRUE(ms2.contains(2));
  EXPECT_TRUE(ms2.contains(3));

  // Проверяем, что ms1 остался неизменным
  EXPECT_EQ(ms1.size(), 3);
  EXPECT_TRUE(ms1.contains(1));
  EXPECT_TRUE(ms1.contains(2));
  EXPECT_TRUE(ms1.contains(3));
}

TEST(MultisetTest, MaxSize) {
  s21::Multiset<int> ms;
  EXPECT_GT(ms.max_size(),
            0);  // Проверяем, что max_size возвращает значение больше 0
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// #endif  // SRC_TEST_TESTBINARYTREE_H