#ifndef _SPIUART_H_
#define _SPIUART_H_

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "pindef.h"

#define     SC16IS750_ADDRESS_AA     (0X90)
#define     SC16IS750_ADDRESS_AB     (0X92)
#define     SC16IS750_ADDRESS_AC     (0X94)
#define     SC16IS750_ADDRESS_AD     (0X96)
#define     SC16IS750_ADDRESS_BA     (0X98)
#define     SC16IS750_ADDRESS_BB     (0X9A)
#define     SC16IS750_ADDRESS_BC     (0X9C)
#define     SC16IS750_ADDRESS_BD     (0X9E)
#define     SC16IS750_ADDRESS_CA     (0XA0)
#define     SC16IS750_ADDRESS_CB     (0XA2)
#define     SC16IS750_ADDRESS_CC     (0XA4)
#define     SC16IS750_ADDRESS_CD     (0XA6)
#define     SC16IS750_ADDRESS_DA     (0XA8)
#define     SC16IS750_ADDRESS_DB     (0XAA)
#define     SC16IS750_ADDRESS_DC     (0XAC)
#define     SC16IS750_ADDRESS_DD     (0XAE)

#define     SC16IS750_REG_RHR        (0x00)
#define     SC16IS750_REG_THR        (0X00)
#define     SC16IS750_REG_IER        (0X01)
#define     SC16IS750_REG_FCR        (0X02)
#define     SC16IS750_REG_IIR        (0X02)
#define     SC16IS750_REG_LCR        (0X03)
#define     SC16IS750_REG_MCR        (0X04)
#define     SC16IS750_REG_LSR        (0X05)
#define     SC16IS750_REG_MSR        (0X06)
#define     SC16IS750_REG_SPR        (0X07)
#define     SC16IS750_REG_TCR        (0X06)
#define     SC16IS750_REG_TLR        (0X07)
#define     SC16IS750_REG_TXLVL      (0X08)
#define     SC16IS750_REG_RXLVL      (0X09)
#define     SC16IS750_REG_IODIR      (0X0A)
#define     SC16IS750_REG_IOSTATE    (0X0B)
#define     SC16IS750_REG_IOINTENA   (0X0C)
#define     SC16IS750_REG_IOCONTROL  (0X0E)
#define     SC16IS750_REG_EFCR       (0X0F)


#define     SC16IS750_REG_DLL        (0x00)
#define     SC16IS750_REG_DLH        (0X01)


#define     SC16IS750_REG_EFR        (0X02)
#define     SC16IS750_REG_XON1       (0X04)
#define     SC16IS750_REG_XON2       (0X05)
#define     SC16IS750_REG_XOFF1      (0X06)
#define     SC16IS750_REG_XOFF2      (0X07)


#define     SC16IS750_INT_CTS        (0X80)
#define     SC16IS750_INT_RTS        (0X40)
#define     SC16IS750_INT_XOFF       (0X20)
#define     SC16IS750_INT_SLEEP      (0X10)
#define     SC16IS750_INT_MODEM      (0X08)
#define     SC16IS750_INT_LINE       (0X04)
#define     SC16IS750_INT_THR        (0X02)
#define     SC16IS750_INT_RHR        (0X01)


#define 	SC16IS750_CRYSTCAL_FREQ (18432000UL)

class SpiUart : public Stream
{ 
    public:
		SpiUart();
        SpiUart(uint8_t addr = SPIUART_CS_PIN);
        void begin(uint32_t baud);                               
        int read();
        size_t write(uint8_t val);
        int available();
		uint8_t ping();
		int peek();
		void flush();
		uint8_t InterruptPendingTest(void);
		void    SetPinInterrupt(uint8_t io_int_ena);
		void    InterruptControl(uint8_t int_ena);
		void    ModemPin(uint8_t gpio);
        
    
    private:
        uint8_t device_address_sspin;
        int16_t SetBaudrate(uint32_t baudrate);
        uint8_t ReadRegister(uint8_t reg_addr);
        void    WriteRegister(uint8_t reg_addr, uint8_t val);
        void    SetLine(uint8_t data_length, uint8_t parity_select, uint8_t stop_length );
        void    __isr(void);
        void    FIFOEnable(uint8_t fifo_enable);
        void    FIFOReset(uint8_t rx_fifo);
        void    FIFOSetTriggerLevel(uint8_t rx_fifo, uint8_t length);
        uint8_t FIFOAvailableData(void);
        uint8_t FIFOAvailableSpace(void);
        void    WriteByte(uint8_t val);
        int     ReadByte(void);
        void    EnableTransmit(uint8_t tx_enable);
		int 	peek_buf;
		uint8_t peek_flag;
		
};

#endif





    
    
