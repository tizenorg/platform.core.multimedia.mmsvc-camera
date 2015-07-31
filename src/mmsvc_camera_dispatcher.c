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

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <dlog.h>
#include "mmsvc_camera.h"
#include "mmsvc_camera_msg.h"
#include "mmsvc_core.h"
#include "mmsvc_core_ipc.h"
#include "mm_types.h"
#include "camera.h"
#include "camera_internal.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "MUSED_CAMERA"
#define KEY_NUM 9527


void _mmsvc_camera_disp_callback_single_param_cb(int param, void *user_data)
{
	Client client = (Client)user_data;
	int event;
	int api_client = mmsvc_core_client_get_capi(client);

	LOGW("FOREACH CB");
	switch (api_client) {
		case MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_THEATER_MODE:
			event = MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_THEATER_MODE;
			break;
		case MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_AF_MODE:
			event = MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_AF_MODE;
			break;
		case MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_EXPOSURE_MODE:
			event = MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_EXPOSURE_MODE;
			break;
		case MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_ISO:
			event = MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_ISO;
			break;
		case MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_WHITEBALANCE:
			event = MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_WHITEBALANCE;
			break;
		case MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_EFFECT:
			event = MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_EFFECT;
			break;
		case MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_SCENE_MODE:
			event = MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_SCENE_MODE;
			break;
		case MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_FLASH_MODE:
			event = MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_FLASH_MODE;
			break;
		case MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_FPS:
			event = MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_FPS;
			break;
		case MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_FPS_BY_RESOLUTION:
			event = MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_FPS_BY_RESOLUTION;
			break;
		case MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_STREAM_FLIP:
			event = MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_STREAM_FLIP;
			break;
		case MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_STREAM_ROTATION:
			event = MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_STREAM_ROTATION;
			break;
		case MMSVC_CAMERA_API_SET_FOREACH_SUPPORTED_CAPTURE_FORMAT:
			event = MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_CAPTURE_FORMAT;
			break;
		case MMSVC_CAMERA_API_SET_FOREACH_SUPPORTED_PREVIEW_FORMAT:
			event = MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_PREVIEW_FORMAT;
			break;
		default:
			LOGE("Invalid Parameter");
			return;
	}
	mmsvc_camera_msg_event1(MMSVC_CAMERA_CB_EVENT,
								event,
								client,
								INT, param);
	return;
}

void _mmsvc_camera_disp_callback_dual_param_cb(int param1, int param2, void *user_data)
{
	Client client = (Client)user_data;
	int event;
	int api_client = mmsvc_core_client_get_capi(client);

	LOGW("FOREACH CB");
	switch (api_client) {
		case MMSVC_CAMERA_API_SET_FOREACH_SUPPORTED_PREVIEW_RESOLUTION:
			event = MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_PREVIEW_RESOLUTION;
			break;
		case MMSVC_CAMERA_API_SET_FOREACH_SUPPORTED_CAPTURE_RESOLUTION:
			event = MMSVC_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_CAPTURE_RESOLUTION;
			break;
		default:
			LOGE("Invalid Parameter");
			return;
	}
	mmsvc_camera_msg_event2(MMSVC_CAMERA_CB_EVENT,
								event,
								client,
								INT, param1,
								INT, param2);
	return;
}

void _mmsvc_camera_disp_capturing_cb(camera_image_data_s* image, camera_image_data_s* postview, camera_image_data_s* thumbnail, void *user_data)
{
	mmsvc_camera_transport_info_s transport_info;
	int tKey = 0;
	Client client = (Client)user_data;
	unsigned char *buf_pos = NULL;
	int is_postview = 0;
	int is_thumbnail = 0;

	LOGW("Enter!!");
	transport_info.data_size = 0;

	if (image != NULL) {
		if (image->size > 0) {
			transport_info.data_size += (sizeof(camera_image_data_s) + image->size);
		}
	}
	if (postview != NULL) {
		if (postview->size > 0) {
			transport_info.data_size += (sizeof(camera_image_data_s) + postview->size);
			is_postview = 1;
		}
	}
	if (thumbnail != NULL) {
		if (thumbnail->size > 0) {
			transport_info.data_size += (sizeof(camera_image_data_s) + thumbnail->size);
			is_thumbnail = 1;
		}
	}
	if (mmsvc_camera_ipc_init_tbm(&transport_info) == FALSE) {
		LOGE("TBM Init failed");
		return;
	}
	LOGW("bohandle_ptr : 0x%x, export_bo : %d, tSize : %d", transport_info.bo_handle.ptr,
													transport_info.bo,
													transport_info.data_size);

	buf_pos = (unsigned char *)transport_info.bo_handle.ptr;
	if (image != NULL) {
		if (image->size > 0) {
			memcpy(buf_pos, image, sizeof(camera_image_data_s));
			buf_pos += sizeof(camera_image_data_s);
			memcpy(buf_pos, image->data, image->size);
			buf_pos += image->size;
		}
	}

	if (is_postview) {
		memcpy(buf_pos, postview, sizeof(camera_image_data_s));
		buf_pos += sizeof(camera_image_data_s);
		memcpy(buf_pos + sizeof(camera_image_data_s), postview->data, postview->size);
		buf_pos += postview->size;
	}

	if (is_thumbnail) {
		memcpy(buf_pos, thumbnail, sizeof(camera_image_data_s));
		buf_pos += sizeof(camera_image_data_s);
		memcpy(buf_pos + sizeof(camera_image_data_s), image->data, thumbnail->size);
	}

	tKey = mmsvc_camera_ipc_export_tbm_bo(transport_info);
	tbm_bo_unmap(transport_info.bo);
	if(tKey == 0) {
		LOGE("Create key_info ERROR!!");
		return;
	}
	LOGW("Create tKey : %d", tKey);

	mmsvc_camera_msg_event3(MMSVC_CAMERA_CB_EVENT,
							      MMSVC_CAMERA_EVENT_TYPE_CAPTURE,
							      client,
							      INT, tKey,
							      INT, is_postview,
							      INT, is_thumbnail);

	return;
}

void _mmsvc_camera_disp_state_changed_cb(camera_state_e previous, camera_state_e current, bool by_policy, void *user_data)
{
	Client client = (Client)user_data;

	LOGW("Enter");
	int cb_previous = (int)previous;
	int cb_current = (int)current;
	int cb_by_policy = (int)by_policy;
	mmsvc_camera_msg_event3(MMSVC_CAMERA_CB_EVENT,
								MMSVC_CAMERA_EVENT_TYPE_STATE_CHANGE,
								client,
								INT, cb_previous,
								INT, cb_current,
								INT, cb_by_policy);
	return;
}

void _mmsvc_camera_disp_interrupted_cb(camera_policy_e policy, camera_state_e previous, camera_state_e current, void *user_data)
{
	Client client = (Client)user_data;

	LOGW("Enter");
	int cb_policy = (int)policy;
	int cb_previous = (int)previous;
	int cb_current = (int)current;
	mmsvc_camera_msg_event3(MMSVC_CAMERA_CB_EVENT,
								MMSVC_CAMERA_EVENT_TYPE_INTERRUPTED,
								client,
								INT, cb_policy,
								INT, cb_previous,
								INT, cb_current);
	return;
}

void _mmsvc_camera_disp_preview_cb(camera_preview_data_s *frame, void *user_data)
{
	Client client = (Client)user_data;

	LOGW("Enter");

	mmsvc_camera_msg_event(MMSVC_CAMERA_CB_EVENT,
							    MMSVC_CAMERA_EVENT_TYPE_PREVIEW,
							    client);
	return;
}

