/*
* Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mm.h>
#include <mm_camcorder.h>
#include <mm_types.h>
#include <legacy_camera.h>
#include <legacy_camera_internal.h>
#include <legacy_camera_private.h>
#include <glib.h>
#include <dlog.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "LEGACY_CAMERA"


int legacy_camera_get_video_caps(camera_h camera, char **caps)
{
	int ret = CAMERA_ERROR_NONE;

#ifdef HAVE_WAYLAND
	camera_s *handle = (camera_s *)camera;

	ret = mm_camcorder_get_video_caps(handle->mm_handle, caps);
	if(ret != MM_ERROR_NONE) {
		return __convert_camera_error_code(__func__, ret);
	}
#endif /* HAVE_WAYLAND */

	return ret;
}

int legacy_camera_set_client_pid(camera_h camera, int pid)
{
	int ret;
	camera_s *handle = (camera_s *)camera;

	if (handle == NULL) {
		LOGE("NULL handle");
		return CAMERA_ERROR_INVALID_PARAMETER;
	}

	LOGE("pid %d", pid);

	ret = mm_camcorder_set_attributes(handle->mm_handle, NULL,
	                                  MMCAM_PID_FOR_SOUND_FOCUS, pid,
	                                  NULL);

	return __convert_camera_error_code(__func__, ret);
}
