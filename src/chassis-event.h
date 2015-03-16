/* $%BEGINLICENSE%$
 Copyright (c) 2009, 2012, Oracle and/or its affiliates. All rights reserved.

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License as
 published by the Free Software Foundation; version 2 of the
 License.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 02110-1301  USA

 $%ENDLICENSE%$ */
 

#ifndef _CHASSIS_EVENT_H_
#define _CHASSIS_EVENT_H_

#include <glib.h>    /* GPtrArray */

#include "chassis-exports.h"
#include "chassis-mainloop.h"

/**
 * event operations
 *
 * event-ops are sent through the async-queues
 */

typedef struct {
	enum {
		CHASSIS_EVENT_OP_UNSET,
		CHASSIS_EVENT_OP_ADD
	} type;

	struct event *ev;

	struct timeval _tv_storage;
	struct timeval *tv; /* points to ._tv_storage or to NULL */
} chassis_event_op_t;

CHASSIS_API chassis_event_op_t *chassis_event_op_new();
CHASSIS_API void chassis_event_op_free(chassis_event_op_t *e);
CHASSIS_API void chassis_event_op_set_timeout(chassis_event_op_t *op, struct timeval *tv); 
CHASSIS_API void chassis_event_add(chassis *chas, struct event *ev);
CHASSIS_API void chassis_event_add_with_timeout(chassis *chas, struct event *ev, struct timeval *tv);
CHASSIS_API void chassis_event_add_local(chassis *chas, struct event *ev);
CHASSIS_API void chassis_event_add_local_with_timeout(chassis *chas, struct event *ev, struct timeval *tv);

/**
 * a event-thread
 */
typedef struct {
	chassis *chas;

	int notify_fd;
	struct event notify_fd_event;

	struct event_base *event_base;
} chassis_event_t;

CHASSIS_API chassis_event_t *chassis_event_new();
CHASSIS_API void chassis_event_free(chassis_event_t *e);
CHASSIS_API void chassis_event_handle(int event_fd, short events, void *user_data);
CHASSIS_API void chassis_event_set_event_base(chassis_event_t *e, struct event_base *event_base);
CHASSIS_API void *chassis_event_loop(chassis_event_t *);

CHASSIS_API int chassis_event_init(chassis_event_t *loop, chassis *chas);

#endif
