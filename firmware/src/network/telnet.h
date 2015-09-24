
#define TELNET_IAC			255
#define TELNET_WILL			251
#define TELNET_WONT			252
#define TELNET_DO			253
#define TELNET_DONT			254

#define TELNET_OPT_ECHO		1
#define TELNET_OPT_GOAHEAD	3	/* Supperss Go-Ahead */

void telnet_init(void);
void telnet_process(void);
