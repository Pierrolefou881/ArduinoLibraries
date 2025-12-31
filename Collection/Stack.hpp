/*
 * ----------------------------------------------------------------------------
 * Stack
 * LIFO collection for data processing and concurrent access avoidance.
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
#pragma once
#include "ProcessingCollection.hpp"

namespace Collection
{
    /**
     * Last in, first out collection for processing purposes and avoiding
     * concurrent accesses.
     * @param T can be any data type. Must have a default constructor.
     */
    template<typename T>
    class Stack : public ProcessingCollection<T>
    {
    public:
        /**
         * Initializes this Stack as an empty collection.
         */
        Stack(void) = default;
        virtual ~Stack(void) = default;

        /**
         * Adds the provided item to this Stack.
         * @param item to add.
         */
        void push(const T& item) override
        {
            auto tmp = ProcessingCollection<T>::get_tail();
            auto new_tail = Memory::S_ptr<ProcessingCollection<T>>{ new Stack{ item } };
            static_cast<Stack<T>*>(new_tail.get())->attach(tmp);
            ProcessingCollection<T>::set_tail(new_tail);
        }

    private:
        Stack(const T& data) : ProcessingCollection<T>{ data }
        {
            // Empty body.
        }

        void attach(const Memory::S_ptr<ProcessingCollection<T>>& link)
        {
            ProcessingCollection<T>::set_tail(link);
        }
    };
}