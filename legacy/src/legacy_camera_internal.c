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
#define LOG_TAG "TIZEN_N_CAMERA"


int legacy_camera_set_mused_display(camera_h camera, camera_display_type_e type)
{
	int ret = MM_ERROR_NONE;
	int set_surface = MM_DISPLAY_SURFACE_X;
	camera_s *handle = NULL;

	if (camera == NULL) {
		LOGE("INVALID_PARAMETER(0x%08x)", CAMERA_ERROR_INVALID_PARAMETER);
		return CAMERA_ERROR_INVALID_PARAMETER;
	}

	handle = (camera_s *)camera;
	handle->display_type = type;

	switch(type) {
		case CAMERA_DISPLAY_TYPE_OVERLAY:
			set_surface = MM_DISPLAY_SURFACE_X;
			LOGD("display type OVERLAY : set_surface : 0x%x", set_surface);
			break;
		case CAMERA_DISPLAY_TYPE_EVAS:
			set_surface = MM_DISPLAY_SURFACE_EVAS;
			break;
		case CAMERA_DISPLAY_TYPE_NONE:
		default:
			set_surface = MM_DISPLAY_SURFACE_NULL;
			break;
	}

	ret = mm_camcorder_set_attributes(handle->mm_handle, NULL,
					  MMCAM_DISPLAY_DEVICE, MM_DISPLAY_DEVICE_MAINLCD,
					  MMCAM_DISPLAY_SURFACE, set_surface,
					  NULL);

	return __convert_camera_error_code(__func__, ret);
}

int legacy_camera_get_video_caps(camera_h camera, char **caps)
{
	int ret;
	camera_s *handle = (camera_s *)camera;

#ifdef HAVE_WAYLAND
	ret = mm_camcorder_get_video_caps(handle->mm_handle, caps);
	if(ret != MM_ERROR_NONE) {
		return __convert_camera_error_code(__func__, ret);
	}
#endif /* HAVE_WAYLAND */

	return CAMERA_ERROR_NONE;
}

int legacy_camera_set_shm_socket_path_for_mused(camera_h camera, char *socket_path)
{
	int ret;
	camera_s *handle = (camera_s *)camera;

	LOGE("var : %s", socket_path);
	ret = mm_camcorder_set_attributes(handle->mm_handle, NULL,
				    MMCAM_DISPLAY_SHM_SOCKET_PATH, socket_path, strlen(socket_path),
				    NULL);

	if (ret != MM_ERROR_NONE) {
		LOGE("error set shm socket path attribute 0x%x", ret);
		return __convert_camera_error_code(__func__, ret);
	}

	return CAMERA_ERROR_NONE;
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
