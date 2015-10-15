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
#include "muse_camera_msg.h"
#include "muse_camera.h"
#include <muse_core.h>
#include <muse_core_ipc.h>
#include <mm_types.h>
#include <muse_core_security.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "MUSED_CAMERA"
#define KEY_NUM 9527

#define CAMERA_PRIVILEGE_NAME "http://tizen.org/privilege/camera"

static int _camera_remove_export_data(muse_module_h module, int key, int remove_all);


void _camera_dispatcher_callback_supported_theater_mode(int param, void *user_data)
{
	muse_module_h module = (muse_module_h)user_data;
	int event;
	event = MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_THEATER_MODE;
	LOGD("Enter!! param : %d", param);
	muse_camera_msg_event1(MUSE_CAMERA_CB_EVENT,
								event,
								module,
								INT, param);
}

void _camera_dispatcher_callback_supported_af_mode(int param, void *user_data)
{
	muse_module_h module = (muse_module_h)user_data;
	int event;
	event = MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_AF_MODE;
	LOGD("Enter!! param : %d", param);
	muse_camera_msg_event1(MUSE_CAMERA_CB_EVENT,
								event,
								module,
								INT, param);
}

void _camera_dispatcher_callback_supported_exposure_mode(int param, void *user_data)
{
	muse_module_h module = (muse_module_h)user_data;
	int event;
	event = MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_EXPOSURE_MODE;
	LOGD("Enter!! param : %d", param);
	muse_camera_msg_event1(MUSE_CAMERA_CB_EVENT,
								event,
								module,
								INT, param);
}

void _camera_dispatcher_callback_supported_iso_mode(int param, void *user_data)
{
	muse_module_h module = (muse_module_h)user_data;
	int event;
	event = MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_ISO;
	LOGD("Enter!! param : %d", param);
	muse_camera_msg_event1(MUSE_CAMERA_CB_EVENT,
								event,
								module,
								INT, param);
}

void _camera_dispatcher_callback_supported_whitebalance(int param, void *user_data)
{
	muse_module_h module = (muse_module_h)user_data;
	int event;
	event = MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_WHITEBALANCE;
	LOGD("Enter!! param : %d", param);
	muse_camera_msg_event1(MUSE_CAMERA_CB_EVENT,
								event,
								module,
								INT, param);
}

void _camera_dispatcher_callback_supported_effect(int param, void *user_data)
{
	muse_module_h module = (muse_module_h)user_data;
	int event;
	event = MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_EFFECT;
	LOGD("Enter!! param : %d", param);
	muse_camera_msg_event1(MUSE_CAMERA_CB_EVENT,
								event,
								module,
								INT, param);
}

void _camera_dispatcher_callback_supported_scene_mode(int param, void *user_data)
{
	muse_module_h module = (muse_module_h)user_data;
	int event;
	event = MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_SCENE_MODE;
	LOGD("Enter!! param : %d", param);
	muse_camera_msg_event1(MUSE_CAMERA_CB_EVENT,
								event,
								module,
								INT, param);
}

void _camera_dispatcher_callback_supported_flash_mode(int param, void *user_data)
{
	muse_module_h module = (muse_module_h)user_data;
	int event;
	event = MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_FLASH_MODE;
	LOGD("Enter!! param : %d", param);
	muse_camera_msg_event1(MUSE_CAMERA_CB_EVENT,
								event,
								module,
								INT, param);
}

void _camera_dispatcher_callback_supported_fps(int param, void *user_data)
{
	muse_module_h module = (muse_module_h)user_data;
	int event;
	event = MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_FPS;
	LOGD("Enter!! param : %d", param);
	muse_camera_msg_event1(MUSE_CAMERA_CB_EVENT,
								event,
								module,
								INT, param);
}

void _camera_dispatcher_callback_supported_fps_by_resolution(int param, void *user_data)
{
	muse_module_h module = (muse_module_h)user_data;
	int event;
	event = MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_FPS_BY_RESOLUTION;
	LOGD("Enter!! param : %d", param);
	muse_camera_msg_event1(MUSE_CAMERA_CB_EVENT,
								event,
								module,
								INT, param);
}

void _camera_dispatcher_callback_supported_stream_flip(int param, void *user_data)
{
	muse_module_h module = (muse_module_h)user_data;
	int event;
	event = MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_STREAM_FLIP;
	LOGD("Enter!! param : %d", param);
	muse_camera_msg_event1(MUSE_CAMERA_CB_EVENT,
								event,
								module,
								INT, param);
}

void _camera_dispatcher_callback_supported_stream_rotation(int param, void *user_data)
{
	muse_module_h module = (muse_module_h)user_data;
	int event;
	event = MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_STREAM_ROTATION;
	LOGD("Enter!! param : %d", param);
	muse_camera_msg_event1(MUSE_CAMERA_CB_EVENT,
								event,
								module,
								INT, param);
}

void _camera_dispatcher_callback_supported_capture_format(int param, void *user_data)
{
	muse_module_h module = (muse_module_h)user_data;
	int event;
	event = MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_CAPTURE_FORMAT;
	LOGD("Enter!! param : %d", param);
	muse_camera_msg_event1(MUSE_CAMERA_CB_EVENT,
								event,
								module,
								INT, param);
}

void _camera_dispatcher_callback_supported_preview_format(int param, void *user_data)
{
	muse_module_h module = (muse_module_h)user_data;
	int event;
	event = MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_PREVIEW_FORMAT;
	LOGD("Enter!! param : %d", param);
	muse_camera_msg_event1(MUSE_CAMERA_CB_EVENT,
								event,
								module,
								INT, param);
}

void _camera_dispatcher_callback_supported_preview_resolution(int param1, int param2, void *user_data)
{
	muse_module_h module = (muse_module_h)user_data;
	int event;
	event = MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_PREVIEW_RESOLUTION;
	LOGD("Enter!! param1 : %d, param2 : %d", param1, param2);
	muse_camera_msg_event2(MUSE_CAMERA_CB_EVENT,
								event,
								module,
								INT, param1,
								INT, param2);
}

void _camera_dispatcher_callback_supported_capture_resolution(int param1, int param2, void *user_data)
{
	muse_module_h module = (muse_module_h)user_data;
	int event;
	event = MUSE_CAMERA_EVENT_TYPE_FOREACH_SUPPORTED_CAPTURE_RESOLUTION;
	LOGD("Enter!! param1 : %d, param2 : %d", param1, param2);
	muse_camera_msg_event2(MUSE_CAMERA_CB_EVENT,
								event,
								module,
								INT, param1,
								INT, param2);
}

static int _camera_remove_export_data(muse_module_h module, int key, int remove_all)
{
	muse_camera_handle_s *muse_camera = NULL;
	GList *tmp_list = NULL;
	muse_camera_export_data *export_data = NULL;

	if (module == NULL || (key <= 0 && remove_all == FALSE)) {
		LOGE("invalid parameter %p, %d", module, key);
		return FALSE;
	}

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);
	if (muse_camera == NULL) {
		LOGE("NULL handle");
		return FALSE;
	}

	g_mutex_lock(&muse_camera->list_lock);

	tmp_list = muse_camera->data_list;

	while (tmp_list) {
		export_data = (muse_camera_export_data *)tmp_list->data;
		if (export_data) {
			if (export_data->key == key || remove_all) {
				LOGD("key %d matched, remove it (remove_all %d)", key, remove_all);

				tbm_bo_unref(export_data->bo);
				export_data->bo = NULL;
				export_data->key = 0;
				muse_camera->data_list = g_list_remove(muse_camera->data_list, export_data);

				if (remove_all == FALSE) {
					LOGD("key %d, remove done");
					g_mutex_unlock(&muse_camera->list_lock);
					return TRUE;
				} else {
					LOGD("check next data");
				}
			}
		} else {
			LOGW("NULL data");
		}

		tmp_list = tmp_list->next;
	}

	g_mutex_unlock(&muse_camera->list_lock);

	if (remove_all) {
		LOGD("remove all done");
	} else {
		LOGE("should not be reached here - key %d", key);
	}

	return FALSE;
}

