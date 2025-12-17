/*
 * ----------------------------------------------------------------------------
 * InputBase
 * Basic behavior for all input managing classes.
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
#include "InOutBase.hpp"

namespace InOut
{
    /**
     * Base behavior for input managing classes. All InputBase derived
     * types shall be able to read the input value and internally actuate
     * its _current_state member.
     */
    class InputBase : public InOutBase
    {
    public:
        InputBase(uint8_t pin_number);
        virtual ~InputBase(void) = default;

        int16_t read_value(void);

    protected:
        /**
         * This template hook only actuates the sensor. All further treatment
         * shall be performed within the read_value method.
         * @return the raw sensor value.
         */
        virtual int16_t actuate_sensor(void) const = 0;
    };
}