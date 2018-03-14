/*
 * Copyright (c) 2017, 2018 The Linux Foundation. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/**
 * DOC: wlan_hdd_spectral_scan.c
 *
 * WLAN Host Device Driver Spectral Scan Implementation
 */

#include <linux/version.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <net/cfg80211.h>
#include "wlan_hdd_includes.h"
#include "cds_api.h"
#include "ani_global.h"
#include "wlan_cfg80211_spectral.h"
#include "wlan_hdd_spectralscan.h"
#include <wlan_spectral_ucfg_api.h>
#ifdef CNSS_GENL
#include <net/cnss_nl.h>
#endif

/**
 * __wlan_hdd_cfg80211_spectral_scan_start() - start spectral scan
 * @wiphy:    WIPHY structure pointer
 * @wdev:     Wireless device structure pointer
 * @data:     Pointer to the data received
 * @data_len: Length of the data received
 *
 * This function starts spectral scan
 *
 * Return: 0 on success and errno on failure
 */
static int __wlan_hdd_cfg80211_spectral_scan_start(struct wiphy *wiphy,
						struct wireless_dev *wdev,
						const void *data,
						int data_len)
{
	int ret;
	struct hdd_context *hdd_ctx = wiphy_priv(wiphy);

	hdd_enter();

	ret = wlan_hdd_validate_context(hdd_ctx);
	if (ret)
		return ret;

	if (QDF_GLOBAL_FTM_MODE == hdd_get_conparam()) {
		hdd_err("Command not allowed in FTM mode");
		return -EPERM;
	}

	ret = wlan_cfg80211_spectral_scan_config_and_start(wiphy,
					hdd_ctx->hdd_pdev,
					data, data_len);
	hdd_exit();

	return ret;
}

/**
 * __wlan_hdd_cfg80211_spectral_scan_stop() - stop spectral scan
 * @wiphy:    WIPHY structure pointer
 * @wdev:     Wireless device structure pointer
 * @data:     Pointer to the data received
 * @data_len: Length of the data received
 *
 * This function stops spectral scan
 *
 * Return: 0 on success and errno on failure
 */
static int __wlan_hdd_cfg80211_spectral_scan_stop(struct wiphy *wiphy,
						struct wireless_dev *wdev,
						const void *data,
						int data_len)
{
	int ret;
	struct hdd_context *hdd_ctx = wiphy_priv(wiphy);

	hdd_enter();

	ret = wlan_hdd_validate_context(hdd_ctx);
	if (ret)
		return ret;

	if (QDF_GLOBAL_FTM_MODE == hdd_get_conparam()) {
		hdd_err("Command not allowed in FTM mode");
		return -EPERM;
	}

	ret = wlan_cfg80211_spectral_scan_stop(wiphy, hdd_ctx->hdd_pdev,
					data, data_len);
	hdd_exit();

	return ret;
}

/**
 * __wlan_hdd_cfg80211_spectral_scan_get_config() - spectral scan get config
 * @wiphy:    WIPHY structure pointer
 * @wdev:     Wireless device structure pointer
 * @data:     Pointer to the data received
 * @data_len: Length of the data received
 *
 * This function to get the spectral scan configuration
 *
 * Return: 0 on success and errno on failure
 */
static int __wlan_hdd_cfg80211_spectral_scan_get_config(
						struct wiphy *wiphy,
						struct wireless_dev *wdev,
						const void *data,
						int data_len)
{
	int ret;
	struct hdd_context *hdd_ctx = wiphy_priv(wiphy);

	hdd_enter();

	ret = wlan_hdd_validate_context(hdd_ctx);
	if (ret)
		return ret;

	if (QDF_GLOBAL_FTM_MODE == hdd_get_conparam()) {
		hdd_err("Command not allowed in FTM mode");
		return -EPERM;
	}

	ret = wlan_cfg80211_spectral_scan_get_config(wiphy, hdd_ctx->hdd_pdev,
					data, data_len);
	hdd_exit();

	return ret;
}

/**
 * __wlan_hdd_cfg80211_spectral_scan_get_diag_stats() - get diag stats
 * @wiphy:    WIPHY structure pointer
 * @wdev:     Wireless device structure pointer
 * @data:     Pointer to the data received
 * @data_len: Length of the data received
 *
 * This function gets the spectral scan diag stats
 *
 * Return: 0 on success and errno on failure
 */
static int __wlan_hdd_cfg80211_spectral_scan_get_diag_stats(
						struct wiphy *wiphy,
						struct wireless_dev *wdev,
						const void *data,
						int data_len)
{
	int ret;
	struct hdd_context *hdd_ctx = wiphy_priv(wiphy);

	hdd_enter();

	ret = wlan_hdd_validate_context(hdd_ctx);
	if (ret)
		return ret;

	if (QDF_GLOBAL_FTM_MODE == hdd_get_conparam()) {
		hdd_err("Command not allowed in FTM mode");
		return -EPERM;
	}

	ret = wlan_cfg80211_spectral_scan_get_diag_stats(wiphy,
					hdd_ctx->hdd_pdev,
					data, data_len);
	hdd_exit();

	return ret;
}

