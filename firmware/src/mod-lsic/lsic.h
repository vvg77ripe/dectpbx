
#ifndef _MOD_LSIC_LSIC_H
#define _MOD_LSIC_LSIC_H


#define LSIC_MAX_KEYS		512
#define LSIC_MAX_LOGS		100
#define LSIC_MAX_INPUTS		4

#define LSIC_CLIENT_PORT	2145

/* LSIC guard system state list */
#define LSIC_STATE_DOOR_OPEN	1
#define LSIC_STATE_ALARM		2
#define LSIC_STATE_BEEP			3

/* LSIC input line types */
#define LSIC_INPUT_NONE			0
#define LSIC_INPUT_ALARM		1
#define LSIC_INPUT_DOOR_KEY		2
#define LSIC_INPUT_DOOR_STATUS	3

/* LSIC status register bitmap */
#define LSIC_STATUS_WBIT	0x01		/* Received wiegand bit value */
#define LSIC_STATUS_WDATA	0x02		/* Wiegand bit received flag */
#define LSIC_STATUS_ALARM	0x04		/* ADC alert */
#define LSIC_STATUS_ZERO	0x80		/* Zero bit */

/* LSIC control register bitmap */
#define LSIC_CONTROL_1WIRE	0x20
#define LSIC_CONTROL_RLY1	0x40
#define LSIC_CONTROL_RLY2	0x80

/* AD7993/AD7994 configuration registers */
#define AD7993_REG_RESULT	0x00
#define AD7993_REG_ALERT	0x01
#define AD7993_REG_CONFIG	0x02
#define AD7993_REG_TIMER	0x03
#define AD7993_REG_DATAL1	0x04
#define AD7993_REG_DATAH1	0x05
#define AD7993_REG_HYST1	0x06
#define AD7993_REG_DATAL2	0x07
#define AD7993_REG_DATAH2	0x08
#define AD7993_REG_HYST2	0x09
#define AD7993_REG_DATAL3	0x0A
#define AD7993_REG_DATAH3	0x0B
#define AD7993_REG_HYST3	0x0C
#define AD7993_REG_DATAL4	0x0D
#define AD7993_REG_DATAH4	0x0E
#define AD7993_REG_HYST4	0x0F

/* AD7993_REG_CONFIG bit mapping */
#define AD7993_CONFIG_CH4	0x80
#define AD7993_CONFIG_CH3	0x40
#define AD7993_CONFIG_CH2	0x20
#define AD7993_CONFIG_CH1	0x10
#define AD7993_CONFIG_FLTR	0x08
#define AD7993_CONFIG_ALERT	0x04
#define AD7993_CONFIG_BUSY	0x02

/* AD7993_REG_TIMER bit mapping */
#define AD7993_TIMER_NONE	0x00
#define AD7993_TIMER_X32	0x01
#define AD7993_TIMER_X64	0x02
#define AD7993_TIMER_X128	0x03
#define AD7993_TIMER_X256	0x04
#define AD7993_TIMER_X512	0x05
#define AD7993_TIMER_X1024	0x06
#define AD7993_TIMER_X2048	0x07

/* Access Key record flags */
#define LSIC_KEY_VALID		0x10	/* Key is valid */
#define LSIC_KEY_SAVE		0x20	/* Key need to be saved to NVRAM */

/* Access Key Record structure */
typedef struct lsic_key {
	uint8		bitcnt;
	uint8		bits[7];
	uint8		chksum;
	uint8		flags;
} PACKED lsic_key_rec;

/* LSIC log event types */
#define LSIC_LOG_KEY_GRANTED	1	/* Access is granted for this RFID */
#define LSIC_LOG_KEY_NOTFOUND	2	/* RFID key not found in table */
#define LSIC_LOG_KEY_RESTRICTED	3	/* Access for this RFID key is restricted */
#define LSIC_LOG_KEY_ASSIGNED	4	/* New RFID key is added to table */

#define LSIC_LOG_DOOR_OPENKEY	10	/* Door is opened by local button */
#define LSIC_LOG_DOOR_OPENNET	11	/* Door is opened by network command */
#define LSIC_LOG_DOOR_NOTOPEN	12	/* Access is granted, but door is not opened */
#define LSIC_LOG_DOOR_NOTCLOSED	13	/* Door is not closed */

#define LSIC_LOG_ALARM			20

