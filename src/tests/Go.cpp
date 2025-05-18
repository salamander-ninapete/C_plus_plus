// #include <iostream>
// #include <vector>

// #include "../s21_map/s21_map.h"
// #include "../s21_multiset/s21_multiset.h"
// #include "../s21_set/s21_set.h"
// // #include "container.hpp"
// int main() {
//   // Создаем объект AVLTree
//   s21::AVLTree<int, int> tree;

//   // // Вставляем элементы
//   tree.insert(1, 10);
//   tree.insert(2, 20);
//   tree.insert(3, 30);

//   // // Проверяем размер дерева
//   // std::cout << "Size: " << tree.size() << std::endl;  // Size: 3

//   // // Проверяем, пусто ли дерево
//   // std::cout << "Empty: " << tree.empty() << std::endl;  // Empty: 0

//   // // // Находим элемент по ключу
//   // auto it = tree.find(2);
//   // if (it != tree.end()) {
//   //   std::cout << "Found: " << *it << std::endl;  // Found: 2
//   // }

//   // // Проверяем, содержится ли элемент с заданным ключом
//   // std::cout << "Contains 3: " << tree.contains(3)
//   //           << std::endl;  // Contains 3: 1

//   // // Удаляем элемент
//   // tree.erase(it);
//   // std::cout << "Size after erase: " << tree.size()
//   //           << std::endl;  // Size after erase: 2

//   // // Проверяем, содержится ли элемент с заданным ключом после удаления
//   // std::cout << "Contains 2: " << tree.contains(2)
//   //           << std::endl;  // Contains 2: 0

//   //   // Очищаем дерево
//   //   tree.clear();
//   //   std::cout << "Size after clear: " << tree.size()
//   //             << std::endl;  // Size after clear: 0

//   //   // Проверяем, пусто ли дерево после очистки
//   //   std::cout << "Empty after clear: " << tree.empty()
//   //             << std::endl;  // Empty after clear: 1

//   //   // Создаем другое дерево
//   //   s21::AVLTree<int, int> tree2 = {{4, 40}, {5, 50}};

//   //   // // Объединяем деревья
//   //   // tree.merge(tree2);
//   //   // std::cout << "Size after merge: " << tree.size()
//   //   //           << std::endl;  // Size after merge: 2

//   //   // // Проверяем, содержится ли элемент с заданным ключом после
//   //   объединения
//   //   // std::cout << "Contains 4: " << tree.contains(4)
//   //   //           << std::endl;  // Contains 4: 1

//   //   // Проверяем максимальный размер дерева
//   //   std::cout << "Max size: " << tree.max_size()
//   //             << std::endl;  // Max size: (зависит от размера size_type)

//   //   // Используем оператор [] для доступа к элементу
//   //   tree[6] = 60;
//   //   std::cout << "Value at key 6: " << tree[6]
//   //             << std::endl;  // Value at key 6: 60

//   //   // Используем at для доступа к элементу
//   //   try {
//   //     std::cout << "Value at key 7: " << tree.at(7)
//   //               << std::endl;  // Key not found
//   //   } catch (const std::out_of_range& e) {
//   //     std::cout << e.what() << std::endl;
//   //   }

//   //   // Используем итераторы
//   //   for (auto it = tree.begin(); it != tree.end(); ++it) {
//   //     std::cout << "Iterator: " << *it
//   //               << std::endl;  // Iterator: 4, Iterator: 5, Iterator: 6
//   //   }

//   return 0;
// }

// int main() {
//   s21::AVLTree<int, int> tree;
//   return 0;
// }

// int main() {
//   // Создаем первое дерево
//   s21::BinaryTree<int, std::string> tree1;
//   tree1.insert(1, "one");
//   tree1.insert(2, "two");
//   tree1.insert(3, "three");

//   // Создаем второе дерево и присваиваем ему первое дерево
//   s21::BinaryTree<int, std::string> tree2;
//   tree2 = tree1;

//   // Проверяем, что деревья совпадают
//   std::cout << "Tree 1 size: " << tree1.size() << std::endl;
//   std::cout << "Tree 2 size: " << tree2.size() << std::endl;

//   // Добавляем элемент в первое дерево и проверяем, что второе дерево не
//   // изменилось
//   tree1.insert(4, "four");
//   std::cout << "Tree 1 size after insert: " << tree1.size() << std::endl;
//   std::cout << "Tree 2 size after insert: " << tree2.size() << std::endl;

