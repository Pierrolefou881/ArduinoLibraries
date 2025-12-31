/*
 * ----------------------------------------------------------------------------
 * ArrayMap
 * Concrete implementation of Map that uses array memory allocation.
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
#include "Map.hpp"
#include "Iterable.hpp"
#include <Memory.hpp>
#include "LinkedList.hpp"

namespace Collection
{
    // Forward declaration.
    template<typename TK, typename TV>
    class ArrayMap;

    /**
     * Iterates over ArrayMap instances.
     * @param TK type of key. Must implement equality and comparison operators.
     *        Most frequently an integer or enumerated type.
     * @param TV can be any type as long as it has a default initializer.
     *        Generally, one should provde smart pointers as such type.
     */
    template<typename TK, typename TV>
    class ArrayMapIterator : public BaseIterator<KeyValue<TK, TV>>
    {
    public:
        /**
         * Initializes this ArrayMapIterator with the given ArrayMap
         * to iterate over.
         * @param map must not be nullptr.
         */
        ArrayMapIterator(ArrayMap<TK, TV>* map) : _map{ map }, _current_index{ 0 }
        {
            // Empty body.
        }

        /**
         * @return true if there is at least one element remaining to iterate
         *         over, false otherwise.
         */
        bool has_next(void) const override
        {
            return _current_index < _map->size();
        }

        /**
         * @return the element currently iterated over.
         */
        KeyValue<TK, TV>& get(void) const override
        {
            return _map->_keyvals->at(_current_index);
        }

        /**
         * Moves to the next element.
         */
        void next(void) override
        {
            _current_index++;
        }
    private:
        ArrayMap<TK, TV>* _map{ };
        uint16_t _current_index{ };
    };

    /**
     * Concrete implementation of Map that uses data array for dynamic memory
     * allocation. Implements also iterable for access to the whole collection.
     * @param TK type of key. Must implement equality and comparison operators.
     *        Most frequently an integer or enumerated type.
     * @param TV can be any type as long as it has a default initializer.
     *        Generally, one should provde smart pointers as such type.
     */
    template<typename TK, typename TV>
    class ArrayMap : public Map<TK, TV>, public Iterable<KeyValue<TK, TV>>
    {
    public:
        /**
         * Initializes this ArrayMap as an empty map.
         */
        ArrayMap(void) = default;
        virtual ~ArrayMap(void) = default;

        /**
         * Registers the provided value with the provided key.
         * Should fail if key already exists wihtin this ArrayMap.
         * @param key should be unique.
         * @param value can be a duplicate or nullptr.
         * @return true if insertion successful, false otherwise.
         */
        bool add(const TK& key, const TV& value) override
        {
            return _keyvals->add({ key, value }, 0);
        }

        /**
         * Removes the value registered at the provided key.
         * Does nothing if key not found.
         * @param key indexing the item to remove.
         */
        void remove(const TK& key) override
        {
            _keyvals->remove({ key, { } });
        }

        /**
         * Unregisters and removes all instances of the provided
         * item from this ArrayMap. Does nothing if said item is not
         * present.
         * @param item to remove.
         */
        void remove_all(const TV& item) override
        {
            LinkedList<uint16_t> indices{ };
            uint16_t index{ };
            auto iterator = create_iterator();
            while (iterator->has_next())
            {
                if (iterator->get().value == item)
                {
                    // todo stack
                }
                iterator->next();
            }
        }

        /**
         * Tries to retrieve the item registered at the provided key.
         * @param key to find the item for.
         * @param out_value out parameter for retrieved value.
         * @return true if item found, false otherwise.
         */
        bool try_get(const TK& key, TV& out_value) override
        {
            uint16_t index{ };
            if (_keyvals->contains({ key, { } }, index))
            {
                out_value = _keyvals->at(index).value;
                return true;
            }
            return false;
        }

        /**
         * @return the number of elements contained in this Map.
         */
        uint16_t size(void) const override
        {
            return _keyvals->size();
        }

        /**
         * Determines whether a provided key is in use within this Map.
         * @param key to check the presence of.
         * @return true if key found used in this Map, false otherwise.
         */
        bool contains_key(const TK& key) const override
        {
            uint16_t _{};
            return _keyvals->contains({ key, { } }, _);
        }

        /**
         * Checks whether the provided value is present in this Map.
         * @param value to check the presence of.
         * @return true if at least one instance of value is present
         *         in this Map, false otherwise.
         */
        bool contains(const TV& value) const override
        {
            auto iterator = create_iterator();
            while (iterator->has_next())
            {
                if (iterator->get().value == value)
                {
                    return true;
                }
                
                iterator->next();
            }
            return false;
        }
        
        /**
         * Removes all elements from this Map and clears its
         * indexed keys. Restores this Map to an empty state.
         */
        void clear(void) override
        {
            _keyvals->clear();
        }

        /**
         * @return a new instance of BaseIterator for this Iterable.
         */
        virtual Memory::U_ptr<BaseIterator<KeyValue<TK, TV>>> create_iterator(void) const override
        {
            return Memory::make_unique<BaseIterator<KeyValue<TK, TV>>, ArrayMapIterator<TK, TV>>((ArrayMap<TK, TV>*) this);
        }

        friend class ArrayMapIterator<TK, TV>;

    private:
        const Memory::U_ptr<OrderedSet<KeyValue<TK, TV>>> _keyvals
        {
            Memory::make_unique<OrderedSet<KeyValue<TK, TV>>>()
        };
    };
}