#ifndef _SCIDRV_H_
#define _SCIDRV_H_

//グローバル変数定義
extern unsigned char SCI0_RX_DATA;
extern unsigned char SCI0_RX_FLAG;
extern unsigned char SCI1_RX_DATA;
extern unsigned char SCI1_RX_FLAG;
extern unsigned char SCI2_RX_DATA;
extern unsigned char SCI2_RX_FLAG;
extern unsigned char SCI3_RX_DATA;
extern unsigned char SCI3_RX_FLAG;
extern unsigned char SCI4_RX_DATA;
extern unsigned char SCI4_RX_FLAG;
extern unsigned char SCI5_RX_DATA;
extern unsigned char SCI5_RX_FLAG;
extern unsigned char SCI6_RX_DATA;
extern unsigned char SCI6_RX_FLAG;
extern unsigned char SCI7_RX_DATA;
extern unsigned char SCI7_RX_FLAG;

void initSCI0(void);
void initSCI1(void);
void initSCI2(void);
void initSCI3(void);
void initSCI4(void);
void initSCI5(void);
void initSCI6(void);
void initSCI7(void);
char pGetChar_SCI();
char pSendChar_SCI(unsigned char data);
unsigned char GetChar_SCI();

void pPrint_SCI(unsigned char *string, int max_length);

#endif // _SCIDRV_H_