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
#include "src/Callable.hpp"
#include <LinkedSet.hpp>
#include <Memory.hpp>
#include "src/FunctionCallback.hpp"
#include "src/MethodCallback.hpp"

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
            auto callback = Memory::make_shared<Callable<TS, TA>, FunctionCallback<TS, TA>>(function);
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
            auto callback = Memory::make_shared<Callable<TS, TA>, MethodCallback<TS, TA, TI>>(instance, method);
            _callbacks->append(callback);
        }

        /**
         * Unsubscribes a function from this EventHandler.
         * @param function to unregister
         */
        void remove_callback(void (*function)(TS*, TA))
        {
            FunctionCallback<TS, TA> callback{ function };
            do_remove(callback);
        }

        /**
         * Unregisters an instance method from this EventHandler.
         * @param TI type of instance.
         * @param instance that was called. Must not be nullptr.
         * @param method that needs to be removed.
         */
        template<typename TI>
        void remove_callback(TI* instance, void (TI::*method)(TS*, TA))
        {
            MethodCallback<TS, TA, TI> callback{ instance, method };
            do_remove(callback);
        }

        /**
         * Calls all registered callbacks.
         * @param sender instigator of the call, usually this EventHandler's owner.
         * @param args context of the call, the reason to change.
         */
        void call(TS* sender, TA args) const override
        {
            auto iterable = static_cast<Collection::LinkedSet<Memory::S_ptr<Callable<TS, TA>>>*>(_callbacks.get());
            auto iterator = iterable->create_iterator();
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

        Memory::U_ptr<Collection::UnorderedCollection<Memory::S_ptr<Callable<TS, TA>>>> _callbacks
        {
            Memory::make_unique<Collection::UnorderedCollection<Memory::S_ptr<Callable<TS, TA>>>, 
                                Collection::LinkedSet<Memory::S_ptr<Callable<TS, TA>>>>()
        };

        void do_remove(const Callable<TS, TA>& callback)
        {
            auto iterator = _callbacks->create_iterator();
            bool has_found{ };
            Memory::S_ptr<Callable<TS, TA>> current_item{ };
            while (iterator->has_next() && !has_found)
            {
                current_item = iterator->get();
                has_found = callback.equals(current_item);
                iterator->next();
            }

            if (has_found)
            {
                _callbacks->remove(current_item);
            }
        }
    };
}