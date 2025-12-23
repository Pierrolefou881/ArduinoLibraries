/*
 * ----------------------------------------------------------------------------
 * Event
 * Testbed for callbacks and event handlers.
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
#include "EventHandler.hpp"

struct TestButton
{
  int pin_number{ };
  int current_state{ };
  Event::EventHandler<const TestButton, int> StateChanged{ };

  TestButton(int a_pin_number) : pin_number{ a_pin_number } 
  {
    pinMode(a_pin_number, INPUT);
  }

  void read()
  {
    auto new_state = digitalRead(pin_number);
    if (new_state != current_state)
    {
      current_state = new_state;
      StateChanged.call(this, new_state);
    }
  }
};

TestButton btn{ 12 };
int state{ };
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  btn.StateChanged.register_callback(&on_button_pressed);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  btn.read();
  state ^= HIGH;
  digitalWrite(LED_BUILTIN, state);
  delay(500);
}

void on_button_pressed(const TestButton* sender, int args)
{
  if (sender == nullptr || args < 0)
  {
    return;
  }
  Serial.println("PRESSED");
}
