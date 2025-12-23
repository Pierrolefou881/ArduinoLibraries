/*
 * ----------------------------------------------------------------------------
 * MethodCallback
 * Callback for instance method called on an object.
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

namespace Event
{
    /**
     * Callback for instance methods. Holds a reference
     * to the instance and the method to call.
     * @param TS type of sender.
     * @param TA type of args, context and reason of the call.
     * @param TI type of instance of which method is called.
     */
    template<typename TS, typename TA, typename TI>
    class MethodCallback : public Callable<TS, TA>
    {
    public:
        /**
         * Initializes this MethodCallback with the provided instance
         * and pointer to method.
         * @param instance that needs to be call. Must not be nullptr.
         * @param method to be called.
         */
        MethodCallback(TI* instance, void (TI::*method)(TS*, TA))
            : Callable<TS, TA>{ TYPE }
            , _instance{ instance }
            , _method{ method }
        {
            // Empty body.
        }

        virtual ~MethodCallback(void) = default;

        /**
         * Calls the registered method for the registered instance.
         * @param sender instigator of the call.
         * @param args context of the call.
         */
        void call(TS* sender, TA args) const override
        {
            (_instance->*_method)(sender, args);
        }

        /**
         * Checks whether this Callable is equal the provided one.
         * @param other to test equality with.
         * @return true if this and other are equal, false otherwise.
         */
        bool equals(const Callable<TS, TA>& other) const override
        {
            if (!Callable<TS, TA>::equals(other))
            {
                return false;
            }
            auto mc = static_cast<const MethodCallback<TS, TA, TI>&>(other);
            return _instance == mc._instance && _method == mc._method;
        }

    private:
        static const char TYPE{ 'M' };

        TI* _instance{ };
        void (TI::*_method)(TS*, TA);
    };
}