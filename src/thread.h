/*
 *  Beansdb - A high available distributed key-value storage system:
 *
 *      http://beansdb.googlecode.com
 *
 *  Copyright 2010 Douban Inc.  All rights reserved.
 *
 *  Use and distribution licensed under the BSD license.  See
 *  the LICENSE file for full text.
 *
 *  Authors:
 *      Hongwei Wang <glinus@gmail.com>
 *
 */

#ifndef __THREAD_H__
#define __THREAD_H__

#include "beansdb.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

#ifdef HAVE_MALLOC_H
#include <malloc.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include <pthread.h>

typedef struct EventLoop {
//    int   maxfd;
    conn* conns[AE_SETSIZE];
    int   fired[AE_SETSIZE];
    int   nready;
    void *apidata;
} EventLoop;

conn *mt_conn_from_freelist();
bool mt_conn_add_to_freelist(conn *);
item *mt_item_from_freelist();
int mt_item_add_to_freelist(item *);

/* Include the best multiplexing layer supported by this system.
 * The following should be ordered by performances, descending. */
#ifdef HAVE_EPOLL
#include "ae_epoll.c"
#else
    #ifdef HAVE_KQUEUE
    #include "ae_kqueue.c"
    #else
    #include "ae_select.c"
    #endif
#endif

void thread_init(int);
int add_event(int, int, conn *);
int update_event(int, int, conn *);
int delete_event(int);

void loop_run(int);

#endif
