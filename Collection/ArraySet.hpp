/*
 * ----------------------------------------------------------------------------
 * ArraySet
 * Unordered set based on array memory allocation.
 * Part of the ArduinoLibraries project, to be used with any Arduino board.
 * <https://github.com/Pierrolefou881/ArduinoLibraries>
 * ----------------------------------------------------------------------------
 *
 * Copyright (C) 2026  Pierre DEBAS
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
#include "UnorderedCollection.hpp"
#include "src/UnorderedArrayContainer.hpp"
#include <Memory.hpp>

namespace Collection
{
    /**
     * Simple generic, unordered collection. Duplicate elements
     * are not allowed. Memory allocation is based on arrays.
     * @param T can be any type as long as it has a default intializer.
     *          Usually smart pointers.
     */
    template <typename T>
    class ArraySet : public UnorderedCollection<T>
    {
    public:
        virtual ~ArraySet(void) = default;

        /**
         * Tries to add the provided item to this ArraySet and
         * at the specified index (at the beginning if no index is provided).
         * @param item to add.
         * @param index where to add the item. Must be within bounds. 0 by default.
         * @return true if adding was succesfull, false otherwise.
         */
        bool add(const T& item, uint16_t index = 0) override
        {
            return _container->add(item, index);
        }

        /**
         * Adds the provided item at the end of this
         * ArraySet.
         * @param item to add.
         */
        void append(const T& item) override
        {
            _container->add(item, size());
        }

        /**
         * Removes the first (and only) encountered instance of the provided item.
         * @param item to remove.
         */
        void remove(const T& item) override
        {
            _container->remove(item);
        }

        /**
         * Removes the item at the specified position.
         * Does nothing if index is out of bounds.
         * @param index of the item to remove.
         */
        void remove_at(uint16_t index) override
        {
            _container->remove_at(index);
        }

        /**
         * Removes all items from this ArraySet.
         */
        void clear(void) override
        {
            _container->clear();
        }

        /**
         * Access the element at the given index.
         * CAUTION: ensure index is within bounds; there are no exceptions
         *          on Arduino platform.
         * @param index must be wihtin bounds.
         * @return the reference to the item at the given position.
         */
        T& at(uint16_t index) const override
        {
            return _container->data_at(index);
        }

        /**
         * Checks the presence of a given item within this ArraySet.
         * @param item to check.
         * @param out_index of the first encountered occurrence, if any. Out parameter.
         * @return true if item is present within this ArraySet,
         *         false otherwise.
         */
        bool contains(const T& item, uint16_t& out_index) const override
        {
            return _container->contains(item, out_index);
        }

        /**
         * @return the number of elements contained in this ArraySet.
         */
        uint16_t size(void) const override
        {
            return _container->get_size();
        }

    private:
        static const bool ALLOWS_DUPLICATES{ false };

        const Memory::U_ptr<ArrayContainer<T>> _container
        { 
            Memory::make_unique<ArrayContainer<T>, UnorderedArrayContainer<T>>(ALLOWS_DUPLICATES)  
        };
    };
}