/*
 * ----------------------------------------------------------------------------
 * MemorySwitch
 * DigitalInput decorator for memory buttons that change state when pressed
 * only.
 * of digital outputs include buttons, switches or any binary sensors.
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
#include "DigitalInput.hpp"
#include <Memory.hpp>

namespace InOut
{
    namespace Digital
    {
        /**
         * DigitalInput decorator that does not change its state until
         * the attached button is pressed again.
         */
        class MemorySwitch : public DigitalInput
        {
        public:
            MemorySwitch(uint8_t pin_number);
            virtual ~MemorySwitch(void) = default;

        protected:
            int16_t actuate_sensor(void) const override;

        private:
            Memory::U_ptr<DigitalInput> _switch{ };

            void on_switch_state_changed(const InOutBase* sender, int args);
        };
    }
}