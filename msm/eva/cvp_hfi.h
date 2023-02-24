/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2018-2021, The Linux Foundation. All rights reserved.
 */

#ifndef __H_CVP_HFI_H__
#define __H_CVP_HFI_H__

#include "cvp_hfi_helper.h"
#include "cvp_hfi_api.h"
#include "cvp_comm_def.h"

#define HFI_CMD_SESSION_CVP_START	\
	(HFI_DOMAIN_BASE_CVP + HFI_ARCH_COMMON_OFFSET +	\
	HFI_CMD_START_OFFSET + 0x1000)

#define  HFI_CMD_SESSION_CVP_SET_BUFFERS\
	(HFI_CMD_SESSION_CVP_START + 0x001)
#define  HFI_CMD_SESSION_CVP_RELEASE_BUFFERS\
	(HFI_CMD_SESSION_CVP_START + 0x002)

#define  HFI_CMD_SESSION_CVP_DS\
	(HFI_CMD_SESSION_CVP_START + 0x003)
#define  HFI_CMD_SESSION_CVP_HCD_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x004)
#define  HFI_CMD_SESSION_CVP_HCD_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x005)
#define  HFI_CMD_SESSION_CVP_CV_HOG_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x006)
#define  HFI_CMD_SESSION_CVP_CV_HOG_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x007)
#define  HFI_CMD_SESSION_CVP_SVM\
	(HFI_CMD_SESSION_CVP_START + 0x008)
#define  HFI_CMD_SESSION_CVP_NCC_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x009)
#define  HFI_CMD_SESSION_CVP_NCC_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x00A)
#define  HFI_CMD_SESSION_CVP_DFS_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x00B)
#define  HFI_CMD_SESSION_CVP_DFS_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x00C)
#define  HFI_CMD_SESSION_CVP_FTEXT\
	(HFI_CMD_SESSION_CVP_START + 0x00F)

/* ==========CHAINED OPERATIONS===================*/
#define  HFI_CMD_SESSION_CVP_CV_HOG_SVM_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x010)
#define  HFI_CMD_SESSION_CVP_CV_HOG_SVM_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x011)
#define  HFI_CMD_SESSION_CVP_CV_HOG_SVM_HCD_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x012)
#define  HFI_CMD_SESSION_CVP_CV_HOG_SVM_HCD_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x013)
#define  HFI_CMD_SESSION_CVP_OPTICAL_FLOW\
	(HFI_CMD_SESSION_CVP_START + 0x014)

/* ===========USECASE OPERATIONS===============*/
#define  HFI_CMD_SESSION_CVP_DC_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x030)
#define  HFI_CMD_SESSION_CVP_DC_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x031)
#define  HFI_CMD_SESSION_CVP_DCM_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x034)
#define  HFI_CMD_SESSION_CVP_DCM_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x035)

#define  HFI_CMD_SESSION_CVP_DME_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x039)
#define  HFI_CMD_SESSION_CVP_DME_BASIC_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x03B)
#define  HFI_CMD_SESSION_CVP_DME_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x03A)

#define  HFI_CMD_SESSION_EVA_DME_ONLY_CONFIG\
    (HFI_CMD_SESSION_CVP_START + 0x040)
#define  HFI_CMD_SESSION_EVA_DME_ONLY_FRAME\
    (HFI_CMD_SESSION_CVP_START + 0x041)

#define  HFI_CMD_SESSION_CVP_CV_TME_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x047)
#define  HFI_CMD_SESSION_CVP_CV_TME_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x048)
#define  HFI_CMD_SESSION_CVP_CV_OD_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x049)
#define  HFI_CMD_SESSION_CVP_CV_OD_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x04A)
#define  HFI_CMD_SESSION_CVP_CV_ODT_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x04B)
#define  HFI_CMD_SESSION_CVP_CV_ODT_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x04C)

#define  HFI_CMD_SESSION_CVP_SET_PERSIST_BUFFERS\
	(HFI_CMD_SESSION_CVP_START + 0x04D)
#define HFI_CMD_SESSION_CVP_PYS_HCD_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x050)
#define HFI_CMD_SESSION_CVP_PYS_HCD_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x051)
#define HFI_CMD_SESSION_CVP_SET_MODEL_BUFFERS\
	(HFI_CMD_SESSION_CVP_START + 0x052)