void _camera_dispatcher_capturing_cb(camera_image_data_s* image, camera_image_data_s* postview, camera_image_data_s* thumbnail, void *user_data)
{
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_transport_info_s transport_info;
	muse_camera_export_data *export_data = NULL;
	int tbm_key = 0;
	muse_module_h module = (muse_module_h)user_data;
	unsigned char *buf_pos = NULL;
	int is_postview = 0;
	int is_thumbnail = 0;

	LOGD("Enter!!");

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);
	if (muse_camera == NULL) {
		LOGE("NULL handle");
		return;
	}

	export_data = g_new0(muse_camera_export_data, 1);
	if (export_data == NULL) {
		LOGE("alloc export_data failed");
		return;
	}

	memset(&transport_info, 0x0, sizeof(muse_camera_transport_info_s));

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

	transport_info.bo = tbm_bo_alloc(muse_camera->bufmgr, transport_info.data_size, TBM_BO_DEFAULT);
	if (transport_info.bo == NULL) {
		LOGE("bo alloc failed");
		g_free(export_data);
		export_data = NULL;
		return;
	}

	transport_info.bo_handle = tbm_bo_map(transport_info.bo, TBM_DEVICE_CPU, TBM_OPTION_WRITE);
	if (transport_info.bo_handle.ptr == NULL) {
		LOGE("bo map Error!");
		tbm_bo_unref(transport_info.bo);
		g_free(export_data);
		export_data = NULL;
		return;
	}

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

	tbm_bo_unmap(transport_info.bo);

	tbm_key = tbm_bo_export(transport_info.bo);

	if(tbm_key == 0) {
		LOGE("Create key_info ERROR!!");
		tbm_bo_unref(transport_info.bo);
		transport_info.bo = NULL;
		g_free(export_data);
		export_data = NULL;
		return;
	}

	LOGD("bo %p, vaddr %p, size %d, key %d",
	     transport_info.bo,
	     transport_info.bo_handle.ptr,
	     transport_info.data_size,
	     tbm_key);

	/* set bo info */
	export_data->key = tbm_key;
	export_data->bo = transport_info.bo;

	/* add bo info to list */
	g_mutex_lock(&muse_camera->list_lock);
	muse_camera->data_list = g_list_append(muse_camera->data_list, (gpointer)export_data);
	g_mutex_unlock(&muse_camera->list_lock);

	/* add bo and key to list */
	muse_camera_msg_event3(MUSE_CAMERA_CB_EVENT,
							      MUSE_CAMERA_EVENT_TYPE_CAPTURE,
							      module,
							      INT, tbm_key,
							      INT, is_postview,
							      INT, is_thumbnail);

	return;
}

void _camera_dispatcher_state_changed_cb(camera_state_e previous, camera_state_e current, bool by_policy, void *user_data)
{
	muse_module_h module = (muse_module_h)user_data;

	LOGD("Enter");
	int cb_previous = (int)previous;
	int cb_current = (int)current;
	int cb_by_policy = (int)by_policy;
	muse_camera_msg_event3(MUSE_CAMERA_CB_EVENT,
								MUSE_CAMERA_EVENT_TYPE_STATE_CHANGE,
								module,
								INT, cb_previous,
								INT, cb_current,
								INT, cb_by_policy);
	return;
}

void _camera_dispatcher_interrupted_cb(camera_policy_e policy, camera_state_e previous, camera_state_e current, void *user_data)
{
	muse_module_h module = (muse_module_h)user_data;

	LOGD("Enter");
	int cb_policy = (int)policy;
	int cb_previous = (int)previous;
	int cb_current = (int)current;
	muse_camera_msg_event3(MUSE_CAMERA_CB_EVENT,
								MUSE_CAMERA_EVENT_TYPE_INTERRUPTED,
								module,
								INT, cb_policy,
								INT, cb_previous,
								INT, cb_current);
	return;
}

void _camera_dispatcher_preview_cb(camera_preview_data_s *frame, void *user_data)
{
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_transport_info_s transport_info;
	muse_camera_export_data *export_data = NULL;
	int tbm_key = 0;
	muse_module_h module = (muse_module_h)user_data;
	unsigned char *buf_pos = NULL;
	int is_postview = 0;
	int is_thumbnail = 0;

	LOGD("Enter!!");

	if (frame == NULL) {
		LOGE("NULL data");
		return;
	}

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);
	if (muse_camera == NULL) {
		LOGE("NULL handle");
		return;
	}

	export_data = g_new0(muse_camera_export_data, 1);
	if (export_data == NULL) {
		LOGE("alloc export_data failed");
		return;
	}

	memset(&transport_info, 0x0, sizeof(muse_camera_transport_info_s));

	transport_info.bo = tbm_bo_alloc(muse_camera->bufmgr, transport_info.data_size, TBM_BO_DEFAULT);
	if (transport_info.bo == NULL) {
		LOGE("bo alloc failed");
		g_free(export_data);
		export_data = NULL;
		return;
	}

	transport_info.bo_handle = tbm_bo_map(transport_info.bo, TBM_DEVICE_CPU, TBM_OPTION_WRITE);
	if (transport_info.bo_handle.ptr == NULL) {
		LOGE("bo map Error!");
		tbm_bo_unref(transport_info.bo);
		g_free(export_data);
		export_data = NULL;
		return;
	}

	buf_pos = (unsigned char *)transport_info.bo_handle.ptr;

	memcpy(buf_pos, frame, sizeof(camera_preview_data_s));
	buf_pos += sizeof(camera_preview_data_s);

	switch (frame->num_of_planes) {
		case 1:
			memcpy(buf_pos, frame->data.single_plane.yuv, frame->data.single_plane.size);
		case 2:
			memcpy(buf_pos, frame->data.double_plane.y, frame->data.double_plane.y_size);
			buf_pos += frame->data.double_plane.y_size;
			memcpy(buf_pos, frame->data.double_plane.uv, frame->data.double_plane.uv_size);
		case 3:
			memcpy(buf_pos, frame->data.triple_plane.y, frame->data.triple_plane.y_size);
			buf_pos += frame->data.triple_plane.y_size;
			memcpy(buf_pos, frame->data.triple_plane.u, frame->data.triple_plane.u_size);
			buf_pos += frame->data.triple_plane.u_size;
			memcpy(buf_pos, frame->data.triple_plane.v, frame->data.triple_plane.v_size);
		default:
			break;
	}

	tbm_bo_unmap(transport_info.bo);

	tbm_key = tbm_bo_export(transport_info.bo);

	if(tbm_key == 0) {
		LOGE("Create key_info ERROR!!");
		tbm_bo_unref(transport_info.bo);
		transport_info.bo = NULL;
		g_free(export_data);
		export_data = NULL;
		return;
	}

	LOGD("bo %p, vaddr %p, size %d, key %d",
	     transport_info.bo,
	     transport_info.bo_handle.ptr,
	     transport_info.data_size,
	     tbm_key);

	/* set bo info */
	export_data->key = tbm_key;
	export_data->bo = transport_info.bo;

	/* add bo info to list */
	g_mutex_lock(&muse_camera->list_lock);
	muse_camera->data_list = g_list_append(muse_camera->data_list, (gpointer)export_data);
	g_mutex_unlock(&muse_camera->list_lock);

	/* add bo and key to list */
	muse_camera_msg_event1(MUSE_CAMERA_CB_EVENT,
							      MUSE_CAMERA_EVENT_TYPE_PREVIEW,
							      module,
							      INT, tbm_key);

	return;
}

void _camera_dispatcher_media_packet_preview_cb(media_packet_h pkt, void *user_data)
{
	muse_module_h module = (muse_module_h)user_data;

	LOGD("Enter");

	muse_camera_msg_event(MUSE_CAMERA_CB_EVENT,
							    MUSE_CAMERA_EVENT_TYPE_MEDIA_PACKET_PREVIEW,
							    module);
	return;
}

void _camera_dispatcher_capture_completed_cb(void *user_data)
{
	muse_module_h module = (muse_module_h)user_data;

	LOGD("Enter");

	muse_camera_msg_event(MUSE_CAMERA_CB_EVENT,
							    MUSE_CAMERA_EVENT_TYPE_CAPTURE_COMPLETE,
							    module);
	return;
}

void _camera_dispatcher_face_detected_cb(camera_detected_face_s *faces, int count, void *user_data)
{
	muse_module_h module = (muse_module_h)user_data;

	LOGD("Enter");

	muse_camera_msg_event1(MUSE_CAMERA_CB_EVENT,
							    MUSE_CAMERA_EVENT_TYPE_FACE_DETECTION,
							    module,
							    INT, count);
	return;
}

void _camera_dispatcher_focus_changed_cb(camera_focus_state_e state, void *user_data)
{
	muse_module_h module = (muse_module_h)user_data;
	int cb_state = (int)state;
	LOGD("Enter");

	muse_camera_msg_event1(MUSE_CAMERA_CB_EVENT,
							    MUSE_CAMERA_EVENT_TYPE_FOCUS_CHANGE,
							    module,
							    INT, cb_state);
	return;
}

void _camera_dispatcher_error_cb(camera_error_e error, camera_state_e current_state, void *user_data)
{
	muse_module_h module = (muse_module_h)user_data;
	int cb_error = (int)error;
	int cb_current_state = (int)current_state;
	LOGD("Enter");

	muse_camera_msg_event2(MUSE_CAMERA_CB_EVENT,
							    MUSE_CAMERA_EVENT_TYPE_ERROR,
							    module,
							    INT, cb_error,
							    INT, cb_current_state);
	return;
}

void _camera_dispatcher_hdr_progress_cb(int percent, void *user_data)
{
	muse_module_h module = (muse_module_h)user_data;
	LOGD("Enter");

	muse_camera_msg_event1(MUSE_CAMERA_CB_EVENT,
							    MUSE_CAMERA_EVENT_TYPE_HDR_PROGRESS,
							    module,
							    INT, percent);
	return;
}


