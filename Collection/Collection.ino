/*
 * ----------------------------------------------------------------------------
 * Collection
 * Testbed for all collections.
 * Part of the ArduinoLibraries project, to be used with any Arduino board.
 * <https://github.com/Pierrolefou881/ArduinoLibraries>
 * ----------------------------------------------------------------------------
 *
 * Copyright (C) 2025  Pierre DEBAS
 * <dpierre394@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "ArrayList.hpp"
#include "LinkedList.hpp"
#include "LinkedSet.hpp"
#include "OrderedSet.hpp"
#include "Queue.hpp"
#include "Stack.hpp"
#include "ArrayMap.hpp"

// #define _LIST
// #define _ARRAY_LIST
// #define _ORDERED_SET
// #define _LINKED
// #define _LINKED_LIST
// #define _LINKED_SET
// #define _QUEUE
// #define _STACK
#define _ARRAY_MAP

Collection::UnorderedList<char>* charList{ };
Collection::LinkedSet<char>* charSet{ };
Collection::OrderedSet<char>* orderedCharSet{ };
Collection::ProcessingCollection<char>* processChar{ };
Collection::Map<int, char>* charMap{ };
char characters[] = { 'f', 'U', 'z', 'a', 'm', 't', 'B', 'P'};

int level{ };

void setup() {
  // put your setup code here, to run once:
  #ifdef _ARRAY_LIST
  charList = new Collection::ArrayList<char>{ };
  #endif

  #ifdef _LINKED_LIST
  charList = new Collection::LinkedList<char>{ };
  #endif

  #ifdef _ORDERED_SET
  // orderedCharSet = new Collection::OrderedSet<char>{ };
  orderedCharSet = new Collection::OrderedSet<char>{ Collection::SortingOrder::DESCENDING };
  #endif

  #ifdef _LINKED_SET
  charSet = new Collection::LinkedSet<char>{ };
  #endif

  #ifdef _QUEUE
  processChar = new Collection::Queue<char>{ };
  #endif

  #ifdef _STACK
  processChar = new Collection::Stack<char>{ };
  #endif

  #ifdef _ARRAY_MAP
  charMap = new Collection::ArrayMap<int, char>{ };
  #endif 

  pinMode(LED_BUILTIN, OUTPUT);
  level = LOW;
  Serial.begin(9600);
}

void loop() {

  #ifdef _LIST
  uint16_t index{ };
  // put your main code here, to run repeatedly:
  if (charList->size() < 5)
  {
    charList->append('a');
  }
  else if (charList->size() < 10)
  {
    charList->add('B', 4);
  }
  else if (charList->size() < 15)
  {
    charList->add('c');
  }
  else if (charList->contains('B', index))
  {
    // charList->remove_at(index);
    // charList->remove('B');
    charList->remove_all('a');
    // charList->clear();
  }
  print_collection(charList);
  #endif

  #ifdef _ORDERED_SET
  auto max_char_num = sizeof(characters) / sizeof(char);
  if (orderedCharSet->size() < max_char_num)
  {
    auto size = orderedCharSet->size();
    orderedCharSet->add(characters[size]);
    orderedCharSet->add(characters[size]);
  }
  print_collection(orderedCharSet);
  #endif

  #ifdef _LINKED_SET
  if (charSet->size() < 5)
  {
    charSet->append('a');   // Test there is no duplicate
    charSet->append('a' + charSet->size());
  }
  else if (charSet->size() < 10)
  {
    charSet->add('a', 3);
    charSet->add('a' + charSet->size(), 3);
  }
  else if (charSet->size() < 15)
  {
    charSet->add('a');
    charSet->add('a' + charSet->size());
  }
  print_collection(charSet);
  #endif

  #if defined(_QUEUE) || defined(_STACK)
  if (processChar->size() < 10)
  {
    auto to_insert = 'a' + processChar->size();
    processChar->push(to_insert);
  }
  else
  {
    Serial.print("POPPED\t");
    Serial.println(processChar->pop());
    // processChar->clear();
  }
  print_collection(processChar);
  #endif

  #ifdef _ARRAY_MAP
  auto size = charMap->size();
  if (size < 10)
  {
      charMap->add(size, 'A' + size % 2);
      charMap->add(size, 'M' + size % 2);
  }
  else
  {
      // charMap->remove(0);
      // charMap->remove_all('B');
      charMap->clear();
  }
  print_collection(charMap);
  #endif

  level ^= HIGH;
  digitalWrite(LED_BUILTIN, level);
  delay(2000);
}

#if defined(_QUEUE) || defined(_STACK)
void print_collection(Collection::ProcessingCollection<char>* collection)
#elif defined (_ARRAY_MAP)
void print_collection(Collection::Map<int, char>* collection)
#else
void print_collection(Collection::BaseCollection<char>* collection)
#endif
{
  #if (defined(_ARRAY_LIST) || defined(_ORDERED_SET))
  for (uint16_t index = 0; index < collection->size(); index++)
  {
    Serial.print(collection->at(index));
    Serial.print('\t');
  }
  #endif

  #ifdef _ARRAY_MAP
  auto cast_collection = static_cast<Collection::ArrayMap<int, char>*>(collection);
  for (uint16_t index = 0; index < cast_collection->size(); index++)
  {
    Serial.print(cast_collection->at(index).key);
    Serial.print(", ");
    Serial.print(cast_collection->at(index).value);
    Serial.print('\t');
  }
  #endif

  #ifdef _LINKED
  #ifdef _LINKED_LIST
  auto linked = static_cast<Collection::LinkedList<char>*>(collection);
  #elif defined (_LINKED_SET)
  auto linked = static_cast<Collection::LinkedSet<char>*>(collection);
  #elif defined(_QUEUE) || defined(_STACK)
  auto linked = static_cast<Collection::ProcessingCollection<char>*>(collection);
  #endif
  auto iterator = linked->create_iterator();
  while (iterator->has_next())
  {
    Serial.print(iterator->get());
    Serial.print('\t');
    iterator->next();
  }
  #endif
  Serial.println(collection->size());
}
