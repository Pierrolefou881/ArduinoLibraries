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
#include <LinkedSet.hpp>
#include <U_ptr.hpp>
#include <S_ptr.hpp>
#include "FunctionCallback.hpp"
#include "MethodCallback.hpp"

namespace Event
{
    /**
     * Manages a group of Callabe implementations and triggers their
     * callback functions or methods when called. Offers the possibilty to
     * subscribe or unsubscribe to the event.
     * @param TS type of sender.
     * @param TA type of args. Informations on the calling context and the
     *           reason for change.
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

        /**
         * Subscribes a function to this EventHandler.
         * @param function to be called on triggering.
         */
        void register_callback(void (*function)(TS*, TA))
        {
            Memory::S_ptr<Callable<TS, TA>> callback{ new FunctionCallback<TS, TA>{ function } };
            _callbacks->append(callback);
        }

        /**
         * Subscribes an instance method to this EventHandler.
         * @param TI type of instance.
         * @param instance to be called. Must not be nullptr.
         * @param method of instance to be called.
         */
        template<typename TI>
        void register_callback(TI* instance, void (TI::*method)(TS*, TA))
        {
            Memory::S_ptr<Callable<TS, TA>> callback{ new MethodCallback<TS, TA, TI>{ instance, method } };
            _callbacks->append(callback);
        }

        /**
         * Calls all registered callbacks.
         * @param sender instigator of the call, usually this EventHandler's owner.
         * @param args context of the call, the reason to change.
         */
        void call(TS* sender, TA args) const override
        {
            // auto linked = static_cast<Collection::LinkedSet<Memory::S_ptr<Callable<TS, TA>>>*>(_callbacks.get());
            // Collection::LinkedListIterator<Memory::S_ptr<Callable<TS, TA>>> iterator(linked);
            auto iterator = _callbacks->create_iterator();
            while (iterator->has_next()) 
            {
                iterator->get()->call(sender, args);
                iterator->next();
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

        Memory::U_ptr<Collection::LinkedSet<Memory::S_ptr<Callable<TS, TA>>>> _callbacks
        {
            Memory::make_unique<Collection::LinkedSet<Memory::S_ptr<Callable<TS, TA>>>>()
        };
    };
}