//   return 0;
// }
// int main() {
//   // Создаем экземпляр BinaryTree с типом ключа int и типом значения

//   s21::Map<int, std::string> tree;
//   // Добавляем элементы в дерево
//   tree.insert(1, "one");
//   tree.insert(2, "two");
//   tree.insert(3, "four");
//   tree.insert(-1, "m_one");
//   tree.insert(-2, "m_two");
//   s21::Map<int, std::string> grass(tree);
//   std::cout << "Under 1     we hawe value: " << grass[1] << std::endl;
//   grass.at(2) = "333";
//   // Выводим размер дерева
//   std::cout << "Under start we hawe value: " <<
//   ((grass.begin().get())->value_)
//             << std::endl;
//   std::cout << "Under 2     we hawe value: " << grass.at(2) << std::endl;
//   grass.insert(-2, "m_two");

//   grass.erase(grass.find(7));
//   grass.erase(grass.find(3));
//   grass.insert(3, "four");
//   grass.erase(grass.find(2));
//   grass.erase(grass.find(-1));
//   std::cout << "Under -2    we hawe value: " << grass.at(-2) << std::endl;

//   grass.swap(tree);
//   tree.merge(grass);
//   auto range = tree.equal_range(2);
//   std::cout << "First key in range: " << range.first.get()->key_ <<
//   std::endl; std::cout << "Last key in range: " << range.second.get()->key_
//   << std::endl;

//   s21::Map<int, char> map{{1, 'a'}, {2, 'b'}, {3, 'c'}};

//   auto it = map.begin();
//   map.erase(it);

//   // // Проверяем, пусто ли дерево
// std::cout << "Is the tree empty? " << (tree.empty() ? "Yes" : "No")
//           << std::endl;

// Выводим элементы дерева
// std::cout << "Elements in the tree:" << std::endl;
// for (auto it = tree.begin(); it != tree.end(); ++it) {
//   std::cout << "Key: " << it->first << ", Value: " << it->second <<
//   std::endl;
// }

// // Очищаем дерево
// tree.clear();

// // Проверяем, пусто ли дерево после очистки
// std::cout << "Is the tree empty after clear? "
//           << (tree.empty() ? "Yes" : "No") << std::endl;
//   std::cout << "Under -2    we hawe value: " << map.at(3) << std::endl;
//   return 0;
// }

// int main() {
//   s21::Set<int> mySet;
//   s21::Set<int> otherSet;

//   mySet.insert(1);
//   mySet.insert(2);
//   mySet.insert(3);

//   otherSet.insert(4);
//   otherSet.insert(5);

//   std::cout << "Set size before merge: " << mySet.size() << std::endl;

//   mySet.merge(otherSet);

//   std::cout << "Set size after merge: " << mySet.size() << std::endl;

//   for (auto it = mySet.begin(); it != mySet.end(); ++it) {
//     std::cout << "Key: " << it->key_ << std::endl;
//   }

//   return 0;
// }

// int main() {
//   s21::Multiset<int> tree;
//   s21::Multiset<int> otherMultiset;

//   // tree.insert(2);
//   // tree.insert(1);
//   // tree.insert(3);
//   // tree.insert(2);
//   // tree.insert(2);
//   // tree.insert(2);
//   // tree.insert(2);
//   tree.insert_many((2), (1), (3), (2), (2), (2));
//   // otherMultiset.insert(4);
//   // otherMultiset.insert(5);

//   std::cout << "Multiset size before merge: " << tree.size() << std::endl;

//   // tree.merge(otherMultiset);

//   std::cout << "Multiset size after merge: " << tree.size() << std::endl;

//   for (auto it = tree.begin(); it != tree.end(); ++it) {
//     std::cout << "Key: " << it->key_ << std::endl;
//   }

//   std::cout << "Count of key 2: " << tree.count(2) << std::endl;

//   return 0;
// }

// int main() {
//   s21::BinaryTree<int, std::string> tree;

//   auto results =
//       tree.insert_many(std::make_pair(1, "one"), std::make_pair(2, "two"),
//                        std::make_pair(3, "three"));

//   // for (const auto& result : results) {
//   //   if (result.second) {
//   //     std::cout << "Inserted: " << (result.first)->first << " -> "
//   //               << (result.first)->second << std::endl;
//   //   } else {
//   //     std::cout << "Failed to insert: " << (result.first)->first << " -> "
//   //               << (result.first)->second << std::endl;
//   //   }
//   // }
//   return 0;
// }