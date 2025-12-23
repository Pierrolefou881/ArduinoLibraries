/*
 * ----------------------------------------------------------------------------
 * Iterable
 * Interface definition for collections that can produce iterators.
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
#include <U_ptr.hpp>

namespace Collection
{
    /**
     * Interface definition for collections that can produce iterators.
     * Useful for LinkedLists, LinkedSets, stacks, queues,...
     * @param T type of elements contained in the iterated over collection.
     */
    template<typename T>
    class Iterable
    {
    public:
        virtual ~Iterable(void) = default;

        /**
         * @return a new instance of BaseIterator for this Iterable.
         */
        virtual Memory::U_ptr<BaseIterator<T>> create_iterator(void) const = 0;
    };
}