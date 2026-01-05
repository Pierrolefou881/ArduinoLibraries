/*
 * ----------------------------------------------------------------------------
 * Map
 * Interface definition for collections of key-indexed values.
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
     * Key-value coupler intended for use within Map
     * implementations.
     * @param TK must be a type that implements ==, !=, >, >=, <, and <=
     *        operators. Must have a default initializer.
     * @param TV can be any type. Must have a default constructor.
     */
    template<typename TK, typename TV>
    struct KeyValue
    {
        TK key{ };
        TV value{ };

        /**
         * Default initializer for declaration purposes.
         */
        KeyValue(void) = default;

        /**
         * Initializes this KeyValue with the provided key and value.
         * @param a_key must be unique.
         * @param a_value can be duplicate or nullptr.
         */
        KeyValue(const TK& a_key, const TV& a_value)
            : key{ a_key }, value{ a_value }
        {
            // Empty body
        }

        virtual ~KeyValue(void) = default;

        friend bool operator ==(const KeyValue<TK, TV>& a, const KeyValue<TK, TV>& b) { return a.key == b.key; }
        friend bool operator !=(const KeyValue<TK, TV>& a, const KeyValue<TK, TV>& b) { return a.key != b.key; }
        friend bool operator >=(const KeyValue<TK, TV>& a, const KeyValue<TK, TV>& b) { return a.key >= b.key; }
        friend bool operator <=(const KeyValue<TK, TV>& a, const KeyValue<TK, TV>& b) { return a.key <= b.key; }
        friend bool operator >(const KeyValue<TK, TV>& a, const KeyValue<TK, TV>& b) { return a.key > b.key; }
        friend bool operator <(const KeyValue<TK, TV>& a, const KeyValue<TK, TV>& b) { return a.key < b.key; }

        
    };
    template<typename TK, typename TV>
    bool operator ==(const KeyValue<TK, TV>& keyval, const TK& key) { return keyval.key == key; }
    template<typename TK, typename TV>
    bool operator ==(const TK& key, const KeyValue<TK, TV>& keyval) { return keyval == key; }
    template<typename TK, typename TV>
    bool operator !=(const KeyValue<TK, TV>& keyval, const TK& key) { return keyval.key != key; }
    template<typename TK, typename TV>
    bool operator !=(const TK& key, const KeyValue<TK, TV>& keyval) { return keyval != key; }
    template<typename TK, typename TV>
    bool operator >=(const KeyValue<TK, TV>& keyval, const TK& key) { return keyval.key >= key; }
    template<typename TK, typename TV>
    bool operator >=(const TK& key, const KeyValue<TK, TV>& keyval) { return keyval >= key; }
    template<typename TK, typename TV>
    bool operator <=(const KeyValue<TK, TV>& keyval, const TK& key) { return keyval.key <= key; }
    template<typename TK, typename TV>
    bool operator <=(const TK& key, const KeyValue<TK, TV>& keyval) { return keyval <= key; }
    template<typename TK, typename TV>
    bool operator >(const KeyValue<TK, TV>& keyval, const TK& key) { return keyval.key > key; }
    template<typename TK, typename TV>
    bool operator >(const TK& key, const KeyValue<TK, TV>& keyval) { return keyval > key; }
    template<typename TK, typename TV>
    bool operator <(const KeyValue<TK, TV>& keyval, const TK& key) { return keyval.key < key; }
    template<typename TK, typename TV>
    bool operator <(const TK& key, const KeyValue<TK, TV>& keyval) { return keyval < key; }

    /**
     * Interface definition for collections of key-indexed values.
     * Items are registered by unique and comparable keys. Duplicate
     * keys shall not be allowed, but duplicate values can.
     * @param TK must be a type that implements ==, !=, >, >=, <, and <=
     *        operators.
     * @param TV can be any type.
     */
    template<typename TK, typename TV>
    class Map
    {
    public:
        virtual ~Map(void) = default;

        /**
         * Registers the provided value with the provided key.
         * Should fail if key already exists wihtin this Map.
         * @param key should be unique.
         * @param value can be a duplicate or nullptr.
         * @return true if insertion successful, false otherwise.
         */
        virtual bool add(const TK& key, const TV& value) = 0;

        /**
         * Removes the value registered at the provided key.
         * Does nothing if key not found.
         * @param key indexing the item to remove.
         */
        virtual void remove(const TK& key) = 0;

        /**
         * Unregisters and removes all instances of the provided
         * item from this Map. Does nothing if said item is not
         * present.
         * @param item to remove.
         */
        virtual void remove_all(const TV& item) = 0;

        /**
         * Tries to retrieve the item registered at the provided key.
         * @param key to find the item for.
         * @param out_value out parameter for retrieved value.
         * @return true if item found, false otherwise.
         */
        virtual bool try_get(const TK& key, TV& out_value) = 0;

        /**
         * @return the number of elements contained in this Map.
         */
        virtual uint16_t size(void) const = 0;

        /**
         * Determines whether a provided key is in use within this Map.
         * @param key to check the presence of.
         * @return true if key found used in this Map, false otherwise.
         */
        virtual bool contains_key(const TK& key) const = 0;

        /**
         * Checks whether the provided value is present in this Map.
         * @param value to check the presence of.
         * @return true if at least one instance of value is present
         *         in this Map, false otherwise.
         */
        virtual bool contains(const TV& value) const = 0;

        /**
         * Accesses the KeyValue pair at the specified index.
         * CAUTION: ensure index is within bounds, for there are no
         * exceptions on Arduino boards.
         * @param index must be within bounds.
         * @return the key and value at the specified index.
         */
        virtual KeyValue<TK, TV> at(uint16_t index) const = 0;
        
        /**
         * Removes all elements from this Map and clears its
         * indexed keys. Restores this Map to an empty state.
         */
        virtual void clear(void) = 0;

        KeyValue<TK, TV> operator [](uint16_t index) { return at(index); }
    };
}