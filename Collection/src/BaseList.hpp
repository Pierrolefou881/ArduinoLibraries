/*
 * ----------------------------------------------------------------------------
 * BaseList
 * Interface definition for all list implementations.
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

namespace Collection
{
    /**
     * Defines behavior for all lists. Lists have the ability to
     * contain several instances of the same item.
     * @param T can be any type.
     */
    template<typename T>
    class BaseList
    {
    public:
        /**
         * Removes all instances of the provided item from this BaseList.
         * @param item to remove completeley.
         */
        virtual void remove_all(const T& item) = 0;
    };
}