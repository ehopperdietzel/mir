/*
 * Copyright © 2014 Canonical Ltd.
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
 * Authored by: Alan Griffiths <alan@octopull.co.uk>
 */

#ifndef MIR_SCENE_SURFACE_OBSERVER_H_
#define MIR_SCENE_SURFACE_OBSERVER_H_

#include "mir/geometry/size.h"
#include "mir_toolkit/common.h"

namespace mir
{
namespace scene
{
// Initial cut - supporting the frontend requirement, more will follow
class SurfaceObserver
{
public:
    virtual void attrib_change(MirSurfaceAttrib attrib, int value) = 0;
    virtual void resize(geometry::Size const& size) = 0;

protected:
    SurfaceObserver() = default;
    virtual ~SurfaceObserver() = default;
    SurfaceObserver(SurfaceObserver const&) = delete;
    SurfaceObserver& operator=(SurfaceObserver const&) = delete;
};
}
}

// TODO move to a sensible place
#include "mir/frontend/surface_id.h"
#include "mir/frontend/event_sink.h"
namespace mir
{
namespace scene
{
class FrontendObserver : public SurfaceObserver
{
public:
    FrontendObserver(
        frontend::SurfaceId id,
        std::shared_ptr<frontend::EventSink> const& event_sink);

    void attrib_change(MirSurfaceAttrib attrib, int value);
    void resize(geometry::Size const& size);

private:
    frontend::SurfaceId const id;
    std::shared_ptr<frontend::EventSink> const event_sink;
};
}
}

#endif // MIR_SCENE_SURFACE_OBSERVER_H_
