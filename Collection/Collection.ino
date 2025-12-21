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

// #define _ARRAY_LIST
#define _LINKED_LIST

Collection::UnorderedList<char>* charList{ };
int level{ };

void setup() {
  // put your setup code here, to run once:
  #ifdef _ARRAY_LIST
  charList = new Collection::ArrayList<char>{ };
  #endif
  #ifdef _LINKED_LIST
  charList = new Collection::LinkedList<char>{ };
  #endif
  pinMode(LED_BUILTIN, OUTPUT);
  level = LOW;
  Serial.begin(9600);
}

void loop() {

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
    // charList->remove_all('a');
    charList->clear();
  }

  level ^= HIGH;
  digitalWrite(LED_BUILTIN, level);
  print_list(*charList);
  delay(2000);
}

void print_list(const Collection::UnorderedList<char>& list)
{
  for (uint16_t index = 0; index < list.size(); index++)
  {
    Serial.print(list.at(index));
    Serial.print('\t');
  }
  Serial.println(list.size());
}
