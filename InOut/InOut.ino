/*
 * ----------------------------------------------------------------------------
 * InOut
 * Testbed for all InOutBase derived types.
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
#include "InOutBase.hpp"
#include "OutputBase.hpp"
#include "DigitalOutput.hpp"
#include "InputBase.hpp"
#include "DigitalInput.hpp"
#include "MemorySwitch.hpp"

// #define _TEST_DIGITAL_OUTPUT
// #define _TEST_DIGITAL_INPUT
#define _TEST_MEMORY_SWITCH

#ifdef _TEST_DIGITAL_OUTPUT
InOut::Digital::DigitalOutput led{ 2 };
InOut::Digital::DigitalOutput green{ 7 };
InOut::Digital::DigitalOutput yellow{ LED_BUILTIN };
uint16_t state{ };

void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
  state ^= HIGH;
  led.write_value(state);

  if (green.get_current_state() > LOW)
  {
    green.turn_off();
  }
  else 
  {
    green.turn_on();
  }

  yellow.toggle();
  delay(500);
}
#endif

#ifdef _TEST_DIGITAL_INPUT
InOut::Digital::DigitalInput btn{ 12 };

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2, btn.read_value());
  auto message = btn.is_active() ? "HIGH" : "LOW";
  Serial.println(message);
}
#endif

#ifdef _TEST_MEMORY_SWITCH
InOut::Digital::MemorySwitch btn{ 12 };

void setup() {
  pinMode(2, OUTPUT);
}

void loop() {
  digitalWrite(2, btn.read_value());
}
#endif

