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

#ifndef __MMSVC_CAMERA_H__
#define __MMSVC_CAMERA_H__

#ifdef _cplusplus
extern "C" {
#endif

#include "tbm_bufmgr.h"
#include <stdbool.h>
#include <glib.h>
#include <stdio.h>

typedef enum {
	MMSVC_CAMERA_API_CREATE, //0
	MMSVC_CAMERA_API_DESTROY,
	MMSVC_CAMERA_API_START_PREVIEW,
	MMSVC_CAMERA_API_STOP_PREVIEW,
	MMSVC_CAMERA_API_START_CAPTURE,
	MMSVC_CAMERA_API_SUPPORT_CONTINUOUS_CAPTURE, //5
	MMSVC_CAMERA_API_START_CONTINUOUS_CAPTURE,
	MMSVC_CAMERA_API_STOP_CONTINUOUS_CAPTURE,
	MMSVC_CAMERA_API_SUPPORT_FACE_DETECTION,
	MMSVC_CAMERA_API_SUPPORT_ZERO_SHUTTER_LAG,
	MMSVC_CAMERA_API_SUPPORT_MEDIA_PACKET_PREVIEW_CB, //10
	MMSVC_CAMERA_API_GET_DEVICE_COUNT,
	MMSVC_CAMERA_API_START_FACE_DETECTION,
	MMSVC_CAMERA_API_STOP_FACE_DETECTION,
	MMSVC_CAMERA_API_GET_STATE,
	MMSVC_CAMERA_API_START_FOCUSING, //15
	MMSVC_CAMERA_API_CANCEL_FOCUSING,
	MMSVC_CAMERA_API_SET_DISPLAY,
	MMSVC_CAMERA_API_SET_PREVIEW_RESOLUTION,
	MMSVC_CAMERA_API_SET_CAPTURE_RESOLUTION,
	MMSVC_CAMERA_API_SET_CAPTURE_FORMAT, //20
	MMSVC_CAMERA_API_SET_PREVIEW_FORMAT,
	MMSVC_CAMERA_API_GET_PREVIEW_RESOLUTION,
	MMSVC_CAMERA_API_SET_DISPLAY_ROTATION,
	MMSVC_CAMERA_API_GET_DISPLAY_ROTATION,
	MMSVC_CAMERA_API_SET_DISPLAY_FLIP, //25
	MMSVC_CAMERA_API_GET_DISPLAY_FLIP,
	MMSVC_CAMERA_API_SET_DISPLAY_VISIBLE,
	MMSVC_CAMERA_API_IS_DISPLAY_VISIBLE,
	MMSVC_CAMERA_API_SET_DISPLAY_MODE,
	MMSVC_CAMERA_API_GET_DISPLAY_MODE, //30
	MMSVC_CAMERA_API_GET_CAPTURE_RESOLUTION,
	MMSVC_CAMERA_API_GET_CAPTURE_FORMAT,
	MMSVC_CAMERA_API_GET_PREVIEW_FORMAT,
	MMSVC_CAMERA_API_SET_PREVIEW_CB,
	MMSVC_CAMERA_API_UNSET_PREVIEW_CB, //35
	MMSVC_CAMERA_API_SET_MEDIA_PACKET_PREVIEW_CB,
	MMSVC_CAMERA_API_UNSET_MEDIA_PACKET_PREVIEW_CB,
	MMSVC_CAMERA_API_SET_STATE_CHANGED_CB,
	MMSVC_CAMERA_API_UNSET_STATE_CHANGED_CB,
	MMSVC_CAMERA_API_SET_INTERRUPTED_CB, //40
	MMSVC_CAMERA_API_UNSET_INTERRUPTED_CB,
	MMSVC_CAMERA_API_SET_FOCUS_CHANGED_CB,
	MMSVC_CAMERA_API_UNSET_FOCUS_CHANGED_CB,
	MMSVC_CAMERA_API_SET_ERROR_CB,
	MMSVC_CAMERA_API_UNSET_ERROR_CB, //45
	MMSVC_CAMERA_API_SET_FOREACH_SUPPORTED_PREVIEW_RESOLUTION,
	MMSVC_CAMERA_API_SET_FOREACH_SUPPORTED_CAPTURE_RESOLUTION,
	MMSVC_CAMERA_API_SET_FOREACH_SUPPORTED_CAPTURE_FORMAT,
	MMSVC_CAMERA_API_SET_FOREACH_SUPPORTED_PREVIEW_FORMAT,
	MMSVC_CAMERA_API_GET_RECOMMENDED_PREVIEW_RESOLUTION, //50
	MMSVC_CAMERA_API_ATTR_GET_LENS_ORIENTATION,
	MMSVC_CAMERA_API_ATTR_SET_THEATER_MODE,
	MMSVC_CAMERA_API_ATTR_GET_THEATER_MODE,
	MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_THEATER_MODE,
	MMSVC_CAMERA_API_ATTR_SET_PREVIEW_FPS, //55
	MMSVC_CAMERA_API_ATTR_SET_IMAGE_QUALITY,
	MMSVC_CAMERA_API_ATTR_GET_PREVIEW_FPS,
	MMSVC_CAMERA_API_ATTR_GET_IMAGE_QUALITY,
	MMSVC_CAMERA_API_ATTR_SET_ZOOM,
	MMSVC_CAMERA_API_ATTR_SET_AF_MODE, //60
	MMSVC_CAMERA_API_ATTR_SET_AF_AREA,
	MMSVC_CAMERA_API_ATTR_CLEAR_AF_AREA,
	MMSVC_CAMERA_API_ATTR_SET_EXPOSURE_MODE,
	MMSVC_CAMERA_API_ATTR_SET_EXPOSURE,
	MMSVC_CAMERA_API_ATTR_SET_ISO, //65
	MMSVC_CAMERA_API_ATTR_SET_BRIGHTNESS,
	MMSVC_CAMERA_API_ATTR_SET_CONTRAST,
	MMSVC_CAMERA_API_ATTR_SET_WHITEBALANCE,
	MMSVC_CAMERA_API_ATTR_SET_EFFECT,
	MMSVC_CAMERA_API_ATTR_SET_SCENE_MODE, //70
	MMSVC_CAMERA_API_ATTR_ENABLE_TAG,
	MMSVC_CAMERA_API_ATTR_SET_TAG_IMAGE_DESCRIPTION,
	MMSVC_CAMERA_API_ATTR_SET_TAG_ORIENTATION,
	MMSVC_CAMERA_API_ATTR_SET_TAG_SOFTWARE,
	MMSVC_CAMERA_API_ATTR_SET_GEOTAG, //75
	MMSVC_CAMERA_API_ATTR_REMOVE_GEOTAG,
	MMSVC_CAMERA_API_ATTR_SET_FLASH_MODE,
	MMSVC_CAMERA_API_ATTR_GET_ZOOM,
	MMSVC_CAMERA_API_ATTR_GET_ZOOM_RANGE,
	MMSVC_CAMERA_API_ATTR_GET_AF_MODE, //80
	MMSVC_CAMERA_API_ATTR_GET_EXPOSURE_MODE,
	MMSVC_CAMERA_API_ATTR_GET_EXPOSURE,
	MMSVC_CAMERA_API_ATTR_GET_EXPOSURE_RANGE,
	MMSVC_CAMERA_API_ATTR_GET_ISO,
	MMSVC_CAMERA_API_ATTR_GET_BRIGHTNESS, //85
	MMSVC_CAMERA_API_ATTR_GET_BRIGHTNESS_RANGE,
	MMSVC_CAMERA_API_ATTR_GET_CONTRAST,
	MMSVC_CAMERA_API_ATTR_GET_CONTRAST_RANGE,
	MMSVC_CAMERA_API_ATTR_GET_WHITEBALANCE,
	MMSVC_CAMERA_API_ATTR_GET_EFFECT, //90
	MMSVC_CAMERA_API_ATTR_GET_SCENE_MODE,
	MMSVC_CAMERA_API_ATTR_IS_ENABLED_TAG,
	MMSVC_CAMERA_API_ATTR_GET_TAG_IMAGE_DESCRIPTION,
	MMSVC_CAMERA_API_ATTR_GET_TAG_ORIENTATION,
	MMSVC_CAMERA_API_ATTR_GET_TAG_SOFTWARE, //95
	MMSVC_CAMERA_API_ATTR_GET_GEOTAG,
	MMSVC_CAMERA_API_ATTR_GET_FLASH_MODE,
	MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_AF_MODE,
	MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_EXPOSURE_MODE,
	MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_ISO, //100
	MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_WHITEBALANCE,
	MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_EFFECT,
	MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_SCENE_MODE,
	MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_FLASH_MODE,
	MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_FPS, //105
	MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_FPS_BY_RESOLUTION,
	MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_STREAM_FLIP,
	MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_STREAM_ROTATION,
	MMSVC_CAMERA_API_ATTR_SET_STREAM_ROTATION,
	MMSVC_CAMERA_API_ATTR_GET_STREAM_ROTATION, //110
	MMSVC_CAMERA_API_ATTR_SET_STREAM_FLIP,
	MMSVC_CAMERA_API_ATTR_GET_STREAM_FLIP,
	MMSVC_CAMERA_API_ATTR_SET_HDR_MODE,
	MMSVC_CAMERA_API_ATTR_GET_HDR_MODE,
	MMSVC_CAMERA_API_ATTR_IS_SUPPORTED_HDR_CAPTURE, //115
	MMSVC_CAMERA_API_ATTR_SET_HDR_CAPTURE_PROGRESS_CB,
	MMSVC_CAMERA_API_ATTR_UNSET_HDR_CAPTURE_PROGRESS_CB,
	MMSVC_CAMERA_API_ATTR_ENABLE_ANTI_SHAKE,
	MMSVC_CAMERA_API_ATTR_IS_ENABLED_ANTI_SHAKE,
	MMSVC_CAMERA_API_ATTR_IS_SUPPORTED_ANTI_SHAKE, //120
	MMSVC_CAMERA_API_ATTR_ENABLE_VIDEO_STABILIZATION,
	MMSVC_CAMERA_API_ATTR_IS_ENABLED_VIDEO_STABILIZATION,
	MMSVC_CAMERA_API_ATTR_IS_SUPPORTED_VIDEO_STABILIZATION,
	MMSVC_CAMERA_API_ATTR_ENABLE_AUTO_CONTRAST,
	MMSVC_CAMERA_API_ATTR_IS_ENABLED_AUTO_CONTRAST, //125
	MMSVC_CAMERA_API_ATTR_IS_SUPPORTED_AUTO_CONTRAST,
	MMSVC_CAMERA_API_ATTR_DISABLE_SHUTTER_SOUND,
	MMSVC_CAMERA_API_MAX
} mmsvc_camera_api_e;

typedef enum {
	MMSVC_CAMERA_EVENT_TYPE_STATE_CHANGE, //0
	MMSVC_CAMERA_EVENT_TYPE_FOCUS_CHANGE,
	MMSVC_CAMERA_EVENT_TYPE_CAPTURE_COMPLETE,
	MMSVC_CAMERA_EVENT_TYPE_PREVIEW,
	MMSVC_CAMERA_EVENT_TYPE_MEDIA_PACKET_PREVIEW,
	MMSVC_CAMERA_EVENT_TYPE_CAPTURE, //5
	MMSVC_CAMERA_EVENT_TYPE_ERROR,
	MMSVC_CAMERA_EVENT_TYPE_HDR_PROGRESS,
	MMSVC_CAMERA_EVENT_TYPE_INTERRUPTED,
	MMSVC_CAMERA_EVENT_TYPE_FACE_DETECTION,
	MMSVC_CAMERA_EVENT_TYPE_VIDEO_FRAME_RENDER_ERROR, //10
	MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_PREVIEW_RESOLUTION,
	MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_CAPTURE_RESOLUTION,
	MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_CAPTURE_FORMAT,
	MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_PREVIEW_FORMAT,
	MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_THEATER_MODE, //15
	MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_AF_MODE,
	MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_EXPOSURE_MODE,
	MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_ISO,
	MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_WHITEBALANCE,
	MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_EFFECT, //20
	MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_SCENE_MODE,
	MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_FLASH_MODE,
	MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_FPS,
	MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_FPS_BY_RESOLUTION,
	MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_STREAM_FLIP, //25
	MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_STREAM_ROTATION,
	MMSVC_CAMERA_EVENT_TYPE_NUM //27
}mmsvc_camera_event_e;

/**
 * @brief The structure type for data transport
 */
typedef struct {
	int data_size;
	int tbm_key;
	tbm_bo bo;
	tbm_bo_handle bo_handle;
	tbm_bufmgr bufmgr;
} mmsvc_camera_transport_info_s;

typedef struct {
	tbm_bufmgr bufmgr;
} mmsvc_camera_info_s;

typedef enum {
	MMSVC_CAMERA_ERROR_INVALID = -1,
	MMSVC_CAMERA_ERROR_NONE = 1,
} mmsvc_camera_error_e;

#define MMSVC_CAMERA_CB_EVENT	MMSVC_CAMERA_API_MAX + 1 //129
#define MMSVC_MSG_MAX_LENGTH		256
#define MMSVC_PARSE_STRING_SIZE	200
#define KEY_HOUSE	0x8000
//#define FD_SHARE

#ifdef USE_SHARED_MEMORY
int camera_ipc_create_shm(int key_num, int size, void *shm_addr);
int camera_ipc_get_shm(int key_num, int size, void *shm_addr);
int camera_ipc_dt_shm(void *shm_addr);

typedef struct _camera_shm_info{
        int written;
        char data[4];
}camera_shm_info;
#endif

#define SOCKET_PATH_LENGTH 32
#define SOCKET_PATH_BASE "/tmp/mused_gst.%d"
#define CALLBACK_TIME_OUT 3
#define CALLBACK_TIME_OUT_LONG 8

bool mmsvc_camera_ipc_make_tbm(mmsvc_camera_transport_info_s *transport_info);
int mmsvc_camera_ipc_export_tbm(mmsvc_camera_transport_info_s transport_info);
bool mmsvc_camera_ipc_init_tbm(mmsvc_camera_transport_info_s *transport_info);
int mmsvc_camera_ipc_import_tbm(mmsvc_camera_transport_info_s *transport_info);
void mmsvc_camera_unref_tbm(mmsvc_camera_transport_info_s *transport_info);

#ifdef __cplusplus
}
#endif
#endif				/* __MMSVC_CAMERA_H__ */