#define HFI_CMD_SESSION_CVP_FD_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x053)
#define HFI_CMD_SESSION_CVP_FD_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x054)
#define HFI_CMD_SESSION_CVP_RELEASE_PERSIST_BUFFERS\
	(HFI_CMD_SESSION_CVP_START + 0x055)
#define  HFI_CMD_SESSION_CVP_RELEASE_MODEL_BUFFERS\
	(HFI_CMD_SESSION_CVP_START + 0x056)
#define  HFI_CMD_SESSION_CVP_SGM_DFS_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x057)
#define  HFI_CMD_SESSION_CVP_SGM_DFS_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x058)
#define  HFI_CMD_SESSION_CVP_SGM_OF_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x059)
#define  HFI_CMD_SESSION_CVP_SGM_OF_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x05A)
#define  HFI_CMD_SESSION_CVP_GCE_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x05B)
#define  HFI_CMD_SESSION_CVP_GCE_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x05C)
#define  HFI_CMD_SESSION_CVP_WARP_NCC_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x05D)
#define  HFI_CMD_SESSION_CVP_WARP_NCC_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x05E)
#define  HFI_CMD_SESSION_CVP_DMM_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x05F)
#define  HFI_CMD_SESSION_CVP_DMM_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x060)
#define HFI_CMD_SESSION_CVP_FLUSH\
	(HFI_CMD_SESSION_CVP_START + 0x061)
#define  HFI_CMD_SESSION_CVP_WARP_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x062)
#define  HFI_CMD_SESSION_CVP_WARP_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x063)
#define  HFI_CMD_SESSION_CVP_DMM_PARAMS\
	(HFI_CMD_SESSION_CVP_START + 0x064)
#define  HFI_CMD_SESSION_CVP_WARP_DS_PARAMS\
	(HFI_CMD_SESSION_CVP_START + 0x065)
#define  HFI_CMD_SESSION_CVP_XRA_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x066)
#define  HFI_CMD_SESSION_CVP_XRA_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x067)
#define  HFI_CMD_SESSION_CVP_XRA_BLOB_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x069)
#define  HFI_CMD_SESSION_CVP_XRA_BLOB_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x06A)
#define  HFI_CMD_SESSION_CVP_XRA_PATCH_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x06B)
#define  HFI_CMD_SESSION_CVP_XRA_PATCH_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x06C)
#define  HFI_CMD_SESSION_CVP_XRA_MATCH_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x06D)
#define  HFI_CMD_SESSION_CVP_XRA_MATCH_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x06E)


#define HFI_CMD_SESSION_CVP_SET_SNAPSHOT_BUFFERS\
	(HFI_CMD_SESSION_CVP_START + 0x070)
#define HFI_CMD_SESSION_CVP_RELEASE_SNAPSHOT_BUFFERS\
	(HFI_CMD_SESSION_CVP_START + 0x071)
#define HFI_CMD_SESSION_CVP_SNAPSHOT_WRITE_DONE\
	(HFI_CMD_SESSION_CVP_START + 0x072)
#define HFI_CMD_SESSION_CVP_SET_SNAPSHOT_MODE\
	(HFI_CMD_SESSION_CVP_START + 0x073)
#define  HFI_CMD_SESSION_EVA_ITOF_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x078)
#define  HFI_CMD_SESSION_EVA_ITOF_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x079)
#define  HFI_CMD_SESSION_EVA_DLFD_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x07C)
#define  HFI_CMD_SESSION_EVA_DLFD_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x07D)
#define  HFI_CMD_SESSION_CVP_RGE_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x07E)
#define  HFI_CMD_SESSION_CVP_RGE_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x07F)
#define  HFI_CMD_SESSION_EVA_DLFL_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x080)
#define  HFI_CMD_SESSION_EVA_DLFL_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x081)
#define  HFI_CMD_SESSION_CVP_SYNX\
	(HFI_CMD_SESSION_CVP_START + 0x086)
#define  HFI_CMD_SESSION_CVP_ICA_FRAME\
	(HFI_CMD_SESSION_CVP_START + 0x100)
#define  HFI_CMD_SESSION_CVP_ICA_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x101)
#define  HFI_CMD_SESSION_CVP_DS_CONFIG\
	(HFI_CMD_SESSION_CVP_START + 0x02F)


#define HFI_MSG_SESSION_CVP_START	\
	(HFI_DOMAIN_BASE_CVP + HFI_ARCH_COMMON_OFFSET +	\
	HFI_MSG_START_OFFSET + 0x1000)

#define HFI_MSG_SESSION_CVP_SET_BUFFERS\
	(HFI_MSG_SESSION_CVP_START + 0x001)