void _mmsvc_camera_disp_media_packet_preview_cb(media_packet_h pkt, void *user_data)
{
	Client client = (Client)user_data;

	LOGW("Enter");

	mmsvc_camera_msg_event(MMSVC_CAMERA_CB_EVENT,
							    MMSVC_CAMERA_EVENT_TYPE_MEDIA_PACKET_PREVIEW,
							    client);
	return;
}

void _mmsvc_camera_disp_capture_completed_cb(void *user_data)
{
	Client client = (Client)user_data;

	LOGW("Enter");

	mmsvc_camera_msg_event(MMSVC_CAMERA_CB_EVENT,
							    MMSVC_CAMERA_EVENT_TYPE_CAPTURE_COMPLETE,
							    client);
	return;
}

void _mmsvc_camera_disp_face_detected_cb(camera_detected_face_s *faces, int count, void *user_data)
{
	Client client = (Client)user_data;

	LOGW("Enter");

	mmsvc_camera_msg_event1(MMSVC_CAMERA_CB_EVENT,
							    MMSVC_CAMERA_EVENT_TYPE_FACE_DETECTION,
							    client,
							    INT, count);
	return;
}

void _mmsvc_camera_disp_focus_changed_cb(camera_focus_state_e state, void *user_data)
{
	Client client = (Client)user_data;
	int cb_state = (int)state;
	LOGW("Enter");

	mmsvc_camera_msg_event1(MMSVC_CAMERA_CB_EVENT,
							    MMSVC_CAMERA_EVENT_TYPE_FOCUS_CHANGE,
							    client,
							    INT, cb_state);
	return;
}

void _mmsvc_camera_disp_error_cb(camera_error_e error, camera_state_e current_state, void *user_data)
{
	Client client = (Client)user_data;
	int cb_error = (int)error;
	int cb_current_state = (int)current_state;
	LOGW("Enter");

	mmsvc_camera_msg_event2(MMSVC_CAMERA_CB_EVENT,
							    MMSVC_CAMERA_EVENT_TYPE_ERROR,
							    client,
							    INT, cb_error,
							    INT, cb_current_state);
	return;
}

void _mmsvc_camera_disp_hdr_progress_cb(int percent, void *user_data)
{
	Client client = (Client)user_data;
	LOGW("Enter");

	mmsvc_camera_msg_event1(MMSVC_CAMERA_CB_EVENT,
							    MMSVC_CAMERA_EVENT_TYPE_HDR_PROGRESS,
							    client,
							    INT, percent);
	return;
}

