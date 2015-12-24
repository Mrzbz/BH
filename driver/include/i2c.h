// i2cDev library collection - Main I2C device class header file
// Abstracts bit and byte I2C R/W functions into a convenient class
// 6/9/2012 by Jeff Rowberg <jeff@rowberg.net>
//
// Changelog:
//     2012-06-09 - fix major issue with reading > 32 bytes at a time with Arduino Wire
//                - add compiler warnings when using outdated or IDE or limited i2cDev implementation
//     2011-11-01 - fix write*Bits mask calculation (thanks sasquatch @ Arduino forums)
//     2011-10-03 - added automatic Arduino version detection for ease of use
//     2011-10-02 - added Gene Knight's NBWire TwoWire class implementation with small modifications
//     2011-08-31 - added support for Arduino 1.0 Wire library (methods are different from 0.x)
//     2011-08-03 - added optional timeout parameter to read* methods to easily change from default
//     2011-08-02 - added support for 16-bit registers
//                - fixed incorrect Doxygen comments on some methods
//                - added timeout value for read operations (thanks mem @ Arduino forums)
//     2011-07-30 - changed read/write function structures to return success or byte counts
//                - made all methods static for multi-device memory savings
//     2011-07-28 - initial release

/* ============================================
I2Cdev device library code is placed under the MIT license
Copyright (c) 2012 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/
#ifndef I2C_H_
#define I2C_H_

namespace BH {

#define RPI2_I2C_0    "/dev/i2c-0"
#define RPI2_I2C_1    "/dev/i2c-1"

#include <stdint.h>

class IIC
{
public:
    IIC();
    ~IIC();

    /** Read a single bit from an 8-bit device register.
	 * @param devBus  I2C bus
     * @param devAddr I2C slave device address
     * @param regAddr Register regAddr to read from
     * @param bitNum Bit position to read (0-7)
     * @param data Container for single bit value
     * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
     * @return Status of read operation (true = success)
    */
    static int8_t readBit(const char* devBus, uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data, uint16_t timeout=IIC::readTimeout);
 
	/** Read a single bit from a 16-bit device register.
	 * @param devBus  I2C bus
	 * @param devAddr I2C slave device address
	 * @param regAddr Register regAddr to read from
	 * @param bitNum Bit position to read (0-15)
	 * @param data Container for single bit value
	 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
	 * @return Status of read operation (true = success)
	 */
	static int8_t readBitW(const char* devBus, uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint16_t *data, uint16_t timeout=IIC::readTimeout);

	/** Read multiple bits from an 8-bit device register.
	 * @param devBus  I2C bus
	 * @param devAddr I2C slave device address
	 * @param regAddr Register regAddr to read from
	 * @param bitStart First bit position to read (0-7)
	 * @param length Number of bits to read (not more than 8)
	 * @param data Container for right-aligned value (i.e. '101' read from any bitStart position will equal 0x05)
	 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
	 * @return Status of read operation (true = success)
	 */ 
     static int8_t readBits(const char* devBus, uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data, uint16_t timeout=IIC::readTimeout);
 
	/** Read multiple bits from a 16-bit device register.
	 * @param devBus  I2C bus
     * @param devAddr I2C slave device address
	 * @param regAddr Register regAddr to read from
	 * @param bitStart First bit position to read (0-15)
	 * @param length Number of bits to read (not more than 16)
	 * @param data Container for right-aligned value (i.e. '101' read from any bitStart position will equal 0x05)
	 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
	 * @return Status of read operation (1 = success, 0 = failure, -1 = timeout)
	 */
    static int8_t readBitsW(const char* devBus, uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t *data, uint16_t timeout=IIC::readTimeout);
	
	/** Read single byte from an 8-bit device register.
	 * @param devBus  I2C bus
	 * @param devAddr I2C slave device address
	 * @param regAddr Register regAddr to read from
	 * @param data Container for byte value read from device
	 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
	 * @return Status of read operation (true = success)
	 */
    static int8_t readByte(const char* devBus, uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint16_t timeout=IIC::readTimeout);

	/** Read single word from a 16-bit device register.
	 * @param devBus  I2C bus
	 * @param devAddr I2C slave device address
	 * @param regAddr Register regAddr to read from
	 * @param data Container for word value read from device
	 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
	 * @return Status of read operation (true = success)
	 */
    static int8_t readWord(const char* devBus, uint8_t devAddr, uint8_t regAddr, uint16_t *data, uint16_t timeout=IIC::readTimeout);
		
	/** Read multiple bytes from an 8-bit device register.
	 * @param devBus  I2C bus
	 * @param devAddr I2C slave device address
	 * @param regAddr First register regAddr to read from
	 * @param length Number of bytes to read
	 * @param data Buffer to store read data in
	 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
	 * @return Number of bytes read (-1 indicates failure)
	 */
    static int8_t readBytes(const char* devBus, uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data, uint16_t timeout=IIC::readTimeout);

	/** Read multiple bytes from an 8-bit device register without sending the register address. Required by MB85RC256(FRAM on Navio+)
	 * @param devBus  I2C bus
	 * @param devAddr I2C slave device address
	 * @param regAddr First register regAddr to read from
	 * @param length Number of bytes to read
	 * @param data Buffer to store read data in
	 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
	 * @return Number of bytes read (-1 indicates failure)
	 */
    static int8_t readBytesNoRegAddress(const char* devBus, uint8_t devAddr, uint8_t length, uint8_t *data, uint16_t timeout=IIC::readTimeout);

	/** Read multiple words from a 16-bit device register.
	 * @param devBus  I2C bus
	 * @param devAddr I2C slave device address
	 * @param regAddr First register regAddr to read from
	 * @param length Number of words to read
	 * @param data Buffer to store read data in
	 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
	 * @return Number of words read (0 indicates failure)
	 */
    static int8_t readWords(const char* devBus, uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data, uint16_t timeout=IIC::readTimeout);

	/** write a single bit in an 8-bit device register.
	 * @param devBus  I2C bus
	 * @param devAddr I2C slave device address
	 * @param regAddr Register regAddr to write to
	 * @param bitNum Bit position to write (0-7)
	 * @param value New bit value to write
	 * @return Status of operation (true = success)
	 */
    static bool writeBit(const char* devBus, uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data);

	/** write a single bit in a 16-bit device register.
	 * @param devBus  I2C bus
	 * @param devAddr I2C slave device address
	 * @param regAddr Register regAddr to write to
	 * @param bitNum Bit position to write (0-15)
	 * @param value New bit value to write
	 * @return Status of operation (true = success)
	 */
    static bool writeBitW(const char* devBus, uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint16_t data);

	/** Write multiple bits in an 8-bit device register.
	 * @param devBus  I2C bus
	 * @param devAddr I2C slave device address
	 * @param regAddr Register regAddr to write to
	 * @param bitStart First bit position to write (0-7)
	 * @param length Number of bits to write (not more than 8)
	 * @param data Right-aligned value to write
	 * @return Status of operation (true = success)
	 */
    static bool writeBits(const char* devBus, uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);

	/** Write multiple bits in a 16-bit device register.
	 * @param devBus  I2C bus
	 * @param devAddr I2C slave device address
	 * @param regAddr Register regAddr to write to
	 * @param bitStart First bit position to write (0-15)
	 * @param length Number of bits to write (not more than 16)
	 * @param data Right-aligned value to write
	 * @return Status of operation (true = success)
	 */
    static bool writeBitsW(const char* devBus, uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t data);

	/** Write single byte to an 8-bit device register.
	 * @param devBus  I2C bus
	 * @param devAddr I2C slave device address
	 * @param regAddr Register address to write to
	 * @param data New byte value to write
	 * @return Status of operation (true = success)
	 */
    static bool writeByte(const char* devBus, uint8_t devAddr, uint8_t regAddr, uint8_t data);

	/** Write single word to a 16-bit device register.
	 * @param devBus  I2C bus
	 * @param devAddr I2C slave device address
	 * @param regAddr Register address to write to
	 * @param data New word value to write
	 * @return Status of operation (true = success)
	 */
    static bool writeWord(const char* devBus, uint8_t devAddr, uint8_t regAddr, uint16_t data);

	/** Write multiple bytes to an 8-bit device register.
	 * @param devBus  I2C bus
	 * @param devAddr I2C slave device address
	 * @param regAddr First register address to write to
	 * @param length Number of bytes to write
	 * @param data Buffer to copy new data from
	 * @return Status of operation (true = success)
	 */
    static bool writeBytes(const char* devBus, uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data);
	
	/** Write multiple words to a 16-bit device register.
	 * @param devBus  I2C bus
	 * @param devAddr I2C slave device address
	 * @param regAddr First register address to write to
	 * @param length Number of words to write
	 * @param data Buffer to copy new data from
	 * @return Status of operation (true = success)
	 */
    static bool writeWords(const char* devBus, uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data);

	/** Default timeout value for read operations.
	 * Set this to 0 to disable timeout detection.
	 */
    static uint16_t readTimeout;
};

} // end of BH

#endif  //I2C_H_