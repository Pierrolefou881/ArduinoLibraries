/*
 * ----------------------------------------------------------------------------
 * Unotdered OrderedArrayContainer
 * Backend logic for array based unordered collection memory allocation.
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
#include "ArrayContainer.hpp"

namespace Collection
{
    template<typename T>
    class UnorderedArrayContainer : public ArrayContainer<T>
    {
    public:
        /**
         * Initializes this UnorderedArrayContainer with an empty array and
         * duplication rule.
         * @param allows_duplicates indicates whether this UnorderedArrayContainer
         *        shall allow data duplication. True by default.
         */
        UnorderedArrayContainer(bool allows_duplicates = true) : ArrayContainer<T>{ allows_duplicates }
        {
            // Empty body
        }

        virtual ~UnorderedArrayContainer(void) = default;

        /**
         * Adds the provided item at the specified index. Insertion should fail
         * if item strictly out of bounds, i.e. strictly superior to _current_size.
         * @param item to insert.
         * @param index of insertion. Max value _current_size.
         * @return true if insertion succesfull, false otherwise.
         */
        bool add(const T& item, uint16_t index = 0) override
        {
            uint16_t _;
            // Out of bounds, don't go further. Allow one step out of bound for appending.
            // Check duplication rule as well.
            if (index > ArrayContainer<T>::current_size() || (!ArrayContainer<T>::allows_duplicates() && contains(item, _)))
            {
                return false;
            }

            ArrayContainer<T>::do_add(item, index);
            return true;
        }

        /**
         * Checks the presence of a given item in the data array.
         * @param item to find.
         * @param out_index of the eventually found item.
         * @return true if the array contains the item, false otherwise.
         */
        bool contains(const T& item, uint16_t& out_index) const override
        {
            out_index = 0;
            for (uint16_t current_index = 0; current_index < ArrayContainer<T>::current_size(); current_index++)
            {
                if (item == ArrayContainer<T>::data_at(current_index))
                {
                    out_index = current_index;
                    return true;
                }
            }
            return false;
        }
    };
}