/*
 * ----------------------------------------------------------------------------
 * Copyright (C) 2025  Pierre DEBAS
 * <dpierre394@gmail.com>
 * ----------------------------------------------------------------------------
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "InputBase.hpp"

/**
 * Initializes this InputBase with the provided pin number.
 * @param pin_number shall correspond to a physical pin on the Arduino board.
 */
InOut::InputBase::InputBase(uint8_t pin_number) : InOutBase{ pin_number }
{
    // Empty body
}

int16_t InOut::InputBase::read_value(void)
{
    auto new_state = actuate_sensor();
    set_current_state(new_state);
    return new_state;
}