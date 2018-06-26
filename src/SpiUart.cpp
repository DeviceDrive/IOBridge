#include "SpiUart.h"
#include <SPI.h>

//#define DEBUG_PRINT


SpiUart::SpiUart(uint8_t addr_sspin)
{
    device_address_sspin = addr_sspin;
	peek_flag = 0;
}

void SpiUart::begin(uint32_t baud)
{
    pinMode(device_address_sspin, OUTPUT);
    digitalWrite(device_address_sspin, HIGH);
    delay(1);
	SPI.begin();
    FIFOEnable(1);
	SetBaudrate(baud);
    SetLine(8,0,1);
}

int SpiUart::available(void)
{
    return FIFOAvailableData();
}

int SpiUart::read(void)
{
	if ( peek_flag == 0) {
		return ReadByte();
	} else {
		peek_flag = 0;
		return peek_buf;
	}
}

size_t SpiUart::write(uint8_t val)
{
    WriteByte(val);
}

uint8_t SpiUart::ReadRegister(uint8_t reg_addr)
{
    uint8_t result;
    digitalWrite(device_address_sspin, LOW);
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));   
		delayMicroseconds(10);
		SPI.transfer(0x80|(reg_addr<<3));
		result = SPI.transfer(0xff);
		delayMicroseconds(10);
    SPI.endTransaction();
    digitalWrite(device_address_sspin, HIGH);

	return result;

}

void SpiUart::WriteRegister(uint8_t reg_addr, uint8_t val)
{
    digitalWrite(device_address_sspin, LOW);
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));   
		delayMicroseconds(10);
		SPI.transfer(reg_addr<<3);
		SPI.transfer(val);
		delayMicroseconds(10);
    SPI.endTransaction();
    digitalWrite(device_address_sspin, HIGH);

    return ;
}

int16_t SpiUart::SetBaudrate(uint32_t baudrate)
{
    uint16_t divisor;
    uint8_t prescaler;
    uint32_t actual_baudrate;
    int16_t error;
    uint8_t temp_lcr;
    if ( (ReadRegister(SC16IS750_REG_MCR)&0x80) == 0) {
        prescaler = 1;
    } else {
        prescaler = 4;
    }

    divisor = (SC16IS750_CRYSTCAL_FREQ/prescaler)/(baudrate*16);

    temp_lcr = ReadRegister(SC16IS750_REG_LCR);
    temp_lcr |= 0x80;
    WriteRegister(SC16IS750_REG_LCR,temp_lcr);

    WriteRegister(SC16IS750_REG_DLL,(uint8_t)divisor);

    WriteRegister(SC16IS750_REG_DLH,(uint8_t)(divisor>>8));
    temp_lcr &= 0x7F;
    WriteRegister(SC16IS750_REG_LCR,temp_lcr);


    actual_baudrate = (SC16IS750_CRYSTCAL_FREQ/prescaler)/(16*divisor);
    error = ((float)actual_baudrate-baudrate)*1000/baudrate;
#ifdef  SC16IS750_DEBUG_PRINT
    Serial.print("Desired baudrate: ");
    Serial.println(baudrate,DEC);
    Serial.print("Calculated divisor: ");
    Serial.println(divisor,DEC);
    Serial.print("Actual baudrate: ");
    Serial.println(actual_baudrate,DEC);
    Serial.print("Baudrate error: ");
    Serial.println(error,DEC);
#endif

    return error;

}

void SpiUart::SetLine(uint8_t data_length, uint8_t parity_select, uint8_t stop_length )
{
    uint8_t temp_lcr;
    temp_lcr = ReadRegister(SC16IS750_REG_LCR);
    temp_lcr &= 0xC0;
#ifdef  DEBUG_PRINT
    Serial.print("LCR Register:0x");
    Serial.println(temp_lcr,DEC);
#endif
    switch (data_length) {            
        case 5:
            break;
        case 6:
            temp_lcr |= 0x01;
            break;
        case 7:
            temp_lcr |= 0x02;
            break;
        case 8:
            temp_lcr |= 0x03;
            break;
        default:
            temp_lcr |= 0x03;
            break;
    }

    if ( stop_length == 2 ) {
        temp_lcr |= 0x04;
    }

    switch (parity_select) {            //parity selection length settings
        case 0:                         //no parity
             break;
        case 1:                         //odd parity
            temp_lcr |= 0x08;
            break;
        case 2:                         //even parity
            temp_lcr |= 0x18;
            break;
        case 3:                         //force '1' parity
            temp_lcr |= 0x03;
            break;
        case 4:                         //force '0' parity
            break;
        default:
            break;
    }

    WriteRegister(SC16IS750_REG_LCR,temp_lcr);
}





void SpiUart::InterruptControl(uint8_t int_ena)
{
    WriteRegister(SC16IS750_REG_IER, int_ena);
}

uint8_t SpiUart::InterruptPendingTest(void)
{
    return (ReadRegister(SC16IS750_REG_IIR) & 0x01);
}

