/*
 * ----------------------------------------------------------------------------
 * OrderedArrayContainer
 * Backend logic for array based ordered collection memory allocation.
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
#include "../OrderedCollection.hpp"

namespace Collection
{
    /**
     * Concrete ArrayContainer specialized in sorting items by
     * comparison.
     * @param T must implement some sort of comparison with operators
     *          >, <, >=, <=, == and !=.
     */
    template<typename T>
    class OrderedArrayContainer : public ArrayContainer<T>
    {
    public:
        /**
         * Initializes this OrderedArrayContainer with an empty array and
         * duplication rule.
         * @param order to sort items with.
         * @param allows_duplicates indicates whether this OrderedArrayContainer
         *        shall allow data duplication. True by default.
         */
        OrderedArrayContainer(const SortingOrder& order, bool allows_duplicates = true) 
            : ArrayContainer<T>{ allows_duplicates }, _order{ order }
        {
            // Empty body
        }

        virtual ~OrderedArrayContainer(void) = default;

        /**
         * Adds the provided item at the correct index, so the one provided
         * shall not be used. Insertion should never fail.
         * @param item to insert.
         * @param index of insertion. used as inout parameter for contains.
         * @return true if insertion succesfull, should never return fase.
         */
        bool add(const T& item, uint16_t index = 0) override
        {
            // Get the right index and check duplication rule
            if (contains(item, index) && !ArrayContainer<T>::allows_duplicates())
            {
                return false;
            }
            
            ArrayContainer<T>::do_add(item, index);
            return true;
        }

        /**
         * Checks the presence of a given item in the data array via a dichotomic
         * algorithm.
         * @param item to find.
         * @param out_index of the eventually found item, or where it should be.
         * @return true if the array contains the item, false otherwise.
         */
        bool contains(const T& item, uint16_t& out_index) const override
        {
            out_index = 0;
            auto max = ArrayContainer<T>::get_size();

            // Empty collection, no item to find.
            if (max == 0)
            {
                return false;
            }

            max--;
            uint16_t min{ };
            for (auto middle = max; middle > min; middle = (min + max) / 2)
            {
                auto current_item = ArrayContainer<T>::data_at(middle);
                if (item == current_item)   // Item found, no need to look for it anymore.
                {
                    out_index = middle;
                    return true;
                }

                // Converge towards middle
                if ((_order == SortingOrder::ASCENDING && item > current_item) 
                        || (_order == SortingOrder::DESCENDING && item < current_item))
                {
                    min = middle;
                }
                else
                {
                    max = middle;
                }
            }

            auto upper_boundary = ArrayContainer<T>::data_at(max);
            auto lower_boundary = ArrayContainer<T>::data_at(min);
            if ((_order == SortingOrder::ASCENDING && item >= upper_boundary) 
                    || (_order == SortingOrder::DESCENDING && item <= upper_boundary))
            {
                out_index = max + 1;
            }
            else if ((_order == SortingOrder::ASCENDING && item < lower_boundary) 
                    || (_order == SortingOrder::DESCENDING && item > lower_boundary))
            {
                out_index = min;
            }
            else
            {
                out_index = max;
            }

            return item == lower_boundary || item == upper_boundary;
        } 

    private:
        SortingOrder _order;
    };
}