#include <stdint.h>
/*
 * ----------------------------------------------------------------------------
 * ProcessingCollection
 * Abstract definition for collections used in data processing.
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
#include <Memory.hpp>
#include "Iterable.hpp"

namespace Collection
{
    // Forward declaration
    template<typename T>
    class ProcessingCollection;

    /**
     * Iterates over ProcessingCollections without exposing their inner
     * algorithms.
     * @param T type of element contained in the queue. Must have a default
     *        constructor.
     */
    template<typename T>
    class ProcessingCollectionIterator : public BaseIterator<T>
    {
    public:
        /**
         * Initializes this ProcessingCollectionIterator with the provided
         * ProcessingCollection.
         */
        ProcessingCollectionIterator(ProcessingCollection<T>* collection) 
            : _collection{ collection }
        {
            // Empty body.
        }

        virtual ~ProcessingCollectionIterator(void) = default;

        /**
         * @return true if there is at least one element remaining to iterate
         *         over, false otherwise.
         */
        bool has_next(void) const override
        {
            return _collection->_tail != nullptr;
        }

        /**
         * @return the element currently iterated over.
         */
        T& get(void) const override
        {
            return _collection->_tail->_data;
        }

        /**
         * Moves to the next element.
         */
        virtual void next(void) override
        {
            _collection = _collection->_tail.get();
        }

    private:
        ProcessingCollection<T>* _collection{ };
    };

    /**
     * Abstract definition for collections that can be used in data
     * processing, like stacks and queues. Unlike traditional
     * collections, ProcessingCollection offer visibility only to
     * the closest element. ProcessingCollection is implemented as a 
     * linked collection and can produce iterators.
     * @param T type of element contained in this ProcessingCollection.
     *        Must have a default constructor.
     */
    template<typename T>
    class ProcessingCollection : public Iterable<T>
    {
    public:
        /**
         * Initializes this ProcessingCollection as an empty collection.
         */
        ProcessingCollection(void) = default;

        virtual ~ProcessingCollection(void) = default;

        /**
         * Adds the provided item to this ProcessingCollection.
         * @param item to add.
         */
        virtual void push(const T& item) = 0;

        /**
         * Accesses and removes the head element.
         * @return the head element.
         */
        T pop(void)
        {
            if (is_empty())
            {
                return { };
            }
            auto ret_val = _tail->_data;
            auto new_tail = _tail->_tail;
            _tail = new_tail;
            return ret_val;
        }

        /**
         * Accesses the head element without removing it.
         * @return the reference to the head element.
         */
        T& peek(void) const
        {
            return *(_tail->_data);
        }

        /**
         * Removes all elements from this Queue.
         */
        void clear(void)
        {
            _tail = nullptr;
        }

        /**
         * @return true if this Queue has no element,
         *         false otherwise.
         */
        bool is_empty(void) const
        {
            return _tail == nullptr;
        }

        /**
         * @return the number of elements in this ProcessingCollection.
         */
        uint16_t size(void) const
        {
            return _tail == nullptr ? 0 : 1 + _tail->size(); 
        }

        /**
         * @return a new instance of ProcessingCollectionIterator for this 
         *         ProcessingCollection.
         */
        Memory::U_ptr<BaseIterator<T>> create_iterator(void) const override
        {
            return Memory::make_unique<BaseIterator<T>, ProcessingCollectionIterator<T>>((ProcessingCollection<T>*) this);
        }

        friend class ProcessingCollectionIterator<T>;
    
    protected:
        /**
         * Initializes a new link with the provided item.
         * @param item can be nullptr.
         */
        ProcessingCollection(const T& item) 
            : _data{ item }
        {
            // Empty body.
        }

        /**
         * @return a reference to _tail for inner working.
         */
        const Memory::S_ptr<ProcessingCollection<T>>& get_tail(void) const
        {
            return _tail;
        }

        /**
         * Assigns the provided valuie as the new _tail.
         * @param new_tail can be nullptr.
         */
        void set_tail(const Memory::S_ptr<ProcessingCollection<T>>& new_tail)
        {
            _tail = new_tail;
        }

    private:
        Memory::S_ptr<ProcessingCollection<T>> _tail{ };
        T _data{ };
    };
}