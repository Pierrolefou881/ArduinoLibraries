/*
 * ----------------------------------------------------------------------------
 * BaseCollection
 * Interface definition for all collections.
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
     * Defines base iterator behavior.
     * @param T type of items contained within the iterated over collection.
     */
    template<typename T>
    class BaseIterator
    {
    public:
        virtual ~BaseIterator(void) = default;

        /**
         * @return true if there is at least one element remaining to iterate
         *         over, false otherwise.
         */
        virtual bool has_next(void) const = 0;

        /**
         * @return the element currently iterated over.
         */
        virtual T& get(void) const = 0;

        /**
         * Moves to the next element.
         */
        virtual void next(void) = 0;
    };

    /**
     * Defines interface for all collections. Collections have the
     * avaibility to add, remove, check and clear items. It can
     * also provide informations on its size. Collections have indices, i.e.
     * they have a position system.
     * @param T can be any type.
     */
    template<typename T>
    class BaseCollection
    {
    public:
        virtual ~BaseCollection(void) = default;

        /**
         * Tries to add the provided item to this BaseCollection and
         * at the specified index (at the beginning if no index is provided).
         * @param item to add.
         * @param index where to add the item. Must be within bounds. 0 by default.
         * @return true if adding was succesfull, false otherwise.
         */
        virtual bool add(const T& item, uint16_t index = 0) = 0;

        /**
         * Removes the first encountered instance of the provided item.
         * @param item to remove.
         */
        virtual void remove(const T& item) = 0;

        /**
         * Removes the item at the specified position.
         * Does nothing if index is out of bounds.
         * @param index of the item to remove.
         */
        virtual void remove_at(uint16_t index) = 0;

        /**
         * Removes all items from this BaseCollection.
         */
        virtual void clear(void) = 0;

        /**
         * Access the element at the given index.
         * CAUTION: ensure index is within bounds; there are no exceptions
         *          on Arduino platform.
         * @param index must be wihtin bounds.
         * @return the reference to the item at the given position.
         */
        virtual T& at(uint16_t index) const = 0;

        /**
         * Checks the presence of a given item within this BaseCollection.
         * @param item to check.
         * @param out_index of the first instance encountered, if any. Out parameter.
         * @return true if item is present within this BaseCollection,
         *         false otherwise.
         */
        virtual bool contains(const T& item, uint16_t& out_index) const = 0;

        /**
         * @return the number of elements contained in this BaseCollection.
         */
        virtual uint16_t size(void) const = 0;

        T& operator [](uint16_t index) const { return at(index); }
        BaseCollection<T>& operator +=(const T& item) 
        { 
            add(item);
            return *this; 
        }

        BaseCollection<T>& operator -=(const T& item)
        {
            remove(item);
            return *this;
        }
    };
}