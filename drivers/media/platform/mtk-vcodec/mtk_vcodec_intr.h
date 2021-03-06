/* SPDX-License-Identifier: GPL-2.0 */
/*
* Copyright (c) 2016 MediaTek Inc.
* Author: Tiffany Lin <tiffany.lin@mediatek.com>
*/

#ifndef _MTK_VCODEC_INTR_H_
#define _MTK_VCODEC_INTR_H_

#define MTK_INST_IRQ_RECEIVED		0x1

struct mtk_vcodec_ctx;

/* timeout is ms */
int mtk_vcodec_wait_for_done_ctx(struct mtk_vcodec_ctx *data, int command,
				unsigned int timeout_ms);
int mtk_vcodec_wait_for_comp_done_ctx(struct mtk_vcodec_ctx  *ctx,
				int command, unsigned int timeout_ms, unsigned int hw_id);

#endif /* _MTK_VCODEC_INTR_H_ */
