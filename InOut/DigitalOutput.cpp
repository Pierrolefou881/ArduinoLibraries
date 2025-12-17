/*
 * ----------------------------------------------------------------------------
 * Copyright (C) 2025  Pierre DEBAS
 * <dpierre394@gmail.com>
 * ----------------------------------------------------------------------------
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "DigitalOutput.hpp"
#include <Arduino.h>

/**
 * Initializes this DigitalOutput with the provided pin number.
 * @param pin_number must correspond to a physical pin on the Arduino board
 *                   connected to a digital type of output.
 */
InOut::Digital::DigitalOutput::DigitalOutput(uint8_t pin_number)
    : OutputBase{ pin_number }
{
    pinMode(pin_number, OUTPUT);
}

void InOut::Digital::DigitalOutput::write_value(int16_t value)
{
    if (value < LOW)
    {
        value = LOW;
    }
    if (value > HIGH)
    {
        value = HIGH;
    }
    set_current_state(value);
    digitalWrite(get_pin_number(), value);  // TODO use future StateChanged event to trigger only when state actually changes.
}

/**
 * Sets this DigitalOutput's current state as active (HIGH).
 */
void InOut::Digital::DigitalOutput::turn_on(void)
{
    write_value(HIGH);
}

/**
 * Sets this DigitalOutput's current state as idle (LOW).
 */
void InOut::Digital::DigitalOutput::turn_off(void)
{
    write_value(LOW);
}

/**
 * Alternates from one state to the other. If this
 * DigitalOutput is active (HIGH), turns it off, turns it on otherwise.
 */
void InOut::Digital::DigitalOutput::toggle(void)
{
    auto new_state = get_current_state() ^ HIGH;
    write_value(new_state);
}