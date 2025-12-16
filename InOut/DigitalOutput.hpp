/*
 * ----------------------------------------------------------------------------
 * DigitalOutput
 * Concrete type managing any digital output pin on Arduino boards. Examples
 * of digital outputs include LEDs, H-Bridge pins or binary logic filters.
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
#include "OutputBase.hpp"

namespace InOut
{
    namespace Digital
    {   
        /**
         * Manages digital ouput pins on Arduino boards.
         * Digital output pins can either have a value of HIGH (1) or
         * LOW(0).
         */
        class DigitalOutput : public OutputBase
        {
        public:
            DigitalOutput(uint8_t pin_number);
            virtual ~DigitalOutput(void) = default;

            void write_value(int16_t value) override;
        };
    }
}