void SpiUart::__isr(void)
{
    uint8_t irq_src;

    irq_src = ReadRegister(SC16IS750_REG_IIR);
    irq_src = (irq_src >> 1);
    irq_src &= 0x3F;

    switch (irq_src) {
        case 0x06:                  //Receiver Line Status Error
            break;
        case 0x0c:               //Receiver time-out interrupt
            break;
        case 0x04:               //RHR interrupt
            break;
        case 0x02:               //THR interrupt
            break;
        case 0x00:                  //modem interrupt;
            break;
        case 0x30:                  //input pin change of state
            break;
        case 0x10:                  //XOFF
            break;
        case 0x20:                  //CTS,RTS
            break;
        default:
            break;
    }
    return;
}

void SpiUart::FIFOEnable(uint8_t fifo_enable)
{
    uint8_t temp_fcr;

    temp_fcr = ReadRegister(SC16IS750_REG_FCR);

    if (fifo_enable == 0){
        temp_fcr &= 0xFE;
    } else {
        temp_fcr |= 0x01;
    }
    WriteRegister(SC16IS750_REG_FCR,temp_fcr);

    return;
}

void SpiUart::FIFOReset(uint8_t rx_fifo)
{
     uint8_t temp_fcr;

    temp_fcr = ReadRegister(SC16IS750_REG_FCR);

    if (rx_fifo == 0){
        temp_fcr |= 0x04;
    } else {
        temp_fcr |= 0x02;
    }
    WriteRegister(SC16IS750_REG_FCR,temp_fcr);

    return;

}

void SpiUart::FIFOSetTriggerLevel(uint8_t rx_fifo, uint8_t length)
{
    uint8_t temp_reg;

    temp_reg = ReadRegister(SC16IS750_REG_MCR);
    temp_reg |= 0x04;
    WriteRegister(SC16IS750_REG_MCR,temp_reg); //SET MCR[2] to '1' to use TLR register or trigger level control in FCR register

    temp_reg = ReadRegister(SC16IS750_REG_EFR);
    WriteRegister(SC16IS750_REG_EFR, temp_reg|0x10); //set ERF[4] to '1' to use the  enhanced features
    if (rx_fifo == 0) {
        WriteRegister(SC16IS750_REG_TLR, length<<4); //Tx FIFO trigger level setting
    } else {
        WriteRegister(SC16IS750_REG_TLR, length);    //Rx FIFO Trigger level setting
    }
    WriteRegister(SC16IS750_REG_EFR, temp_reg); //restore EFR register

    return;
}

uint8_t SpiUart::FIFOAvailableData(void)
{
#ifdef  DEBUG_PRINT
    Serial.print("=====Available data:");
    Serial.println(ReadRegister(SC16IS750_REG_RXLVL), DEC);
#endif
   return ReadRegister(SC16IS750_REG_RXLVL);
}

uint8_t SpiUart::FIFOAvailableSpace(void)
{
   return ReadRegister(SC16IS750_REG_TXLVL);

}

void SpiUart::WriteByte(uint8_t val)
{
	uint8_t tmp_lsr;
  Serial.println("++++++++++++Starting send");
	do {
		tmp_lsr = ReadRegister(SC16IS750_REG_LSR);
	} while ((tmp_lsr&0x20) ==0);

	WriteRegister(SC16IS750_REG_THR,val);
  Serial.println("++++++++++++Data sent");


}

int SpiUart::ReadByte(void)
{
	volatile uint8_t val;
	if (FIFOAvailableData() == 0) {
#ifdef  DEBUG_PRINT
	Serial.println("No data available");
#endif
		return -1;

	} else {

#ifdef  DEBUG_PRINT
	Serial.println("***********Data available***********");
#endif
	  val = ReadRegister(SC16IS750_REG_RHR);
	  return val;
	}


}

void SpiUart::EnableTransmit(uint8_t tx_enable)
{
    uint8_t temp_efcr;
    temp_efcr = ReadRegister(SC16IS750_REG_EFCR);
    if ( tx_enable == 0) {
        temp_efcr |= 0x04;
    } else {
        temp_efcr &= 0xFB;
    }
    WriteRegister(SC16IS750_REG_EFCR,temp_efcr);

    return;
}

uint8_t SpiUart::ping()
{
	WriteRegister(SC16IS750_REG_SPR,0x55);
	if (ReadRegister(SC16IS750_REG_SPR) !=0x55) {
		return 0;
	}

	WriteRegister(SC16IS750_REG_SPR,0xAA);
	if (ReadRegister(SC16IS750_REG_SPR) !=0xAA) {
		return 0;
	}

	return 1;

}

void SpiUart::flush()
{
	uint8_t tmp_lsr;

	do {
		tmp_lsr = ReadRegister(SC16IS750_REG_LSR);
	} while ((tmp_lsr&0x20) ==0);


}

int SpiUart:: peek()
{
	if ( peek_flag == 0 ) {
		peek_buf =ReadByte();
		if (  peek_buf >= 0 ) {
			peek_flag = 1;
		}
	}

	return peek_buf;

}
