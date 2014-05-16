
#include "user.h"

#undef DBG_TRACE

//#ifdef MS_DEBUG
//#define DBG_TRACE(fmt, args...) printf(fmt, ##args)
//#else#define DBG_TRACE(fmt, args...) {}
//#endif

//extern MS_U32 SysDelay(MS_U32 dwMs);


/**
 * Variable of critical section
 */

Dword User_memoryCopy (
    IN  Demodulator*    demodulator,
    IN  void*           dest,
    IN  void*           src,
    IN  Dword           count
) {
    /*
     *  ToDo:  Add code here
     *
     *  //Pseudo code
     *  memcpy(dest, src, (size_t)count);
     *  return (0);
     */
    return (Error_NO_ERROR);
}

Dword User_delay (
    IN  Demodulator*    demodulator,
    IN  Dword           dwMs
) {
    /*
     *  ToDo:  Add code here
     *
     *  //Pseudo code
     *  delay(dwMs);
     *  return (0);
     */
	msleep(dwMs);
 //    SysDelay(dwMs);
    return (Error_NO_ERROR);
}


Dword User_enterCriticalSection (
    IN  Demodulator*    demodulator
) {
    /*
     *  ToDo:  Add code here
     *
     *  //Pseudo code
     *  return (0);
     */
    return (Error_NO_ERROR);
}


Dword User_leaveCriticalSection (
    IN  Demodulator*    demodulator
) {
    /*
     *  ToDo:  Add code here
     *
     *  //Pseudo code
     *  return (0);
     */
    return (Error_NO_ERROR);
}


Dword User_mpegConfig (
    IN  Demodulator*    demodulator
) {
    /*
     *  ToDo:  Add code here
     *
     */
    return (Error_NO_ERROR);
}


Dword User_busTx (
    IN  Demodulator*    demodulator,
    IN  Dword           bufferLength,
    IN  Byte*           buffer
) {

	unsigned long  error   = 0;

	DefaultDemodulator*   demod;
	demod     = (DefaultDemodulator*) demodulator;
	error = Ite9173_I2CWrite(demod->userData, (Word)demod->demodAddr,buffer,(Word)bufferLength);

	return error;     
}


Dword User_busRx (
    IN  Demodulator*    demodulator,
    IN  Dword           bufferLength,
    OUT Byte*           buffer
) {

	unsigned long  error   = 0;

	DefaultDemodulator*   demod;
	demod     = (DefaultDemodulator*) demodulator;

	error = Ite9173_I2CRead(demod->userData, (Word)demod->demodAddr,buffer,(Word)bufferLength);

	return error;     
}

Dword User_busRxData (
    IN  Demodulator*    demodulator,
    IN  Dword           bufferLength,
    OUT Byte*           buffer
) {
    return (Error_NO_ERROR);
}


Dword Ite9173_I2CWrite(int i2c, Word I2CSlaveAddr,  Byte *data, Word length)
{
	int ret = 0;
	int i;
	struct i2c_msg msg;

	memset(&msg, 0, sizeof(msg));
	msg.addr = I2CSlaveAddr;
	msg.flags = 0;
	msg.buf = data;
	msg.len = length;

	ret = i2c_transfer((struct i2c_adapter *)i2c, &msg, 1);
	if(ret<0) {
		printk("DVB---- %s: writereg error, errno is %d \n", __FUNCTION__, ret);
		return 1;
	}

	return 0;
 }
 
Dword  Ite9173_I2CRead(int i2c, Word I2CSlaveAddr,  Byte *data, Word length)
{
	 int ret = 0;
	 int i;
	 struct i2c_msg msg;
	 
	 memset(&msg, 0, sizeof(msg));
	 msg.addr = I2CSlaveAddr;
	 msg.flags |=  I2C_M_RD;
	 msg.buf = data;
	 msg.len = length;

	 ret = i2c_transfer((struct i2c_adapter *)i2c, &msg, 1); 
	if(ret<0) {
		printk("DVB---- %s: readreg error, errno is %d \n", __FUNCTION__, ret);
		return 1;
	}

	return 0;
 }


