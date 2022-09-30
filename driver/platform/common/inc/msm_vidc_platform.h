/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2020-2021,, The Linux Foundation. All rights reserved.
 */

#ifndef _MSM_VIDC_PLATFORM_H_
#define _MSM_VIDC_PLATFORM_H_

#include <linux/platform_device.h>
#include <media/v4l2-ctrls.h>

#include "msm_vidc_internal.h"
#include "msm_vidc_core.h"

#define DDR_TYPE_LPDDR4 0x6
#define DDR_TYPE_LPDDR4X 0x7
#define DDR_TYPE_LPDDR5 0x8
#define DDR_TYPE_LPDDR5X 0x9

#define UBWC_CONFIG(mc, ml, hbb, bs1, bs2, bs3, bsp) \
{	                                                 \
	.max_channels = mc,                              \
	.mal_length = ml,                                \
	.highest_bank_bit = hbb,                         \
	.bank_swzl_level = bs1,                          \
	.bank_swz2_level = bs2,                          \
	.bank_swz3_level = bs3,                          \
	.bank_spreading = bsp,                           \
}

#define EFUSE_ENTRY(sa, s, m, sh, p) \
{	                                 \
	.start_address = sa,             \
	.size = s,                       \
	.mask = m,                       \
	.shift = sh,                     \
	.purpose = p                     \
}

extern u32 vpe_csc_custom_matrix_coeff[MAX_MATRIX_COEFFS];
extern u32 vpe_csc_custom_bias_coeff[MAX_BIAS_COEFFS];
extern u32 vpe_csc_custom_limit_coeff[MAX_LIMIT_COEFFS];

struct codec_info {
	u32 v4l2_codec;
	enum msm_vidc_codec_type vidc_codec;
	const char *pixfmt_name;
};

struct color_format_info {
	u32 v4l2_color_format;
	enum msm_vidc_colorformat_type vidc_color_format;
	const char *pixfmt_name;
};

struct color_primaries_info {
	u32 v4l2_color_primaries;
	enum msm_vidc_color_primaries vidc_color_primaries;
};

struct transfer_char_info {
	u32 v4l2_transfer_char;
	enum msm_vidc_transfer_characteristics vidc_transfer_char;
};

struct matrix_coeff_info {
	u32 v4l2_matrix_coeff;
	enum msm_vidc_matrix_coefficients vidc_matrix_coeff;
};

struct msm_platform_core_capability {
	enum msm_vidc_core_capability_type type;
	u32 value;
};

struct msm_platform_inst_capability {
	enum msm_vidc_inst_capability_type cap_id;
	enum msm_vidc_domain_type domain;
	enum msm_vidc_codec_type codec;
	s32 min;
	s32 max;
	u32 step_or_mask;
	s32 value;
	u32 v4l2_id;
	u32 hfi_id;
	enum msm_vidc_inst_capability_flags flags;
};

struct msm_platform_inst_cap_dependency {
	enum msm_vidc_inst_capability_type cap_id;
	enum msm_vidc_domain_type domain;
	enum msm_vidc_codec_type codec;
	enum msm_vidc_inst_capability_type parents[MAX_CAP_PARENTS];
	enum msm_vidc_inst_capability_type children[MAX_CAP_CHILDREN];
	int (*adjust)(void *inst,
		struct v4l2_ctrl *ctrl);
	int (*set)(void *inst,
		enum msm_vidc_inst_capability_type cap_id);
};

struct msm_vidc_csc_coeff {
	u32 *vpe_csc_custom_matrix_coeff;
	u32 *vpe_csc_custom_bias_coeff;
	u32 *vpe_csc_custom_limit_coeff;
};

struct msm_vidc_efuse_data {
	u32 start_address;
	u32 size;
	u32 mask;
	u32 shift;
	enum efuse_purpose purpose;
};

struct msm_vidc_ubwc_config_data {
	u32 max_channels;
	u32 mal_length;
	u32 highest_bank_bit;
	u32 bank_swzl_level;
	u32 bank_swz2_level;
	u32 bank_swz3_level;
	u32 bank_spreading;
};

struct msm_vidc_format_capability {
	struct codec_info *codec_info;
	u32 codec_info_size;
	struct color_format_info *color_format_info;
	u32 color_format_info_size;
	struct color_primaries_info *color_prim_info;
	u32 color_prim_info_size;
	struct transfer_char_info *transfer_char_info;
	u32 transfer_char_info_size;
	struct matrix_coeff_info *matrix_coeff_info;
	u32 matrix_coeff_info_size;
};

struct msm_vidc_platform_data {
	struct msm_platform_core_capability *core_data;
	u32 core_data_size;
	struct msm_platform_inst_capability *inst_cap_data;
	u32 inst_cap_data_size;
	struct msm_platform_inst_cap_dependency *inst_cap_dependency_data;
	u32 inst_cap_dependency_data_size;
	struct msm_vidc_csc_coeff csc_data;
	struct msm_vidc_ubwc_config_data *ubwc_config;
	struct msm_vidc_efuse_data *efuse_data;
	unsigned int efuse_data_size;
	unsigned int sku_version;
	struct msm_vidc_format_capability *format_data;
};

struct msm_vidc_platform {
	void *core;
	struct msm_vidc_platform_data data;
};

int msm_vidc_init_platform(struct platform_device *pdev);
int msm_vidc_deinit_platform(struct platform_device *pdev);
int msm_vidc_read_efuse(struct msm_vidc_core *core);
void msm_vidc_sort_table(struct msm_vidc_core *core);

#endif // _MSM_VIDC_PLATFORM_H_
