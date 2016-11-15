/*
 * Copyright © 2014 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Kevin DuBois <kevin.dubois@canonical.com>
 */

#include "mir/graphics/nested_context.h"
#include "mir/graphics/platform_operation_message.h"
#include "nested_authentication.h"

#include "mir_toolkit/mesa/platform_operation.h"
#include "mir_toolkit/extensions/mesa_drm.h"

#include <boost/exception/errinfo_errno.hpp>
#include <boost/throw_exception.hpp>

#include <cstring>
#include <mutex>
#include <condition_variable>

namespace mg = mir::graphics;
namespace mgm = mir::graphics::mesa;

mgm::NestedAuthentication::NestedAuthentication(
    std::shared_ptr<NestedContext> const& nested_context)
    : nested_context{nested_context}
{
}

void mgm::NestedAuthentication::auth_magic(drm_magic_t magic)
{
    static int const success{0};

    int rc = -1;
    auto ext = nested_context->auth_extensions();
    if (ext.is_set())
        rc = ext.value()->auth_magic(magic);

    if (rc != success)
    {
        std::string const error_msg{
            "Nested server failed to authenticate DRM device magic cookie"};
        BOOST_THROW_EXCEPTION(
            boost::enable_error_info(std::runtime_error(error_msg)) << boost::errinfo_errno(rc));
    }
}

mir::Fd mgm::NestedAuthentication::authenticated_fd()
{
    auto ext = nested_context->auth_extensions();
    if (ext.is_set())
        return ext.value()->auth_fd();
    else
        BOOST_THROW_EXCEPTION(std::runtime_error("Nested server failed to get authenticated DRM fd"));
}
