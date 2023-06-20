/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2012-2021, The Linux Foundation. All rights reserved.
 * Copyright (c) 2022-2023, Qualcomm Innovation Center, Inc. All rights reserved.
 */
#ifndef ADSPRPC_SHARED_H
#define ADSPRPC_SHARED_H

#include <linux/types.h>
#include <linux/cdev.h>

#ifdef CONFIG_MSM_ADSPRPC_TRUSTED
#include "../include/uapi/fastrpc_shared.h"
#else
#include "fastrpc_shared.h"
#endif

#define FASTRPC_GLINK_GUID "fastrpcglink-apps-dsp"
#define FASTRPC_SMD_GUID "fastrpcsmd-apps-dsp"
#define DEVICE_NAME      "adsprpc-smd"
#define DEVICE_NAME_SECURE "adsprpc-smd-secure"

/* Pre-defined parameter for print gfa structure*/

#define smq_invoke_ctx_params "pid: %d, tgid: %d, handle: %d, sc: 0x%x, fl: %p, fd: %p, magic: %d\n"

#define fastrpc_file_params "fl->tgid: %d, fl->cid: %d, fl->ssrcount: %p, fl->pd: %d, fl->profile: %p, fl->mode: %p, fl->tgid_open: %d, fl->num_cached_buf: %d, num_pers_hdrs: %d, fl->sessionid: %d, fl->servloc_name: %s, fl->file_close: %d, fl->dsp_proc_init: %d,fl->apps: %p, fl->qos_request: %d, fl->dev_minor: %d, fl->debug_buf: %s fl->debug_buf_alloced_attempted: %d, fl->wake_enable: %d, fl->ws_timeout: %d, fl->untrusted_process: %d\n"

#define fastrpc_mmap_params "fd: %d, flags: %p, buf: %p, phys: %p, size : %d, va : %p, map->raddr: %p, len : %d, refs : %d, secure: %d\n"

#define fastrpc_buf_params "buf->fl: %p, buf->phys: %p, buf->virt: %p, buf->size: %d, buf->dma_attr: %ld, buf->raddr: %p, buf->flags: %d, buf->type: %d, buf->in_use: %d\n"
/* Set for buffers that have no virtual mapping in userspace */
#define FASTRPC_ATTR_NOVA 0x1

/* Set for buffers that are NOT dma coherent */
#define FASTRPC_ATTR_NON_COHERENT 0x2

/* Set for buffers that are dma coherent */
#define FASTRPC_ATTR_COHERENT 0x4

/* Fastrpc attribute for keeping the map persistent */
#define FASTRPC_ATTR_KEEP_MAP	0x8

/* Fastrpc attribute for no mapping of fd  */
#define FASTRPC_ATTR_NOMAP (16)

/*
 * Fastrpc attribute to skip flush by fastrpc
 */
#define FASTRPC_ATTR_FORCE_NOFLUSH  (32)

/*
 * Fastrpc attribute to skip invalidate by fastrpc
 */
#define FASTRPC_ATTR_FORCE_NOINVALIDATE (64)

/* Driver should operate in parallel with the co-processor */
#define FASTRPC_MODE_PARALLEL    0

/* Driver should operate in serial mode with the co-processor */
#define FASTRPC_MODE_SERIAL      1

/* Driver should operate in profile mode with the co-processor */
#define FASTRPC_MODE_PROFILE     2

/* Set FastRPC session ID to 1 */
#define FASTRPC_MODE_SESSION     4

/* Retrives number of input buffers from the scalars parameter */
#define REMOTE_SCALARS_INBUFS(sc)        (((sc) >> 16) & 0x0ff)

/* Retrives number of output buffers from the scalars parameter */
#define REMOTE_SCALARS_OUTBUFS(sc)       (((sc) >> 8) & 0x0ff)

/* Retrives number of input handles from the scalars parameter */
#define REMOTE_SCALARS_INHANDLES(sc)     (((sc) >> 4) & 0x0f)

/* Retrives number of output handles from the scalars parameter */
#define REMOTE_SCALARS_OUTHANDLES(sc)    ((sc) & 0x0f)

/* Remote domains ID */
#define ADSP_DOMAIN_ID	(0)
#define MDSP_DOMAIN_ID	(1)
#define SDSP_DOMAIN_ID	(2)
#define CDSP_DOMAIN_ID	(3)
#define MAX_DOMAIN_ID	CDSP_DOMAIN_ID

#define NUM_CHANNELS	4	/* adsp, mdsp, slpi, cdsp*/
#define NUM_SESSIONS	14	/* max 11 compute, 3 cpz */

/* Default maximum sessions allowed per process */
#define DEFAULT_MAX_SESS_PER_PROC 4

