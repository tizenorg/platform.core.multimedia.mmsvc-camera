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
#include <limits.h>
#include <errno.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <glib.h>
#include "mmsvc_core.h"
#include "mmsvc_core_workqueue.h"
#include "mused_camera.h"
#include "mm_types.h"
#include "mm_debug.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "MMSVC_CAMERA_IPC"

bool mmsvc_camera_ipc_make_tbm(mmsvc_camera_transport_info_s *transport_info)
{
	int drm_fd = -1;
	tbm_bufmgr bufmgr = transport_info->bufmgr;

	LOGD("Enter!");

	if(bufmgr == NULL) {
		LOGE("tbm_bufmgr is NULL!");
		return FALSE;
	}

	transport_info->bo = tbm_bo_alloc(bufmgr, transport_info->data_size, TBM_BO_DEFAULT);

	if(transport_info->bo == NULL) {
		LOGE("tbm_bo_alloc Error!");
		tbm_bufmgr_deinit(bufmgr);
		return FALSE;
	}

	transport_info->bo_handle = tbm_bo_map(transport_info->bo, TBM_DEVICE_CPU, TBM_OPTION_WRITE);

	if(transport_info->bo_handle.ptr == NULL) {
		tbm_bo_unref(transport_info->bo);
		tbm_bufmgr_deinit(bufmgr);
		LOGE("tbm_bo_map Error!");
		return FALSE;
	}

	return TRUE;
}

int mmsvc_camera_ipc_import_tbm(mmsvc_camera_transport_info_s *transport_info)
{
	int drm_fd = -1;

	LOGE("mmsvc_camera_ipc_import_tbm enter!!");

	transport_info->bufmgr = tbm_bufmgr_init(drm_fd);
	if (transport_info->bufmgr == NULL) {
		LOGE("tbm_bufmgr_init error!!");
		goto INIT_FAIL;
	}

	transport_info->bo = tbm_bo_import(transport_info->bufmgr, transport_info->tbm_key);
	if (transport_info->bo == NULL) {
		goto IMPORT_FAIL;
	}

	transport_info->bo_handle = tbm_bo_map(transport_info->bo, TBM_DEVICE_CPU, TBM_OPTION_READ);

	LOGE("tbm_bo_map passed!!!!!!!bo_handle.ptr : 0x%x", transport_info->bo_handle.ptr);

	return TRUE;

IMPORT_FAIL:
	tbm_bufmgr_deinit(transport_info->bufmgr);
INIT_FAIL:
	return FALSE;
}

int mmsvc_camera_ipc_export_tbm(mmsvc_camera_transport_info_s transport_info)
{
	LOGD("mmsvc_camera_ipc_export_tbm_bo!");
	return tbm_bo_export(transport_info.bo);
}

void mmsvc_camera_deinit_tbm(mmsvc_camera_transport_info_s transport_info)
{
	if (transport_info.bo) {
		tbm_bo_unmap(transport_info.bo);
		LOGD("tbm_bo_unref!!!");
		tbm_bo_unref(transport_info.bo);
	}

	if (transport_info.bufmgr) {
		tbm_bufmgr_deinit(transport_info.bufmgr);
	}

	return;
}
