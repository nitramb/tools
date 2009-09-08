#include "GenericTypeDefs.h"
#include "Compiler.h"
#include "XSPI.h"
#include "delays.h"

#define EJLo	LATBbits.LATB1 = 0
#define EJHi	LATBbits.LATB1 = 1
#define EJTris	TRISBbits.TRISB1

#define XXLo	LATBbits.LATB0 = 0
#define XXHi	LATBbits.LATB0 = 1
#define XXTris	TRISBbits.TRISB0

#define SSLo	LATBbits.LATB4 = 0
#define SSHi	LATBbits.LATB4 = 1
#define SSTris  TRISBbits.TRISB4

#define SCKLo	LATBbits.LATB3 = 0
#define SCKHi	LATBbits.LATB3 = 1
#define SCKTris TRISBbits.TRISB3

#define MOSILo	LATBbits.LATB6 = 0
#define MOSIHi	LATBbits.LATB6 = 1
#define MOSITris TRISBbits.TRISB6

#define MISO	PORTBbits.RB2

void XSPIInit()
{
	EJHi; SSHi; XXHi; SCKHi;

	EJTris = 0;
	XXTris = 0;
	SSTris = 0;
	SCKTris = 0;
	MOSITris = 0;
}

void XSPIEnterFlashMode()
{
	XXLo;

	Delay10KTCYx(0);

	SSLo; EJLo;

	Delay10KTCYx(0);

	XXHi; EJHi;

	Delay10KTCYx(0);
}

void XSPILeaveFlashMode()
{
	SSHi; EJLo;

	Delay10KTCYx(0);

	XXLo; EJHi;
}

BYTE XSPI(BYTE o)
{
	BYTE i = 0x00;
	
	if (o & 0x01) MOSIHi; else MOSILo;
	SCKHi;
	i |= MISO?0x01:0x00;
	SCKLo;	
	
	if (o & 0x02) MOSIHi; else MOSILo;
	SCKHi;
	i |= MISO?0x02:0x00;
	SCKLo;
	
	if (o & 0x04) MOSIHi; else MOSILo;
	SCKHi;
	i |= MISO?0x04:0x00;
	SCKLo;
	
	if (o & 0x08) MOSIHi; else MOSILo;
	SCKHi;
	i |= MISO?0x08:0x00;
	SCKLo;
	
	if (o & 0x10) MOSIHi; else MOSILo;
	SCKHi;
	i |= MISO?0x10:0x00;
	SCKLo;
	
	if (o & 0x20) MOSIHi; else MOSILo;
	SCKHi;
	i |= MISO?0x20:0x00;
	SCKLo;
	
	if (o & 0x40) MOSIHi; else MOSILo;
	SCKHi;
	i |= MISO?0x40:0x00;	
	SCKLo;
	
	if (o & 0x80) MOSIHi; else MOSILo;
	SCKHi;
	i |= MISO?0x80:0x00;
	SCKLo;
	
	return i;
}

void XSPIW(BYTE o)
{
	if (o & 0x01) MOSIHi; else MOSILo;
	SCKHi; SCKLo;	
	
	if (o & 0x02) MOSIHi; else MOSILo;
	SCKHi; SCKLo;	
	
	if (o & 0x04) MOSIHi; else MOSILo;
	SCKHi; SCKLo;	
	
	if (o & 0x08) MOSIHi; else MOSILo;
	SCKHi; SCKLo;	
	
	if (o & 0x10) MOSIHi; else MOSILo;
	SCKHi; SCKLo;	
	
	if (o & 0x20) MOSIHi; else MOSILo;
	SCKHi; SCKLo;	
	
	if (o & 0x40) MOSIHi; else MOSILo;
	SCKHi; SCKLo;	
	
	if (o & 0x80) MOSIHi; else MOSILo;
	SCKHi; SCKLo;	
}

void XSPIW0()
{
	MOSILo;

	SCKHi; SCKLo;	
	SCKHi; SCKLo;	
	SCKHi; SCKLo;	
	SCKHi; SCKLo;	
	SCKHi; SCKLo;	
	SCKHi; SCKLo;	
	SCKHi; SCKLo;	
	SCKHi; SCKLo;	
}


BYTE XSPIR()
{
	BYTE i = 0x00;
	MOSILo;
	
	SCKHi;
	i |= MISO?0x01:0x00;
	SCKLo;	
	
	SCKHi;
	i |= MISO?0x02:0x00;
	SCKLo;
	
	SCKHi;
	i |= MISO?0x04:0x00;
	SCKLo;
	
	SCKHi;
	i |= MISO?0x08:0x00;
	SCKLo;
	
	SCKHi;
	i |= MISO?0x10:0x00;
	SCKLo;
	
	SCKHi;
	i |= MISO?0x20:0x00;
	SCKLo;

	SCKHi;
	i |= MISO?0x40:0x00;	
	SCKLo;
	
	SCKHi;
	i |= MISO?0x80:0x00;
	SCKLo;
	
	return i;
}

void XSPIRead(BYTE reg, BYTE *data)
{
	SSLo;

	XSPIW((reg << 2) | 1);
	
	XSPIW(0xFF);

	*data++ = XSPIR();
	*data++ = XSPIR();
	*data++ = XSPIR();
	*data++ = XSPIR();

	SSHi;
}

void XSPIWrite(BYTE reg, BYTE *data)
{
	SSLo;

	XSPIW((reg << 2) | 2);

	XSPIW(*data++);
	XSPIW(*data++);
	XSPIW(*data++);
	XSPIW(*data++);

	SSHi;
}

void XSPIWrite0(BYTE reg)
{
	SSLo;

	XSPIW((reg << 2) | 2);

	XSPIW0();
	XSPIW0();
	XSPIW0();
	XSPIW0();

	SSHi;
}

void XSPIWriteByte(BYTE reg, BYTE d)
{
	SSLo;

	XSPIW((reg << 2) | 2);

	XSPIW(d);
	XSPIW0();
	XSPIW0();
	XSPIW0();

	SSHi;
}