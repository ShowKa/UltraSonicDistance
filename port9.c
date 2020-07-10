#include	"iodefine.h"

//É}ÉNÉçíËã`
// port9 SEG7
#define   PORT9_IO  PORT9.PDR.BYTE
#define   PORT9_OUTPUT   PORT9.PODR.BYTE

initPort9() {
	PORT9_IO = 0xff;
}

setPort9(char output) {
	PORT9_OUTPUT = output;
}