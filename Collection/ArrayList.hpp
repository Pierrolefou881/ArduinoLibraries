/*
 * ----------------------------------------------------------------------------
 * ArrayList
 * Unordered list based on array memory allocation.
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
#include "UnorderedList.hpp"
#include "UnorderedArrayContainer.hpp"

namespace Collection
{
    /**
     * Simple generic, unordered collection. Duplicate elements
     * are allowed. Memory allocation is based on arrays.
     */
    template <typename T>
    class ArrayList : public UnorderedList<T>, private UnorderedArrayContainer<T>
    {
    public:
        /**
         * Tries to add the provided item to this ArrayList and
         * at the specified index (at the beginning if no index is provided).
         * @param item to add
         * @param index where to add the item. Must be within bounds. 0 by default.
         * @return true if adding was succesfull, false otherwise.
         */
        bool add(const T& item, uint16_t index = 0) override
        {
            return false;
        }

        /**
         * Removes the first encountered instance of the provided item.
         * @param item to remove.
         */
        void remove(const T& item) override
        {

        }

        /**
         * Removes the item at the specified position.
         * Does nothing if index is out of bounds.
         */
        void remove_at(uint16_t index) override
        {

        }

        /**
         * Removes all instances of the provided item from this ArrayList.
         * @param item to remove completeley.
         */
        void remove_all(const T& item) override
        {

        }

        /**
         * Removes all items from this ArrayList.
         */
        void clear(void) override
        {

        }

        /**
         * Access the element at the given index.
         * CAUTION: ensure index is within bounds; there are no exceptions
         *          on Arduino platform.
         * @param index must be wihtin bounds.
         * @return the reference to the item at the given position.
         */
        T& at(uint16_t index) override
        {
            return data()[0];
        }

        /**
         * Checks the presence of a given item within this ArrayList.
         * @param item to check.
         * @return true if item is present within this ArrayList,
         *         false otherwise.
         */
        bool contains(const T& item) override
        {
            return false;
        }

        /**
         * @return the number of elements contained in this ArrayList
         */
        uint16_t size(void) const override
        {
            return 0;
        }
    private:
    };
}