/*
 * ----------------------------------------------------------------------------
 * Callable
 * Interface definition for callbacks and event handlers.
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

namespace Event
{
    /**
     * Interface definition for callbacks to be used in event handlers and
     * event handlers themselves.
     * All Callable implementations shall have a call function
     * referring to a sender and a context (arguments).
     * @param TS type of sender. Owner of the triggered event.
     * @param TA type of args. Defines the context of the call. 
     *           Can be of any type.
     */
    template<typename TS, typename TA>
    class Callable
    {
    public:
        /**
         * Initializes this Callable with the provided type.
         * @param type of the concrete class, for equality checks.
         */
        Callable(char type) : _type{ type }
        {
            // Empty body.
        }
        
        virtual ~Callable(void) = default;
        
        /**
         * Calls the registered method or function or collection
         * thereof.
         * @param sender instigator of the call.
         * @param args context of the call.
         */
        virtual void call(TS* sender, TA args) const = 0;

        /**
         * Checks whether this Callable is equal the provided one.
         * @param other to test equality with.
         * @return true if this and other are equal, false otherwise.
         */
        virtual bool equals(const Callable<TS, TA>& other) const
        {
            return _type == other._type;
        }

        friend bool operator ==(const Callable<TS, TA>& a, const Callable<TS, TA>& b)
        {
            return a.equals(b);
        }

        friend bool operator !=(const Callable<TS, TA>& a, const Callable<TS, TA>& b)
        {
            return !a.equals(b);
        }

    private:
        const char _type{ };
    };
}