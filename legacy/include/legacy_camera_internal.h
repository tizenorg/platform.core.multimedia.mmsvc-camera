/*
* Copyright (c) 2013 Samsung Electronics Co., Ltd All Rights Reserved
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

#ifndef __TIZEN_MULTIMEDIA_LEGACY_CAMERA_INTERNAL_H__
#define __TIZEN_MULTIMEDIA_LEGACY_CAMERA_INTERNAL_H__
#include <legacy_camera.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @file camera_internal.h
  * @brief This file contains the Camera Product-internal API for framework, related structures and enumerations.
  */

/**
 * @brief Registers a callback function to be invoked when camera needs updated xid.
 * @ingroup CAPI_MEDIA_CAMERA_MUSED_MODULE
 * @remarks This function is valid only for #CAMERA_DISPLAY_TYPE_OVERLAY.
 * @param[in] camera The handle to the camera
 * @param[in] caps The caps information of the server's video element
 *
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #CAMERA_ERROR_INVALID_OPERATION Invalid operation
 * @retval #CAMERA_ERROR_INVALID_STATE Invalid state
 * @pre	The camera state must be #CAMERA_STATE_CREATED by camera_create().
 * @post camera_get_video_caps() will be invoked.
 *
 * @see camera_get_video_caps()
 */
int legacy_camera_get_video_caps(camera_h camera, char **caps);

/**
 * @brief Set pid of client for sound focus API.
 * @ingroup CAPI_MEDIA_CAMERA_MUSED_MODULE
 * @param[in] camera The handle to the camera
 * @param[in] pid The pid of client
 *
 * @return @c 0 on success, otherwise a negative error value
 * @retval #CAMERA_ERROR_NONE Successful
 * @retval #CAMERA_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #CAMERA_ERROR_INVALID_OPERATION Invalid operation
 * @retval #CAMERA_ERROR_INVALID_STATE Invalid state
 * @pre	The camera state must be #CAMERA_STATE_CREATED by camera_create().
 */
int legacy_camera_set_client_pid(camera_h camera, int pid);


#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_MULTIMEDIA_LEGACY_CAMERA_INTERNAL_H__ */