int mmsvc_camera_disp_create(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int device_type;
	int handle;
	static guint stream_id = 0;
	char socket_path[SOCKET_PATH_LENGTH] = {0,};

	camera_h camera;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_CREATE;
	mmsvc_camera_msg_get(device_type, mmsvc_core_client_get_msg(client));
	ret = camera_create((camera_device_e)device_type, &camera);
	handle = (int)camera;
	LOGW("device_type : %d, handle : 0x%x", device_type, handle);

	if (ret == CAMERA_ERROR_NONE) {
		stream_id = mmsvc_core_get_atomic_uint();
		snprintf(socket_path, SOCKET_PATH_LENGTH, SOCKET_PATH_BASE, stream_id);
		unlink(socket_path);
		LOGW("socket_path : %s", socket_path);
		ret = camera_set_shm_socket_path_for_mused(camera, socket_path);
		mmsvc_camera_msg_return2(api, ret, client,
								INT, handle,
								STRING, socket_path);
	} else {
		mmsvc_camera_msg_return1(api, ret, client, INT, handle);
	}

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_destroy(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_DESTROY;
	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("Enter, handle : 0x%x", handle);
	ret = camera_destroy((camera_h)handle);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_start_preview(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_START_PREVIEW;
	char *caps = NULL;
	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	ret = camera_start_preview((camera_h)handle);
	LOGW("enter ret : 0x%x, handle : 0x%x", ret, handle);
	if(ret == CAMERA_ERROR_NONE) {
		ret = camera_get_video_caps((camera_h)handle, &caps);
		if((ret == CAMERA_ERROR_NONE) && caps) {
			LOGW("caps : %s", caps);
			mmsvc_camera_msg_return1(api, ret, client, STRING, caps);
			g_free(caps);
			return MMSVC_CAMERA_ERROR_NONE;
		} else {
			LOGW("Failed to get server's video caps");
			mmsvc_camera_msg_return(api, ret, client);
			return ret;
		}
	} else {
		LOGW("start preview failed");
		mmsvc_camera_msg_return(api, ret, client);
		return ret;
	}
	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_stop_preview(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_STOP_PREVIEW;
	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_stop_preview((camera_h)handle);
	mmsvc_camera_msg_return(api, ret, client);
	return MMSVC_CAMERA_ERROR_NONE;

}

int mmsvc_camera_disp_start_capture(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int is_completed_cb = 0;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_START_CAPTURE;
	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(is_completed_cb, mmsvc_core_client_get_msg(client));
	LOGW("Enter, handle : 0x%x, client : %d", handle, client);
	if (is_completed_cb) {
		ret = camera_start_capture((camera_h)handle,
								(camera_capturing_cb)_mmsvc_camera_disp_capturing_cb,
								(camera_capture_completed_cb)_mmsvc_camera_disp_capture_completed_cb,
								(void *)client);
	} else {
		ret = camera_start_capture((camera_h)handle,
								(camera_capturing_cb)_mmsvc_camera_disp_capturing_cb,
								NULL,
								(void *)client);
	}
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_is_supported_continuous_capture(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_SUPPORT_CONTINUOUS_CAPTURE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_is_supported_continuous_capture((camera_h)handle);
	LOGW("is supported ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_start_continuous_capture(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int count;
	int interval;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_START_CONTINUOUS_CAPTURE;
	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(count, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(interval, mmsvc_core_client_get_msg(client));
	LOGW("Enter, handle : 0x%x, client : %d", handle, client);
	ret = camera_start_continuous_capture((camera_h)handle,
										count,
										interval,
										(camera_capturing_cb)_mmsvc_camera_disp_capturing_cb,
										NULL,
										(void *)client);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_stop_continuous_capture(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_STOP_CONTINUOUS_CAPTURE;
	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_stop_continuous_capture((camera_h)handle);
	mmsvc_camera_msg_return(api, ret, client);
	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_is_supported_zero_shutter_lag(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_SUPPORT_ZERO_SHUTTER_LAG;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_is_supported_zero_shutter_lag((camera_h)handle);
	LOGW("is supported ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_is_supported_media_packet_preview_cb(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_SUPPORT_MEDIA_PACKET_PREVIEW_CB;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_is_supported_media_packet_preview_cb((camera_h)handle);
	LOGW("is supported ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_get_device_count(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int get_device_count;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_GET_DEVICE_COUNT;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_get_device_count((camera_h)handle, &get_device_count);
	LOGW("ret : %d, device count : %d", ret, get_device_count);
	mmsvc_camera_msg_return1(api, ret, client, INT, get_device_count);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_start_face_detection(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_START_FACE_DETECTION;
	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("Enter, handle : 0x%x, client : %d", handle, client);

	/*
	 * TODO : set callback handler.
	 */
	ret = camera_start_face_detection((camera_h)handle, NULL, NULL);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_stop_face_detection(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_STOP_FACE_DETECTION;
	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_stop_face_detection((camera_h)handle);
	mmsvc_camera_msg_return(api, ret, client);
	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_get_state(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int get_state;
	camera_state_e state;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_GET_STATE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_get_state((camera_h)handle, &state);
	LOGW("ret : %d, state : %d", ret, state);
	get_state = (int)state;
	mmsvc_camera_msg_return1(api, ret, client, INT, get_state);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_start_focusing(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int is_continuous;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_START_FOCUSING;
	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(is_continuous, mmsvc_core_client_get_msg(client));
	LOGW("Enter, handle : 0x%x, client : %d", handle, client);
	ret = camera_start_focusing((camera_h)handle, (bool)is_continuous);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_stop_focusing(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_CANCEL_FOCUSING;
	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_cancel_focusing((camera_h)handle);
	mmsvc_camera_msg_return(api, ret, client);
	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_set_display(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int display_type;
	int display_handle;
	int display_surface;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_SET_DISPLAY;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(display_type, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(display_handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(display_surface, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, display_type : %d, display_handle : 0x%x", handle, display_type, display_handle);
	ret = camera_set_mused_display((camera_h)handle, (camera_display_type_e)display_type, (camera_display_h)display_handle);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_set_preview_resolution(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int width;
	int height;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_SET_PREVIEW_RESOLUTION;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(width, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(height, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, set_width : %d, set_height : 0x%x", handle, width, height);
	ret = camera_set_preview_resolution((camera_h)handle, width, height);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_set_capture_resolution(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int width;
	int height;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_SET_CAPTURE_RESOLUTION;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(width, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(height, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, set_width : %d, set_height : %d", handle, width, height);
	ret = camera_set_capture_resolution((camera_h)handle, width, height);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_set_capture_format(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int set_format;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_SET_CAPTURE_FORMAT;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(set_format, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, set_format : %d", handle, set_format);
	ret = camera_set_capture_format((camera_h)handle, (camera_pixel_format_e)set_format);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_set_preview_format(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int set_format;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_SET_PREVIEW_FORMAT;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(set_format, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, set_format : %d", handle, set_format);
	ret = camera_set_preview_format((camera_h)handle, (camera_pixel_format_e)set_format);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_get_preview_resolution(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int get_width;
	int get_height;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_GET_PREVIEW_RESOLUTION;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_get_preview_resolution((camera_h)handle, &get_width, &get_height);
	mmsvc_camera_msg_return2(api, ret, client, INT, get_width, INT, get_height);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_set_display_rotation(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int set_rotation;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_SET_DISPLAY_ROTATION;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(set_rotation, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, set_rotation : %d", handle, set_rotation);
	ret = camera_set_display_rotation((camera_h)handle, (camera_rotation_e)set_rotation);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_get_display_rotation(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	camera_rotation_e rotation;
	int get_rotation;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_GET_DISPLAY_ROTATION;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_get_display_rotation((camera_h)handle, &rotation);
	get_rotation = (int)rotation;
	mmsvc_camera_msg_return1(api, ret, client, INT, get_rotation);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_set_display_flip(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int set_flip;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_SET_DISPLAY_FLIP;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(set_flip, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, set_flip : %d", handle, set_flip);
	ret = camera_set_display_flip((camera_h)handle, (camera_flip_e)set_flip);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_get_display_flip(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int get_flip;
	camera_flip_e flip;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_GET_DISPLAY_FLIP;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_get_display_flip((camera_h)handle, &flip);
	get_flip = (int)flip;
	mmsvc_camera_msg_return1(api, ret, client, INT, get_flip);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_set_display_visible(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int set_visible;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_SET_DISPLAY_VISIBLE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(set_visible, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, set_visible : %d", handle, set_visible);
	ret = camera_set_display_visible((camera_h)handle, (bool)set_visible);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_is_display_visible(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int get_visible;
	bool visible;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_IS_DISPLAY_VISIBLE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_is_display_visible((camera_h)handle, &visible);
	get_visible = (int)visible;
	mmsvc_camera_msg_return1(api, ret, client, INT, get_visible);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_set_display_mode(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int set_mode;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_SET_DISPLAY_MODE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(set_mode, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, display_mode : %d", handle, set_mode);
	ret = camera_set_display_mode((camera_h)handle, (camera_display_mode_e)set_mode);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_get_display_mode(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int get_mode;
	camera_display_mode_e mode;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_GET_DISPLAY_MODE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_get_display_mode((camera_h)handle, &mode);
	get_mode = (int)mode;
	mmsvc_camera_msg_return1(api, ret, client, INT, get_mode);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_get_capture_resolution(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int get_width;
	int get_height;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_GET_CAPTURE_RESOLUTION;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_get_capture_resolution((camera_h)handle, &get_width, &get_height);
	mmsvc_camera_msg_return2(api, ret, client, INT, get_width, INT, get_height);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_get_capture_format(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int get_format;
	camera_pixel_format_e format;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_GET_CAPTURE_FORMAT;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_get_capture_format((camera_h)handle, &format);
	get_format = (int)format;
	mmsvc_camera_msg_return1(api, ret, client, INT, get_format);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_get_preview_format(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int get_format;
	camera_pixel_format_e format;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_GET_PREVIEW_FORMAT;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_get_preview_format((camera_h)handle, &format);
	get_format = (int)format;
	mmsvc_camera_msg_return1(api, ret, client, INT, get_format);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_set_preview_cb(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_SET_PREVIEW_CB;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);

	ret = camera_set_preview_cb((camera_h)handle,
								(camera_preview_cb)_mmsvc_camera_disp_preview_cb,
								(void *)client);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_unset_preview_cb(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_UNSET_PREVIEW_CB;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_unset_preview_cb((camera_h)handle);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_set_media_packet_preview_cb(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_SET_MEDIA_PACKET_PREVIEW_CB;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);

	ret = camera_set_media_packet_preview_cb((camera_h)handle,
						(camera_media_packet_preview_cb)_mmsvc_camera_disp_media_packet_preview_cb,
						(void *)client);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_unset_media_packet_preview_cb(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_UNSET_MEDIA_PACKET_PREVIEW_CB;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_unset_media_packet_preview_cb((camera_h)handle);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_set_state_changed_cb(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_SET_STATE_CHANGED_CB;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);

	ret = camera_set_state_changed_cb((camera_h)handle,
									(camera_state_changed_cb)_mmsvc_camera_disp_state_changed_cb,
									(void *)client);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_unset_state_changed_cb(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_UNSET_STATE_CHANGED_CB;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_unset_state_changed_cb((camera_h)handle);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_set_interrupted_cb(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_SET_INTERRUPTED_CB;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);

	ret = camera_set_interrupted_cb((camera_h)handle,
								(camera_interrupted_cb)_mmsvc_camera_disp_interrupted_cb,
								(void *)client);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_unset_interrupted_cb(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_UNSET_INTERRUPTED_CB;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_unset_interrupted_cb((camera_h)handle);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_set_focus_changed_cb(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_SET_FOCUS_CHANGED_CB;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_set_focus_changed_cb((camera_h)handle,
								(camera_focus_changed_cb)_mmsvc_camera_disp_focus_changed_cb,
								(void *)client);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_unset_focus_changed_cb(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_UNSET_FOCUS_CHANGED_CB;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_unset_focus_changed_cb((camera_h)handle);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_set_error_cb(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_SET_ERROR_CB;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);

	ret = camera_set_error_cb((camera_h)handle,
							(camera_error_cb)_mmsvc_camera_disp_error_cb,
							(void *)client);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_unset_error_cb(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_UNSET_ERROR_CB;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_unset_error_cb((camera_h)handle);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_foreach_supported_preview_resolution(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_SET_FOREACH_SUPPORTED_PREVIEW_RESOLUTION;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);

	ret = camera_foreach_supported_preview_resolution((camera_h)handle,
						(camera_supported_preview_resolution_cb)_mmsvc_camera_disp_callback_dual_param_cb,
						(void *)client);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_foreach_supported_capture_resolution(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_SET_FOREACH_SUPPORTED_CAPTURE_RESOLUTION;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);

	ret = camera_foreach_supported_capture_resolution((camera_h)handle,
						(camera_supported_capture_resolution_cb)_mmsvc_camera_disp_callback_dual_param_cb,
						(void *)client);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_foreach_supported_capture_format(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_SET_FOREACH_SUPPORTED_CAPTURE_FORMAT;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);

	ret = camera_foreach_supported_capture_format((camera_h)handle,
						(camera_supported_capture_format_cb)_mmsvc_camera_disp_callback_single_param_cb,
						(void *)client);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_foreach_supported_preview_format(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_SET_FOREACH_SUPPORTED_PREVIEW_FORMAT;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);

	ret = camera_foreach_supported_preview_format((camera_h)handle,
						(camera_supported_preview_format_cb)_mmsvc_camera_disp_callback_single_param_cb,
						(void *)client);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_get_recommended_preview_resolution(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int get_width;
	int get_height;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_GET_RECOMMENDED_PREVIEW_RESOLUTION;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_get_recommended_preview_resolution((camera_h)handle, &get_width, &get_height);
	mmsvc_camera_msg_return2(api, ret, client, INT, get_width, INT, get_height);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_lens_orientation(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int get_angle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_LENS_ORIENTATION;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_get_lens_orientation((camera_h)handle, &get_angle);
	mmsvc_camera_msg_return1(api, ret, client, INT, get_angle);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_set_theater_mode(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int set_mode;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_SET_THEATER_MODE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(set_mode, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_set_theater_mode((camera_h)handle, (camera_attr_theater_mode_e)set_mode);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_theater_mode(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int get_mode;
	camera_attr_theater_mode_e mode;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_THEATER_MODE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_get_theater_mode((camera_h)handle, &mode);
	get_mode = (int)mode;
	mmsvc_camera_msg_return1(api, ret, client, INT, get_mode);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_foreach_supported_theater_mode(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_THEATER_MODE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);

	ret = camera_attr_foreach_supported_theater_mode((camera_h)handle,
						(camera_attr_supported_theater_mode_cb)_mmsvc_camera_disp_callback_single_param_cb,
						(void *)client);

	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_set_preview_fps(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int set_fps;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_SET_PREVIEW_FPS;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(set_fps, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_set_preview_fps((camera_h)handle, (camera_attr_fps_e)set_fps);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_set_image_quality(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int quality;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_SET_IMAGE_QUALITY;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(quality, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, image_quality : %d", handle, quality);
	ret = camera_attr_set_image_quality((camera_h)handle, quality);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_preview_fps(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	camera_attr_fps_e fps;
	int get_fps;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_PREVIEW_FPS;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_get_preview_fps((camera_h)handle, &fps);
	get_fps = (int)fps;
	mmsvc_camera_msg_return1(api, ret, client, INT, get_fps);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_image_quality(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int get_quality;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_IMAGE_QUALITY;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_get_image_quality((camera_h)handle, &get_quality);
	mmsvc_camera_msg_return1(api, ret, client, INT, get_quality);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_set_zoom(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int zoom;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_SET_ZOOM;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(zoom, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, zoom : %d", handle, zoom);
	ret = camera_attr_set_zoom((camera_h)handle, zoom);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_set_af_mode(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int set_mode;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_SET_AF_MODE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(set_mode, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, set_mode : %d", handle, set_mode);
	ret = camera_attr_set_af_mode((camera_h)handle, (camera_attr_af_mode_e)set_mode);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_set_af_area(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int x;
	int y;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_SET_AF_AREA;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(x, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(y, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_set_af_area((camera_h)handle, x, y);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_clear_af_area(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_CLEAR_AF_AREA;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_clear_af_area((camera_h)handle);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_set_exposure_mode(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int set_mode;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_SET_EXPOSURE_MODE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(set_mode, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, set_mode : %d", handle, set_mode);
	ret = camera_attr_set_exposure_mode((camera_h)handle, (camera_attr_exposure_mode_e)set_mode);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_set_exposure(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int value;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_SET_EXPOSURE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(value, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, value : %d", handle, value);
	ret = camera_attr_set_exposure((camera_h)handle, value);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_set_iso(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int set_iso;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_SET_ISO;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(set_iso, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, set_iso : %d", handle, set_iso);
	ret = camera_attr_set_iso((camera_h)handle, (camera_attr_iso_e)set_iso);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_set_brightness(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int level;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_SET_BRIGHTNESS;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(level, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, level : %d", handle, level);
	ret = camera_attr_set_brightness((camera_h)handle, level);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_set_contrast(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int level;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_SET_CONTRAST;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(level, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, level : %d", handle, level);
	ret = camera_attr_set_contrast((camera_h)handle, level);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_set_whitebalance(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int set_whitebalance;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_SET_WHITEBALANCE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(set_whitebalance, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, set_whitebalance : %d", handle, set_whitebalance);
	ret = camera_attr_set_whitebalance((camera_h)handle, (camera_attr_whitebalance_e)set_whitebalance);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_set_effect(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int set_effect;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_SET_EFFECT;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(set_effect, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, set_effect : %d", handle, set_effect);
	ret = camera_attr_set_effect((camera_h)handle, (camera_attr_effect_mode_e)set_effect);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_set_scene_mode(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int set_mode;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_SET_SCENE_MODE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(set_mode, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, set_mode : %d", handle, set_mode);
	ret = camera_attr_set_scene_mode((camera_h)handle, (camera_attr_scene_mode_e)set_mode);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_enable_tag(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int set_enable;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_ENABLE_TAG;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(set_enable, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, set_enable : %d", handle, set_enable);
	ret = camera_attr_enable_tag((camera_h)handle, (bool)set_enable);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_set_tag_image_description(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_SET_TAG_IMAGE_DESCRIPTION;
	char description[MMSVC_MSG_MAX_LENGTH] = {0,};

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get_string(description, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, description : %s", handle, description);
	ret = camera_attr_set_tag_image_description((camera_h)handle, description);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_set_tag_orientation(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int set_orientation;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_SET_TAG_ORIENTATION;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(set_orientation, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, set_orientation : %d", handle, set_orientation);
	ret = camera_attr_set_tag_orientation((camera_h)handle, (camera_attr_tag_orientation_e)set_orientation);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_set_tag_software(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_SET_TAG_SOFTWARE;
	char software[MMSVC_MSG_MAX_LENGTH] = {0,};

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get_string(software, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, software : %s", handle, software);
	ret = camera_attr_set_tag_software((camera_h)handle, software);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_set_geotag(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_SET_GEOTAG;
	double set_geotag[3] = {0,};

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get_array(set_geotag, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, set_geotag1 : %d, set_geotag2 : %d, set_geotag3 : %d", handle, set_geotag[0], set_geotag[1], set_geotag[2]);
	ret = camera_attr_set_geotag((camera_h)handle, set_geotag[0], set_geotag[1], set_geotag[2]);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_remove_geotag(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_REMOVE_GEOTAG;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_remove_geotag((camera_h)handle);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_set_flash_mode(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int set_mode;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_SET_FLASH_MODE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(set_mode, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, set_mode : %d", handle, set_mode);
	ret = camera_attr_set_flash_mode((camera_h)handle, (camera_attr_flash_mode_e)set_mode);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_zoom(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int get_zoom;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_ZOOM;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_get_zoom((camera_h)handle, &get_zoom);
	mmsvc_camera_msg_return1(api, ret, client, INT, get_zoom);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_zoom_range(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int get_min;
	int get_max;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_ZOOM_RANGE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_get_zoom_range((camera_h)handle, &get_min, &get_max);
	mmsvc_camera_msg_return2(api, ret, client, INT, get_min, INT, get_max);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_af_mode(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	camera_attr_af_mode_e mode;
	int get_mode;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_AF_MODE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_get_af_mode((camera_h)handle, &mode);
	get_mode = (int)mode;
	mmsvc_camera_msg_return1(api, ret, client, INT, get_mode);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_exposure_mode(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	camera_attr_exposure_mode_e mode;
	int get_mode;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_EXPOSURE_MODE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_get_exposure_mode((camera_h)handle, &mode);
	get_mode = (int)mode;
	mmsvc_camera_msg_return1(api, ret, client, INT, get_mode);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_exposure(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int get_value;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_EXPOSURE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_get_exposure((camera_h)handle, &get_value);
	mmsvc_camera_msg_return1(api, ret, client, INT, get_value);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_exposure_range(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int get_min;
	int get_max;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_EXPOSURE_RANGE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_get_exposure_range((camera_h)handle, &get_min, &get_max);
	mmsvc_camera_msg_return2(api, ret, client, INT, get_min, INT, get_max);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_iso(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	camera_attr_iso_e iso;
	int get_iso;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_ISO;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_get_iso((camera_h)handle, &iso);
	get_iso = (int)iso;
	mmsvc_camera_msg_return1(api, ret, client, INT, get_iso);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_brightness(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int get_level;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_BRIGHTNESS;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_get_brightness((camera_h)handle, &get_level);
	mmsvc_camera_msg_return1(api, ret, client, INT, get_level);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_brightness_range(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int get_min;
	int get_max;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_BRIGHTNESS_RANGE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_get_brightness_range((camera_h)handle, &get_min, &get_max);
	mmsvc_camera_msg_return2(api, ret, client, INT, get_min, INT, get_max);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_contrast(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int get_level;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_CONTRAST;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_get_contrast((camera_h)handle, &get_level);
	mmsvc_camera_msg_return1(api, ret, client, INT, get_level);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_contrast_range(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	int get_min;
	int get_max;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_CONTRAST_RANGE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_get_contrast_range((camera_h)handle, &get_min, &get_max);
	mmsvc_camera_msg_return2(api, ret, client, INT, get_min, INT, get_max);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_whitebalance(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	camera_attr_whitebalance_e wb;
	int get_wb;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_WHITEBALANCE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_get_whitebalance((camera_h)handle, &wb);
	get_wb = (int)wb;
	mmsvc_camera_msg_return1(api, ret, client, INT, get_wb);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_effect(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	camera_attr_effect_mode_e effect;
	int get_effect;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_EFFECT;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_get_effect((camera_h)handle, &effect);
	get_effect = (int)effect;
	mmsvc_camera_msg_return1(api, ret, client, INT, get_effect);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_scene_mode(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	camera_attr_scene_mode_e mode;
	int get_mode;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_SCENE_MODE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_get_scene_mode((camera_h)handle, &mode);
	get_mode = (int)mode;
	mmsvc_camera_msg_return1(api, ret, client, INT, get_mode);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_is_enabled_tag(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	bool enable;
	int get_enable;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_IS_ENABLED_TAG;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_is_enabled_tag((camera_h)handle, &enable);
	get_enable = (int)enable;
	mmsvc_camera_msg_return1(api, ret, client, INT, get_enable);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_tag_image_description(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_TAG_IMAGE_DESCRIPTION;
	char *get_description;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, get_description : %s", handle, get_description);
	ret = camera_attr_get_tag_image_description((camera_h)handle, &get_description);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return1(api, ret, client, STRING, get_description);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_tag_orientation(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	camera_attr_tag_orientation_e orientation;
	int get_orientation;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_TAG_ORIENTATION;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_get_tag_orientation((camera_h)handle, &orientation);
	get_orientation = (int)orientation;
	mmsvc_camera_msg_return1(api, ret, client, INT, get_orientation);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_tag_software(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_TAG_SOFTWARE;
	char *get_software;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x, get_software : %s", handle, get_software);
	ret = camera_attr_get_tag_software((camera_h)handle, &get_software);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return1(api, ret, client, STRING, get_software);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_geotag(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_GEOTAG;
	double latitude;
	double longitude;
	double altitude;
	double get_geotag[3] = {0,};

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_get_geotag((camera_h)handle, &latitude, &longitude, &altitude);
	get_geotag[0] = latitude;
	get_geotag[1] = longitude;
	get_geotag[2] = altitude;
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return_array(api, ret, client, get_geotag, sizeof(get_geotag), sizeof(double));

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_flash_mode(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	camera_attr_flash_mode_e mode;
	int get_mode;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_FLASH_MODE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_get_flash_mode((camera_h)handle, &mode);
	get_mode = (int)mode;
	mmsvc_camera_msg_return1(api, ret, client, INT, get_mode);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_foreach_supported_af_mode(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_AF_MODE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);

	ret = camera_attr_foreach_supported_af_mode((camera_h)handle,
						(camera_attr_supported_af_mode_cb)_mmsvc_camera_disp_callback_single_param_cb,
						(void *)client);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_foreach_supported_exposure_mode(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_EXPOSURE_MODE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);

	ret = camera_attr_foreach_supported_exposure_mode((camera_h)handle,
						(camera_attr_supported_exposure_mode_cb)_mmsvc_camera_disp_callback_single_param_cb,
						(void *)client);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_foreach_supported_iso(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_ISO;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);

	ret = camera_attr_foreach_supported_iso((camera_h)handle,
						(camera_attr_supported_iso_cb)_mmsvc_camera_disp_callback_single_param_cb,
						(void *)client);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_foreach_supported_whitebalance(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_WHITEBALANCE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);

	ret = camera_attr_foreach_supported_whitebalance((camera_h)handle,
						(camera_attr_supported_whitebalance_cb)_mmsvc_camera_disp_callback_single_param_cb,
						(void *)client);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_foreach_supported_effect(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_EFFECT;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);

	ret = camera_attr_foreach_supported_effect((camera_h)handle,
						(camera_attr_supported_effect_cb)_mmsvc_camera_disp_callback_single_param_cb,
						(void *)client);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_foreach_supported_scene_mode(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_SCENE_MODE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);

	ret = camera_attr_foreach_supported_scene_mode((camera_h)handle,
						(camera_attr_supported_scene_mode_cb)_mmsvc_camera_disp_callback_single_param_cb,
						(void *)client);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_foreach_supported_flash_mode(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_FLASH_MODE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);

	ret = camera_attr_foreach_supported_flash_mode((camera_h)handle,
						(camera_attr_supported_flash_mode_cb)_mmsvc_camera_disp_callback_single_param_cb,
						(void *)client);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_foreach_supported_fps(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_FPS;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);

	ret = camera_attr_foreach_supported_fps((camera_h)handle,
						(camera_attr_supported_fps_cb)_mmsvc_camera_disp_callback_single_param_cb,
						(void *)client);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_foreach_supported_fps_by_resolution(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_FPS_BY_RESOLUTION;
	int width;
	int height;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(width, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(height, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);

	ret = camera_attr_foreach_supported_fps_by_resolution((camera_h)handle,
						width, height,
						(camera_attr_supported_fps_cb)_mmsvc_camera_disp_callback_single_param_cb,
						(void *)client);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_foreach_supported_stream_flip(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_STREAM_FLIP;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);

	ret = camera_attr_foreach_supported_stream_flip((camera_h)handle,
						(camera_attr_supported_stream_flip_cb)_mmsvc_camera_disp_callback_single_param_cb,
						(void *)client);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_foreach_supported_stream_rotation(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_STREAM_ROTATION;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);

	ret = camera_attr_foreach_supported_stream_rotation((camera_h)handle,
						(camera_attr_supported_stream_rotation_cb)_mmsvc_camera_disp_callback_single_param_cb,
						(void *)client);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_set_stream_rotation(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_SET_STREAM_ROTATION;
	int set_rotation;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(set_rotation, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_set_stream_rotation((camera_h)handle, (camera_rotation_e)set_rotation);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_stream_rotation(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_STREAM_ROTATION;
	camera_rotation_e rotation;
	int get_rotation;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_get_stream_rotation((camera_h)handle, &rotation);
	LOGW("ret : %d", ret);
	get_rotation = (int)rotation;
	mmsvc_camera_msg_return1(api, ret, client, INT, get_rotation);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_set_stream_flip(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_SET_STREAM_FLIP;
	int set_flip;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(set_flip, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_set_stream_flip((camera_h)handle, (camera_flip_e)set_flip);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_stream_flip(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_STREAM_FLIP;
	camera_flip_e flip;
	int get_flip;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_get_stream_flip((camera_h)handle, &flip);
	LOGW("ret : %d", ret);
	get_flip = (int)flip;
	mmsvc_camera_msg_return1(api, ret, client, INT, get_flip);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_set_hdr_mode(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_SET_HDR_MODE;
	int set_mode;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(set_mode, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_set_hdr_mode((camera_h)handle, (camera_attr_hdr_mode_e)set_mode);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_get_hdr_mode(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_GET_HDR_MODE;
	camera_attr_hdr_mode_e mode;
	int get_mode;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_get_hdr_mode((camera_h)handle, &mode);
	LOGW("ret : %d", ret);
	get_mode = (int)mode;
	mmsvc_camera_msg_return1(api, ret, client, INT, get_mode);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_is_supported_hdr_capture(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_IS_SUPPORTED_HDR_CAPTURE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_is_supported_hdr_capture((camera_h)handle);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_set_hdr_capture_progress_cb(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_SET_HDR_CAPTURE_PROGRESS_CB;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	/*
	 *	TODO : set the cb function here.
	 */
	ret = camera_attr_set_hdr_capture_progress_cb((camera_h)handle, NULL, NULL);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_unset_hdr_capture_progress_cb(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_UNSET_HDR_CAPTURE_PROGRESS_CB;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_unset_hdr_capture_progress_cb((camera_h)handle);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_enable_anti_shake(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_ENABLE_ANTI_SHAKE;
	int set_enable;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(set_enable, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_enable_anti_shake((camera_h)handle, (bool)set_enable);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_is_enabled_anti_shake(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_IS_ENABLED_ANTI_SHAKE;
	bool enabled;
	int get_enabled;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_is_enabled_anti_shake((camera_h)handle, &enabled);
	LOGW("ret : %d", ret);
	get_enabled = (int)enabled;
	mmsvc_camera_msg_return1(api, ret, client, INT, get_enabled);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_is_supported_anti_shake(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_IS_SUPPORTED_ANTI_SHAKE;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_is_supported_anti_shake((camera_h)handle);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_enable_video_stabilization(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_ENABLE_VIDEO_STABILIZATION;
	int set_enable;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(set_enable, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_enable_video_stabilization((camera_h)handle, (bool)set_enable);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_is_enabled_video_stabilization(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_IS_ENABLED_VIDEO_STABILIZATION;
	bool enabled;
	int get_enabled;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_is_enabled_video_stabilization((camera_h)handle, &enabled);
	LOGW("ret : %d", ret);
	get_enabled = (int)enabled;
	mmsvc_camera_msg_return1(api, ret, client, INT, get_enabled);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_is_supported_video_stabilization(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_IS_SUPPORTED_VIDEO_STABILIZATION;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_is_supported_video_stabilization((camera_h)handle);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_enable_auto_contrast(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_ENABLE_AUTO_CONTRAST;
	int set_enable;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(set_enable, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_enable_auto_contrast((camera_h)handle, (bool)set_enable);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_is_enabled_auto_contrast(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_IS_ENABLED_AUTO_CONTRAST;
	bool enabled;
	int get_enabled;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_is_enabled_auto_contrast((camera_h)handle, &enabled);
	LOGW("ret : %d", ret);
	get_enabled = (int)enabled;
	mmsvc_camera_msg_return1(api, ret, client, INT, get_enabled);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_is_supported_auto_contrast(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_IS_SUPPORTED_AUTO_CONTRAST;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_is_supported_auto_contrast((camera_h)handle);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int mmsvc_camera_disp_attr_disable_shutter_sound(Client client)
{
	int ret = CAMERA_ERROR_NONE;
	int handle;
	mmsvc_camera_api_e api = MMSVC_CAMERA_API_ATTR_DISABLE_SHUTTER_SOUND;
	int set_disable;

	mmsvc_camera_msg_get(handle, mmsvc_core_client_get_msg(client));
	mmsvc_camera_msg_get(set_disable, mmsvc_core_client_get_msg(client));
	LOGW("handle : 0x%x", handle);
	ret = camera_attr_disable_shutter_sound((camera_h)handle, (bool)set_disable);
	LOGW("ret : %d", ret);
	mmsvc_camera_msg_return(api, ret, client);

	return MMSVC_CAMERA_ERROR_NONE;
}

int (*dispatcher[MMSVC_CAMERA_API_MAX]) (Client client) = {
	mmsvc_camera_disp_create,				/* MMSVC_CAMERA_API_CREATE */
	mmsvc_camera_disp_destroy,			/* MMSVC_CAMERA_API_DESTROY */
	mmsvc_camera_disp_start_preview,		/* MMSVC_CAMERA_START_PREVIEW */
	mmsvc_camera_disp_stop_preview,		/* MMSVC_CAMERA_API_START_PREVIEW */
	mmsvc_camera_disp_start_capture,		/* MMSVC_CAMERA_START_CAPTURE */
	mmsvc_camera_disp_is_supported_continuous_capture, 	/* MMSVC_CAMERA_API_SUPPORT_CONTINUOUS_CAPTURE */
	mmsvc_camera_disp_start_continuous_capture, 			/* MMSVC_CAMERA_API_START_CONTINUOUS_CAPTURE, */
	mmsvc_camera_disp_stop_continuous_capture, 			/* MMSVC_CAMERA_API_STOP_CONTINUOUS_CAPTURE, */
	mmsvc_camera_disp_is_supported_zero_shutter_lag,		/* MMSVC_CAMERA_API_SUPPORT_ZERO_SHUTTER_LAG, */
	mmsvc_camera_disp_is_supported_media_packet_preview_cb,		/* MMSVC_CAMERA_API_SUPPORT_MEDIA_PACKET_PREVIEW_CB, */
	mmsvc_camera_disp_get_device_count, 					/* MMSVC_CAMERA_API_GET_DEVICE_COUNT, */
	mmsvc_camera_disp_start_face_detection, 				/* MMSVC_CAMERA_API_START_FACE_DETECTION, */
	mmsvc_camera_disp_stop_face_detection, 				/* MMSVC_CAMERA_API_STOP_FACE_DETECTION, */
	mmsvc_camera_disp_get_state, 					/* MMSVC_CAMERA_API_GET_STATE, */
	mmsvc_camera_disp_start_focusing, 				/* MMSVC_CAMERA_API_START_FOCUSING, */
	mmsvc_camera_disp_stop_focusing, 				/* MMSVC_CAMERA_API_CANCEL_FOCUSING, */
	mmsvc_camera_disp_set_display, 				/* MMSVC_CAMERA_API_SET_DISPLAY, */
	mmsvc_camera_disp_set_preview_resolution, 	/* MMSVC_CAMERA_API_SET_PREVIEW_RESOLUTION, */
	mmsvc_camera_disp_set_capture_resolution, 		/* MMSVC_CAMERA_API_SET_CAPTURE_RESOLUTION, */
	mmsvc_camera_disp_set_capture_format, 		/* MMSVC_CAMERA_API_SET_CAPTURE_FORMAT, */
	mmsvc_camera_disp_set_preview_format, 		/* MMSVC_CAMERA_API_SET_PREVIEW_FORMAT, */
	mmsvc_camera_disp_get_preview_resolution, 	/* MMSVC_CAMERA_API_GET_PREVIEW_RESOLUTION, */
	mmsvc_camera_disp_set_display_rotation, 		/* MMSVC_CAMERA_API_SET_DISPLAY_ROTATION, */
	mmsvc_camera_disp_get_display_rotation,		/* MMSVC_CAMERA_API_GET_DISPLAY_ROTATION, */
	mmsvc_camera_disp_set_display_flip, 			/* MMSVC_CAMERA_API_SET_DISPLAY_FLIP, */
	mmsvc_camera_disp_get_display_flip, 			/* MMSVC_CAMERA_API_GET_DISPLAY_FLIP, */
	mmsvc_camera_disp_set_display_visible, 		/* MMSVC_CAMERA_API_SET_DISPLAY_VISIBLE, */
	mmsvc_camera_disp_is_display_visible, /* MMSVC_CAMERA_API_IS_DISPLAY_VISIBLE, */
	mmsvc_camera_disp_set_display_mode, /* MMSVC_CAMERA_API_SET_DISPLAY_MODE, */
	mmsvc_camera_disp_get_display_mode, /* MMSVC_CAMERA_API_GET_DISPLAY_MODE, */
	mmsvc_camera_disp_get_capture_resolution, /* MMSVC_CAMERA_API_GET_CAPTURE_RESOLUTION, */
	mmsvc_camera_disp_get_capture_format, /* MMSVC_CAMERA_API_GET_CAPTURE_FORMAT, */
	mmsvc_camera_disp_get_preview_format, /* MMSVC_CAMERA_API_GET_PREVIEW_FORMAT, */
	mmsvc_camera_disp_set_preview_cb, /* MMSVC_CAMERA_API_SET_PREVIEW_CB, */
	mmsvc_camera_disp_unset_preview_cb, /* MMSVC_CAMERA_API_UNSET_PREVIEW_CB, */
	mmsvc_camera_disp_set_media_packet_preview_cb, /* MMSVC_CAMERA_API_SET_MEDIA_PACKET_PREVIEW_CB, */
	mmsvc_camera_disp_unset_media_packet_preview_cb, /* MMSVC_CAMERA_API_UNSET_MEDIA_PACKET_PREVIEW_CB, */
	mmsvc_camera_disp_set_state_changed_cb, /* MMSVC_CAMERA_API_SET_STATE_CHANGED_CB, */
	mmsvc_camera_disp_unset_state_changed_cb, /* MMSVC_CAMERA_API_UNSET_STATE_CHANGED_CB, */
	mmsvc_camera_disp_set_interrupted_cb, /* MMSVC_CAMERA_API_SET_INTERRUPTED_CB, */
	mmsvc_camera_disp_unset_interrupted_cb, /* MMSVC_CAMERA_API_UNSET_INTERRUPTED_CB, */
	mmsvc_camera_disp_set_focus_changed_cb, /* MMSVC_CAMERA_API_SET_FOCUS_CHANGED_CB, */
	mmsvc_camera_disp_unset_focus_changed_cb, /* MMSVC_CAMERA_API_UNSET_FOCUS_CHANGED_CB, */
	mmsvc_camera_disp_set_error_cb, /* MMSVC_CAMERA_API_SET_ERROR_CB, */
	mmsvc_camera_disp_unset_error_cb, /* MMSVC_CAMERA_API_UNSET_ERROR_CB, */
	mmsvc_camera_disp_foreach_supported_preview_resolution, /* MMSVC_CAMERA_API_SET_FOREACH_SUPPORTED_PREVIEW_RESOLUTION, */
	mmsvc_camera_disp_foreach_supported_capture_resolution, /* MMSVC_CAMERA_API_SET_FOREACH_SUPPORTED_CAPTURE_RESOLUTION, */
	mmsvc_camera_disp_foreach_supported_capture_format, /* MMSVC_CAMERA_API_SET_FOREACH_SUPPORTED_CAPTURE_FORMAT, */
	mmsvc_camera_disp_foreach_supported_preview_format, /* MMSVC_CAMERA_API_SET_FOREACH_SUPPORTED_PREVIEW_FORMAT, */
	mmsvc_camera_disp_get_recommended_preview_resolution, /* MMSVC_CAMERA_API_GET_RECOMMENDED_PREVIEW_RESOLUTION, */
	mmsvc_camera_disp_attr_get_lens_orientation, /* MMSVC_CAMERA_API_ATTR_GET_LENS_ORIENTATION, */
	mmsvc_camera_disp_attr_set_theater_mode, /* MMSVC_CAMERA_API_ATTR_SET_THEATER_MODE, */
	mmsvc_camera_disp_attr_get_theater_mode, /* MMSVC_CAMERA_API_ATTR_GET_THEATER_MODE, */
	mmsvc_camera_disp_attr_foreach_supported_theater_mode, /* MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_THEATER_MODE, */
	mmsvc_camera_disp_attr_set_preview_fps, /* MMSVC_CAMERA_API_ATTR_SET_PREVIEW_FPS, */
	mmsvc_camera_disp_attr_set_image_quality, /* MMSVC_CAMERA_API_ATTR_SET_IMAGE_QUALITY, */
	mmsvc_camera_disp_attr_get_preview_fps, /* MMSVC_CAMERA_API_ATTR_GET_PREVIEW_FPS, */
	mmsvc_camera_disp_attr_get_image_quality, /* MMSVC_CAMERA_API_ATTR_GET_IMAGE_QUALITY, */
	mmsvc_camera_disp_attr_set_zoom, /* MMSVC_CAMERA_API_ATTR_SET_ZOOM, */
	mmsvc_camera_disp_attr_set_af_mode, /* MMSVC_CAMERA_API_ATTR_SET_AF_MODE, */
	mmsvc_camera_disp_attr_set_af_area, /* MMSVC_CAMERA_API_ATTR_SET_AF_AREA, */
	mmsvc_camera_disp_attr_clear_af_area, /* MMSVC_CAMERA_API_ATTR_CLEAR_AF_AREA, */
	mmsvc_camera_disp_attr_set_exposure_mode, /* MMSVC_CAMERA_API_ATTR_SET_EXPOSURE_MODE, */
	mmsvc_camera_disp_attr_set_exposure, /* MMSVC_CAMERA_API_ATTR_SET_EXPOSURE, */
	mmsvc_camera_disp_attr_set_iso, /* MMSVC_CAMERA_API_ATTR_SET_ISO, */
	mmsvc_camera_disp_attr_set_brightness, /* MMSVC_CAMERA_API_ATTR_SET_BRIGHTNESS, */
	mmsvc_camera_disp_attr_set_contrast, /* MMSVC_CAMERA_API_ATTR_SET_CONTRAST, */
	mmsvc_camera_disp_attr_set_whitebalance, /* MMSVC_CAMERA_API_ATTR_SET_WHITEBALANCE, */
	mmsvc_camera_disp_attr_set_effect, /* MMSVC_CAMERA_API_ATTR_SET_EFFECT, */
	mmsvc_camera_disp_attr_set_scene_mode, /* MMSVC_CAMERA_API_ATTR_SET_SCENE_MODE, */
	mmsvc_camera_disp_attr_enable_tag, /* MMSVC_CAMERA_API_ATTR_ENABLE_TAG, */
	mmsvc_camera_disp_attr_set_tag_image_description, /* MMSVC_CAMERA_API_ATTR_SET_TAG_IMAGE_DESCRIPTION, */
	mmsvc_camera_disp_attr_set_tag_orientation, /* MMSVC_CAMERA_API_ATTR_SET_TAG_ORIENTATION, */
	mmsvc_camera_disp_attr_set_tag_software, /* MMSVC_CAMERA_API_ATTR_SET_TAG_SOFTWARE, */
	mmsvc_camera_disp_attr_set_geotag, /* MMSVC_CAMERA_API_ATTR_SET_GEOTAG, */
	mmsvc_camera_disp_attr_remove_geotag, /* MMSVC_CAMERA_API_ATTR_REMOVE_GEOTAG, */
	mmsvc_camera_disp_attr_set_flash_mode, /* MMSVC_CAMERA_API_ATTR_SET_FLASH_MODE, */
	mmsvc_camera_disp_attr_get_zoom, /* MMSVC_CAMERA_API_ATTR_GET_ZOOM, */
	mmsvc_camera_disp_attr_get_zoom_range, /* MMSVC_CAMERA_API_ATTR_GET_ZOOM_RANGE, */
	mmsvc_camera_disp_attr_get_af_mode, /* MMSVC_CAMERA_API_ATTR_GET_AF_MODE, */
	mmsvc_camera_disp_attr_get_exposure_mode, /* MMSVC_CAMERA_API_ATTR_GET_EXPOSURE_MODE, */
	mmsvc_camera_disp_attr_get_exposure, /* MMSVC_CAMERA_API_ATTR_GET_EXPOSURE, */
	mmsvc_camera_disp_attr_get_exposure_range, /* MMSVC_CAMERA_API_ATTR_GET_EXPOSURE_RANGE, */
	mmsvc_camera_disp_attr_get_iso, /* MMSVC_CAMERA_API_ATTR_GET_ISO, */
	mmsvc_camera_disp_attr_get_brightness, /* MMSVC_CAMERA_API_ATTR_GET_BRIGHTNESS, */
	mmsvc_camera_disp_attr_get_brightness_range, /* MMSVC_CAMERA_API_ATTR_GET_BRIGHTNESS_RANGE, */
	mmsvc_camera_disp_attr_get_contrast, /* MMSVC_CAMERA_API_ATTR_GET_CONTRAST, */
	mmsvc_camera_disp_attr_get_contrast_range, /* MMSVC_CAMERA_API_ATTR_GET_CONTRAST_RANGE, */
	mmsvc_camera_disp_attr_get_whitebalance, /* MMSVC_CAMERA_API_ATTR_GET_WHITEBALANCE, */
	mmsvc_camera_disp_attr_get_effect, /* MMSVC_CAMERA_API_ATTR_GET_EFFECT, */
	mmsvc_camera_disp_attr_get_scene_mode, /* MMSVC_CAMERA_API_ATTR_GET_SCENE_MODE, */
	mmsvc_camera_disp_attr_is_enabled_tag, /* MMSVC_CAMERA_API_ATTR_IS_ENABLED_TAG, */
	mmsvc_camera_disp_attr_get_tag_image_description, /* MMSVC_CAMERA_API_ATTR_GET_TAG_IMAGE_DESCRIPTION, */
	mmsvc_camera_disp_attr_get_tag_orientation, /* MMSVC_CAMERA_API_ATTR_GET_TAG_ORIENTATION, */
	mmsvc_camera_disp_attr_get_tag_software, /* MMSVC_CAMERA_API_ATTR_GET_TAG_SOFTWARE, */
	mmsvc_camera_disp_attr_get_geotag, /* MMSVC_CAMERA_API_ATTR_GET_GEOTAG, */
	mmsvc_camera_disp_attr_get_flash_mode, /* MMSVC_CAMERA_API_ATTR_GET_FLASH_MODE, */
	mmsvc_camera_disp_attr_foreach_supported_af_mode, /* MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_AF_MODE, */
	mmsvc_camera_disp_attr_foreach_supported_exposure_mode, /* MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_EXPOSURE_MODE, */
	mmsvc_camera_disp_attr_foreach_supported_iso, /* MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_ISO, */
	mmsvc_camera_disp_attr_foreach_supported_whitebalance, /* MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_WHITEBALANCE, */
	mmsvc_camera_disp_attr_foreach_supported_effect, /* MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_EFFECT, */
	mmsvc_camera_disp_attr_foreach_supported_scene_mode, /* MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_SCENE_MODE, */
	mmsvc_camera_disp_attr_foreach_supported_flash_mode, /* MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_FLASH_MODE, */
	mmsvc_camera_disp_attr_foreach_supported_fps, /* MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_FPS, */
	mmsvc_camera_disp_attr_foreach_supported_fps_by_resolution, /* MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_FPS_BY_RESOLUTION, */
	mmsvc_camera_disp_attr_foreach_supported_stream_flip, /* MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_STREAM_FLIP, */
	mmsvc_camera_disp_attr_foreach_supported_stream_rotation, /* MMSVC_CAMERA_API_ATTR_FOREACH_SUPPORTED_STREAM_ROTATION, */
	mmsvc_camera_disp_attr_set_stream_rotation, /* MMSVC_CAMERA_API_ATTR_SET_STREAM_ROTATION, */
	mmsvc_camera_disp_attr_get_stream_rotation, /* MMSVC_CAMERA_API_ATTR_GET_STREAM_ROTATION, */
	mmsvc_camera_disp_attr_set_stream_flip, /* MMSVC_CAMERA_API_ATTR_SET_STREAM_FLIP, */
	mmsvc_camera_disp_attr_get_stream_flip, /* MMSVC_CAMERA_API_ATTR_GET_STREAM_FLIP, */
	mmsvc_camera_disp_attr_set_hdr_mode, /* MMSVC_CAMERA_API_ATTR_SET_HDR_MODE, */
	mmsvc_camera_disp_attr_get_hdr_mode, /* MMSVC_CAMERA_API_ATTR_GET_HDR_MODE, */
	mmsvc_camera_disp_attr_is_supported_hdr_capture, /* MMSVC_CAMERA_API_ATTR_IS_SUPPORTED_HDR_CAPTURE, */
	mmsvc_camera_disp_attr_set_hdr_capture_progress_cb, /* MMSVC_CAMERA_API_ATTR_SET_HDR_CAPTURE_PROGRESS_CB, */
	mmsvc_camera_disp_attr_unset_hdr_capture_progress_cb, /* MMSVC_CAMERA_API_ATTR_UNSET_HDR_CAPTURE_PROGRESS_CB, */
	mmsvc_camera_disp_attr_enable_anti_shake, /* MMSVC_CAMERA_API_ATTR_ENABLE_ANTI_SHAKE, */
	mmsvc_camera_disp_attr_is_enabled_anti_shake, /* MMSVC_CAMERA_API_ATTR_IS_ENABLED_ANTI_SHAKE, */
	mmsvc_camera_disp_attr_is_supported_anti_shake, /* MMSVC_CAMERA_API_ATTR_IS_SUPPORTED_ANTI_SHAKE, */
	mmsvc_camera_disp_attr_enable_video_stabilization, /* MMSVC_CAMERA_API_ATTR_ENABLE_VIDEO_STABILIZATION, */
	mmsvc_camera_disp_attr_is_enabled_video_stabilization, /* MMSVC_CAMERA_API_ATTR_IS_ENABLED_VIDEO_STABILIZATION, */
	mmsvc_camera_disp_attr_is_supported_video_stabilization, /* MMSVC_CAMERA_API_ATTR_IS_SUPPORTED_VIDEO_STABILIZATION, */
	mmsvc_camera_disp_attr_enable_auto_contrast, /* MMSVC_CAMERA_API_ATTR_ENABLE_AUTO_CONTRAST, */
	mmsvc_camera_disp_attr_is_enabled_auto_contrast, /* MMSVC_CAMERA_API_ATTR_IS_ENABLED_AUTO_CONTRAST, */
	mmsvc_camera_disp_attr_is_supported_auto_contrast, /* MMSVC_CAMERA_API_ATTR_IS_SUPPORTED_AUTO_CONTRAST, */
	mmsvc_camera_disp_attr_disable_shutter_sound, /* MMSVC_CAMERA_API_ATTR_DISABLE_SHUTTER_SOUND, */
};
