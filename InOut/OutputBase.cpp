/*
 * ----------------------------------------------------------------------------
 * Copyright (C) 2025  Pierre DEBAS
 * <dpierre394@gmail.com>
 * ----------------------------------------------------------------------------
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "OutputBase.hpp"

/**
 * Initializes this OutputBase with the provided pin number.
 * @param pin_number must correspond to a physical pin on the Arduino board.
 */
InOut::OutputBase::OutputBase(uint8_t pin_number)
    : InOutBase{ pin_number }
{
    // Empty body
}