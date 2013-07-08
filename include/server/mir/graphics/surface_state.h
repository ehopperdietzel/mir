/*
 * Copyright © 2013 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Kevin DuBois <kevin.dubois@canonical.com>
 */

#ifndef MIR_GRAPHICS_SURFACE_STATE_H_
#define MIR_GRAPHICS_SURFACE_STATE_H_

#include "surface_info.h"

#include <memory>
#include <functional>

namespace mir
{
namespace surfaces
{
class SurfaceInfo;
}
namespace graphics
{

class SurfaceState 
{
public:
    SurfaceState(std::shared_ptr<surfaces::SurfaceInfo> const& basic_info,
                 std::function<void()> change_cb);

    void apply_alpha(float alpha);
    float alpha() const;
};

}
}

#endif /* MIR_GRAPHICS_SURFACE_STATE_H_ */
