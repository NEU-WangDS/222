#ifndef _SOFT_I2C_H_
#define _SOFT_I2C_H_
#include <stdio.h>

#include "stm32f10x_conf.h"
#include "stm32f10x.h"

void i2c_timeout_delay(void); //延时 用于等待应答时的超时判断 移植时需修改
void soft_i2c_gpio_init(void);

// I2C所有操作函数
void i2c_start(void);       //发送I2C开始信号
void i2c_stop(void);        //发送I2C停止信号
uint8_t i2c_wait_ack(void); // I2C等待ACK信号
void i2c_ack(void);         // I2C发送ACK信号
void i2c_nack(void);        // I2C不发送ACK信号

void i2c_write_byte(uint8_t txd);   // I2C发送一个字节
uint8_t i2c_read_byte(uint8_t ack); // I2C读取一个字节

uint8_t i2c_mem_write(uint8_t DevAddress, uint8_t MemAddress, uint16_t Len, uint8_t *pData);              // I2C对指定器件、指定寄存器连续写入
uint8_t i2c_mem_read(uint8_t DevAddress, uint8_t MemAddress, uint16_t Len, uint8_t *pBuffer);             // I2C对指定器件、指定寄存器连续读取

uint8_t i2c_write_bit(uint8_t DevAddress, uint8_t addr, uint8_t bitNum, uint8_t Data);                    //写入8位寄存器的一个位
uint8_t i2c_write_bits(uint8_t DevAddress, uint8_t addr, uint8_t bitStart, uint8_t length, uint8_t Data); //写入8位寄存器的多个位
uint8_t i2c_read_bit(uint8_t DevAddress, uint8_t addr, uint8_t bitNum, uint8_t *Data);                    //读取一个位从8位器件的寄存器
uint8_t i2c_read_bits(uint8_t DevAddress, uint8_t addr, uint8_t bitStart, uint8_t length, uint8_t *Data); //读取8位寄存器的多个位

#endif
