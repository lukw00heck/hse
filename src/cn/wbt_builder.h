/* SPDX-License-Identifier: Apache-2.0 */
/*
 * Copyright (C) 2015-2020 Micron Technology, Inc.  All rights reserved.
 */

#ifndef HSE_KVS_CN_WBT_BUILDER_H
#define HSE_KVS_CN_WBT_BUILDER_H

#include <hse_util/hse_err.h>
#include <hse_util/inttypes.h>

struct wbb;
struct wbt_hdr_omf;

/* MTF_MOCK_DECL(wbt_builder) */

/**
 * wbb_create() - create a wbtree builder
 * @wbb_out: (output) builder handle
 * @max_pgc: (in) max allowable size of wbtree in pages
 * @wbt_pgc: (in/out) actual size (in pages) of wbtree creation
 */
/* MTF_MOCK */
merr_t
wbb_create(struct wbb **wbb_out, uint max_pgc, uint *wbt_pgc);

/* MTF_MOCK */
void
wbb_reset(struct wbb *wbb, uint *wbt_pgc);

/**
 * wbb_destroy() - destroy a wbtree builder
 */
/* MTF_MOCK */
void
wbb_destroy(struct wbb *wbb);

uint
wbb_entries(struct wbb *wbb);

/**
 * wbb_add_entry() - add an entry to a wbtree
 * @wbb: builder handle
 * @kobj: key to be added
 * @key_kmd, @key_kmd_len: encoded key metadata
 * @max_pgc: (in) max allowable size of wbtree in pages
 * @wbt_pgc: (in/out) actual size (in pages) of wbtree creation
 * @added: (output) this value is set to true if the key was added
 *
 * Return:
 *  (rc == 0 && added == true)  ==> success
 *  (rc == 0 && added == false) ==> not enough space for new entry
 *  (rc != 0)                   ==> error
 */
/* MTF_MOCK */
merr_t
wbb_add_entry(
    struct wbb *          wbb,
    const struct key_obj *kobj,
    uint                  nvals,
    const void *          key_kmd,
    uint                  key_kmd_len,
    uint                  max_pgc,
    uint *                wbt_pgc,
    bool *                added);

#define WBB_FREEZE_IOV_MAX 33

void
wbb_hdr_init(struct wbb *wbb, struct wbt_hdr_omf *hdr);

/**
 * wbb_freeze() - finalize a wbtree
 */
/* MTF_MOCK */
merr_t
wbb_freeze(
    struct wbb *        wbb,
    struct wbt_hdr_omf *hdr,
    uint                max_pgc,
    uint *              wbt_pgc,
    struct iovec *      iov,
    uint                iov_max,
    uint *              iov_cnt);

/**
 * wbb_freeze() - get min/max keys from a finalized wbtree
 */
/* MTF_MOCK */
void
wbb_min_max_keys(struct wbb *wbb, struct key_obj **first_kobj, struct key_obj **last_kobj);

/**
 * wbb_page_cnt() - Get total number of pages consumed by wbtree and the
 *                  associated kmd region.
 * @wbb: wbtree builder
 */
/* MTF_MOCK */
uint
wbb_page_cnt_get(struct wbb *wbb);

#if defined(HSE_UNIT_TEST_MODE) && HSE_UNIT_TEST_MODE == 1
#include "wbt_builder_ut.h"
#endif /* HSE_UNIT_TEST_MODE */

#endif