#define HFI_MSG_SESSION_CVP_RELEASE_BUFFERS \
	(HFI_MSG_SESSION_CVP_START + 0x002)
#define HFI_MSG_SESSION_CVP_DS\
	(HFI_MSG_SESSION_CVP_START + 0x003)
#define HFI_MSG_SESSION_CVP_HCD\
	(HFI_MSG_SESSION_CVP_START + 0x004)
#define HFI_MSG_SESSION_CVP_CV_HOG\
	(HFI_MSG_SESSION_CVP_START + 0x005)
#define HFI_MSG_SESSION_CVP_SVM\
	(HFI_MSG_SESSION_CVP_START + 0x006)
#define HFI_MSG_SESSION_CVP_NCC\
	(HFI_MSG_SESSION_CVP_START + 0x007)
#define HFI_MSG_SESSION_CVP_DFS\
	(HFI_MSG_SESSION_CVP_START + 0x008)
#define HFI_MSG_SESSION_CVP_TME\
	(HFI_MSG_SESSION_CVP_START + 0x009)
#define HFI_MSG_SESSION_CVP_FTEXT\
	(HFI_MSG_SESSION_CVP_START + 0x00A)

#define HFI_MSG_SESSION_CVP_ICA\
	(HFI_MSG_SESSION_CVP_START + 0x014)

#define HFI_MSG_SESSION_CVP_DME\
	(HFI_MSG_SESSION_CVP_START + 0x023)
#define  HFI_MSG_SESSION_EVA_DME_ONLY\
    (HFI_MSG_SESSION_CVP_START + 0x050)
#define HFI_MSG_SESSION_CVP_OPERATION_CONFIG (HFI_MSG_SESSION_CVP_START + 0x030)

#define HFI_MSG_SESSION_CVP_SET_PERSIST_BUFFERS\
	(HFI_MSG_SESSION_CVP_START + 0x034)
#define HFI_MSG_SESSION_CVP_SET_MODEL_BUFFERS\
	(HFI_MSG_SESSION_CVP_START + 0x036)
#define HFI_MSG_SESSION_CVP_FD\
	(HFI_MSG_SESSION_CVP_START + 0x037)
#define HFI_MSG_SESSION_CVP_RELEASE_PERSIST_BUFFERS\
	(HFI_MSG_SESSION_CVP_START + 0x038)
#define  HFI_MSG_SESSION_CVP_RELEASE_MODEL_BUFFERS\
	(HFI_MSG_SESSION_CVP_START + 0x039)
#define  HFI_MSG_SESSION_CVP_SGM_OF\
	(HFI_MSG_SESSION_CVP_START + 0x03A)
#define  HFI_MSG_SESSION_CVP_GCE\
	(HFI_MSG_SESSION_CVP_START + 0x03B)
#define  HFI_MSG_SESSION_CVP_WARP_NCC\
	(HFI_MSG_SESSION_CVP_START + 0x03C)
#define  HFI_MSG_SESSION_CVP_DMM\
	(HFI_MSG_SESSION_CVP_START + 0x03D)
#define  HFI_MSG_SESSION_CVP_SGM_DFS\
	(HFI_MSG_SESSION_CVP_START + 0x03E)
#define  HFI_MSG_SESSION_CVP_WARP\
	(HFI_MSG_SESSION_CVP_START + 0x03F)
#define  HFI_MSG_SESSION_CVP_DMM_PARAMS\
	(HFI_MSG_SESSION_CVP_START + 0x040)
#define  HFI_MSG_SESSION_CVP_WARP_DS_PARAMS\
	(HFI_MSG_SESSION_CVP_START + 0x041)
#define  HFI_MSG_SESSION_CVP_SET_SNAPSHOT_BUFFERS\
	(HFI_MSG_SESSION_CVP_START + 0x042)
#define  HFI_MSG_SESSION_CVP_RELEASE_SNAPSHOT_BUFFERS\
	(HFI_MSG_SESSION_CVP_START + 0x043)
#define  HFI_MSG_EVENT_NOTIFY_SNAPSHOT_READY\
	(HFI_MSG_SESSION_CVP_START + 0x044)

#define HFI_MSG_SESSION_CVP_FLUSH\
	(HFI_MSG_SESSION_CVP_START + 0x004A)

