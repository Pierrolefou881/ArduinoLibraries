/*
 * ----------------------------------------------------------------------------
 * Copyright (C) 2025  Pierre DEBAS
 * <dpierre394@gmail.com>
 * ----------------------------------------------------------------------------
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "InOutBase.hpp"

/**
 * Initializes this InOutBase with the provided pin number and sets its state
 * to 0 (idle).
 * @param pin_number to assign to this InOutBase. Must correspond to a physical
 *                   pin on the Arduino board.
 */
InOut::InOutBase::InOutBase(uint8_t pin_number) 
    : _pin_number{ pin_number }
    , _current_state{ 0 }
{
    // Empty body
}

/**
 * @return the pin number assigned to this InOutBase.
 */
uint8_t InOut::InOutBase::get_pin_number(void) const
{
    return _pin_number;
}

/**
 * Accesses this InOutBase's current state. Should be used by derived types.
 * @return the reference to this InOutBase's current state.
 */
int16_t InOut::InOutBase::get_current_state(void) const
{
    return _current_state;
}

/**
 * Actuates this InOutBase's current state and notifies eventual
 * subscribers to the StateChanged event. does nothing if new_state
 * equal to _current_state member.
 * @param new_state desired for this InOutBase.
 */
void InOut::InOutBase::set_current_state(int16_t new_state)
{
    if (_current_state == new_state)
    {
        return;
    }
    _current_state = new_state;
}