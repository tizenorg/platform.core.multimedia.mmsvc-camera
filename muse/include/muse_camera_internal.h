/*
* Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef __MUSE_CAMERA_INTERNAL_H__
#define __MUSE_CAMERA_INTERNAL_H__

#ifdef _cplusplus
extern "C" {
#endif

/**
  * @file muse_camera_internal.h
  * @brief This file contains the muse camera internal API for framework, related structures and enumerations.
  */

#include <muse_camera.h>
#include <legacy_camera_internal.h>

#define PREVIEW_CB_TYPE_USER 0x0000000F
#define PREVIEW_CB_TYPE_EVAS 0x000000F0

#define NEED_RELEASE_BUFFER(x) \
	(x && !(x == (PREVIEW_CB_TYPE_USER | PREVIEW_CB_TYPE_EVAS)) && \
	((x == PREVIEW_CB_TYPE_USER) || (x == PREVIEW_CB_TYPE_EVAS)))
#define CHECK_PREVIEW_CB(cb_info, cb_type) ((cb_info)->preview_cb_flag & cb_type)

typedef struct {
	camera_h camera_handle;
	tbm_bufmgr bufmgr;
	GList *data_list;
	GMutex list_lock;
	GMutex preview_cb_lock;
	GCond preview_cb_cond;
	guint preview_cb_flag;
#ifdef HAVE_WAYLAND
	MMCamWaylandInfo wl_info;
#endif /* HAVE_WAYLAND */
} muse_camera_handle_s;


#ifdef __cplusplus
}
#endif

#endif /* __MUSE_CAMERA_INTERNAL_H__ */
