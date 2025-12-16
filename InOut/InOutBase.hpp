/*
 * ----------------------------------------------------------------------------
 * InOutBase
 * Basic behavior for input and output managing classes.
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
#include <stdint.h>

namespace InOut
{
    /**
     * Basic behaviors for all objects managing inputs and outputs
     * on arduino boards. All InOuts have at least one pin number that
     * corresponds to a physical pin on an Arduino board.
     * InOutBase also keep trace of their current functionning state.
     * They are capable upon state change of propagating events
     * accordingly.
     */
    class InOutBase
    {
    public:
        virtual ~InOutBase(void) = default;

        uint8_t get_pin_number(void) const;
        int16_t get_current_state(void) const;

    protected:
        InOutBase(uint8_t pin_number);
        void set_current_state(int16_t new_state);
        
    private:
        // No negative value allowed. 255 max value is plenty enough.
        uint8_t _pin_number{ };

        // Allow negative values for eventual decorators.
        int16_t _current_state{ };
    };
}