/*
 * Copyright (C) 2023 Microchip Technology Inc.  All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "detail/multimedia/gstmeta.h"

#include <string>

#include <gst/gst.h>

#include "detail/egtlog.h"


namespace egt
{
inline namespace v1
{
namespace detail
{

void gstreamer_init()
{
    GError* gst_err = nullptr;
    if (!gst_init_check(nullptr, nullptr, &gst_err))
    {
        detail::GstErrorHandle err;
        err.reset(gst_err);
        std::string ss = "failed to initialize gstreamer: ";
        if (err && err->message)
            ss = ss + err->message;
        else
            ss = ss + "unknown error";
        throw std::runtime_error(ss);
    }
}

std::string gstreamer_get_device_path(GstDevice* device)
{
    std::string devnode;
    GstStructureHandle props{gst_device_get_properties(device)};
    if (props)
    {
        /*
         * Most of the providers set this property. If the pipewire provider is
         * present, it hides some providers as the v4l2 one so we won't see
         * devices handled by the v4l2 provider. The device is handled by the
         * pipewire provider which doesn't set the device.path property. The
         * property to look for is the api.v4l2.path one.
         */
        GstStringHandle s{gst_structure_to_string(props.get())};
        EGTLOG_DEBUG("gstreamer_get_device_path: device properties: {}", s.get());
        const gchar* str = gst_structure_get_string(props.get(), "device.path");
        if (!str)
            str = gst_structure_get_string(props.get(), "api.v4l2.path");

        if (str)
            devnode = str;
    }

    return devnode;
}

}
}
}
