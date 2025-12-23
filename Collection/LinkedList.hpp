/*
 * ----------------------------------------------------------------------------
 * LinkedList
 * Unordered list based on composite dynamic memory allocation.
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
#include <Memory.hpp>
#include "Iterable.hpp"

namespace Collection
{
    // Forward declaration
    template<typename T>
    class LinkedList;

    /**
     * Iterates over LinkedLists without exposing inner algorithms.
     * @param T type conained witin the LinkedList.
     */
    template<typename T>
    class LinkedListIterator : public BaseIterator<T>
    {
    public:
        /**
         * Initializes this LinkedListIterator with the provided LinkedList
         * to iterate over.
         * @param list must not be nullptr.
         */
        LinkedListIterator(LinkedList<T>* list) : _list{ list }
        {
            // Empty body.
        }

        virtual ~LinkedListIterator(void) = default;

        /**
         * @return true if there is at least one element remaining to iterate
         *         over, false otherwise.
         */
        bool has_next(void) const override
        {
            return _list->_next != nullptr;
        }

        /**
         * @return the element currently iterated over.
         */
        T& get(void) const override
        {
            return *(_list->_next->_data);
        }

        /**
         * Moves to the next element.
         */
        void next(void) override
        {
            _list = _list->_next.get();
        }

    private:
        LinkedList<T>* _list{ };
    };

    /**
     * Dynamic sized linked list of objects.
     * @param T can be any type as long as it has a default initializer.
     *          Usually smart pointers.
     */
    template<typename T>
    class LinkedList : public UnorderedList<T>, public Iterable<T>
    {
    public:
        /**
         * Initializes this LinkedList as an empty list.
         */
        LinkedList(void) = default;
        virtual ~LinkedList(void) = default;

        /**
         * Tries to add the provided item to this LinkedList and
         * at the specified index (at the beginning if no index is provided).
         * @param item to add.
         * @param index where to add the item. Must be within bounds. 0 by default.
         * @return true if adding was succesfull, false otherwise.
         */
        bool add(const T& item, uint16_t index = 0) override
        {
            if (index >= *_current_size)
            {
              return false;
            }

            add_recursive(item, index, 0);
            return true;
        }

        /**
         * Adds the provided item at the end of this
         * LinkedList.
         * @param item to add.
         */
        void append(const T& item) override
        {
            if (_next == nullptr)
            {
                _next = new LinkedList<T>{ item, _current_size };
                (*_current_size)++;
            }
            else 
            {
                _next->append(item);
            }
        }

        /**
         * Removes the first encountered instance of the provided item.
         * @param item to remove.
         */
        void remove(const T& item) override
        {
            if (_next == nullptr)
            {
                return;
            }

            if (item == *(_next->_data))
            {
                remove_link();
                return;
            }
            _next->remove(item);
        }

        /**
         * Removes the item at the specified position.
         * Does nothing if index is out of bounds.
         */
        void remove_at(uint16_t index) override
        {
            if (index >= *_current_size)
            {
                return;
            }

            auto to_delete = access_link(index, 0);
            to_delete->remove_link();
        }

        /**
         * Removes all instances of the provided item from this LinkedList.
         * @param item to remove completeley.
         */
        void remove_all(const T& item) override
        {
            if (_next == nullptr)
            {
                return;
            }

            if (item == *(_next->_data))
            {
                remove_link();
                remove_all(item);   // re-run to avoid jumping links.
            }
            else
            {
                _next->remove_all(item);
            }
        }

        /**
         * Removes all items from this LinkedList.
         */
        void clear(void) override
        {
            _next = nullptr;
            *_current_size = 0;
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
            return *(access_link(index, 0)->_next->_data);
        }

        /**
         * Checks the presence of a given item within this LinkedList.
         * @param item to check.
         * @param out_index of the first instance encountered, if any. Out parameter.
         * @return true if item is present within this BaseCollection,
         *         false otherwise.
         */
        bool contains(const T& item, uint16_t& out_index = 0) const override
        {
            return _next != nullptr && (*(_next->_data) == item || _next->contains(item, ++out_index));
        }

        /**
         * @return the number of elements contained in this LinkedList.
         */
        uint16_t size(void) const override 
        { 
            return *_current_size;
        }

        /**
         * @return a new instance of BaseIterator for this LinkedList.
         */
        Memory::U_ptr<BaseIterator<T>> create_iterator(void) const override
        {
            return { new LinkedListIterator<T>{ (LinkedList<T>*) this } };
        }

        friend class LinkedListIterator<T>;

    private:
        Memory::S_ptr<T> _data{ };
        Memory::S_ptr<LinkedList<T>> _next{ };
        Memory::S_ptr<uint16_t> _current_size{ Memory::make_shared<uint16_t>() };

        // Link insertion Ctor.
        LinkedList(const T& item, const Memory::S_ptr<uint16_t>& current_size)
            : _data{ Memory::make_shared<T>(item) }
            , _next{ }
            , _current_size{ current_size }
        {
            // Empty body
        }

        void add_recursive(const T& item, uint16_t target_index, uint16_t current_index)
        {
            if (current_index == target_index)
            {
                auto tmp = _next;
                _next = new LinkedList<T>{ item, _current_size };
                _next->_next = tmp;
                (*_current_size)++;
            }
            else 
            {
                _next->add_recursive(item, target_index, current_index + 1);
            }
        }

        LinkedList<T>* access_link(uint16_t target_index, uint16_t current_index) const
        {
            return current_index == target_index ? (LinkedList<T>*) this : _next->access_link(target_index, current_index + 1);
        }

        void remove_link(void)
        {
            auto tmp = _next->_next;
            _next = tmp;
            (*_current_size)--;
        }
    };
}