/**
 * __wlan_hdd_cfg80211_spectral_scan_get_cap_info() - get spectral caps
 * @wiphy:    WIPHY structure pointer
 * @wdev:     Wireless device structure pointer
 * @data:     Pointer to the data received
 * @data_len: Length of the data received
 *
 * This function gets spectral scan configured capabilities
 *
 * Return: 0 on success and errno on failure
 */
static int __wlan_hdd_cfg80211_spectral_scan_get_cap_info(
						struct wiphy *wiphy,
						struct wireless_dev *wdev,
						const void *data,
						int data_len)
{
	int ret;
	struct hdd_context *hdd_ctx = wiphy_priv(wiphy);

	hdd_enter();

	ret = wlan_hdd_validate_context(hdd_ctx);
	if (ret)
		return ret;

	if (QDF_GLOBAL_FTM_MODE == hdd_get_conparam()) {
		hdd_err("Command not allowed in FTM mode");
		return -EPERM;
	}

	ret = wlan_cfg80211_spectral_scan_get_cap(wiphy, hdd_ctx->hdd_pdev,
					data, data_len);
	hdd_exit();

	return ret;
}

/*
 * __wlan_hdd_cfg80211_spectral_scan_get_status() - get spectral scan
 * status
 * @wiphy:    WIPHY structure pointer
 * @wdev:     Wireless device structure pointer
 * @data:     Pointer to the data received
 * @data_len: Length of the data received
 *
 * This function gets current status of spectral scan
 *
 * Return: 0 on success and errno on failure
 */
static int __wlan_hdd_cfg80211_spectral_scan_get_status(
						struct wiphy *wiphy,
						struct wireless_dev *wdev,
						const void *data,
						int data_len)
{
	int ret;
	struct hdd_context *hdd_ctx = wiphy_priv(wiphy);

	hdd_enter();

	ret = wlan_hdd_validate_context(hdd_ctx);
	if (ret)
		return ret;

	if (QDF_GLOBAL_FTM_MODE == hdd_get_conparam()) {
		hdd_err("Command not allowed in FTM mode");
		return -EPERM;
	}

	ret = wlan_cfg80211_spectral_scan_get_status(wiphy, hdd_ctx->hdd_pdev,
					data, data_len);
	hdd_exit();

	return ret;
}

int wlan_hdd_cfg80211_spectral_scan_start(struct wiphy *wiphy,
						struct wireless_dev *wdev,
						const void *data,
						int data_len)
{
	int ret;

	cds_ssr_protect(__func__);
	ret = __wlan_hdd_cfg80211_spectral_scan_start(
				wiphy, wdev, data, data_len);
	cds_ssr_unprotect(__func__);

	return ret;
}

int wlan_hdd_cfg80211_spectral_scan_stop(struct wiphy *wiphy,
						struct wireless_dev *wdev,
						const void *data,
						int data_len)
{
	int ret;

	cds_ssr_protect(__func__);
	ret = __wlan_hdd_cfg80211_spectral_scan_stop(
				wiphy, wdev, data, data_len);

	cds_ssr_unprotect(__func__);

	return ret;
}

int wlan_hdd_cfg80211_spectral_scam_get_config(struct wiphy *wiphy,
						struct wireless_dev *wdev,
						const void *data,
						int data_len)
{
	int ret;

	cds_ssr_protect(__func__);
	ret = __wlan_hdd_cfg80211_spectral_scan_get_config(
				wiphy, wdev, data, data_len);

	cds_ssr_unprotect(__func__);

	return ret;
}

int wlan_hdd_cfg80211_spectral_scan_get_diag_stats(struct wiphy *wiphy,
						struct wireless_dev *wdev,
						const void *data,
						int data_len)
{
	int ret;

	cds_ssr_protect(__func__);
	ret = __wlan_hdd_cfg80211_spectral_scan_get_diag_stats(
				wiphy, wdev, data, data_len);

	cds_ssr_unprotect(__func__);

	return ret;
}

int wlan_hdd_cfg80211_spectral_scan_get_cap_info(struct wiphy *wiphy,
						struct wireless_dev *wdev,
						const void *data,
						int data_len)
{
	int ret;

	cds_ssr_protect(__func__);
	ret = __wlan_hdd_cfg80211_spectral_scan_get_cap_info(
				wiphy, wdev, data, data_len);
	cds_ssr_unprotect(__func__);

	return ret;
}

