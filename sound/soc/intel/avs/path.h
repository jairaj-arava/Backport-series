/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright(c) 2021 Intel Corporation. All rights reserved.
 *
 * Authors: Cezary Rojewski <cezary.rojewski@intel.com>
 *          Amadeusz Slawinski <amadeuszx.slawinski@linux.intel.com>
 */

#ifndef __SOUND_SOC_INTEL_AVS_PATH_H
#define __SOUND_SOC_INTEL_AVS_PATH_H

#include "avs.h"
#include "topology.h"

#define AVS_COND_TYPE_NONE	0
#define AVS_COND_TYPE_AECREF	1

struct avs_path {
	struct kobject kobj;
	u32 dma_id;
	struct list_head ppl_list;
	u32 state;

	/* condpath navigation for standard paths */
	struct list_head source_list;
	struct list_head sink_list;

	/* conditional path fields */
	struct avs_path *source;
	struct avs_path *sink;
	struct list_head source_node;
	struct list_head sink_node;

	struct avs_tplg_path *template;
	struct avs_dev *owner;
	/* device path management */
	struct list_head node;
};

struct avs_path_pipeline {
	struct kobject kobj;
	u8 instance_id;
	struct list_head mod_list;
	struct list_head binding_list;

	struct avs_tplg_pipeline *template;
	struct avs_path *owner;
	/* path pipelines management */
	struct list_head node;
};

struct avs_path_module {
	struct kobject kobj;
	u16 module_id;
	u16 instance_id;
	union avs_gtw_attributes gtw_attrs;

	struct avs_tplg_module *template;
	struct avs_path_pipeline *owner;
	/* pipeline modules management */
	struct list_head node;
};

struct avs_path_binding {
	struct avs_path_module *source;
	u8 source_pin;
	struct avs_path_module *sink;
	u8 sink_pin;

	struct avs_tplg_binding *template;
	struct avs_path_pipeline *owner;
	/* pipeline bindings management */
	struct list_head node;
};

struct avs_path *avs_path_create(struct avs_dev *adev, u32 dma_id,
				 struct avs_tplg_path_template *template,
				 struct snd_pcm_hw_params *fe_params,
				 struct snd_pcm_hw_params *be_params);
void avs_path_free(struct avs_path *path);
int avs_path_bind(struct avs_path *path);
int avs_path_unbind(struct avs_path *path);
int avs_path_reset(struct avs_path *path);
int avs_path_pause(struct avs_path *path);
int avs_path_run(struct avs_path *path, int trigger);

#endif
