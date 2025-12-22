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
    /**
     * Manages a group of Callabe implementations and triggers their
     * callback functions or methods when called. Offers the possibilty to
     * subscribe or unsubscribe to the event.
     */
    template<typename TS, typename TA>
    class EventHandler : public Callable<TS, TA>
    {
    public:
        /**
         * Initializes this EventHandler with default values.
         */
        EventHandler(void) : Callable<TS, TA>{ TYPE }
        {
            // Empty body.
        }
        virtual ~EventHandler(void) = default;

        void register_callback(void (*func)(TS*, TA))
        {
            
        }

        /**
         * Calls all registered callbacks and event handlers.
         * @param sender instigator of the call, usually this EventHandler's owner.
         * @param args context of the call, the reason to change.
         */
        void call(TS* sender, TA args) const override
        {
            auto linked = static_cast<Collection::LinkedList<Memory::S_ptr<Callable<TS, TA>>>*>(_callbacks.get());
            Collection::LinkedListIterator<Memory::S_ptr<Callable<TS, TA>>> iterator(linked);
            while (iterator.has_next()) 
            {
                iterator.get()->call(sender, args);
                iterator.next();
            }
        }

        /**
         * Checks whether this EventHandler is equal the provided one.
         * @param other to test equality with.
         * @return true if this and other are equal, false otherwise.
         */
        bool equals(const Callable<TS, TA>& other) const override
        {
            // Check type before performing a cast.
            if (!Callable<TS, TA>::equals(other))
            {
                return false;
            }

            auto eh = static_cast<const EventHandler<TS, TA>&>(other);
            return _callbacks == eh._callbacks;
        }

    private:
        static const char TYPE{ 'E' };

        Memory::U_ptr<Collection::LinkedList<Memory::S_ptr<Callable<TS, TA>>>> _callbacks
        {
            Memory::make_unique<Collection::LinkedList<Memory::S_ptr<Callable<TS, TA>>>>()
        };
    };
}