#define CVP_IFACEQ_MAX_PKT_SIZE       1024
#define CVP_IFACEQ_MED_PKT_SIZE       768
#define CVP_IFACEQ_MIN_PKT_SIZE       8
#define CVP_IFACEQ_VAR_SMALL_PKT_SIZE 100
#define CVP_IFACEQ_VAR_LARGE_PKT_SIZE 512
#define CVP_IFACEQ_VAR_HUGE_PKT_SIZE  (1024*12)

/* HFI packet info needed for sanity check */
#define HFI_DFS_CONFIG_CMD_SIZE	38
#define HFI_DFS_FRAME_CMD_SIZE	16

#define HFI_DMM_CONFIG_CMD_SIZE	194
#define HFI_DMM_BASIC_CONFIG_CMD_SIZE	51
#define HFI_DMM_FRAME_CMD_SIZE	28

#define HFI_PERSIST_CMD_SIZE	11

#define HFI_DS_CONFIG_CMD_SIZE 11
#define HFI_DS_CMD_SIZE	50

#define HFI_OF_CONFIG_CMD_SIZE 34
#define HFI_OF_FRAME_CMD_SIZE 24

#define HFI_ODT_CONFIG_CMD_SIZE 23
#define HFI_ODT_FRAME_CMD_SIZE 33

#define HFI_OD_CONFIG_CMD_SIZE 24
#define HFI_OD_FRAME_CMD_SIZE 12

#define HFI_NCC_CONFIG_CMD_SIZE 47
#define HFI_NCC_FRAME_CMD_SIZE 22

#define HFI_ICA_CONFIG_CMD_SIZE 127
#define HFI_ICA_FRAME_CMD_SIZE 14

#define HFI_HCD_CONFIG_CMD_SIZE 46
#define HFI_HCD_FRAME_CMD_SIZE 18

#define HFI_DCM_CONFIG_CMD_SIZE 20
#define HFI_DCM_FRAME_CMD_SIZE 19

#define HFI_PYS_HCD_CONFIG_CMD_SIZE 461
#define HFI_PYS_HCD_FRAME_CMD_SIZE 66

#define HFI_FD_CONFIG_CMD_SIZE 28
#define HFI_FD_FRAME_CMD_SIZE  10


struct cvp_hfi_cmd_session_flush_packet {
	u32 size;
	u32 packet_type;
	u32 session_id;
	u32 flush_type;
};

struct cvp_hfi_cmd_session_get_property_packet {
	u32 size;
	u32 packet_type;
	u32 session_id;
	u32 num_properties;
	u32 rg_property_data[1];
};

struct cvp_hfi_msg_sys_session_abort_done_packet {
	u32 size;
	u32 packet_type;
	u32 session_id;
	u32 error_type;
};

struct cvp_hfi_msg_sys_property_info_packet {
	u32 size;
	u32 packet_type;
	u32 num_properties;
	u32 rg_property_data[128];
};

enum session_flags {
	SESSION_PAUSE = BIT(1),
};

struct cvp_hal_session {
	struct list_head list;
	void *session_id;
	u32 flags;
	void *device;
};

enum buf_map_type {
	MAP_PERSIST = 1,
	UNMAP_PERSIST = 2,
	MAP_FRAME = 3,
	MAP_INVALID,
};

static inline enum buf_map_type cvp_find_map_type(int pkt_type)
{
	if (pkt_type == HFI_CMD_SESSION_CVP_SET_PERSIST_BUFFERS ||
			pkt_type == HFI_CMD_SESSION_CVP_SET_MODEL_BUFFERS ||
			pkt_type == HFI_CMD_SESSION_CVP_DMM_PARAMS ||
			pkt_type == HFI_CMD_SESSION_CVP_SET_SNAPSHOT_BUFFERS ||
			pkt_type == HFI_CMD_SESSION_CVP_WARP_DS_PARAMS ||
			pkt_type == HFI_CMD_SESSION_EVA_DLFL_CONFIG)
		return MAP_PERSIST;
	else if (pkt_type == HFI_CMD_SESSION_CVP_RELEASE_PERSIST_BUFFERS ||
			pkt_type ==
				HFI_CMD_SESSION_CVP_RELEASE_SNAPSHOT_BUFFERS)
		return UNMAP_PERSIST;
	else
		return MAP_FRAME;
}

static inline bool is_params_pkt(int pkt_type)
{
	if (pkt_type == HFI_CMD_SESSION_CVP_DMM_PARAMS ||
		pkt_type == HFI_CMD_SESSION_CVP_WARP_DS_PARAMS)
		return true;

	return false;
}

#endif
