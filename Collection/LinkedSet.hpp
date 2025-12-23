/*
 * ----------------------------------------------------------------------------
 * LinkedSet
 * Unordered set based on composite dynamic memory allocation.
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
#include "UnorderedCollection.hpp"
#include "LinkedList.hpp"
#include <Memory.hpp>

namespace Collection
{
    // Forward declaration.
    template<typename T>
    class LinkedSet;

    /**
     * Iterates over LinkedSets without exposing inner algorithms.
     * @param T type conained witin the LinkedSet.
     */
    template<typename T>
    class LinkedSetIterator : public BaseIterator<T>
    {
    public:
        LinkedSetIterator(LinkedSet<T>* set) : _wrapped_iterator{ set->_list->create_iterator() }
        {
            // Empty body
        }

        virtual ~LinkedSetIterator(void) = default;

        /**
         * @return true if there is at least one element remaining to iterate
         *         over, false otherwise.
         */
        bool has_next(void) const override
        {
            return _wrapped_iterator->has_next();
        }

        /**
         * @return the element currently iterated over.
         */
        T& get(void) const override
        {
            return _wrapped_iterator->get();
        }

        /**
         * Moves to the next element.
         */
        void next(void) override
        {
            _wrapped_iterator->next();
        }

    private:
        Memory::U_ptr<BaseIterator<T>> _wrapped_iterator{ };
    };
    
    /**
     * Dynamic sized linked set of objects. Decorates a LinkedList and forbids
     * adding duplicates.
     * @param T can be any type as long as it has a default initializer.
     *          Usually smart pointers.
     */
    template<typename T>
    class LinkedSet : public UnorderedCollection<T>, public Iterable<T>
    {
    public:
        virtual ~LinkedSet(void) = default;

        /**
         * Tries to add the provided item to this LinkedSet and
         * at the specified index (at the beginning if no index is provided).
         * @param item to add.
         * @param index where to add the item. Must be within bounds. 0 by default.
         * @return true if adding was succesfull, false otherwise.
         */
        bool add(const T& item, uint16_t index = 0) override
        {
            uint16_t _{};
            return !contains(item, _) && _list->add(item, index);
        }

        /**
         * Adds the provided item at the end of this
         * LinkedSet.
         * @param item to add.
         */
        void append(const T& item) override
        {
            uint16_t _{};
            if (!contains(item, _))
            {
                _list->append(item);
            }
        }

        /**
         * Removes the first encountered instance of the provided item.
         * @param item to remove.
         */
        void remove(const T& item) override
        {
            _list->remove(item);
        }

        /**
         * Removes the item at the specified position.
         * Does nothing if index is out of bounds.
         */
        void remove_at(uint16_t index) override
        {
            _list->remove_at(index);
        }

        /**
         * Removes all items from this LinkedSet.
         */
        void clear(void) override
        {
            _list->clear();
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
            return _list->at(index);
        }

        /**
         * Checks the presence of a given item within this LinkedSet.
         * @param item to check.
         * @param out_index of the first instance encountered, if any. Out parameter.
         * @return true if item is present within this LinkedSet,
         *         false otherwise.
         */
        bool contains(const T& item, uint16_t& out_index) const override
        {
            return _list->contains(item, out_index);
        }

        /**
         * @return the number of elements contained in this LinkedSet.
         */
        uint16_t size(void) const override
        {
            return _list->size();
        }

        /**
         * @return a new instance of BaseIterator for this LinkedSet.
         */
        Memory::U_ptr<BaseIterator<T>> create_iterator(void) const override
        {
            return { new LinkedSetIterator<T>{ (LinkedSet*) this } };
        }

        friend class LinkedSetIterator<T>;

    private:
        Memory::U_ptr<LinkedList<T>> _list
        {
            Memory::make_unique<LinkedList<T>>()
        };
    };
}