int camera_dispatcher_create(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	int device_type;
	int client_fd = -1;
	intptr_t handle;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_CREATE;

	muse_camera_msg_get(device_type, muse_core_client_get_msg(module));

	/* privilege check */
	client_fd = muse_core_client_get_msg_fd(module);
	if (!muse_core_security_check_cynara(client_fd, CAMERA_PRIVILEGE_NAME)) {
		LOGE("security check failed");
		ret = CAMERA_ERROR_PERMISSION_DENIED;
		muse_camera_msg_return(api, ret, module);
		return MUSE_CAMERA_ERROR_NONE;
	}

	/* init handle */
	muse_camera = (muse_camera_handle_s *)malloc(sizeof(muse_camera_handle_s));
	if (muse_camera == NULL) {
		LOGE("handle alloc failed");
		ret = CAMERA_ERROR_OUT_OF_MEMORY;
		muse_camera_msg_return(api, ret, module);
		return MUSE_CAMERA_ERROR_NONE;
	}

	g_mutex_init(&muse_camera->list_lock);

	if (muse_core_ipc_get_bufmgr(&muse_camera->bufmgr) != MM_ERROR_NONE) {
		LOGE("muse_core_ipc_get_bufmgr failed");

		free(muse_camera);
		muse_camera = NULL;

		ret = CAMERA_ERROR_INVALID_OPERATION;
		muse_camera_msg_return(api, ret, module);

		return MUSE_CAMERA_ERROR_NONE;
	}

	ret = legacy_camera_create((camera_device_e)device_type, &muse_camera->camera_handle);

	LOGD("device_type : %d, handle : 0x%x, ret : 0x%x", device_type, muse_camera, ret);

	handle = (intptr_t)muse_camera;

	if (ret == CAMERA_ERROR_NONE) {
		muse_core_ipc_set_handle(module, (intptr_t)muse_camera);
		muse_camera_msg_return1(api, ret, module, POINTER, handle);
	} else {
		free(muse_camera);
		muse_camera = NULL;

		muse_camera_msg_return(api, ret, module);
	}

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_destroy(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_DESTROY;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("Enter, handle : %p", muse_camera);

	ret = legacy_camera_destroy(muse_camera->camera_handle);
	muse_camera_msg_return(api, ret, module);

	if (ret == CAMERA_ERROR_NONE) {
		g_mutex_clear(&muse_camera->list_lock);
		muse_camera->bufmgr = NULL;
		free(muse_camera);
		muse_camera = NULL;
	}

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_start_preview(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_START_PREVIEW;
	char *caps = NULL;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_start_preview(muse_camera->camera_handle);
	if(ret == CAMERA_ERROR_NONE) {
		ret = legacy_camera_get_video_caps(muse_camera->camera_handle, &caps);
		if((ret == CAMERA_ERROR_NONE) && caps) {
			LOGD("caps : %s", caps);
			muse_camera_msg_return1(api, ret, module, STRING, caps);
			g_free(caps);
		} else {
			LOGD("Failed to get server's video caps. ret 0x%x, caps %p", ret, caps);
			muse_camera_msg_return(api, ret, module);
			if (legacy_camera_stop_preview(muse_camera->camera_handle) != CAMERA_ERROR_NONE) {
				LOGW("failed to stop preview");
			}
		}
	} else {
		LOGD("start preview failed 0x%x", ret);
		muse_camera_msg_return(api, ret, module);
		return ret;
	}

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_stop_preview(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_STOP_PREVIEW;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_stop_preview(muse_camera->camera_handle);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_start_capture(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int is_capturing_cb = 0;
	int is_completed_cb = 0;
	void *capturing_cb = NULL;
	void *completed_cb = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_START_CAPTURE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(is_capturing_cb, muse_core_client_get_msg(module));
	muse_camera_msg_get(is_completed_cb, muse_core_client_get_msg(module));

	LOGD("Enter, handle : %p, module : %p, capturing_cb %d, completed_cb %d",
	     muse_camera, module, is_capturing_cb, is_completed_cb);

	if (is_capturing_cb) {
		capturing_cb = _camera_dispatcher_capturing_cb;
	}
	if (is_completed_cb) {
		completed_cb = _camera_dispatcher_capture_completed_cb;
	}

	ret = legacy_camera_start_capture(muse_camera->camera_handle,
							(camera_capturing_cb)capturing_cb,
							(camera_capture_completed_cb)completed_cb,
							(void *)module);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_is_supported_continuous_capture(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_SUPPORT_CONTINUOUS_CAPTURE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_is_supported_continuous_capture(muse_camera->camera_handle);

	LOGD("is supported ret : %d", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_start_continuous_capture(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int count;
	int interval;
	muse_camera_api_e api = MUSE_CAMERA_API_START_CONTINUOUS_CAPTURE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(count, muse_core_client_get_msg(module));
	muse_camera_msg_get(interval, muse_core_client_get_msg(module));

	LOGD("Enter, handle : %p, module : %p", muse_camera, module);

	ret = legacy_camera_start_continuous_capture(muse_camera->camera_handle,
										count,
										interval,
										(camera_capturing_cb)_camera_dispatcher_capturing_cb,
										NULL,
										(void *)module);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_stop_continuous_capture(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_STOP_CONTINUOUS_CAPTURE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_stop_continuous_capture(muse_camera->camera_handle);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_is_supported_face_detection(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_SUPPORT_FACE_DETECTION;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_is_supported_face_detection(muse_camera->camera_handle);

	LOGD("is supported ret : %d", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_is_supported_zero_shutter_lag(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_SUPPORT_ZERO_SHUTTER_LAG;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_is_supported_zero_shutter_lag(muse_camera->camera_handle);

	LOGD("is supported ret : %d", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_is_supported_media_packet_preview_cb(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_SUPPORT_MEDIA_PACKET_PREVIEW_CB;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_is_supported_media_packet_preview_cb(muse_camera->camera_handle);

	LOGD("is supported ret : %d", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_get_device_count(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int get_device_count;
	muse_camera_api_e api = MUSE_CAMERA_API_GET_DEVICE_COUNT;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_get_device_count(muse_camera->camera_handle, &get_device_count);

	LOGD("ret : %d, device count : %d", ret, get_device_count);

	muse_camera_msg_return1(api, ret, module, INT, get_device_count);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_start_face_detection(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_START_FACE_DETECTION;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("Enter, handle : 0x%x, module : %d", muse_camera, module);

	/*
	 * TODO : set callback handler.
	 */
	ret = legacy_camera_start_face_detection(muse_camera->camera_handle, NULL, NULL);
	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_stop_face_detection(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_STOP_FACE_DETECTION;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_stop_face_detection(muse_camera->camera_handle);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_get_state(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int get_state;
	camera_state_e state;
	muse_camera_api_e api = MUSE_CAMERA_API_GET_STATE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_get_state(muse_camera->camera_handle, &state);

	LOGD("ret : %d, state : %d", ret, state);

	get_state = (int)state;

	muse_camera_msg_return1(api, ret, module, INT, get_state);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_start_focusing(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int is_continuous;
	muse_camera_api_e api = MUSE_CAMERA_API_START_FOCUSING;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(is_continuous, muse_core_client_get_msg(module));

	LOGD("Enter, handle : 0x%x, module : %d", muse_camera, module);

	ret = legacy_camera_start_focusing(muse_camera->camera_handle, (bool)is_continuous);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_stop_focusing(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_CANCEL_FOCUSING;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_cancel_focusing(muse_camera->camera_handle);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_set_display(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int display_type;
	int display_surface;
	muse_camera_api_e api = MUSE_CAMERA_API_SET_DISPLAY;
	static guint stream_id = 0;
	char socket_path[SOCKET_PATH_LENGTH] = {0,};
	camera_h camera;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(display_type, muse_core_client_get_msg(module));
	muse_camera_msg_get(display_surface, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, display_type : %d", muse_camera, display_type);

	camera = muse_camera->camera_handle;
	stream_id = muse_core_get_atomic_uint();

	snprintf(socket_path, SOCKET_PATH_LENGTH, SOCKET_PATH_BASE, stream_id);

	LOGD("socket_path : %s", socket_path);

	ret = legacy_camera_set_shm_socket_path_for_mused(camera, socket_path);

	ret |= legacy_camera_set_mused_display(muse_camera->camera_handle, (camera_display_type_e)display_type);

	if (ret != CAMERA_ERROR_NONE) {
		muse_camera_msg_return(api, ret, module);
	} else {
		muse_camera_msg_return1(api, ret, module,
								STRING, socket_path);
	}

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_set_preview_resolution(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int width;
	int height;
	muse_camera_api_e api = MUSE_CAMERA_API_SET_PREVIEW_RESOLUTION;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(width, muse_core_client_get_msg(module));
	muse_camera_msg_get(height, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, set_width : %d, set_height : 0x%x", muse_camera, width, height);

	ret = legacy_camera_set_preview_resolution(muse_camera->camera_handle, width, height);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_set_capture_resolution(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int width;
	int height;
	muse_camera_api_e api = MUSE_CAMERA_API_SET_CAPTURE_RESOLUTION;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(width, muse_core_client_get_msg(module));
	muse_camera_msg_get(height, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, set_width : %d, set_height : %d", muse_camera, width, height);

	ret = legacy_camera_set_capture_resolution(muse_camera->camera_handle, width, height);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_set_capture_format(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int set_format;
	muse_camera_api_e api = MUSE_CAMERA_API_SET_CAPTURE_FORMAT;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(set_format, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, set_format : %d", muse_camera, set_format);

	ret = legacy_camera_set_capture_format(muse_camera->camera_handle, (camera_pixel_format_e)set_format);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_set_preview_format(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int set_format;
	muse_camera_api_e api = MUSE_CAMERA_API_SET_PREVIEW_FORMAT;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(set_format, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, set_format : %d", muse_camera, set_format);

	ret = legacy_camera_set_preview_format(muse_camera->camera_handle, (camera_pixel_format_e)set_format);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_get_preview_resolution(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int get_width;
	int get_height;
	muse_camera_api_e api = MUSE_CAMERA_API_GET_PREVIEW_RESOLUTION;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_get_preview_resolution(muse_camera->camera_handle, &get_width, &get_height);

	muse_camera_msg_return2(api, ret, module, INT, get_width, INT, get_height);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_set_display_rotation(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int set_rotation;
	muse_camera_api_e api = MUSE_CAMERA_API_SET_DISPLAY_ROTATION;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(set_rotation, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, set_rotation : %d", muse_camera, set_rotation);

	ret = legacy_camera_set_display_rotation(muse_camera->camera_handle, (camera_rotation_e)set_rotation);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_get_display_rotation(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	camera_rotation_e rotation;
	int get_rotation;
	muse_camera_api_e api = MUSE_CAMERA_API_GET_DISPLAY_ROTATION;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_get_display_rotation(muse_camera->camera_handle, &rotation);

	get_rotation = (int)rotation;

	muse_camera_msg_return1(api, ret, module, INT, get_rotation);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_set_display_flip(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int set_flip;
	muse_camera_api_e api = MUSE_CAMERA_API_SET_DISPLAY_FLIP;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(set_flip, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, set_flip : %d", muse_camera, set_flip);

	ret = legacy_camera_set_display_flip(muse_camera->camera_handle, (camera_flip_e)set_flip);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_get_display_flip(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int get_flip;
	camera_flip_e flip;
	muse_camera_api_e api = MUSE_CAMERA_API_GET_DISPLAY_FLIP;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_get_display_flip(muse_camera->camera_handle, &flip);

	get_flip = (int)flip;

	muse_camera_msg_return1(api, ret, module, INT, get_flip);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_set_display_visible(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int set_visible;
	muse_camera_api_e api = MUSE_CAMERA_API_SET_DISPLAY_VISIBLE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(set_visible, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, set_visible : %d", muse_camera, set_visible);

	ret = legacy_camera_set_display_visible(muse_camera->camera_handle, (bool)set_visible);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_is_display_visible(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int get_visible;
	bool visible;
	muse_camera_api_e api = MUSE_CAMERA_API_IS_DISPLAY_VISIBLE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_is_display_visible(muse_camera->camera_handle, &visible);

	get_visible = (int)visible;

	muse_camera_msg_return1(api, ret, module, INT, get_visible);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_set_display_mode(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int set_mode;
	muse_camera_api_e api = MUSE_CAMERA_API_SET_DISPLAY_MODE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(set_mode, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, display_mode : %d", muse_camera, set_mode);

	ret = legacy_camera_set_display_mode(muse_camera->camera_handle, (camera_display_mode_e)set_mode);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_get_display_mode(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int get_mode;
	camera_display_mode_e mode;
	muse_camera_api_e api = MUSE_CAMERA_API_GET_DISPLAY_MODE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_get_display_mode(muse_camera->camera_handle, &mode);

	get_mode = (int)mode;

	muse_camera_msg_return1(api, ret, module, INT, get_mode);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_get_capture_resolution(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int get_width;
	int get_height;
	muse_camera_api_e api = MUSE_CAMERA_API_GET_CAPTURE_RESOLUTION;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_get_capture_resolution(muse_camera->camera_handle, &get_width, &get_height);

	muse_camera_msg_return2(api, ret, module, INT, get_width, INT, get_height);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_get_capture_format(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int get_format;
	camera_pixel_format_e format;
	muse_camera_api_e api = MUSE_CAMERA_API_GET_CAPTURE_FORMAT;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_get_capture_format(muse_camera->camera_handle, &format);

	get_format = (int)format;

	muse_camera_msg_return1(api, ret, module, INT, get_format);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_get_preview_format(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int get_format;
	camera_pixel_format_e format;
	muse_camera_api_e api = MUSE_CAMERA_API_GET_PREVIEW_FORMAT;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_get_preview_format(muse_camera->camera_handle, &format);

	get_format = (int)format;

	muse_camera_msg_return1(api, ret, module, INT, get_format);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_set_preview_cb(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_SET_PREVIEW_CB;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_set_preview_cb(muse_camera->camera_handle,
								(camera_preview_cb)_camera_dispatcher_preview_cb,
								(void *)module);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_unset_preview_cb(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_UNSET_PREVIEW_CB;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_unset_preview_cb(muse_camera->camera_handle);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_set_media_packet_preview_cb(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_SET_MEDIA_PACKET_PREVIEW_CB;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_set_media_packet_preview_cb(muse_camera->camera_handle,
						(camera_media_packet_preview_cb)_camera_dispatcher_media_packet_preview_cb,
						(void *)module);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_unset_media_packet_preview_cb(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_UNSET_MEDIA_PACKET_PREVIEW_CB;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_unset_media_packet_preview_cb(muse_camera->camera_handle);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_set_state_changed_cb(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_SET_STATE_CHANGED_CB;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_set_state_changed_cb(muse_camera->camera_handle,
									(camera_state_changed_cb)_camera_dispatcher_state_changed_cb,
									(void *)module);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_unset_state_changed_cb(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_UNSET_STATE_CHANGED_CB;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_unset_state_changed_cb(muse_camera->camera_handle);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_set_interrupted_cb(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_SET_INTERRUPTED_CB;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_set_interrupted_cb(muse_camera->camera_handle,
								(camera_interrupted_cb)_camera_dispatcher_interrupted_cb,
								(void *)module);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_unset_interrupted_cb(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_UNSET_INTERRUPTED_CB;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_unset_interrupted_cb(muse_camera->camera_handle);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_set_focus_changed_cb(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_SET_FOCUS_CHANGED_CB;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_set_focus_changed_cb(muse_camera->camera_handle,
								(camera_focus_changed_cb)_camera_dispatcher_focus_changed_cb,
								(void *)module);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_unset_focus_changed_cb(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_UNSET_FOCUS_CHANGED_CB;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_unset_focus_changed_cb(muse_camera->camera_handle);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_set_error_cb(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_SET_ERROR_CB;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_set_error_cb(muse_camera->camera_handle,
							(camera_error_cb)_camera_dispatcher_error_cb,
							(void *)module);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_unset_error_cb(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_UNSET_ERROR_CB;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_unset_error_cb(muse_camera->camera_handle);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_foreach_supported_preview_resolution(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_SET_FOREACH_SUPPORTED_PREVIEW_RESOLUTION;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_foreach_supported_preview_resolution(muse_camera->camera_handle,
						(camera_supported_preview_resolution_cb)_camera_dispatcher_callback_supported_preview_resolution,
						(void *)module);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_foreach_supported_capture_resolution(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_SET_FOREACH_SUPPORTED_CAPTURE_RESOLUTION;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_foreach_supported_capture_resolution(muse_camera->camera_handle,
						(camera_supported_capture_resolution_cb)_camera_dispatcher_callback_supported_capture_resolution,
						(void *)module);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_foreach_supported_capture_format(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_SET_FOREACH_SUPPORTED_CAPTURE_FORMAT;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_foreach_supported_capture_format(muse_camera->camera_handle,
						(camera_supported_capture_format_cb)_camera_dispatcher_callback_supported_capture_format,
						(void *)module);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_foreach_supported_preview_format(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_SET_FOREACH_SUPPORTED_PREVIEW_FORMAT;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_foreach_supported_preview_format(muse_camera->camera_handle,
						(camera_supported_preview_format_cb)_camera_dispatcher_callback_supported_preview_format,
						(void *)module);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_get_recommended_preview_resolution(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int get_width;
	int get_height;
	muse_camera_api_e api = MUSE_CAMERA_API_GET_RECOMMENDED_PREVIEW_RESOLUTION;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_get_recommended_preview_resolution(muse_camera->camera_handle, &get_width, &get_height);

	muse_camera_msg_return2(api, ret, module, INT, get_width, INT, get_height);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_lens_orientation(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int get_angle;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_LENS_ORIENTATION;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_get_lens_orientation(muse_camera->camera_handle, &get_angle);

	muse_camera_msg_return1(api, ret, module, INT, get_angle);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_set_theater_mode(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int set_mode;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_SET_THEATER_MODE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(set_mode, muse_core_client_get_msg(module));

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_set_theater_mode(muse_camera->camera_handle, (camera_attr_theater_mode_e)set_mode);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_theater_mode(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int get_mode;
	camera_attr_theater_mode_e mode;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_THEATER_MODE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_get_theater_mode(muse_camera->camera_handle, &mode);

	get_mode = (int)mode;

	muse_camera_msg_return1(api, ret, module, INT, get_mode);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_foreach_supported_theater_mode(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_THEATER_MODE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);
	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_foreach_supported_theater_mode(muse_camera->camera_handle,
						(camera_attr_supported_theater_mode_cb)_camera_dispatcher_callback_supported_theater_mode,
						(void *)module);

	muse_camera_msg_return(api, ret, module);

	LOGD("ret : 0x%x!!!!!!!!!!", ret);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_set_preview_fps(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int set_fps;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_SET_PREVIEW_FPS;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(set_fps, muse_core_client_get_msg(module));

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_set_preview_fps(muse_camera->camera_handle, (camera_attr_fps_e)set_fps);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_set_image_quality(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int quality;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_SET_IMAGE_QUALITY;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(quality, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, image_quality : %d", muse_camera, quality);

	ret = legacy_camera_attr_set_image_quality(muse_camera->camera_handle, quality);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_preview_fps(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	camera_attr_fps_e fps;
	int get_fps;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_PREVIEW_FPS;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_get_preview_fps(muse_camera->camera_handle, &fps);

	get_fps = (int)fps;

	muse_camera_msg_return1(api, ret, module, INT, get_fps);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_image_quality(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int get_quality;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_IMAGE_QUALITY;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_get_image_quality(muse_camera->camera_handle, &get_quality);

	muse_camera_msg_return1(api, ret, module, INT, get_quality);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_set_zoom(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int zoom;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_SET_ZOOM;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(zoom, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, zoom : %d", muse_camera, zoom);

	ret = legacy_camera_attr_set_zoom(muse_camera->camera_handle, zoom);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_set_af_mode(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int set_mode;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_SET_AF_MODE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(set_mode, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, set_mode : %d", muse_camera, set_mode);

	ret = legacy_camera_attr_set_af_mode(muse_camera->camera_handle, (camera_attr_af_mode_e)set_mode);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_set_af_area(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int x;
	int y;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_SET_AF_AREA;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(x, muse_core_client_get_msg(module));
	muse_camera_msg_get(y, muse_core_client_get_msg(module));

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_set_af_area(muse_camera->camera_handle, x, y);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_clear_af_area(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_CLEAR_AF_AREA;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_clear_af_area(muse_camera->camera_handle);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_set_exposure_mode(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int set_mode;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_SET_EXPOSURE_MODE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(set_mode, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, set_mode : %d", muse_camera, set_mode);

	ret = legacy_camera_attr_set_exposure_mode(muse_camera->camera_handle, (camera_attr_exposure_mode_e)set_mode);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_set_exposure(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int value;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_SET_EXPOSURE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(value, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, value : %d", muse_camera, value);

	ret = legacy_camera_attr_set_exposure(muse_camera->camera_handle, value);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_set_iso(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int set_iso;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_SET_ISO;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(set_iso, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, set_iso : %d", muse_camera, set_iso);

	ret = legacy_camera_attr_set_iso(muse_camera->camera_handle, (camera_attr_iso_e)set_iso);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_set_brightness(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int level;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_SET_BRIGHTNESS;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(level, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, level : %d", muse_camera, level);

	ret = legacy_camera_attr_set_brightness(muse_camera->camera_handle, level);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_set_contrast(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int level;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_SET_CONTRAST;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(level, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, level : %d", muse_camera, level);

	ret = legacy_camera_attr_set_contrast(muse_camera->camera_handle, level);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_set_whitebalance(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int set_whitebalance;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_SET_WHITEBALANCE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(set_whitebalance, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, set_whitebalance : %d", muse_camera, set_whitebalance);

	ret = legacy_camera_attr_set_whitebalance(muse_camera->camera_handle, (camera_attr_whitebalance_e)set_whitebalance);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_set_effect(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int set_effect;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_SET_EFFECT;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(set_effect, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, set_effect : %d", muse_camera, set_effect);

	ret = legacy_camera_attr_set_effect(muse_camera->camera_handle, (camera_attr_effect_mode_e)set_effect);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_set_scene_mode(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int set_mode;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_SET_SCENE_MODE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(set_mode, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, set_mode : %d", muse_camera, set_mode);

	ret = legacy_camera_attr_set_scene_mode(muse_camera->camera_handle, (camera_attr_scene_mode_e)set_mode);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_enable_tag(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int set_enable;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_ENABLE_TAG;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(set_enable, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, set_enable : %d", muse_camera, set_enable);

	ret = legacy_camera_attr_enable_tag(muse_camera->camera_handle, (bool)set_enable);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_set_tag_image_description(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_SET_TAG_IMAGE_DESCRIPTION;
	char description[MUSE_MSG_MAX_LENGTH] = {0,};

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get_string(description, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, description : %s", muse_camera, description);

	ret = legacy_camera_attr_set_tag_image_description(muse_camera->camera_handle, description);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_set_tag_orientation(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int set_orientation;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_SET_TAG_ORIENTATION;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(set_orientation, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, set_orientation : %d", muse_camera, set_orientation);

	ret = legacy_camera_attr_set_tag_orientation(muse_camera->camera_handle, (camera_attr_tag_orientation_e)set_orientation);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_set_tag_software(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_SET_TAG_SOFTWARE;
	char software[MUSE_MSG_MAX_LENGTH] = {0,};

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get_string(software, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, software : %s", muse_camera, software);

	ret = legacy_camera_attr_set_tag_software(muse_camera->camera_handle, software);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_set_geotag(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_SET_GEOTAG;
	double set_geotag[3] = {0,};

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get_array(set_geotag, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, set_geotag1 : %d, set_geotag2 : %d, set_geotag3 : %d", muse_camera, set_geotag[0], set_geotag[1], set_geotag[2]);

	ret = legacy_camera_attr_set_geotag(muse_camera->camera_handle, set_geotag[0], set_geotag[1], set_geotag[2]);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_remove_geotag(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_REMOVE_GEOTAG;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_remove_geotag(muse_camera->camera_handle);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_set_flash_mode(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int set_mode;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_SET_FLASH_MODE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(set_mode, muse_core_client_get_msg(module));

	LOGD("handle : 0x%x, set_mode : %d", muse_camera, set_mode);

	ret = legacy_camera_attr_set_flash_mode(muse_camera->camera_handle, (camera_attr_flash_mode_e)set_mode);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_zoom(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int get_zoom;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_ZOOM;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_get_zoom(muse_camera->camera_handle, &get_zoom);

	muse_camera_msg_return1(api, ret, module, INT, get_zoom);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_zoom_range(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int get_min;
	int get_max;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_ZOOM_RANGE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_get_zoom_range(muse_camera->camera_handle, &get_min, &get_max);

	muse_camera_msg_return2(api, ret, module, INT, get_min, INT, get_max);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_af_mode(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	camera_attr_af_mode_e mode;
	int get_mode;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_AF_MODE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_get_af_mode(muse_camera->camera_handle, &mode);

	get_mode = (int)mode;

	muse_camera_msg_return1(api, ret, module, INT, get_mode);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_exposure_mode(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	camera_attr_exposure_mode_e mode;
	int get_mode;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_EXPOSURE_MODE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_get_exposure_mode(muse_camera->camera_handle, &mode);

	get_mode = (int)mode;

	muse_camera_msg_return1(api, ret, module, INT, get_mode);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_exposure(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int get_value;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_EXPOSURE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_get_exposure(muse_camera->camera_handle, &get_value);

	muse_camera_msg_return1(api, ret, module, INT, get_value);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_exposure_range(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int get_min;
	int get_max;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_EXPOSURE_RANGE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_get_exposure_range(muse_camera->camera_handle, &get_min, &get_max);

	muse_camera_msg_return2(api, ret, module, INT, get_min, INT, get_max);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_iso(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	camera_attr_iso_e iso;
	int get_iso;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_ISO;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_get_iso(muse_camera->camera_handle, &iso);

	get_iso = (int)iso;

	muse_camera_msg_return1(api, ret, module, INT, get_iso);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_brightness(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int get_level;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_BRIGHTNESS;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_get_brightness(muse_camera->camera_handle, &get_level);

	muse_camera_msg_return1(api, ret, module, INT, get_level);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_brightness_range(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int get_min;
	int get_max;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_BRIGHTNESS_RANGE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_get_brightness_range(muse_camera->camera_handle, &get_min, &get_max);

	muse_camera_msg_return2(api, ret, module, INT, get_min, INT, get_max);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_contrast(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int get_level;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_CONTRAST;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_get_contrast(muse_camera->camera_handle, &get_level);

	muse_camera_msg_return1(api, ret, module, INT, get_level);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_contrast_range(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	int get_min;
	int get_max;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_CONTRAST_RANGE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_get_contrast_range(muse_camera->camera_handle, &get_min, &get_max);

	muse_camera_msg_return2(api, ret, module, INT, get_min, INT, get_max);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_whitebalance(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	camera_attr_whitebalance_e wb;
	int get_wb;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_WHITEBALANCE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_get_whitebalance(muse_camera->camera_handle, &wb);

	get_wb = (int)wb;

	muse_camera_msg_return1(api, ret, module, INT, get_wb);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_effect(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	camera_attr_effect_mode_e effect;
	int get_effect;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_EFFECT;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_get_effect(muse_camera->camera_handle, &effect);

	get_effect = (int)effect;

	muse_camera_msg_return1(api, ret, module, INT, get_effect);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_scene_mode(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	camera_attr_scene_mode_e mode;
	int get_mode;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_SCENE_MODE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_get_scene_mode(muse_camera->camera_handle, &mode);

	get_mode = (int)mode;

	muse_camera_msg_return1(api, ret, module, INT, get_mode);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_is_enabled_tag(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	bool enable;
	int get_enable;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_IS_ENABLED_TAG;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_is_enabled_tag(muse_camera->camera_handle, &enable);

	get_enable = (int)enable;

	muse_camera_msg_return1(api, ret, module, INT, get_enable);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_tag_image_description(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_TAG_IMAGE_DESCRIPTION;
	char *get_description;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	ret = legacy_camera_attr_get_tag_image_description(muse_camera->camera_handle, &get_description);

	LOGD("handle : 0x%x, get_description : %s", muse_camera, get_description);
	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return1(api, ret, module, STRING, get_description);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_tag_orientation(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	camera_attr_tag_orientation_e orientation;
	int get_orientation;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_TAG_ORIENTATION;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_get_tag_orientation(muse_camera->camera_handle, &orientation);

	get_orientation = (int)orientation;

	muse_camera_msg_return1(api, ret, module, INT, get_orientation);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_tag_software(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_TAG_SOFTWARE;
	char *get_software;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	ret = legacy_camera_attr_get_tag_software(muse_camera->camera_handle, &get_software);

	LOGD("handle : 0x%x, get_software : %s", muse_camera, get_software);
	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return1(api, ret, module, STRING, get_software);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_geotag(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_GEOTAG;
	double latitude;
	double longitude;
	double altitude;
	double get_geotag[3] = {0,};

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_get_geotag(muse_camera->camera_handle, &latitude, &longitude, &altitude);

	get_geotag[0] = latitude;
	get_geotag[1] = longitude;
	get_geotag[2] = altitude;

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return_array(api, ret, module, get_geotag, sizeof(get_geotag), sizeof(double));

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_flash_mode(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	camera_attr_flash_mode_e mode;
	int get_mode;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_FLASH_MODE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_get_flash_mode(muse_camera->camera_handle, &mode);

	get_mode = (int)mode;

	muse_camera_msg_return1(api, ret, module, INT, get_mode);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_foreach_supported_af_mode(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_AF_MODE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_foreach_supported_af_mode(muse_camera->camera_handle,
						(camera_attr_supported_af_mode_cb)_camera_dispatcher_callback_supported_af_mode,
						(void *)module);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_foreach_supported_exposure_mode(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_EXPOSURE_MODE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : 0x%x, api : %d", muse_camera, api);

	ret = legacy_camera_attr_foreach_supported_exposure_mode(muse_camera->camera_handle,
						(camera_attr_supported_exposure_mode_cb)_camera_dispatcher_callback_supported_exposure_mode,
						(void *)module);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_foreach_supported_iso(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_ISO;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_foreach_supported_iso(muse_camera->camera_handle,
						(camera_attr_supported_iso_cb)_camera_dispatcher_callback_supported_iso_mode,
						(void *)module);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_foreach_supported_whitebalance(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_WHITEBALANCE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_foreach_supported_whitebalance(muse_camera->camera_handle,
						(camera_attr_supported_whitebalance_cb)_camera_dispatcher_callback_supported_whitebalance,
						(void *)module);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_foreach_supported_effect(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_EFFECT;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_foreach_supported_effect(muse_camera->camera_handle,
						(camera_attr_supported_effect_cb)_camera_dispatcher_callback_supported_effect,
						(void *)module);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_foreach_supported_scene_mode(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_SCENE_MODE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_foreach_supported_scene_mode(muse_camera->camera_handle,
						(camera_attr_supported_scene_mode_cb)_camera_dispatcher_callback_supported_scene_mode,
						(void *)module);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_foreach_supported_flash_mode(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_FLASH_MODE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_foreach_supported_flash_mode(muse_camera->camera_handle,
						(camera_attr_supported_flash_mode_cb)_camera_dispatcher_callback_supported_flash_mode,
						(void *)module);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_foreach_supported_fps(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_FPS;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_foreach_supported_fps(muse_camera->camera_handle,
						(camera_attr_supported_fps_cb)_camera_dispatcher_callback_supported_fps,
						(void *)module);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_foreach_supported_fps_by_resolution(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_FPS_BY_RESOLUTION;
	int width;
	int height;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(width, muse_core_client_get_msg(module));
	muse_camera_msg_get(height, muse_core_client_get_msg(module));

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_foreach_supported_fps_by_resolution(muse_camera->camera_handle,
						width, height,
						(camera_attr_supported_fps_cb)_camera_dispatcher_callback_supported_fps_by_resolution,
						(void *)module);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_foreach_supported_stream_flip(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_STREAM_FLIP;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_foreach_supported_stream_flip(muse_camera->camera_handle,
						(camera_attr_supported_stream_flip_cb)_camera_dispatcher_callback_supported_stream_flip,
						(void *)module);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_foreach_supported_stream_rotation(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_STREAM_ROTATION;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_foreach_supported_stream_rotation(muse_camera->camera_handle,
						(camera_attr_supported_stream_rotation_cb)_camera_dispatcher_callback_supported_stream_rotation,
						(void *)module);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_set_stream_rotation(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_SET_STREAM_ROTATION;
	int set_rotation;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(set_rotation, muse_core_client_get_msg(module));

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_set_stream_rotation(muse_camera->camera_handle, (camera_rotation_e)set_rotation);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_stream_rotation(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_STREAM_ROTATION;
	camera_rotation_e rotation;
	int get_rotation;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_get_stream_rotation(muse_camera->camera_handle, &rotation);

	LOGD("ret : 0x%x", ret);

	get_rotation = (int)rotation;

	muse_camera_msg_return1(api, ret, module, INT, get_rotation);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_set_stream_flip(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_SET_STREAM_FLIP;
	int set_flip;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(set_flip, muse_core_client_get_msg(module));

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_set_stream_flip(muse_camera->camera_handle, (camera_flip_e)set_flip);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_stream_flip(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_STREAM_FLIP;
	camera_flip_e flip;
	int get_flip;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_get_stream_flip(muse_camera->camera_handle, &flip);

	LOGD("ret : 0x%x", ret);

	get_flip = (int)flip;

	muse_camera_msg_return1(api, ret, module, INT, get_flip);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_set_hdr_mode(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_SET_HDR_MODE;
	int set_mode;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(set_mode, muse_core_client_get_msg(module));

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_set_hdr_mode(muse_camera->camera_handle, (camera_attr_hdr_mode_e)set_mode);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_get_hdr_mode(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_GET_HDR_MODE;
	camera_attr_hdr_mode_e mode;
	int get_mode;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_get_hdr_mode(muse_camera->camera_handle, &mode);

	LOGD("ret : 0x%x", ret);

	get_mode = (int)mode;

	muse_camera_msg_return1(api, ret, module, INT, get_mode);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_is_supported_hdr_capture(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_IS_SUPPORTED_HDR_CAPTURE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_is_supported_hdr_capture(muse_camera->camera_handle);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_set_hdr_capture_progress_cb(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_SET_HDR_CAPTURE_PROGRESS_CB;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);
	/*
	 *	TODO : set the cb function here.
	 */
	ret = legacy_camera_attr_set_hdr_capture_progress_cb(muse_camera->camera_handle, NULL, NULL);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_unset_hdr_capture_progress_cb(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_UNSET_HDR_CAPTURE_PROGRESS_CB;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_unset_hdr_capture_progress_cb(muse_camera->camera_handle);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_enable_anti_shake(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_ENABLE_ANTI_SHAKE;
	int set_enable;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(set_enable, muse_core_client_get_msg(module));

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_enable_anti_shake(muse_camera->camera_handle, (bool)set_enable);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_is_enabled_anti_shake(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_IS_ENABLED_ANTI_SHAKE;
	bool enabled;
	int get_enabled;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_is_enabled_anti_shake(muse_camera->camera_handle, &enabled);

	LOGD("ret : 0x%x", ret);

	get_enabled = (int)enabled;

	muse_camera_msg_return1(api, ret, module, INT, get_enabled);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_is_supported_anti_shake(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_IS_SUPPORTED_ANTI_SHAKE;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_is_supported_anti_shake(muse_camera->camera_handle);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_enable_video_stabilization(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_ENABLE_VIDEO_STABILIZATION;
	int set_enable;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(set_enable, muse_core_client_get_msg(module));

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_enable_video_stabilization(muse_camera->camera_handle, (bool)set_enable);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_is_enabled_video_stabilization(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_IS_ENABLED_VIDEO_STABILIZATION;
	bool enabled;
	int get_enabled;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_is_enabled_video_stabilization(muse_camera->camera_handle, &enabled);

	LOGD("ret : 0x%x", ret);

	get_enabled = (int)enabled;

	muse_camera_msg_return1(api, ret, module, INT, get_enabled);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_is_supported_video_stabilization(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_IS_SUPPORTED_VIDEO_STABILIZATION;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_is_supported_video_stabilization(muse_camera->camera_handle);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_enable_auto_contrast(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_ENABLE_AUTO_CONTRAST;
	int set_enable;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(set_enable, muse_core_client_get_msg(module));

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_enable_auto_contrast(muse_camera->camera_handle, (bool)set_enable);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_is_enabled_auto_contrast(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_IS_ENABLED_AUTO_CONTRAST;
	bool enabled;
	int get_enabled;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_is_enabled_auto_contrast(muse_camera->camera_handle, &enabled);

	LOGD("ret : 0x%x", ret);

	get_enabled = (int)enabled;

	muse_camera_msg_return1(api, ret, module, INT, get_enabled);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_is_supported_auto_contrast(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_IS_SUPPORTED_AUTO_CONTRAST;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_is_supported_auto_contrast(muse_camera->camera_handle);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_attr_disable_shutter_sound(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_DISABLE_SHUTTER_SOUND;
	int set_disable;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(set_disable, muse_core_client_get_msg(module));

	LOGD("handle : %p", muse_camera);

	ret = legacy_camera_attr_disable_shutter_sound(muse_camera->camera_handle, (bool)set_disable);

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int camera_dispatcher_return_buffer(muse_module_h module)
{
	int ret = CAMERA_ERROR_NONE;
	muse_camera_handle_s *muse_camera = NULL;
	muse_camera_api_e api = MUSE_CAMERA_API_ATTR_DISABLE_SHUTTER_SOUND;
	int tbm_key;

	muse_camera = (muse_camera_handle_s *)muse_core_ipc_get_handle(module);

	muse_camera_msg_get(tbm_key, muse_core_client_get_msg(module));

	LOGD("handle : %p, key : %d", muse_camera, tbm_key);

	if (_camera_remove_export_data(module, tbm_key, FALSE)) {
		ret = CAMERA_ERROR_NONE;
	} else {
		ret = CAMERA_ERROR_INVALID_OPERATION;
	}

	LOGD("ret : 0x%x", ret);

	muse_camera_msg_return(api, ret, module);

	return MUSE_CAMERA_ERROR_NONE;
}

int (*dispatcher[MUSE_CAMERA_API_MAX]) (muse_module_h module) = {
	camera_dispatcher_create,				/* MUSE_CAMERA_API_CREATE */
	camera_dispatcher_destroy,			/* MUSE_CAMERA_API_DESTROY */
	camera_dispatcher_start_preview,		/* MUSE_CAMERA_START_PREVIEW */
	camera_dispatcher_stop_preview,		/* MUSE_CAMERA_API_START_PREVIEW */
	camera_dispatcher_start_capture,		/* MUSE_CAMERA_START_CAPTURE */
	camera_dispatcher_is_supported_continuous_capture, 	/* MUSE_CAMERA_API_SUPPORT_CONTINUOUS_CAPTURE */
	camera_dispatcher_start_continuous_capture, 			/* MUSE_CAMERA_API_START_CONTINUOUS_CAPTURE, */
	camera_dispatcher_stop_continuous_capture, 			/* MUSE_CAMERA_API_STOP_CONTINUOUS_CAPTURE, */
	camera_dispatcher_is_supported_face_detection,		/* MUSE_CAMERA_API_SUPPORT_FACE_DETECTION, */
	camera_dispatcher_is_supported_zero_shutter_lag,		/* MUSE_CAMERA_API_SUPPORT_ZERO_SHUTTER_LAG, */
	camera_dispatcher_is_supported_media_packet_preview_cb,		/* MUSE_CAMERA_API_SUPPORT_MEDIA_PACKET_PREVIEW_CB, */
	camera_dispatcher_get_device_count, 					/* MUSE_CAMERA_API_GET_DEVICE_COUNT, */
	camera_dispatcher_start_face_detection, 				/* MUSE_CAMERA_API_START_FACE_DETECTION, */
	camera_dispatcher_stop_face_detection, 				/* MUSE_CAMERA_API_STOP_FACE_DETECTION, */
	camera_dispatcher_get_state, 					/* MUSE_CAMERA_API_GET_STATE, */
	camera_dispatcher_start_focusing, 				/* MUSE_CAMERA_API_START_FOCUSING, */
	camera_dispatcher_stop_focusing, 				/* MUSE_CAMERA_API_CANCEL_FOCUSING, */
	camera_dispatcher_set_display, 				/* MUSE_CAMERA_API_SET_DISPLAY, */
	camera_dispatcher_set_preview_resolution, 	/* MUSE_CAMERA_API_SET_PREVIEW_RESOLUTION, */
	camera_dispatcher_set_capture_resolution, 		/* MUSE_CAMERA_API_SET_CAPTURE_RESOLUTION, */
	camera_dispatcher_set_capture_format, 		/* MUSE_CAMERA_API_SET_CAPTURE_FORMAT, */
	camera_dispatcher_set_preview_format, 		/* MUSE_CAMERA_API_SET_PREVIEW_FORMAT, */
	camera_dispatcher_get_preview_resolution, 	/* MUSE_CAMERA_API_GET_PREVIEW_RESOLUTION, */
	camera_dispatcher_set_display_rotation, 		/* MUSE_CAMERA_API_SET_DISPLAY_ROTATION, */
	camera_dispatcher_get_display_rotation,		/* MUSE_CAMERA_API_GET_DISPLAY_ROTATION, */
	camera_dispatcher_set_display_flip, 			/* MUSE_CAMERA_API_SET_DISPLAY_FLIP, */
	camera_dispatcher_get_display_flip, 			/* MUSE_CAMERA_API_GET_DISPLAY_FLIP, */
	camera_dispatcher_set_display_visible, 		/* MUSE_CAMERA_API_SET_DISPLAY_VISIBLE, */
	camera_dispatcher_is_display_visible, /* MUSE_CAMERA_API_IS_DISPLAY_VISIBLE, */
	camera_dispatcher_set_display_mode, /* MUSE_CAMERA_API_SET_DISPLAY_MODE, */
	camera_dispatcher_get_display_mode, /* MUSE_CAMERA_API_GET_DISPLAY_MODE, */
	camera_dispatcher_get_capture_resolution, /* MUSE_CAMERA_API_GET_CAPTURE_RESOLUTION, */
	camera_dispatcher_get_capture_format, /* MUSE_CAMERA_API_GET_CAPTURE_FORMAT, */
	camera_dispatcher_get_preview_format, /* MUSE_CAMERA_API_GET_PREVIEW_FORMAT, */
	camera_dispatcher_set_preview_cb, /* MUSE_CAMERA_API_SET_PREVIEW_CB, */
	camera_dispatcher_unset_preview_cb, /* MUSE_CAMERA_API_UNSET_PREVIEW_CB, */
	camera_dispatcher_set_media_packet_preview_cb, /* MUSE_CAMERA_API_SET_MEDIA_PACKET_PREVIEW_CB, */
	camera_dispatcher_unset_media_packet_preview_cb, /* MUSE_CAMERA_API_UNSET_MEDIA_PACKET_PREVIEW_CB, */
	camera_dispatcher_set_state_changed_cb, /* MUSE_CAMERA_API_SET_STATE_CHANGED_CB, */
	camera_dispatcher_unset_state_changed_cb, /* MUSE_CAMERA_API_UNSET_STATE_CHANGED_CB, */
	camera_dispatcher_set_interrupted_cb, /* MUSE_CAMERA_API_SET_INTERRUPTED_CB, */
	camera_dispatcher_unset_interrupted_cb, /* MUSE_CAMERA_API_UNSET_INTERRUPTED_CB, */
	camera_dispatcher_set_focus_changed_cb, /* MUSE_CAMERA_API_SET_FOCUS_CHANGED_CB, */
	camera_dispatcher_unset_focus_changed_cb, /* MUSE_CAMERA_API_UNSET_FOCUS_CHANGED_CB, */
	camera_dispatcher_set_error_cb, /* MUSE_CAMERA_API_SET_ERROR_CB, */
	camera_dispatcher_unset_error_cb, /* MUSE_CAMERA_API_UNSET_ERROR_CB, */
	camera_dispatcher_foreach_supported_preview_resolution, /* MUSE_CAMERA_API_SET_FOREACH_SUPPORTED_PREVIEW_RESOLUTION, */
	camera_dispatcher_foreach_supported_capture_resolution, /* MUSE_CAMERA_API_SET_FOREACH_SUPPORTED_CAPTURE_RESOLUTION, */
	camera_dispatcher_foreach_supported_capture_format, /* MUSE_CAMERA_API_SET_FOREACH_SUPPORTED_CAPTURE_FORMAT, */
	camera_dispatcher_foreach_supported_preview_format, /* MUSE_CAMERA_API_SET_FOREACH_SUPPORTED_PREVIEW_FORMAT, */
	camera_dispatcher_get_recommended_preview_resolution, /* MUSE_CAMERA_API_GET_RECOMMENDED_PREVIEW_RESOLUTION, */
	camera_dispatcher_attr_get_lens_orientation, /* MUSE_CAMERA_API_ATTR_GET_LENS_ORIENTATION, */
	camera_dispatcher_attr_set_theater_mode, /* MUSE_CAMERA_API_ATTR_SET_THEATER_MODE, */
	camera_dispatcher_attr_get_theater_mode, /* MUSE_CAMERA_API_ATTR_GET_THEATER_MODE, */
	camera_dispatcher_attr_foreach_supported_theater_mode, /* MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_THEATER_MODE, */
	camera_dispatcher_attr_set_preview_fps, /* MUSE_CAMERA_API_ATTR_SET_PREVIEW_FPS, */
	camera_dispatcher_attr_set_image_quality, /* MUSE_CAMERA_API_ATTR_SET_IMAGE_QUALITY, */
	camera_dispatcher_attr_get_preview_fps, /* MUSE_CAMERA_API_ATTR_GET_PREVIEW_FPS, */
	camera_dispatcher_attr_get_image_quality, /* MUSE_CAMERA_API_ATTR_GET_IMAGE_QUALITY, */
	camera_dispatcher_attr_set_zoom, /* MUSE_CAMERA_API_ATTR_SET_ZOOM, */
	camera_dispatcher_attr_set_af_mode, /* MUSE_CAMERA_API_ATTR_SET_AF_MODE, */
	camera_dispatcher_attr_set_af_area, /* MUSE_CAMERA_API_ATTR_SET_AF_AREA, */
	camera_dispatcher_attr_clear_af_area, /* MUSE_CAMERA_API_ATTR_CLEAR_AF_AREA, */
	camera_dispatcher_attr_set_exposure_mode, /* MUSE_CAMERA_API_ATTR_SET_EXPOSURE_MODE, */
	camera_dispatcher_attr_set_exposure, /* MUSE_CAMERA_API_ATTR_SET_EXPOSURE, */
	camera_dispatcher_attr_set_iso, /* MUSE_CAMERA_API_ATTR_SET_ISO, */
	camera_dispatcher_attr_set_brightness, /* MUSE_CAMERA_API_ATTR_SET_BRIGHTNESS, */
	camera_dispatcher_attr_set_contrast, /* MUSE_CAMERA_API_ATTR_SET_CONTRAST, */
	camera_dispatcher_attr_set_whitebalance, /* MUSE_CAMERA_API_ATTR_SET_WHITEBALANCE, */
	camera_dispatcher_attr_set_effect, /* MUSE_CAMERA_API_ATTR_SET_EFFECT, */
	camera_dispatcher_attr_set_scene_mode, /* MUSE_CAMERA_API_ATTR_SET_SCENE_MODE, */
	camera_dispatcher_attr_enable_tag, /* MUSE_CAMERA_API_ATTR_ENABLE_TAG, */
	camera_dispatcher_attr_set_tag_image_description, /* MUSE_CAMERA_API_ATTR_SET_TAG_IMAGE_DESCRIPTION, */
	camera_dispatcher_attr_set_tag_orientation, /* MUSE_CAMERA_API_ATTR_SET_TAG_ORIENTATION, */
	camera_dispatcher_attr_set_tag_software, /* MUSE_CAMERA_API_ATTR_SET_TAG_SOFTWARE, */
	camera_dispatcher_attr_set_geotag, /* MUSE_CAMERA_API_ATTR_SET_GEOTAG, */
	camera_dispatcher_attr_remove_geotag, /* MUSE_CAMERA_API_ATTR_REMOVE_GEOTAG, */
	camera_dispatcher_attr_set_flash_mode, /* MUSE_CAMERA_API_ATTR_SET_FLASH_MODE, */
	camera_dispatcher_attr_get_zoom, /* MUSE_CAMERA_API_ATTR_GET_ZOOM, */
	camera_dispatcher_attr_get_zoom_range, /* MUSE_CAMERA_API_ATTR_GET_ZOOM_RANGE, */
	camera_dispatcher_attr_get_af_mode, /* MUSE_CAMERA_API_ATTR_GET_AF_MODE, */
	camera_dispatcher_attr_get_exposure_mode, /* MUSE_CAMERA_API_ATTR_GET_EXPOSURE_MODE, */
	camera_dispatcher_attr_get_exposure, /* MUSE_CAMERA_API_ATTR_GET_EXPOSURE, */
	camera_dispatcher_attr_get_exposure_range, /* MUSE_CAMERA_API_ATTR_GET_EXPOSURE_RANGE, */
	camera_dispatcher_attr_get_iso, /* MUSE_CAMERA_API_ATTR_GET_ISO, */
	camera_dispatcher_attr_get_brightness, /* MUSE_CAMERA_API_ATTR_GET_BRIGHTNESS, */
	camera_dispatcher_attr_get_brightness_range, /* MUSE_CAMERA_API_ATTR_GET_BRIGHTNESS_RANGE, */
	camera_dispatcher_attr_get_contrast, /* MUSE_CAMERA_API_ATTR_GET_CONTRAST, */
	camera_dispatcher_attr_get_contrast_range, /* MUSE_CAMERA_API_ATTR_GET_CONTRAST_RANGE, */
	camera_dispatcher_attr_get_whitebalance, /* MUSE_CAMERA_API_ATTR_GET_WHITEBALANCE, */
	camera_dispatcher_attr_get_effect, /* MUSE_CAMERA_API_ATTR_GET_EFFECT, */
	camera_dispatcher_attr_get_scene_mode, /* MUSE_CAMERA_API_ATTR_GET_SCENE_MODE, */
	camera_dispatcher_attr_is_enabled_tag, /* MUSE_CAMERA_API_ATTR_IS_ENABLED_TAG, */
	camera_dispatcher_attr_get_tag_image_description, /* MUSE_CAMERA_API_ATTR_GET_TAG_IMAGE_DESCRIPTION, */
	camera_dispatcher_attr_get_tag_orientation, /* MUSE_CAMERA_API_ATTR_GET_TAG_ORIENTATION, */
	camera_dispatcher_attr_get_tag_software, /* MUSE_CAMERA_API_ATTR_GET_TAG_SOFTWARE, */
	camera_dispatcher_attr_get_geotag, /* MUSE_CAMERA_API_ATTR_GET_GEOTAG, */
	camera_dispatcher_attr_get_flash_mode, /* MUSE_CAMERA_API_ATTR_GET_FLASH_MODE, */
	camera_dispatcher_attr_foreach_supported_af_mode, /* MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_AF_MODE, */
	camera_dispatcher_attr_foreach_supported_exposure_mode, /* MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_EXPOSURE_MODE, */
	camera_dispatcher_attr_foreach_supported_iso, /* MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_ISO, */
	camera_dispatcher_attr_foreach_supported_whitebalance, /* MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_WHITEBALANCE, */
	camera_dispatcher_attr_foreach_supported_effect, /* MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_EFFECT, */
	camera_dispatcher_attr_foreach_supported_scene_mode, /* MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_SCENE_MODE, */
	camera_dispatcher_attr_foreach_supported_flash_mode, /* MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_FLASH_MODE, */
	camera_dispatcher_attr_foreach_supported_fps, /* MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_FPS, */
	camera_dispatcher_attr_foreach_supported_fps_by_resolution, /* MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_FPS_BY_RESOLUTION, */
	camera_dispatcher_attr_foreach_supported_stream_flip, /* MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_STREAM_FLIP, */
	camera_dispatcher_attr_foreach_supported_stream_rotation, /* MUSE_CAMERA_API_ATTR_FOREACH_SUPPORTED_STREAM_ROTATION, */
	camera_dispatcher_attr_set_stream_rotation, /* MUSE_CAMERA_API_ATTR_SET_STREAM_ROTATION, */
	camera_dispatcher_attr_get_stream_rotation, /* MUSE_CAMERA_API_ATTR_GET_STREAM_ROTATION, */
	camera_dispatcher_attr_set_stream_flip, /* MUSE_CAMERA_API_ATTR_SET_STREAM_FLIP, */
	camera_dispatcher_attr_get_stream_flip, /* MUSE_CAMERA_API_ATTR_GET_STREAM_FLIP, */
	camera_dispatcher_attr_set_hdr_mode, /* MUSE_CAMERA_API_ATTR_SET_HDR_MODE, */
	camera_dispatcher_attr_get_hdr_mode, /* MUSE_CAMERA_API_ATTR_GET_HDR_MODE, */
	camera_dispatcher_attr_is_supported_hdr_capture, /* MUSE_CAMERA_API_ATTR_IS_SUPPORTED_HDR_CAPTURE, */
	camera_dispatcher_attr_set_hdr_capture_progress_cb, /* MUSE_CAMERA_API_ATTR_SET_HDR_CAPTURE_PROGRESS_CB, */
	camera_dispatcher_attr_unset_hdr_capture_progress_cb, /* MUSE_CAMERA_API_ATTR_UNSET_HDR_CAPTURE_PROGRESS_CB, */
	camera_dispatcher_attr_enable_anti_shake, /* MUSE_CAMERA_API_ATTR_ENABLE_ANTI_SHAKE, */
	camera_dispatcher_attr_is_enabled_anti_shake, /* MUSE_CAMERA_API_ATTR_IS_ENABLED_ANTI_SHAKE, */
	camera_dispatcher_attr_is_supported_anti_shake, /* MUSE_CAMERA_API_ATTR_IS_SUPPORTED_ANTI_SHAKE, */
	camera_dispatcher_attr_enable_video_stabilization, /* MUSE_CAMERA_API_ATTR_ENABLE_VIDEO_STABILIZATION, */
	camera_dispatcher_attr_is_enabled_video_stabilization, /* MUSE_CAMERA_API_ATTR_IS_ENABLED_VIDEO_STABILIZATION, */
	camera_dispatcher_attr_is_supported_video_stabilization, /* MUSE_CAMERA_API_ATTR_IS_SUPPORTED_VIDEO_STABILIZATION, */
	camera_dispatcher_attr_enable_auto_contrast, /* MUSE_CAMERA_API_ATTR_ENABLE_AUTO_CONTRAST, */
	camera_dispatcher_attr_is_enabled_auto_contrast, /* MUSE_CAMERA_API_ATTR_IS_ENABLED_AUTO_CONTRAST, */
	camera_dispatcher_attr_is_supported_auto_contrast, /* MUSE_CAMERA_API_ATTR_IS_SUPPORTED_AUTO_CONTRAST, */
	camera_dispatcher_attr_disable_shutter_sound, /* MUSE_CAMERA_API_ATTR_DISABLE_SHUTTER_SOUND, */
	camera_dispatcher_return_buffer, /* MUSE_CAMERA_API_RETURN_BUFFER, */
};
