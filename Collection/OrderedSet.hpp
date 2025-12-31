/*
 * ----------------------------------------------------------------------------
 * OrderedSet
 * Based on data array memory allocation.
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
#include "OrderedCollection.hpp"
#include "src/OrderedArrayContainer.hpp"
#include <Memory.hpp>

namespace Collection
{
    /**
     * Dynamic sized linked set of objects. Decorates a LinkedList and forbids
     * adding duplicates.
     * @param T can be any type as long as it has a default initializer.
     *          Usually smart pointers.
     */
    template<typename T>
    class OrderedSet : public OrderedCollection<T>
    {
    public:
        /**
         * Initializes this OrderedSet with the provided sorting order.
         * If no order is provided, ith should be ascending by default.
         * @param order set to ascending by default.
         */
        OrderedSet(const Collection::SortingOrder& order = Collection::SortingOrder::ASCENDING)
            : _container{ Memory::make_unique<ArrayContainer<T>, OrderedArrayContainer<T>>(order, ALLOWS_DUPLICATES) }
        {
            // Empty body
        }

        virtual ~OrderedSet(void) = default;

        /**
         * Tries to add the provided item to this OrderedSet. Should fail if
         * item already present.
         * @param item to add.
         * @param index can be any value, used as input parameter for inner
         *        algorithms, but value shall be reset. No real purpose then.
         * @return true if adding was succesfull, false otherwise.
         */
        bool add(const T& item, uint16_t index = 0) override
        {
            return _container->add(item, index);
        }

        /**
         * Removes the first encountered instance of the provided item.
         * @param item to remove.
         */
        void remove(const T& item) override
        {
            _container->remove(item);
        }

        /**
         * Removes the item at the specified position.
         * Does nothing if index is out of bounds.
         */
        void remove_at(uint16_t index) override
        {
            _container->remove_at(index);
        }

        /**
         * Removes all items from this OrderedSet.
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
         * Checks the presence of a given item within this OrderedSet.
         * @param item to check.
         * @param out_index of the first instance encountered, if any. Out parameter.
         * @return true if item is present within this OrderedSet,
         *         false otherwise.
         */
        bool contains(const T& item, uint16_t& out_index) const override
        {
            return _container->contains(item, out_index);
        }

        /**
         * @return the number of elements contained in this BaseCollection.
         */
        uint16_t size(void) const override
        {
            return _container->get_size();
        }

    private:
        static const bool ALLOWS_DUPLICATES{ false };
        Memory::U_ptr<ArrayContainer<T>> _container{ };
    };
}