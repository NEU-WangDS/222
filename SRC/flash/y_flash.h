/****************************************************************************
 *	@笔者	：	Q
 *	@日期	：	2023年2月9日
 *	@所属	：	杭州友辉科技
 *	@功能	：	存放FLASH相关的函数
 ****************************************************************************/

#ifndef _Y_FLASH_H_
#define _Y_FLASH_H_
#include "main.h"

/* SPI 片选引脚选择 */
#define SPI_FLASH_CS(x) GPIO_WriteBit(GPIOB, GPIO_Pin_12, (BitAction)x)

/*******W25Q系列芯片ID*******/
#define W25Q80 0XEF13
#define W25Q16 0XEF14
#define W25Q32 0XEF15
#define W25Q64 0XEF16

/*******W25Q64芯片变量宏定义*******/
#define W25Q64_SECTOR_SIZE 4096 // 4K
#define W25Q64_SECTOR_NUM 2048  // 8*1024/4 = 2048

/*******W25Q64芯片地址存储表*******/
#define FLASH_ASC16_ADDRESS 0
#define FLASH_HZK16_ADDRESS 0x1000

#define FLASH_SYSTEM_CONFIG_ADDRESS 0x43000

#define FLASH_BITMAP1_SIZE_ADDRESS 0x50000
#define FLASH_BITMAP2_SIZE_ADDRESS FLASH_BITMAP1_SIZE_ADDRESS + 0x28000
#define FLASH_BITMAP3_SIZE_ADDRESS FLASH_BITMAP2_SIZE_ADDRESS + 0x28000
#define FLASH_BITMAP4_SIZE_ADDRESS FLASH_BITMAP3_SIZE_ADDRESS + 0x28000
#define FLASH_BITMAP5_SIZE_ADDRESS FLASH_BITMAP4_SIZE_ADDRESS + 0x28000
#define FLASH_BITMAP6_SIZE_ADDRESS FLASH_BITMAP5_SIZE_ADDRESS + 0x28000

#define FLASH_BITMAPMAIN_SIZE_ADDRESS FLASH_BITMAP6_SIZE_ADDRESS + 0x28000
#define FLASH_BITMAPDS1302_SIZE_ADDRESS FLASH_BITMAPMAIN_SIZE_ADDRESS + 0x28000
#define FLASH_BITMAPDS18B20_SIZE_ADDRESS FLASH_BITMAPDS1302_SIZE_ADDRESS + 0x28000
#define FLASH_BITMAPBLUETOOTH_SIZE_ADDRESS FLASH_BITMAPDS18B20_SIZE_ADDRESS + 0x28000

/*******FLASH相关指令表*******/
#define W25X_WriteEnable 0x06
#define W25X_WriteDisable 0x04
#define W25X_ReadStatusReg 0x05
#define W25X_WriteStatusReg 0x01
#define W25X_ReadData 0x03
#define W25X_FastReadData 0x0B
#define W25X_FastReadDual 0x3B
#define W25X_PageProgram 0x02 /* 写页命令 */
#define W25X_SectorErase 0x20 /* 扇区擦除指令 */
#define W25X_BlockErase 0xD8
#define W25X_ChipErase 0xC7        /* 芯片擦除命令 */
#define W25X_PowerDown 0xB9        /* 掉电命令 */
#define W25X_ReleasePowerDown 0xAB /* 唤醒指令 */
#define W25X_DeviceID 0xAB
#define W25X_ManufactDeviceID 0x90 /* 读取ID命令 */
#define W25X_JedecDeviceID 0x9F

void spi_flash_on(u8 x);               /* LED引脚和SPI引脚重合，切换SPI和LED引脚状态 */
void spi_flash_init(void);             /* 初始化SPI FLASH的IO口 */
void spi_set_speed(uint16_t SpeedSet); /* SPI 速度设置函数 */
u8 spi_write_read(u8 TxData);          /* SPI读写数据 */

u16 spi_flash_read_id(void);                        /* 读取芯片ID W25X16的ID:0XEF14 */
u8 spi_flash_read_SR(void);                         /* 读SPI_FLASH的状态寄存器 */
void spi_flash_write_SR(u8 byte);                   /* 写SPI_FLASH的状态寄存器 */
void spi_flash_write_enable(void);                  /* SPI_FLASH写使能，WEL置位 */
void spi_flash_write_disable(void);                 /* SPI_FLASH写禁止，将WEL清零 */
char spi_flash_read_char(u32 readAddr);             /* SPI读取1个字节的数据 */
void spi_flash_write_char(char tmp, u32 WriteAddr); /* SPI写入1个字节的数据 */

void spi_flash_read(u8 *pBuffer, u32 ReadAddr, u16 NumByteToRead);             /* 在指定地址开始读取指定长度的数据 */
void spi_flash_write(u8 *pBuffer, u32 WriteAddr, u16 NumByteToWrite);          /* 在指定地址开始写入指定长度的数据 */
void spi_flash_write_page(u8 *pBuffer, u32 WriteAddr, u16 NumByteToWrite);     /* SPI在一页内写入少于256个字节的数据 */
void spi_flash_write_sector(u8 *pBuffer, u32 WriteAddr, u16 NumByteToWrite);   /* SPI在一扇区内写入少于4096个字节的数据 */
void spi_flash_write_no_check(u8 *pBuffer, u32 WriteAddr, u16 NumByteToWrite); /* 无检验写SPI_FLASH */
void spi_flash_erase_sector(u32 Dst_Addr);                                     /* 擦除一个扇区 最少150毫秒 */
void spi_flash_erase_chip(void);                                               /* 擦除整个芯片 */
void spi_flash_wait_busy(void);                                                /* 等待空闲 */
void spi_flash_power_down(void);                                               /* 进入掉电模式 */
void spi_flash_wake_up(void);                                                  /* 唤醒 */
void SpiFlashWriteS(u8 *pBuffer, u32 WriteAddr, u16 NumByteToWrite);

#define spiFlahsOn(x) spi_flash_on(x)

#define w25x_init() spi_flash_init()
#define w25x_readId() spi_flash_read_id()
#define w25x_read(buf, addr, len) spi_flash_read(buf, addr, len)
#define w25x_write(buf, addr, len) spi_flash_write_no_check(buf, addr, len)
#define w25x_writeS(buf, addr, len) SpiFlashWriteS(buf, addr, len)
#define w25x_erase_sector(addr) spi_flash_erase_sector(addr)
#define w25x_wait_busy() spi_flash_wait_busy()
#endif
