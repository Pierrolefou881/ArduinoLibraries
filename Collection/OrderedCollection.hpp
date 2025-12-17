/*
 * ----------------------------------------------------------------------------
 * OrderedCollection
 * Interface definition for ordered collections.
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
#include "BaseCollection.hpp"

namespace Collection
{
    /**
     * Declarative interface for ordered collections. In such
     * collections, items shall be sorted according to an
     * ascending or descending order.
     * @param T must have a comparison operators implemented.
     */
    template<typename T>
    class OrderedCollection : public BaseCollection<T>
    {
    public:
        enum class SortingOrder
        {
            ASCENDING,
            DESCENDING
        };
        
        virtual ~OrderedCollection(void) = default;
    };
}