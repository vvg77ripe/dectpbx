
#define MAX_ARP_ENTRIES		8

#define	ARP_REQUEST			1
#define	ARP_REPLY			2

#define ARP_ENTRY_VALID		1
#define ARP_ENTRY_STATIC	2

#define ARP_EXPIRE_MERGED	30
#define ARP_EXPIRE_REPLIED	300

/*
 * This data definition is defined for Ethernet only!
 */
typedef struct {
	uint16		ar_hrd;
	uint16		ar_pro;
	uint8		ar_hln;		/* hardware address length */
	uint8		ar_pln;		/* protocol address length */
	uint16		opcode;
	uint8		ar_sha[6];	/* ethernet hw address */
	uint32		ar_spa;		/* ip address */
	uint8		ar_tha[6];	/* ethernet hw address */
	uint32		ar_tpa;		/* ip address */
} arp_frame_hdr;


typedef struct {
	uint8		arp_flags;
	uint16		arp_expire;
	uint32		ip_addr;
	uint8		hw_addr[6];
} arp_table_rec;


void arp_init(void);
void arp_handler(IF_PACKET *pkt);

int arp_lookup(uint32 ip_addr, uint8 *mac_addr);
void arp_merge(uint32 ip_addr, uint8 *mac_addr);
void arp_request(uint32 ip_addr);
