/*
 * ----------------------------------------------------------------------------
 * EventHandler
 * Calls a set of registered Callable implementations upon triggering.
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
#include "Callable.hpp"
#include <LinkedList.hpp>
#include <U_ptr.hpp>
#include <S_ptr.hpp>

namespace Event
{
    template<typename TS, typename TA>
    class EventHandler : public Callable<TS, TA>
    {
    public:
        void call(TS* sender, TA args) override
        {

        }

    private:
        Memory::U_ptr<Collection::UnorderedList<Memory::S_ptr<Callable<TS, TA>>>> _callbacks
        {
            new Collection::LinkedList<Memory::S_ptr<Callable<TS, TA>>>{ }
        };
    };
}