/*
 * ----------------------------------------------------------------------------
 * Copyright (C) 2025  Pierre DEBAS
 * <dpierre394@gmail.com>
 * ----------------------------------------------------------------------------
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "DigitalInput.hpp"
#include <Arduino.h>

/**
 * Initializes this DigitalInput at the provided pin number.
 * @param pin_number must correspond to a physical pin on the Arduino board,
 *                   connected to a binary sensor.
 */
InOut::Digital::DigitalInput::DigitalInput(uint8_t pin_number) 
    : InputBase{ pin_number }
{
    // Empty body.
}

/**
 * @return true if this DigitalInput is active (HIGH),
 *         false otherwise.
 */
bool InOut::Digital::DigitalInput::is_active(void)
{
    return read_value() > LOW;
}

/**
 * Triggers the digitalRead function at the given pin.
 * @return the value obtained through digitalRead.
 */
int16_t InOut::Digital::DigitalInput::actuate_sensor(void) const
{
    return digitalRead(get_pin_number());
}