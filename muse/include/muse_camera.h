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

#ifndef __MUSE_CAMERA_H__
#define __MUSE_CAMERA_H__

#ifdef _cplusplus
extern "C" {
#endif

/**
  * @file muse_camera.h
  * @brief This file contains the muse camera API for framework, related structures and enumerations.
  */

#include <stdbool.h>
#include <glib.h>
#include <stdio.h>
#include <tbm_bufmgr.h>
#include "legacy_camera_internal.h"

/**
 * @brief Enumeration for the muse camera apis.
 */
typedef enum {
	MUSE_CAMERA_API_CREATE, //0
	MUSE_CAMERA_API_DESTROY,
	MUSE_CAMERA_API_START_PREVIEW,
	MUSE_CAMERA_API_STOP_PREVIEW,
	MUSE_CAMERA_API_START_CAPTURE,
	MUSE_CAMERA_API_SUPPORT_CONTINUOUS_CAPTURE, //5
	MUSE_CAMERA_API_START_CONTINUOUS_CAPTURE,
	MUSE_CAMERA_API_STOP_CONTINUOUS_CAPTURE,
	MUSE_CAMERA_API_SUPPORT_FACE_DETECTION,
	MUSE_CAMERA_API_SUPPORT_ZERO_SHUTTER_LAG,
	MUSE_CAMERA_API_SUPPORT_MEDIA_PACKET_PREVIEW_CB, //10
	MUSE_CAMERA_API_GET_DEVICE_COUNT,
	MUSE_CAMERA_API_START_FACE_DETECTION,
	MUSE_CAMERA_API_STOP_FACE_DETECTION,
	MUSE_CAMERA_API_GET_STATE,
	MUSE_CAMERA_API_START_FOCUSING, //15
	MUSE_CAMERA_API_CANCEL_FOCUSING,
	MUSE_CAMERA_API_SET_DISPLAY,
	MUSE_CAMERA_API_SET_PREVIEW_RESOLUTION,
	MUSE_CAMERA_API_SET_CAPTURE_RESOLUTION,
	MUSE_CAMERA_API_SET_CAPTURE_FORMAT, //20
	MUSE_CAMERA_API_SET_PREVIEW_FORMAT,
	MUSE_CAMERA_API_GET_PREVIEW_RESOLUTION,
	MUSE_CAMERA_API_SET_DISPLAY_ROTATION,
	MUSE_CAMERA_API_GET_DISPLAY_ROTATION,
	MUSE_CAMERA_API_SET_DISPLAY_FLIP, //25
	MUSE_CAMERA_API_GET_DISPLAY_FLIP,
	MUSE_CAMERA_API_SET_DISPLAY_VISIBLE,
	MUSE_CAMERA_API_IS_DISPLAY_VISIBLE,
	MUSE_CAMERA_API_SET_DISPLAY_MODE,
	MUSE_CAMERA_API_GET_DISPLAY_MODE, //30
	MUSE_CAMERA_API_GET_CAPTURE_RESOLUTION,
	MUSE_CAMERA_API_GET_CAPTURE_FORMAT,
	MUSE_CAMERA_API_GET_PREVIEW_FORMAT,
	MUSE_CAMERA_API_SET_PREVIEW_CB,
	MUSE_CAMERA_API_UNSET_PREVIEW_CB, //35
	MUSE_CAMERA_API_SET_MEDIA_PACKET_PREVIEW_CB,
	MUSE_CAMERA_API_UNSET_MEDIA_PACKET_PREVIEW_CB,
	MUSE_CAMERA_API_SET_STATE_CHANGED_CB,
	MUSE_CAMERA_API_UNSET_STATE_CHANGED_CB,
	MUSE_CAMERA_API_SET_INTERRUPTED_CB, //40
	MUSE_CAMERA_API_UNSET_INTERRUPTED_CB,
	MUSE_CAMERA_API_SET_FOCUS_CHANGED_CB,
	MUSE_CAMERA_API_UNSET_FOCUS_CHANGED_CB,
	MUSE_CAMERA_API_SET_ERROR_CB,
	MUSE_CAMERA_API_UNSET_ERROR_CB, //45
	MUSE_CAMERA_API_SET_FOREACH_SUPPORTED_PREVIEW_RESOLUTION,
	MUSE_CAMERA_API_SET_FOREACH_SUPPORTED_CAPTURE_RESOLUTION,
	MUSE_CAMERA_API_SET_FOREACH_SUPPORTED_CAPTURE_FORMAT,
	MUSE_CAMERA_API_SET_FOREACH_SUPPORTED_PREVIEW_FORMAT,
	MUSE_CAMERA_API_GET_RECOMMENDED_PREVIEW_RESOLUTION, //50
	MUSE_CAMERA_API_ATTR_GET_LENS_ORIENTATION,
	MUSE_CAMERA_API_ATTR_SET_THEATER_MODE,
	MUSE_CAMERA_API_ATTR_GET_THEATER_MODE,
	MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_THEATER_MODE,
	MUSE_CAMERA_API_ATTR_SET_PREVIEW_FPS, //55
	MUSE_CAMERA_API_ATTR_SET_IMAGE_QUALITY,
	MUSE_CAMERA_API_ATTR_GET_PREVIEW_FPS,
	MUSE_CAMERA_API_ATTR_GET_IMAGE_QUALITY,
	MUSE_CAMERA_API_ATTR_SET_ZOOM,
	MUSE_CAMERA_API_ATTR_SET_AF_MODE, //60
	MUSE_CAMERA_API_ATTR_SET_AF_AREA,
	MUSE_CAMERA_API_ATTR_CLEAR_AF_AREA,
	MUSE_CAMERA_API_ATTR_SET_EXPOSURE_MODE,
	MUSE_CAMERA_API_ATTR_SET_EXPOSURE,
	MUSE_CAMERA_API_ATTR_SET_ISO, //65
	MUSE_CAMERA_API_ATTR_SET_BRIGHTNESS,
	MUSE_CAMERA_API_ATTR_SET_CONTRAST,
	MUSE_CAMERA_API_ATTR_SET_WHITEBALANCE,
	MUSE_CAMERA_API_ATTR_SET_EFFECT,
	MUSE_CAMERA_API_ATTR_SET_SCENE_MODE, //70
	MUSE_CAMERA_API_ATTR_ENABLE_TAG,
	MUSE_CAMERA_API_ATTR_SET_TAG_IMAGE_DESCRIPTION,
	MUSE_CAMERA_API_ATTR_SET_TAG_ORIENTATION,
	MUSE_CAMERA_API_ATTR_SET_TAG_SOFTWARE,
	MUSE_CAMERA_API_ATTR_SET_GEOTAG, //75
	MUSE_CAMERA_API_ATTR_REMOVE_GEOTAG,
	MUSE_CAMERA_API_ATTR_SET_FLASH_MODE,
	MUSE_CAMERA_API_ATTR_GET_ZOOM,
	MUSE_CAMERA_API_ATTR_GET_ZOOM_RANGE,
	MUSE_CAMERA_API_ATTR_GET_AF_MODE, //80
	MUSE_CAMERA_API_ATTR_GET_EXPOSURE_MODE,
	MUSE_CAMERA_API_ATTR_GET_EXPOSURE,
	MUSE_CAMERA_API_ATTR_GET_EXPOSURE_RANGE,
	MUSE_CAMERA_API_ATTR_GET_ISO,
	MUSE_CAMERA_API_ATTR_GET_BRIGHTNESS, //85
	MUSE_CAMERA_API_ATTR_GET_BRIGHTNESS_RANGE,
	MUSE_CAMERA_API_ATTR_GET_CONTRAST,
	MUSE_CAMERA_API_ATTR_GET_CONTRAST_RANGE,
	MUSE_CAMERA_API_ATTR_GET_WHITEBALANCE,
	MUSE_CAMERA_API_ATTR_GET_EFFECT, //90
	MUSE_CAMERA_API_ATTR_GET_SCENE_MODE,
	MUSE_CAMERA_API_ATTR_IS_ENABLED_TAG,
	MUSE_CAMERA_API_ATTR_GET_TAG_IMAGE_DESCRIPTION,
	MUSE_CAMERA_API_ATTR_GET_TAG_ORIENTATION,
	MUSE_CAMERA_API_ATTR_GET_TAG_SOFTWARE, //95
	MUSE_CAMERA_API_ATTR_GET_GEOTAG,
	MUSE_CAMERA_API_ATTR_GET_FLASH_MODE,
	MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_AF_MODE,
	MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_EXPOSURE_MODE,
	MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_ISO, //100
	MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_WHITEBALANCE,
	MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_EFFECT,
	MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_SCENE_MODE,
	MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_FLASH_MODE,
	MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_FPS, //105
	MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_FPS_BY_RESOLUTION,
	MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_STREAM_FLIP,
	MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_STREAM_ROTATION,
	MUSE_CAMERA_API_ATTR_SET_STREAM_ROTATION,
	MUSE_CAMERA_API_ATTR_GET_STREAM_ROTATION, //110
	MUSE_CAMERA_API_ATTR_SET_STREAM_FLIP,
	MUSE_CAMERA_API_ATTR_GET_STREAM_FLIP,
	MUSE_CAMERA_API_ATTR_SET_HDR_MODE,
	MUSE_CAMERA_API_ATTR_GET_HDR_MODE,
	MUSE_CAMERA_API_ATTR_IS_SUPPORTED_HDR_CAPTURE, //115
	MUSE_CAMERA_API_ATTR_SET_HDR_CAPTURE_PROGRESS_CB,
	MUSE_CAMERA_API_ATTR_UNSET_HDR_CAPTURE_PROGRESS_CB,
	MUSE_CAMERA_API_ATTR_ENABLE_ANTI_SHAKE,
	MUSE_CAMERA_API_ATTR_IS_ENABLED_ANTI_SHAKE,
	MUSE_CAMERA_API_ATTR_IS_SUPPORTED_ANTI_SHAKE, //120
	MUSE_CAMERA_API_ATTR_ENABLE_VIDEO_STABILIZATION,
	MUSE_CAMERA_API_ATTR_IS_ENABLED_VIDEO_STABILIZATION,
	MUSE_CAMERA_API_ATTR_IS_SUPPORTED_VIDEO_STABILIZATION,
	MUSE_CAMERA_API_ATTR_ENABLE_AUTO_CONTRAST,
	MUSE_CAMERA_API_ATTR_IS_ENABLED_AUTO_CONTRAST, //125
	MUSE_CAMERA_API_ATTR_IS_SUPPORTED_AUTO_CONTRAST,
	MUSE_CAMERA_API_ATTR_DISABLE_SHUTTER_SOUND,
	MUSE_CAMERA_API_RETURN_BUFFER,
	MUSE_CAMERA_API_PREVIEW_CB_RETURN,
	MUSE_CAMERA_API_MAX
} muse_camera_api_e;

/**
 * @brief Enumeration for the muse camera API class.
 */
typedef enum {
	MUSE_CAMERA_API_CLASS_IMMEDIATE,
	MUSE_CAMERA_API_CLASS_THREAD_SUB,
	MUSE_CAMERA_API_CLASS_NUM
} muse_camera_api_class_e;

/**
 * @brief Enumeration for the muse camera events.
 */
typedef enum {
	MUSE_CAMERA_EVENT_TYPE_STATE_CHANGE, //0
	MUSE_CAMERA_EVENT_TYPE_FOCUS_CHANGE,
	MUSE_CAMERA_EVENT_TYPE_CAPTURE_COMPLETE,
	MUSE_CAMERA_EVENT_TYPE_PREVIEW,
	MUSE_CAMERA_EVENT_TYPE_MEDIA_PACKET_PREVIEW,
	MUSE_CAMERA_EVENT_TYPE_CAPTURE, //5
	MUSE_CAMERA_EVENT_TYPE_ERROR,
	MUSE_CAMERA_EVENT_TYPE_HDR_PROGRESS,
	MUSE_CAMERA_EVENT_TYPE_INTERRUPTED,
	MUSE_CAMERA_EVENT_TYPE_FACE_DETECTION,
	MUSE_CAMERA_EVENT_TYPE_VIDEO_FRAME_RENDER_ERROR, //10
	MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_PREVIEW_RESOLUTION,
	MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_CAPTURE_RESOLUTION,
	MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_CAPTURE_FORMAT,
	MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_PREVIEW_FORMAT,
	MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_THEATER_MODE, //15
	MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_AF_MODE,
	MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_EXPOSURE_MODE,
	MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_ISO,
	MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_WHITEBALANCE,
	MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_EFFECT, //20
	MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_SCENE_MODE,
	MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_FLASH_MODE,
	MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_FPS,
	MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_FPS_BY_RESOLUTION,
	MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_STREAM_FLIP, //25
	MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_STREAM_ROTATION,
	MUSE_CAMERA_EVENT_TYPE_NUM //27
}muse_camera_event_e;

/**
 * @brief Enumeration for the muse camera events class.
 */
typedef enum {
	MUSE_CAMERA_EVENT_CLASS_THREAD_MAIN,
	MUSE_CAMERA_EVENT_CLASS_THREAD_SUB,
	MUSE_CAMERA_EVENT_CLASS_NUM
} muse_camera_event_class_e;

typedef struct {
	tbm_bo bo;
	int key;
	void *internal_buffer;
} muse_camera_export_data;

typedef struct {
	camera_h camera_handle;
	tbm_bufmgr bufmgr;
	GList *data_list;
	GMutex list_lock;
	GMutex preview_cb_lock;
	GCond preview_cb_cond;
} muse_camera_handle_s;


/**
 * @brief The structure type for muse camera errors.
 */
typedef enum {
	MUSE_CAMERA_ERROR_INVALID = -1,
	MUSE_CAMERA_ERROR_NONE = 1,
} muse_camera_error_e;

/**
 * @brief Definition for the callback event id.
 */
#define MUSE_CAMERA_CB_EVENT	MUSE_CAMERA_API_MAX + 1 //129

/**
 * @brief Definition for the max message length.
 */
#define MUSE_CAMERA_MSG_MAX_LENGTH		512

/**
 * @brief Definition for the socket path length of the shmsink.
 */
#define SOCKET_PATH_LENGTH 32

/**
 * @brief Definition for the socket path base of the shmsink.
 */
#define SOCKET_PATH_BASE "/tmp/mused_gst.%d"

/**
 * @brief Definition for the wait time of the ipc callback.
 */
#define CALLBACK_TIME_OUT 3

/**
 * @brief Definition for the long wait time of the ipc callback.
 */
#define CALLBACK_TIME_OUT_LONG 8


#ifdef __cplusplus
}
#endif
#endif				/* __MUSE_CAMERA_H__ */