/* LSIC log record */
typedef struct lsic_log {
	uint16		id;					/* Record ID */
	uint32		tms;				/* Event timestamp */
	uint8		type;				/* Event type */
	uint8		bitcnt;				/* Associated key bit count */
	uint8		bits[7];			/* Associated key bit values */
	uint8		param;				/* Associated parameter */
} PACKED lsic_log_rec;

/* LSIC input line config */
typedef struct lsic_input {
	uint8		type;
	uint16		min;
	uint16		max;
} PACKED lsic_inp_t;

/* LSIC config */
typedef struct lsic_config {
	uint8		version;				/* Config structure version */
	uint8		tv_door_open;			/* Open door timeout (1s-interval) */
	uint8		tv_assign;				/* Assign key timeout (1s-interval) */
	uint8		relay1_state;
	uint8		relay2_state;
	uint8		onewire_state;
	uint16		adc_1k_value;			/* ADC result for 1k resistor */
	lsic_inp_t	inp[LSIC_MAX_INPUTS];
} PACKED lsic_config_t;

/* LSIC module memory */
struct lsic_ram {
	lsic_config_t	config;
	int				tmr_counter;		/* 0.5ms timer */
	unsigned int	tmr_seconds;		/* 1s timer */
	uint8 *			modbase;			/* module base address */
	lsic_key_rec	keys[LSIC_MAX_KEYS];/* Access Keys */
	uint16			log_next_idx;		/* Index of next free log table entry */
	uint16			log_last_id;		/* Last event id */
	lsic_log_rec	logs[LSIC_MAX_LOGS];
	uint16			tmr_door_open;		/* Door open timer (1s)*/
	uint16			tmr_beep;			/* Beep timer (0.5ms) */
	uint16			tmr_rfid_assign;	/* New key assign timer (1s) */
	uint8			alert;				/* ADC alert bits */
	uint8			alarm;				/* System alarm bits */
};

/* Network structures */
#define LSIC_CMD_STATUS			1		/* Get device status */
#define LSIC_CMD_ASSIGN			2		/* assign new rfid */
#define LSIC_CMD_DOOR_OPEN		3		/* Open the door */
#define LSIC_CMD_KEY_LIST		4		/* Get rfid key list */
#define LSIC_CMD_LOGENTRY		5		/* Get log entry */
#define LSIC_CMD_CONFIG_GET		6		/* Get current configuration */
#define LSIC_CMD_CONFIG_PUT		7		/* Change configuration */
#define LSIC_CMD_INPUTS_GET		8		/* Get inputs state */
#define LSIC_CMD_KEY_UPDATE		9		/* Update/delete rfid key info */

struct lsic_net_header {
	uint8			sign[4];			/* 'LSIC' */
	uint16			code;				/* Command/response code */
} PACKED;

struct lsic_net_packet {
	struct lsic_net_header	header;
	union {
		/* LSIC_CMD_STATUS */
		struct {
			uint8		door;			/* 1 if door is open */
			uint8		alarm;			/* Input alarm bits */
			uint8		assign;			/* 1 if waiting for new key */
			uint16		last_log_id;	/* Last event ID */
		} PACKED r_status;
		/* LSIC_CMD_ASSIGN */
		/* LSIC_CMD_DOOR_OPEN */
		/* LSIC_CMD_KEY_LIST */
		struct {
			uint16		start;
			uint16		count;
			lsic_key_rec keys[10];
		} PACKED r_key_list;
		/* LSIC_CMD_KEY_UPDATE */
		struct {
			lsic_key_rec	key;
		} c_key_update;
		/* LSIC_CMD_LOGENTRY */
		struct {
			uint16		id;
		} PACKED c_logentry;
		struct {
			uint16		count;
			lsic_log_rec entry;
		} PACKED r_logentry;
		/* LSIC_CMD_CONFIG_GET */
		struct {
			lsic_config_t	config;
		} r_config_get;
		/* LSIC_CONFIG_PUT */
		struct {
			lsic_config_t	config;
		} c_config_put;
		/* LSIC_CMD_INPUTS_GET */
		struct {
			uint16		adc_1k_value;
			uint16		inputs[LSIC_MAX_INPUTS];
		} PACKED r_inputs_get;
	} data;
} PACKED;

/* Module functions */
void mod_lsic_init(void);
void lsic_serv_handler(uint32 s_addr, uint16 s_port, uint8 *data, uint16 len);

#endif
