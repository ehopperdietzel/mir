/*
 * Copyright © 2013 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Alexandros Frantzis <alexandros.frantzis@canonical.com>
 */

#ifndef MIR_GRAPHICS_DISPLAY_CONFIGURATION_H_
#define MIR_GRAPHICS_DISPLAY_CONFIGURATION_H_

#include "mir/int_wrapper.h"
#include "mir/geometry/size.h"

#include <functional>
#include <vector>

namespace mir
{
namespace graphics
{

typedef IntWrapper<IntWrapperTypeTag::GraphicsConfCardId> DisplayConfigurationCardId;
typedef IntWrapper<IntWrapperTypeTag::GraphicsConfOutputId> DisplayConfigurationOutputId;

/**
 * Configuration information for a display card.
 */
struct DisplayConfigurationCard
{
    DisplayConfigurationCardId id;
};

/**
 * Configuration information for a display output mode.
 */
struct DisplayConfigurationMode
{
    geometry::Size size;
    double vrefresh_hz;
};

/**
 * Configuration information for a display output.
 */
struct DisplayConfigurationOutput
{
    /** The output's id. */
    DisplayConfigurationOutputId id;
    /** The id of the card the output is connected to. */
    DisplayConfigurationCardId card_id;
    /** The modes supported by the output. */
    std::vector<DisplayConfigurationMode> modes;
    /** The physical size of the output. */
    geometry::Size physical_size_mm;
    /** Whether the output is connected. */
    bool connected;
    /** The index in the 'modes' vector of the current output mode. */
    size_t current_mode_index;
};

std::ostream& operator<<(std::ostream& out, DisplayConfigurationMode const& val);
bool operator==(DisplayConfigurationMode const& val1, DisplayConfigurationMode const& val2);
bool operator!=(DisplayConfigurationMode const& val1, DisplayConfigurationMode const& val2);

std::ostream& operator<<(std::ostream& out, DisplayConfigurationOutput const& val);
bool operator==(DisplayConfigurationOutput const& val1, DisplayConfigurationOutput const& val2);
bool operator!=(DisplayConfigurationOutput const& val1, DisplayConfigurationOutput const& val2);

/**
 * Interface to a configuration of display cards and outputs.
 */
class DisplayConfiguration
{
public:
    virtual ~DisplayConfiguration() {}

    /** Executes a function object for each card in the configuration. */
    virtual void for_each_card(std::function<void(DisplayConfigurationCard const&)> f) const = 0;
    /** Executes a function object for each output in the configuration. */
    virtual void for_each_output(std::function<void(DisplayConfigurationOutput const&)> f) const = 0;

protected:
    DisplayConfiguration() = default;
    DisplayConfiguration(DisplayConfiguration const& c) = delete;
    DisplayConfiguration& operator=(DisplayConfiguration const& c) = delete;
};

}
}

#endif /* MIR_GRAPHICS_DISPLAY_CONFIGURATION_H_ */
