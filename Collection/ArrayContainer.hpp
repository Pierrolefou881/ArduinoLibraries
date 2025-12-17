/*
 * ----------------------------------------------------------------------------
 * ArrayContainer
 * Backend logic for array based collection memory allocation.
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
     * Wrapper for arrays used in array-based collections such as
     * ArrayList, OrderedSet,...
     * ArrayContainer manages dynamic resizing of the array, insertion
     * and deletion of items.
     */
    template<typename T>
    class ArrayContainer
    {
    public:
        virtual ~ArrayContainer(void) = default;

    protected:
        /**
         * @return the reference to this ArrayContainer's data array.
         */
        T* data(void) { return _data; }

        /**
         * @return this ArrayContainer's current size.
         */
        uint16_t get_size(void) const { return _current_size; }

        void check_size(uint16_t future_size)
        {
          
        }
    private:
        static const uint16_t MIN_SIZE{ 3 };
        static const uint16_t RESIZING_FACTOR{ 2 };

        T _data[MIN_SIZE]{ };
        uint16_t _current_size{ };
        uint16_t _current_capacity{ MIN_SIZE };
    };
}