#define VALID_FASTRPC_CID(cid) \
	(cid >= ADSP_DOMAIN_ID && cid < NUM_CHANNELS)

#define REMOTE_SCALARS_LENGTH(sc)	(REMOTE_SCALARS_INBUFS(sc) +\
					REMOTE_SCALARS_OUTBUFS(sc) +\
					REMOTE_SCALARS_INHANDLES(sc) +\
					REMOTE_SCALARS_OUTHANDLES(sc))

#define REMOTE_SCALARS_MAKEX(attr, method, in, out, oin, oout) \
		((((uint32_t)   (attr) & 0x7) << 29) | \
		(((uint32_t) (method) & 0x1f) << 24) | \
		(((uint32_t)     (in) & 0xff) << 16) | \
		(((uint32_t)    (out) & 0xff) <<  8) | \
		(((uint32_t)    (oin) & 0x0f) <<  4) | \
		((uint32_t)   (oout) & 0x0f))

#define REMOTE_SCALARS_MAKE(method, in, out) \
		REMOTE_SCALARS_MAKEX(0, method, in, out, 0, 0)

#ifdef VERIFY_PRINT_ERROR
#define VERIFY_EPRINTF(format, ...) pr_err(format, ##__VA_ARGS__)
#else
#define VERIFY_EPRINTF(format, args) ((void)0)
#endif

#ifndef VERIFY_PRINT_INFO
#define VERIFY_IPRINTF(args) ((void)0)
#endif

#ifndef VERIFY
#define __STR__(x) #x ":"
#define __TOSTR__(x) __STR__(x)
#define __FILE_LINE__ __FILE__ ":" __TOSTR__(__LINE__)
#define __ADSPRPC_LINE__ "adsprpc:" __TOSTR__(__LINE__)

