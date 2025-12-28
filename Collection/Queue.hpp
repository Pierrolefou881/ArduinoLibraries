/*
 * ----------------------------------------------------------------------------
 * Queue
 * FIFO collection for data processing and concurrent access avoidance.
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
#include "Iterable.hpp"

namespace Collection
{
    /**
     * First in, first out collection for processing purposes and avoiding
     * concurrent accesses.
     * @param T can be any data type.
     */
    template<typename T>
    class Queue : public ProcessingCollection<T>
    {
    public:
        /**
         * Initializes this Queue as an empty collection.
         */
        Queue(void) = default;

        virtual ~Queue(void) = default;

        /**
         * Adds the provided item at the tail of this Queue.
         * @param item to add.
         */
        void push(const T& item) override
        {
            if (ProcessingCollection<T>::is_empty())
            {
              auto new_tail = Memory::S_ptr<ProcessingCollection<T>>{ new Queue{ item } };
              ProcessingCollection<T>::set_tail(new_tail);
            }
            else
            {
              ProcessingCollection<T>::get_tail()->push(item);
            }
        }
    private:
        Queue(const T& data) : ProcessingCollection<T>{ data }
        {
            // Empty body.
        }
    };
}