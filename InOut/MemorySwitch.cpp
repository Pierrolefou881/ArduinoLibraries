/*
 * ----------------------------------------------------------------------------
 * Copyright (C) 2025  Pierre DEBAS
 * <dpierre394@gmail.com>
 * ----------------------------------------------------------------------------
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "MemorySwitch.hpp"

/**
 * Initializes this MemorySwitch at the provided pin number and initializes its
 * wrapped DigitalInput.
 * @param pin_number must correspond to a physical pin on the Arduino board
 *                   attached to a binary input sensor.
 */
InOut::Digital::MemorySwitch::MemorySwitch(uint8_t pin_number)
    : DigitalInput(pin_number)
    , _switch{ Memory::make_unique<DigitalInput>(pin_number) }
{
    _switch->StateChanged->register_callback(this, &MemorySwitch::on_switch_state_changed);
}

/**
 * Actuates the wrapped DigitalInput to trigger its StateChanged event.
 * @return the current state of this MemorySwitch, since it is only
 *         modified through events.
 */
int16_t InOut::Digital::MemorySwitch::actuate_sensor(void) const
{
    _switch->read_value();
    return get_current_state();
}

void InOut::Digital::MemorySwitch::on_switch_state_changed(const InOutBase* sender, int args)
{
    if (sender == nullptr)  // Should never happen, here for suppress warning.
    {
        return;
    }
    auto new_state = get_current_state() ^ args;
    set_current_state(new_state);
}