#define VERIFY(err, val) \
do {\
	VERIFY_IPRINTF(__FILE_LINE__"info: calling: " #val "\n");\
	if ((val) == 0) {\
		(err) = (err) == 0 ? -1 : (err);\
		VERIFY_EPRINTF(__ADSPRPC_LINE__" error: %d: "#val "\n", (err));\
	} else {\
		VERIFY_IPRINTF(__FILE_LINE__"info: passed: " #val "\n");\
	} \
} while (0)
#endif

#define ADSPRPC_ERR(fmt, args...)\
	pr_err("Error: adsprpc (%d): %s: %s: " fmt, __LINE__,\
	current->comm, __func__, ##args)
#define ADSPRPC_INFO(fmt, args...)\
	pr_info("Info: adsprpc (%d): %s: %s: " fmt, __LINE__,\
	current->comm, __func__, ##args)
#define ADSPRPC_WARN(fmt, args...)\
	pr_warn("Warning: adsprpc (%d): %s: %s: " fmt, __LINE__,\
	current->comm, __func__, ##args)
#define ADSPRPC_DEBUG(fmt, args...)\
	pr_debug("Debug: adsprpc (%d): %s: %s: " fmt, __LINE__,\
	current->comm, __func__, ##args)

#define DEBUG_PRINT_SIZE_LIMIT (512*1024)

#define remote_arg64_t    union remote_arg64

struct remote_buf64 {
	uint64_t pv;
	uint64_t len;
};

struct remote_dma_handle64 {
	int fd;
	uint32_t offset;
	uint32_t len;
};

union remote_arg64 {
	struct remote_buf64	buf;
	struct remote_dma_handle64 dma;
	uint32_t h;
};

struct remote_buf {
	void *pv;		/* buffer pointer */
	size_t len;		/* length of buffer */
};

/* structure to hold fd and size of buffer shared with DSP,
* which contains inital debug parameters that needs to be passed
* during process initialization.
*/
struct fastrpc_proc_sharedbuf_info {
	int buf_fd;
	int buf_size;
};

struct remote_dma_handle {
	int fd;
	uint32_t offset;
};

union remote_arg {
	struct remote_buf buf;	/* buffer info */
	struct remote_dma_handle dma;
	uint32_t h;		/* remote handle */
};

struct fastrpc_async_job {
	uint32_t isasyncjob; /* flag to distinguish async job */
	uint64_t jobid;      /* job id generated by user */
	uint32_t reserved;   /* reserved */
};

/* FastRPC ioctl structure to set session related info */
struct fastrpc_proc_sess_info {
	uint32_t domain_id;  /* Set the remote subsystem, Domain ID of the session  */
	uint32_t session_id; /* Unused, Set the Session ID on remote subsystem */
	uint32_t pd_type;    /* Set the process type on remote subsystem */
	uint32_t sharedcb;   /* Unused, Session can share context bank with other sessions */
};

/* INIT a new process or attach to guestos */
enum fastrpc_init_flags {
	FASTRPC_INIT_NO_CREATE       = -1,
	FASTRPC_INIT_ATTACH          = 0,
	FASTRPC_INIT_CREATE          = 1,
	FASTRPC_INIT_CREATE_STATIC   = 2,
	FASTRPC_INIT_ATTACH_SENSORS  = 3,
};

enum fastrpc_invoke2_type {
	FASTRPC_INVOKE2_ASYNC		   = 1,
	FASTRPC_INVOKE2_ASYNC_RESPONSE = 2,
	FASTRPC_INVOKE2_KERNEL_OPTIMIZATIONS,
	FASTRPC_INVOKE2_STATUS_NOTIF,
	FASTRPC_INVOKE2_PROC_SHAREDBUF_INFO,
	/* Set session info of remote sub system */
	FASTRPC_INVOKE2_SESS_INFO,
};

/**
 * Control flags for mapping memory on DSP user process
 */
enum fastrpc_map_flags {
	/**
	 * Map memory pages with RW- permission and CACHE WRITEBACK.
	 * The driver is responsible for cache maintenance when passed
	 * the buffer to FastRPC calls. Same virtual address will be
	 * assigned for subsequent FastRPC calls.
	 */
	FASTRPC_MAP_STATIC = 0,

	/* Reserved */
	FASTRPC_MAP_RESERVED,

	/**
	 * Map memory pages with RW- permission and CACHE WRITEBACK.
	 * Mapping tagged with a file descriptor. User is responsible for
	 * CPU and DSP cache maintenance for the buffer. Get virtual address
	 * of buffer on DSP using HAP_mmap_get() and HAP_mmap_put() APIs.
	 */
	FASTRPC_MAP_FD = 2,

	/**
	 * Mapping delayed until user call HAP_mmap() and HAP_munmap()
	 * functions on DSP. It is useful to map a buffer with cache modes
	 * other than default modes. User is responsible for CPU and DSP
	 * cache maintenance for the buffer.
	 */
	FASTRPC_MAP_FD_DELAYED,

	/**
	 * This flag is used to skip CPU mapping,
	 * otherwise behaves similar to FASTRPC_MAP_FD_DELAYED flag.
	 */
	FASTRPC_MAP_FD_NOMAP = 16,

	FASTRPC_MAP_MAX,
};

/*
 * This enum is shared with DSP. So, existing values should NOT
 * be modified. Only new members can be added.
 */
enum dsp_map_flags {
	/* Add memory to static PD pool, protection thru XPU */
	ADSP_MMAP_HEAP_ADDR = 4,

	/* MAP static DMA buffer on DSP User PD */
	ADSP_MMAP_DMA_BUFFER = 6,

	/* Add memory to static PD pool, protection thru hypervisor */
	ADSP_MMAP_REMOTE_HEAP_ADDR = 8,

	/* Add memory to userPD pool, for user heap */
	ADSP_MMAP_ADD_PAGES = 0x1000,

	/* Add memory to userPD pool, for LLC heap */
	ADSP_MMAP_ADD_PAGES_LLC = 0x3000,

	/* Map persistent header buffer on DSP */
	ADSP_MMAP_PERSIST_HDR = 0x4000,
};

enum fastrpc_control_type {
	FASTRPC_CONTROL_LATENCY		=	1,
	/* Share SMMU context bank */
	FASTRPC_CONTROL_SMMU		=	2,
	FASTRPC_CONTROL_KALLOC		=	3,
	FASTRPC_CONTROL_WAKELOCK	=	4,
	FASTRPC_CONTROL_PM		=	5,
/* Clean process on DSP */
	FASTRPC_CONTROL_DSPPROCESS_CLEAN	=	6,
	FASTRPC_CONTROL_RPC_POLL = 7,
	FASTRPC_CONTROL_ASYNC_WAKE = 8,
	FASTRPC_CONTROL_NOTIF_WAKE = 9,
};

#define FASTRPC_MAX_DSP_ATTRIBUTES	(256)
#define FASTRPC_MAX_ATTRIBUTES	(260)

enum fastrpc_dsp_capability {
	ASYNC_FASTRPC_CAP = 9,
	DMA_HANDLE_REVERSE_RPC_CAP = 129,
};

struct smq_null_invoke {
	uint64_t ctx;			/* invoke caller context */
	uint32_t handle;	    /* handle to invoke */
	uint32_t sc;		    /* scalars structure describing the data */
};

struct smq_phy_page {
	uint64_t addr;		/* physical address */
	uint64_t size;		/* size of contiguous region */
};

struct smq_invoke_buf {
	int num;		/* number of contiguous regions */
	int pgidx;		/* index to start of contiguous region */
};

struct smq_invoke {
	struct smq_null_invoke header;
	struct smq_phy_page page;   /* remote arg and list of pages address */
};

struct smq_msg {
	uint32_t pid;           /* process group id */
	uint32_t tid;           /* thread id */
	struct smq_invoke invoke;
};

struct smq_invoke_rsp {
	uint64_t ctx;			/* invoke caller context */
	int retval;	             /* invoke return value */
};

enum fastrpc_response_flags {
	NORMAL_RESPONSE = 0,
	EARLY_RESPONSE = 1,
	USER_EARLY_SIGNAL = 2,
	COMPLETE_SIGNAL = 3,
	STATUS_RESPONSE = 4,
	POLL_MODE = 5,
};

enum fastrpc_process_create_state {
	PROCESS_CREATE_DEFAULT = 0,			/* Process is not created */
	PROCESS_CREATE_IS_INPROGRESS = 1,	/* Process creation is in progress */
	PROCESS_CREATE_SUCCESS = 2,			/* Process creation is successful */
};

struct smq_invoke_rspv2 {
	uint64_t ctx;		  /* invoke caller context */
	int retval;		  /* invoke return value */
	uint32_t flags;		  /* early response flags */
	uint32_t early_wake_time; /* user predicted early wakeup time in us */
	uint32_t version;	  /* Version number for validation */
};

enum fastrpc_status_flags {
	FASTRPC_USERPD_UP = 0,
	FASTRPC_USERPD_EXIT = 1,
	FASTRPC_USERPD_FORCE_KILL = 2,
	FASTRPC_USERPD_EXCEPTION = 3,
	FASTRPC_DSP_SSR = 4,
};

struct smq_notif_rspv3 {
	uint64_t ctx;		  /* response context */
	uint32_t type;        /* Notification type */
	int pid;		      /* user process pid */
	uint32_t status;	  /* userpd status notification */
};

enum fastrpc_process_exit_states {
	/* Process Default State */
	FASTRPC_PROCESS_DEFAULT_STATE				= 0,
	/* Process exit initiated */
	FASTRPC_PROCESS_EXIT_START				= 1,
	/* Process exit issued to DSP */
	FASTRPC_PROCESS_DSP_EXIT_INIT				= 2,
	/* Process exit in DSP complete */
	FASTRPC_PROCESS_DSP_EXIT_COMPLETE			= 3,
	/* Process exit in DSP error */
	FASTRPC_PROCESS_DSP_EXIT_ERROR				= 4,
};

/*
 * Process types on remote subsystem
 * Always add new PD types at the end, before MAX_PD_TYPE
 */
#define DEFAULT_UNUSED    0  /* pd type not configured for context banks */
#define ROOT_PD           1  /* Root PD */
#define AUDIO_STATICPD    2  /* ADSP Audio Static PD */
#define SENSORS_STATICPD  3  /* ADSP Sensors Static PD */
#define SECURE_STATICPD   4  /* CDSP Secure Static PD */
#define OIS_STATICPD      5  /* ADSP OIS Static PD */
#define CPZ_USERPD        6  /* CDSP CPZ USER PD */
#define USERPD            7  /* DSP User Dynamic PD */
#define GUEST_OS_SHARED   8  /* Legacy Guest OS Shared */
#define MAX_PD_TYPE       9  /* Max PD type */

struct fastrpc_file;

int fastrpc_transport_send(int cid, void *rpc_msg, uint32_t rpc_msg_size, int tvm_remote_domain);
inline int fastrpc_handle_rpc_response(void *data, int len, int cid);
inline int verify_transport_device(int cid, int tvm_remote_domain);
int fastrpc_transport_init(void);
void fastrpc_transport_deinit(void);
void fastrpc_transport_session_init(int cid, char *subsys);
void fastrpc_transport_session_deinit(int cid);
int fastrpc_wait_for_transport_interrupt(int cid, unsigned int flags);
int fastrpc_set_tvm_remote_domain(struct fastrpc_file *fl, struct fastrpc_ioctl_init *init);
void fastrpc_restart_drivers(int cid);

static inline struct smq_invoke_buf *smq_invoke_buf_start(remote_arg64_t *pra,
							uint32_t sc)
{
	unsigned int len = REMOTE_SCALARS_LENGTH(sc);

	return (struct smq_invoke_buf *)(&pra[len]);
}

static inline struct smq_phy_page *smq_phy_page_start(uint32_t sc,
						struct smq_invoke_buf *buf)
{
	unsigned int nTotal = REMOTE_SCALARS_LENGTH(sc);

	return (struct smq_phy_page *)(&buf[nTotal]);
}

/*
 * Fastrpc context ID bit-map:
 *
 * bits 0-3   : type of remote PD
 * bit  4     : type of job (sync/async)
 * bit  5     : reserved
 * bits 6-15  : index in context table
 * bits 16-63 : incrementing context ID
 */
#define FASTRPC_CTX_MAX (1024)

/* Length of glink transaction history to store */
#define GLINK_MSG_HISTORY_LEN (128)


/* Type of fastrpc DMA bufs sent to DSP */
enum fastrpc_buf_type {
	METADATA_BUF,
	COPYDATA_BUF,
	INITMEM_BUF,
	USERHEAP_BUF,
};


/* Types of RPC calls to DSP */
enum fastrpc_msg_type {
	USER_MSG = 0,
	KERNEL_MSG_WITH_ZERO_PID,
	KERNEL_MSG_WITH_NONZERO_PID,
};

/* Fastrpc remote pd type */
enum fastrpc_remote_pd_type {
	FASTRPC_ROOT_PD = 0,
	FASTRPC_USER_PD,
	FASTRPC_SENSORS_PD,
};

#define DSPSIGNAL_TIMEOUT_NONE 0xffffffff
#define DSPSIGNAL_NUM_SIGNALS 1024

// Signal state and completions are stored in groups of DSPSIGNAL_GROUP_SIZE.
// Must be a power of two.
#define DSPSIGNAL_GROUP_SIZE 256


struct secure_vm {
	int *vmid;
	int *vmperm;
	int vmcount;
};

struct gid_list {
	unsigned int *gids;
	unsigned int gidcount;
};

struct fastrpc_buf {
	struct hlist_node hn;
	struct hlist_node hn_rem;
	struct hlist_node hn_init;
	struct fastrpc_file *fl;
	void *virt;
	uint64_t phys;
	size_t size;
	unsigned long dma_attr;
	uintptr_t raddr;
	uint32_t flags;
	int type;		/* One of "fastrpc_buf_type" */
	bool in_use;	/* Used only for persistent header buffers */
	struct timespec64 buf_start_time;
	struct timespec64 buf_end_time;
};

struct fastrpc_ctx_lst;

struct fastrpc_tx_msg {
	struct smq_msg msg;     /* Msg sent to remote subsystem */
	int transport_send_err; /* transport error */
	int64_t ns;             /* Timestamp (in ns) of msg */
	uint64_t xo_time_in_us; /* XO Timestamp (in us) of sent message */
	uint64_t xo_time_in_us_interrupted; /* XO Timestamp (in us) of interrupted ctx */
	uint64_t xo_time_in_us_restored; /* XO Timestamp (in us) of restored ctx */
};

struct fastrpc_rx_msg {
	struct smq_invoke_rspv2 rsp;  /* Response from remote subsystem */
	int64_t ns;   /* Timestamp (in ns) of response */
	uint64_t xo_time_in_us; /* XO Timestamp (in us) of response */
};

struct fastrpc_transport_log {
	unsigned int tx_index;  /* Current index of 'tx_msgs' array */
	unsigned int rx_index;  /* Current index of 'rx_msgs' array */

	/* Rolling history of messages sent to remote subsystem */
	struct fastrpc_tx_msg tx_msgs[GLINK_MSG_HISTORY_LEN];

	/* Rolling history of responses from remote subsystem */
	struct fastrpc_rx_msg rx_msgs[GLINK_MSG_HISTORY_LEN];
	spinlock_t lock;
};

struct overlap {
	uintptr_t start;
	uintptr_t end;
	int raix;
	uintptr_t mstart;
	uintptr_t mend;
	uintptr_t offset;
	int do_cmo;		/*used for cache maintenance of inrout buffers*/
};

struct fastrpc_perf {
	uint64_t count;
	uint64_t flush;
	uint64_t map;
	uint64_t copy;
	uint64_t link;
	uint64_t getargs;
	uint64_t putargs;
	uint64_t invargs;
	uint64_t invoke;
	uint64_t tid;
};

struct smq_notif_rsp {
	struct list_head notifn;
	int domain;
	int session;
	enum fastrpc_status_flags status;
};

struct smq_invoke_ctx {
	struct hlist_node hn;
	/* Async node to add to async job ctx list */
	struct list_head asyncn;
	struct completion work;
	int retval;
	int pid;
	int tgid;
	remote_arg_t *lpra;
	remote_arg64_t *rpra;
	remote_arg64_t *lrpra;		/* Local copy of rpra for put_args */
	int *fds;
	unsigned int *attrs;
	struct fastrpc_mmap **maps;
	struct fastrpc_buf *buf;
	struct fastrpc_buf *copybuf;	/*used to copy non-ion buffers */
	size_t used;
	struct fastrpc_file *fl;
	uint32_t handle;
	uint32_t sc;
	struct overlap *overs;
	struct overlap **overps;
	struct smq_msg msg;
	uint32_t *crc;
	uint64_t *perf_kernel;
	uint64_t *perf_dsp;
	unsigned int magic;
	uint64_t ctxid;
	struct fastrpc_perf *perf;
	/* response flags from remote processor */
	enum fastrpc_response_flags rsp_flags;
	/* user hint of completion time in us */
	uint32_t early_wake_time;
	/* work done status flag */
	bool is_work_done;
	/* Store Async job in the context*/
	struct fastrpc_async_job asyncjob;
	/* Async early flag to check the state of context */
	bool is_early_wakeup;
	uint32_t sc_interrupted;
	struct fastrpc_file *fl_interrupted;
	uint32_t handle_interrupted;
	uint64_t xo_time_in_us_created; /* XO Timestamp (in us) of ctx creation */
	uint64_t xo_time_in_us_interrupted; /* XO Timestamp (in us) of interrupted ctx */
	uint64_t xo_time_in_us_restored; /* XO Timestamp (in us) of restored ctx */
	int tx_index; /* index of current ctx in channel gmsg_log array */
	bool is_job_sent_to_remote_ss; /* Flag to check if job is sent to remote sub system */
};

struct fastrpc_ctx_lst {
	struct hlist_head pending;
	struct hlist_head interrupted;
	/* Number of active contexts queued to DSP */
	uint32_t num_active_ctxs;
	/* Queue which holds all async job contexts of process */
	struct list_head async_queue;
	/* Queue which holds all status notifications of process */
	struct list_head notif_queue;
};

struct fastrpc_smmu {
	struct device *dev;
	const char *dev_name;
	int cb;
	int enabled;
	int faults;
	int secure;
	int coherent;
	int sharedcb;
	int pd_type; /* Process type on remote sub system */
	/* gen pool for QRTR */
	struct gen_pool *frpc_genpool;
	/* fastrpc gen pool buffer */
	struct fastrpc_buf *frpc_genpool_buf;
	/* fastrpc gen pool buffer fixed IOVA */
	unsigned long genpool_iova;
	/* fastrpc gen pool buffer size */
	size_t genpool_size;
};

struct fastrpc_session_ctx {
	struct device *dev;
	struct fastrpc_smmu smmu;
	int used;
};

struct fastrpc_static_pd {
	char *servloc_name;
	char *spdname;
	void *pdrhandle;
	uint64_t pdrcount;
	uint64_t prevpdrcount;
	atomic_t ispdup;
	int cid;
	wait_queue_head_t wait_for_pdup;
};

struct fastrpc_dsp_capabilities {
	uint32_t is_cached;	//! Flag if dsp attributes are cached
	uint32_t dsp_attributes[FASTRPC_MAX_DSP_ATTRIBUTES];
};

struct fastrpc_channel_ctx {
	char *name;
	char *subsys;
	struct device *dev;
	struct fastrpc_session_ctx session[NUM_SESSIONS];
	struct fastrpc_static_pd spd[NUM_SESSIONS];
	struct completion work;
	struct completion workport;
	struct notifier_block nb;
	struct mutex smd_mutex;
	uint64_t sesscount;
	uint64_t ssrcount;
	int in_hib;
	void *handle;
	uint64_t prevssrcount;
	int subsystemstate;
	int vmid;
	struct secure_vm rhvm;
	void *rh_dump_dev;
	/* Indicates, if channel is restricted to secure node only */
	int secure;
	/* Indicates whether the channel supports unsigned PD */
	bool unsigned_support;
	struct fastrpc_dsp_capabilities dsp_cap_kernel;
	/* cpu capabilities shared to DSP */
	uint64_t cpuinfo_todsp;
	bool cpuinfo_status;
	struct smq_invoke_ctx *ctxtable[FASTRPC_CTX_MAX];
	spinlock_t ctxlock;
	struct fastrpc_transport_log gmsg_log;
	struct hlist_head initmems;
	/* Store gfa structure debug details */
	struct fastrpc_buf *buf;
};

struct fastrpc_apps {
	struct fastrpc_channel_ctx *channel;
	struct cdev cdev;
	struct class *class;
	struct smq_phy_page range;
	struct hlist_head maps;
	uint32_t staticpd_flags;
	dev_t dev_no;
	int compat;
	struct hlist_head drivers;
	spinlock_t hlock;
	struct device *dev;
	/* Indicates fastrpc device node info */
	struct device *dev_fastrpc;
	unsigned int latency;
	int transport_initialized;
	/* Flag to determine fastrpc bus registration */
	int fastrpc_bus_register;
	bool legacy_remote_heap;
	/* Unique job id for each message */
	uint64_t jobid[NUM_CHANNELS];
	struct gid_list gidlist;
	struct device *secure_dev;
	struct device *non_secure_dev;
	/* Secure subsystems like ADSP/SLPI will use secure client */
	struct wakeup_source *wake_source_secure;
	/* Non-secure subsystem like CDSP will use regular client */
	struct wakeup_source *wake_source;
	uint32_t duplicate_rsp_err_cnt;
	uint32_t max_size_limit;
	struct hlist_head frpc_devices;
	struct hlist_head frpc_drivers;
	struct mutex mut_uid;
	/* Indicates nsp status */
	int fastrpc_nsp_status;
	/* Indicates secure context bank to be shared */
	int share_securecb;
	/* Indicates process type is configured for SMMU context bank */
	bool cb_pd_type;
	/* Number of lowest capacity cores for given platform */
	unsigned int lowest_capacity_core_count;
	/* Flag to check if PM QoS vote needs to be done for only one core */
	bool single_core_latency_vote;
	/* Maximum sessions allowed to be created per process */
	uint32_t max_sess_per_proc;
};

struct fastrpc_mmap {
	struct hlist_node hn;
	struct fastrpc_file *fl;
	struct fastrpc_apps *apps;
	int fd;
	uint32_t flags;
	struct dma_buf *buf;
	struct sg_table *table;
	struct dma_buf_attachment *attach;
	struct ion_handle *handle;
	uint64_t phys;
	size_t size;
	uintptr_t va;
	size_t len;
	int refs;
	uintptr_t raddr;
	int secure;
	bool is_persistent;			/* the map is persistenet across sessions */
	int frpc_md_index;			/* Minidump unique index */
	uintptr_t attr;
	bool in_use;				/* Indicates if persistent map is in use*/
	struct timespec64 map_start_time;
	struct timespec64 map_end_time;
	/* Mapping for fastrpc shell */
	bool is_filemap;
	char *servloc_name;			/* Indicate which daemon mapped this */
	/* Indicates map is being used by a pending RPC call */
	unsigned int ctx_refs;
};

enum fastrpc_perfkeys {
	PERF_COUNT = 0,
	PERF_FLUSH = 1,
	PERF_MAP = 2,
	PERF_COPY = 3,
	PERF_LINK = 4,
	PERF_GETARGS = 5,
	PERF_PUTARGS = 6,
	PERF_INVARGS = 7,
	PERF_INVOKE = 8,
	PERF_TID = 9,
	PERF_KEY_MAX = 10,
};

struct fastrpc_notif_queue {
	/* Number of pending status notifications in queue */
	atomic_t notif_queue_count;

	/* Wait queue to synchronize notifier thread and response */
	wait_queue_head_t notif_wait_queue;

	/* IRQ safe spin lock for protecting notif queue */
	spinlock_t nqlock;
};

enum fastrpc_dspsignal_state {
	DSPSIGNAL_STATE_UNUSED = 0,
	DSPSIGNAL_STATE_PENDING,
	DSPSIGNAL_STATE_SIGNALED,
	DSPSIGNAL_STATE_CANCELED
};

struct fastrpc_dspsignal {
	struct completion comp;
	int state;
};

struct memory_snapshot {
	/* Total size of heap buffers allocated in userspace */
	size_t heap_bufs_size;
	/* Total size of non-heap buffers allocated in userspace */
	size_t nonheap_bufs_size;
};

struct fastrpc_file {
	struct hlist_node hn;
	spinlock_t hlock;
	struct hlist_head maps;
	struct hlist_head cached_bufs;
	uint32_t num_cached_buf;
	struct hlist_head remote_bufs;
	struct fastrpc_ctx_lst clst;
	struct fastrpc_session_ctx *sctx;
	struct fastrpc_buf *init_mem;

	/* No. of persistent headers */
	unsigned int num_pers_hdrs;
	/* Pre-allocated header buffer */
	struct fastrpc_buf *pers_hdr_buf;
	/* Pre-allocated buffer divided into N chunks */
	struct fastrpc_buf *hdr_bufs;
	/* Store snapshot of memory occupied by different buffers */
	struct memory_snapshot mem_snap;

	struct fastrpc_session_ctx *secsctx;
	uint32_t mode;
	uint32_t profile;
	int sessionid;
	int tgid_open;	/* Process ID during device open */
	int tgid;		/* Process ID that uses device for RPC calls */
	/* Unique HLOS process ID created by fastrpc for each client */
	int tgid_frpc;
	int cid;
	int tvm_remote_domain;
	uint64_t ssrcount;
	int pd;
	char *servloc_name;
	int file_close;
	int dsp_proc_init;
	int sharedcb;
	int pd_type; /* Process type on remote subsystem */
	struct fastrpc_apps *apps;
	struct dentry *debugfs_file;
	struct dev_pm_qos_request *dev_pm_qos_req;
	int qos_request;
	struct mutex map_mutex;
	struct mutex internal_map_mutex;
	/* Identifies the device (MINOR_NUM_DEV / MINOR_NUM_SECURE_DEV) */
	int dev_minor;
	char *debug_buf;
	/* Flag to indicate attempt has been made to allocate memory for debug_buf*/
	int debug_buf_alloced_attempted;
	/* Flag to enable PM wake/relax voting for every remote invoke */
	int wake_enable;
	struct gid_list gidlist;
	/* Number of jobs pending in Async Queue */
	atomic_t async_queue_job_count;
	/* Async wait queue to synchronize glink response and async thread */
	wait_queue_head_t async_wait_queue;
	/* IRQ safe spin lock for protecting async queue */
	spinlock_t aqlock;
	/* Process status notification queue */
	struct fastrpc_notif_queue proc_state_notif;
	uint32_t ws_timeout;
	bool untrusted_process;
	struct fastrpc_device *device;
	/* Process kill will wait on work when ram dump collection in progress */
	struct completion work;
	/* Flag to indicate ram dump collection status*/
	bool is_ramdump_pend;
	/* Process kill will wait on bus driver invoke thread to complete its process */
	struct completion dma_invoke;
	/* Flag to indicate invoke pending */
	bool is_dma_invoke_pend;
	/* Flag to indicate type of process (static, dynamic) */
	uint32_t proc_flags;
	/* If set, threads will poll for DSP response instead of glink wait */
	bool poll_mode;
	/* Threads poll for specified timeout and fall back to glink wait */
	uint32_t poll_timeout;
	/* Flag to indicate dynamic process creation status*/
	enum fastrpc_process_create_state dsp_process_state;
	bool is_unsigned_pd;
	/* Flag to indicate 32 bit driver*/
	bool is_compat;
	/* Completion objects and state for dspsignals */
	struct fastrpc_dspsignal *signal_groups[DSPSIGNAL_NUM_SIGNALS / DSPSIGNAL_GROUP_SIZE];
	spinlock_t dspsignals_lock;
	struct mutex signal_create_mutex;
	struct completion shutdown;
	/* Flag to indicate notif thread exit requested*/
	bool exit_notif;
	/* Flag to indicate async thread exit requested*/
	bool exit_async;
	/*
	* structure to hold fd and size of buffer shared with DSP,
	* which contains initial debug configurations and other initial
	* config paramters.
	*/
	struct fastrpc_proc_sharedbuf_info sharedbuf_info;
	/* Flag to indicate 4 session support available */
	bool multi_session_support;
	/* Flag to indicate session info is set */
	bool set_session_info;
};

int fastrpc_internal_invoke(struct fastrpc_file *fl, uint32_t mode,
				   uint32_t kernel,
				   struct fastrpc_ioctl_invoke_async *inv);

int fastrpc_internal_invoke2(struct fastrpc_file *fl,
				struct fastrpc_ioctl_invoke2 *inv2);

int fastrpc_internal_munmap(struct fastrpc_file *fl,
				   struct fastrpc_ioctl_munmap *ud);

int fastrpc_internal_mem_map(struct fastrpc_file *fl,
				struct fastrpc_ioctl_mem_map *ud);

int fastrpc_internal_mem_unmap(struct fastrpc_file *fl,
				struct fastrpc_ioctl_mem_unmap *ud);

int fastrpc_internal_mmap(struct fastrpc_file *fl,
				 struct fastrpc_ioctl_mmap *ud);

int fastrpc_init_process(struct fastrpc_file *fl,
				struct fastrpc_ioctl_init_attrs *uproc);

int fastrpc_get_info(struct fastrpc_file *fl, uint32_t *info);

int fastrpc_internal_control(struct fastrpc_file *fl,
					struct fastrpc_ioctl_control *cp);

int fastrpc_setmode(unsigned long ioctl_param,
				struct fastrpc_file *fl);

int fastrpc_get_info_from_kernel(
		struct fastrpc_ioctl_capability *cap,
		struct fastrpc_file *fl);

int fastrpc_dspsignal_signal(struct fastrpc_file *fl,
			     struct fastrpc_ioctl_dspsignal_signal *sig);

int fastrpc_dspsignal_wait(struct fastrpc_file *fl,
			   struct fastrpc_ioctl_dspsignal_wait *wait);

int fastrpc_dspsignal_create(struct fastrpc_file *fl,
			     struct fastrpc_ioctl_dspsignal_create *create);

int fastrpc_dspsignal_destroy(struct fastrpc_file *fl,
			      struct fastrpc_ioctl_dspsignal_destroy *destroy);

int fastrpc_dspsignal_cancel_wait(struct fastrpc_file *fl,
				  struct fastrpc_ioctl_dspsignal_cancel_wait *cancel);

void fastrpc_rproc_trace_events(const char *name, const char *event,
				const char *subevent);

#endif
