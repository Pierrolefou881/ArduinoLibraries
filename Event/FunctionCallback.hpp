/*
 * ----------------------------------------------------------------------------
 * FunctionCallback
 * Callback for non instance function.
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
    template<typename TS, typename TA>
    class FunctionCallback : public Callable<TS, TA>
    {
    public:
        FunctionCallback(void (*func)(TS*, TA))
            : Callable<TS, TA>{ TYPE }
            , _func{ func }
        {
            // Empty body.
        }

        virtual ~FunctionCallback(void) = default;

        /**
         * Calls the registered function.
         * @param sender instigator of the call.
         * @param args context of the call.
         */
        void call(TS* sender, TA args) const override
        {
            _func(sender, args);
        }

        /**
         * Checks whether this FunctionCallback is equal the provided one.
         * @param other to test equality with.
         * @return true if this and other are equal, false otherwise.
         */
        bool equals(const Callable<TS, TA>& other) const override
        {
            if (!Callable<TS, TA>::equals(other))
            {
                return false;
            }
            
            auto fc = static_cast<const FunctionCallback<TS, TA>&>(other);
            return _func == fc._func;
        }

    private:
        static const char TYPE{ 'F' };

        void (*_func)(TS*, TA);
    };
}