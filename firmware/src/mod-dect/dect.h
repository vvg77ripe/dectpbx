
#ifndef _MOD_DECT_DECT_H
#define _MOD_DECT_DECT_H

/*
 * DECT Controller registers
 */
#define DECT_REG_DATA		(*(uint8 *)(void *)(&dect->modbase[3]))
#define DECT_REG_RXD		(*(uint16 *)(void *)(&dect->modbase[6]))
#define DECT_REG_TXD		(*(uint16 *)(void *)(&dect->modbase[6]))
#define DECT_REG_ADDR		dect->modbase[7]
#define DECT_REG_STATUS		dect->modbase[7]

/* Status register bitmap */
#define DECT_STATUS_RECV	0x01	/* Packet received */
#define DECT_STATUS_HALF	0x02	/* Half-frame indicator */
#define DECT_STATUS_1PPS	0x04	/* GPS 1-PPS signal */

/* Indirect registers */
#define DECT_ADDR_SN		1		/* Recv slot number register */
#define DECT_ADDR_FRQ0		16		/* Current oscillator frequency register */
#define DECT_ADDR_FRQ1		17
#define DECT_ADDR_FRQ2		18

#define DECT_SLOT_IDLE		0x00
#define DECT_SLOT_TX_P00	0x80
#define DECT_SLOT_TX_P32	0xC0
#define DECT_SLOT_RX		0x40
#define DECT_SLOT_BLIND		0x20

/*
 * MAC layer definions
 */
#define DECT_STYPE_IDLE		0
#define DECT_STYPE_DUMMY	1
#define DECT_STYPE_PSCAN	2
#define DECT_STYPE_TRAFFIC	3
#define DECT_STYPE_BLIND	4

#define DECT_BEARER_NONE	0
#define DECT_BEARER_DUPLEX	1

#define DECT_TMUX_CT		0
#define DECT_TMUX_NT		3
#define DECT_TMUX_QT		4
#define DECT_TMUX_MT		6
#define DECT_TMUX_PT		7
#define DECT_TMUX_FIRST_MT	7

#define DECT_BMUX_NONE		7


#define DECT_MBC_MAX		6
#define DECT_CS_MAX_FLEN	70

#define DECT_URX_SIZE		80

/*
 * MAC layer timers
 */
#define DECT_TMR_TIMEOUT	500

/* mbc_instance defines a MAC layer connection */
typedef struct mbc_instance {
	uint32		pmid;
	uint8		ecn;
	/* Control Channel */
	uint8		cs_send_seq;
	uint8		cs_recv_seq;
	uint8		cs_recv[DECT_CS_MAX_FLEN];
	uint8		cs_recv_len;
	uint8		cs_recv_pos;
	uint8		cs_send[DECT_CS_MAX_FLEN];
	uint8		cs_send_len;
	uint8		cs_send_pos;
	/* Voice (user) Channel */
	uint8		uplane;
	uint8		voice_tx[160];
	uint8		voice_rx[160];
} mbc_inst_t;

/* timeslot configuration */
typedef struct dect_slot {
	uint8		type;			/* Slot type */
	uint8		sn;				/* Slot number */
	uint8		cn;				/* Carrier number */
	uint8		bt;				/* Bearer type */
	uint8		mtail[6];		/* MAC tail to send */
	uint8		mbc;			/* MBC instance ID */
	uint16		tmr_timeout;	/* Bearer timeout timer */
} dect_slot_t;

/* dect module configuration */
typedef struct dect_config {
	uint32		dect_server;		/* DECT server address */
	uint32		fpid;
} PACKED dect_cfg_t;

/* GPS related variables */

#define DECT_GPS_NONE		0		/* No GPS receiver */
#define DECT_GPS_NOLOCK		1		/* GPS not locked */
#define DECT_GPS_LOCK		2		/* GPS locked */

typedef struct dect_gps {
	uint8		state;				/* GPS receiver state */
	uint8		log;				/* GPS logging enabled */
	uint8		urx_len;			/* UART received data length  */
	char		urx_buf[DECT_URX_SIZE];	/* UART RX buffer */
	uint8		pps;				/* 1-PPS signal */
	uint32		freq;				/* Meansured oscillator frequency */
	uint16		lg_high;			/* Longitude high word */
	uint16		lg_low;				/* Longitude low word */
	uint8		lg_dir;				/* Longitude direction (E/W) */
	uint16		lt_high;			/* Latitude high word */
	uint16		lt_low;				/* Latitude low word */
	uint8		lt_dir;				/* Latitude direction (N/S) */
} dect_gps_t;

/* All module variables is here */
struct dect_ram {
	uint8 *		modbase;			/* Module base address */
	uint16		tmr;				/* Status request timer */
	uint8		frame;				/* Current frame number */
	uint32		mframe;				/* Current multiframe number */
	uint8		pscan_cn;			/* Primary scan carrier number */
	uint8		dummypos;			/* Dummy bearer position */
	uint8		rfpi[5];			/* Radio Fixed Part Identity */
	dect_cfg_t	config;
	dect_slot_t	slots[12];
	mbc_inst_t	mbc[DECT_MBC_MAX];
	uint8		ptail[5];			/* Paging tail */
	uint16		tmr_ping;			/* Server ping timer */
	dect_gps_t	gps;
	uint8		dect_pid;
};

extern struct dect_ram *dect;

void mod_dect_init(void);

#endif