int wlan_hdd_cfg80211_spectral_scan_get_status(struct wiphy *wiphy,
						struct wireless_dev *wdev,
						const void *data,
						int data_len)
{
	int ret;

	cds_ssr_protect(__func__);
	ret = __wlan_hdd_cfg80211_spectral_scan_get_status(
				wiphy, wdev, data, data_len);

	cds_ssr_unprotect(__func__);

	return ret;
}

#ifdef CNSS_GENL
static void send_spectral_scan_reg_rsp_msg(struct hdd_context *hdd_ctx)
{
	struct sk_buff *skb;
	struct nlmsghdr *nlh;
	struct spectral_scan_msg *rsp_msg;
	int err;

	skb = alloc_skb(NLMSG_SPACE(sizeof(struct spectral_scan_msg)),
				GFP_KERNEL);
	if (skb == NULL) {
		hdd_err("Skb allocation failed");
		return;
	}

	nlh = (struct nlmsghdr *)skb->data;
	nlh->nlmsg_pid = 0;
	nlh->nlmsg_flags = 0;
	nlh->nlmsg_seq = 0;
	nlh->nlmsg_type = WLAN_NL_MSG_SPECTRAL_SCAN;

	rsp_msg = NLMSG_DATA(nlh);
	rsp_msg->msg_type = SPECTRAL_SCAN_REGISTER_RSP;
	rsp_msg->pid = hdd_ctx->sscan_pid;

	nlh->nlmsg_len = NLMSG_LENGTH(sizeof(struct spectral_scan_msg));
	skb_put(skb, NLMSG_SPACE(sizeof(struct spectral_scan_msg)));

	hdd_info("sending App Reg Response to process pid %d",
			hdd_ctx->sscan_pid);

	err = nl_srv_ucast(skb, hdd_ctx->sscan_pid, MSG_DONTWAIT,
			WLAN_NL_MSG_SPECTRAL_SCAN, CLD80211_MCGRP_OEM_MSGS);

	if (err < 0)
		hdd_err("SPECTRAL: failed to send to spectral scan reg"
			" response");
}

/**
 * __spectral_scan_msg_handler() - API to handle spectral scan
 * command
 * @data: Data received
 * @data_len: length of the data received
 * @ctx: Pointer to stored context
 * @pid: Process ID
 *
 * API to handle spectral scan commands from user space
 *
 * Return: None
 */
static void __spectral_scan_msg_handler(const void *data, int data_len,
					void *ctx, int pid)
{
	struct spectral_scan_msg *ss_msg = NULL;
	struct nlattr *tb[QCA_WLAN_VENDOR_ATTR_MAX + 1];
	struct hdd_context *hdd_ctx;
	int ret;

	hdd_ctx = (struct hdd_context *)cds_get_context(QDF_MODULE_ID_HDD);
	ret = wlan_hdd_validate_context(hdd_ctx);
	if (0 != ret)
		return;

	if (wlan_cfg80211_nla_parse(tb, CLD80211_ATTR_MAX, data,
				    data_len, NULL)) {
		hdd_err("nla parse fails");
		return;
	}

	if (!tb[CLD80211_ATTR_DATA]) {
		hdd_err("attr VENDOR_DATA fails");
		return;
	}
	ss_msg = (struct spectral_scan_msg *)nla_data(tb[CLD80211_ATTR_DATA]);

	if (!ss_msg) {
		hdd_err("data NULL");
		return;
	}

	switch (ss_msg->msg_type) {
	case SPECTRAL_SCAN_REGISTER_REQ:
		hdd_ctx->sscan_pid = ss_msg->pid;
		hdd_debug("spectral scan application registered, pid=%d",
				 hdd_ctx->sscan_pid);
		send_spectral_scan_reg_rsp_msg(hdd_ctx);
		ucfg_spectral_scan_set_ppid(hdd_ctx->hdd_pdev,
						hdd_ctx->sscan_pid);
		break;
	default:
		hdd_warn("invalid message type %d", ss_msg->msg_type);
		break;
	}
}

static void spectral_scan_msg_handler(const void *data, int data_len,
					void *ctx, int pid)
{
	cds_ssr_protect(__func__);
	__spectral_scan_msg_handler(data, data_len, ctx, pid);
	cds_ssr_unprotect(__func__);
}

/**
 * spectral_scan_activate_service() - API to register spectral
 * scan cmd handler
 *
 * API to register the spectral scan command handler using new
 * genl infra. Return type is zero to match with legacy
 * prototype
 *
 * Return: 0
 */
int spectral_scan_activate_service(void)
{
	register_cld_cmd_cb(WLAN_NL_MSG_SPECTRAL_SCAN,
				spectral_scan_msg_handler, NULL);
	return 0;
}
#else
int spectral_scan_activate_service(void)
{
	return 0;
}
#endif
