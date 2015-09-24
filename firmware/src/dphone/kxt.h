

#define KXT_HDLC_RBUF	8
#define KXT_HDLC_SBUF	32

void kxt_init(void);
void kxt_process(void);
uint16 kxt_process_data(uint16 rdata);
