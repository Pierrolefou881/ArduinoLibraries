/*
 * ----------------------------------------------------------------------------
 * ArrayContainer
 * Backend logic for array based collection memory allocation.
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
#include <stdint.h>

namespace Collection
{
    /**
     * Wrapper for arrays used in array-based collections such as
     * ArrayList, OrderedSet,...
     * ArrayContainer manages dynamic resizing of the array, insertion
     * and deletion of items.
     * @param T can be any type.
     */
    template<typename T>
    class ArrayContainer
    {
    public:
        virtual ~ArrayContainer(void)
        {
            delete _data;
        }

        /**
         * Adds the provided item at the specified index. In some cases,
         * index might not be used, so its value might not have an impact
         * upon success of insertion.
         * @param item to insert.
         * @param index of insertion.
         * @return true if insertion succesfull, false otherwise.
         */
        bool add(const T& item, uint16_t index = 0)
        {
            // Out of bounds, don't go further. Allow one step out of bound for appending.
            if (index > _current_size)
            {
                return false;
            }

            manage_capacity(_current_size + 1);
            _current_size++;
            do_add(item, index);
            return true;
        }

        /**
         * Removes the first encountered occurrence of the provided
         * item, if any. Does nothing otherwise. Uses permutation
         * algorithm to push the removed item out of this
         * ArrayContainer's size boundary.
         * @param item to remove.
         */
        void remove(const T& item)
        {
            uint16_t index{ };
            if (contains(item, index))
            {
                remove_at(index);
            }
        }

        /**
         * Removes the item at the provided index, if said index is valid.
         * Does nothing otherwise. Uses permutations to push the removed
         * item out of boundaries.
         */
        void remove_at(uint16_t index)
        {
            // Out of bounds; do nothing.
            if (index >= _current_size)
            {
                return;
            }
            _current_size--;
            for (auto i = index; i < _current_size; i++)
            {
                _data[i] = _data[i + 1];
            }

            manage_capacity(_current_size);
        }

        /**
         * Removes all occurrences of the provided item.
         * Does nothing if there is no instance of it.
         * @param item to remove completely.
         */
        void remove_all(const T& item)
        {
            for (uint16_t current_index = _current_size - 1; current_index > 0; current_index--)
            {
                if (_data[current_index] == item)
                {
                    _current_size--;
                    for (auto swap_index = current_index; 
                        swap_index < _current_size; 
                        swap_index++)
                    {
                        _data[swap_index] = _data[swap_index + 1];
                    }
                }
            }
            manage_capacity(_current_size);
        }

        /**
         * Removes all items from this ArrayContainer.
         * Does it by setting the size at 0.
         */
        void clear(void)
        {
            _current_size = 0;
            manage_capacity(_current_size);
        }

        /**
         * Checks the presence of a given item in the data array.
         * @param item to find.
         * @param out_index of the eventually found item.
         * @return true if the array contains the item, false otherwise.
         */
        virtual bool contains(const T& item, uint16_t& out_index) const
        {
            out_index = 0;
            for (uint16_t current_index = 0; current_index < _current_size; current_index++)
            {
                if (item == _data[current_index])
                {
                    out_index = current_index;
                    return true;
                }
            }
            return false;
        }

        /**
         * Retrieves an item at the given index.
         * CAUTION: ensure index is correct, for there are no
         *          exceptions on Arduino
         * @param index of the data to retrieve. Must be within bounds.
         * @return the reference to the sought after item.
         */
        T& data_at(uint16_t index) { return _data[index]; }

        /**
         * @return this ArrayContainer's current size.
         */
        uint16_t get_size(void) const { return _current_size; }
        
    protected:

        /**
         * Proceeds to the actual adding of an item at the given
         * index.
         * @param item to add.
         * @param index of insertion. Must be within bounds.
         */
        virtual void do_add(const T& item, uint16_t index)
        {
            T current_item = _data[index];
            _data[index] = item;
            for (auto i = index + 1; i < _current_size; i++)
            {
                auto tmp = _data[i];
                _data[i] = current_item;
                current_item = tmp;
            }
        }

    private:
        static const uint16_t MIN_CAPACITY{ 3 };
        static const uint16_t RESIZING_FACTOR{ 2 };

        T* _data{ new T[MIN_CAPACITY] };
        uint16_t _current_size{ };
        uint16_t _current_capacity{ MIN_CAPACITY };

        void manage_capacity(uint16_t future_size)
        {
            if (future_size == _current_capacity)
            {
                resize(_current_capacity * RESIZING_FACTOR);
            }
            else if(_current_capacity > MIN_CAPACITY && _current_capacity > RESIZING_FACTOR * future_size)
            {
                resize(_current_capacity / RESIZING_FACTOR);
            }
        }

        void resize(uint16_t new_size)
        {
            auto tmp = _data;
            _data = new T[new_size];
            for (uint16_t index = 0; index < _current_size; index++)
            {
                _data[index] = tmp[index];
            }
            delete tmp;
        }
    };
}