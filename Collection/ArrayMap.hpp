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
#include <Memory.hpp>
#include "OrderedSet.hpp"
#include "ArraySet.hpp"
#include "Stack.hpp"

namespace Collection
{
    /**
     * Concrete implementation of Map that uses data array for dynamic memory
     * allocation. Keys are stored within an ordered set, while values are stored
     * within an unordered set.
     * @param TK type of key. Must implement equality and comparison operators.
     *        Most frequently an integer or enumerated type.
     * @param TV can be any type as long as it has a default initializer.
     *        Generally, one should provde smart pointers as such type.
     */
    template<typename TK, typename TV>
    class ArrayMap : public Map<TK, TV>
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
            if (!_keys->add(key))
            {
                return false;
            }

            uint16_t index{ };
            return _keys->contains(key, index) && _values->add(value, index);
        }

        /**
         * Removes the value registered at the provided key.
         * Does nothing if key not found.
         * @param key indexing the item to remove.
         */
        void remove(const TK& key) override
        {
            uint16_t index{ };
            if (_keys->contains(key, index))
            {
                _keys->remove_at(index);
                _values->remove_at(index);
            }
        }

        /**
         * Unregisters and removes all instances of the provided
         * item from this ArrayMap. Does nothing if said item is not
         * present.
         * @param item to remove.
         */
        void remove_all(const TV& item) override
        {
            Stack<uint16_t> indices{ };
            for (uint16_t index = 0; index < _values->size(); index++)
            {
                if (_values->at(index) == item)
                {
                    indices.push(index);
                }
            }

            while (!indices.is_empty())
            {
                auto index = indices.pop();
                _keys->remove_at(index);
                _values->remove_at(index);
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
            auto success = _keys->contains(key, index);
            if (success)
            {
                out_value = _values->at(index);
            }
            return success;
        }

        /**
         * @return the number of elements contained in this Map.
         */
        uint16_t size(void) const override
        {
            return _keys->size();
        }

        /**
         * Determines whether a provided key is in use within this Map.
         * @param key to check the presence of.
         * @return true if key found used in this Map, false otherwise.
         */
        bool contains_key(const TK& key) const override
        {
            uint16_t _{};
            return _keys->contains(key, _);
        }

        /**
         * Checks whether the provided value is present in this Map.
         * @param value to check the presence of.
         * @return true if at least one instance of value is present
         *         in this Map, false otherwise.
         */
        bool contains(const TV& value) const override
        {
            uint16_t _{ };
            return _values->contains(value, _);
        }

        /**
         * Accesses the KeyValue pair at the specified index.
         * CAUTION: ensure index is within bounds, for there are no
         * exceptions on Arduino boards.
         * @param index must be within bounds.
         * @return the key and value at the specified index.
         */
        KeyValue<TK, TV> at(uint16_t index) const
        {
            return { _keys->at(index), _values->at(index) };
        }
        
        /**
         * Removes all elements from this Map and clears its
         * indexed keys. Restores this Map to an empty state.
         */
        void clear(void) override
        {
            _keys->clear();
            _values->clear();
        }

        KeyValue<TK, TV> operator [](uint16_t index) { return at(index); }

    private:
        const Memory::U_ptr<Collection::OrderedCollection<TK>> _keys
        {
            Memory::make_unique<Collection::OrderedCollection<TK>, Collection::OrderedSet<TK>>()
        };

        const Memory::U_ptr<Collection::UnorderedCollection<TV>> _values
        {
            Memory::make_unique<Collection::UnorderedCollection<TV>, Collection::ArrayList<TV>>()
        };
    };
}