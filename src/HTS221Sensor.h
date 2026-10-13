/**
 ******************************************************************************
 * @file    HTS221Sensor.h
 * @author  AST
 * @version V1.0.0
 * @date    7 September 2017
 * @brief   Abstract class of a HTS221 Humidity and Temperature sensor.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */


/* Prevent recursive inclusion -----------------------------------------------*/

#ifndef __HTS221Sensor_H__
#define __HTS221Sensor_H__


/* Includes ------------------------------------------------------------------*/

#include "Wire.h"
#include "HTS221_Driver.h"


/** Result codes returned by HTS221Sensor operations. */
typedef enum
{
  HTS221_STATUS_OK = 0,
  HTS221_STATUS_ERROR,
  HTS221_STATUS_TIMEOUT,
  HTS221_STATUS_NOT_IMPLEMENTED
} HTS221StatusTypeDef;

/* Class Declaration ---------------------------------------------------------*/

/** Controls an HTS221 humidity and temperature sensor over I2C. */
class HTS221Sensor
{
  public:
    /** Construct the sensor interface using the supplied I2C bus. */
    HTS221Sensor                       (TwoWire *i2c);

    /** Initialize the sensor and its communication interface. */
    HTS221StatusTypeDef begin          (void);

    /** Shut down the sensor interface. */
    HTS221StatusTypeDef end            (void);

    /** Enable sensor measurements. */
    HTS221StatusTypeDef Enable         (void);

    /** Disable sensor measurements. */
    HTS221StatusTypeDef Disable        (void);

    /** Read the sensor identifier into @p ht_id. */
    HTS221StatusTypeDef ReadID         (uint8_t *ht_id);

    /** Reset the sensor. */
    HTS221StatusTypeDef Reset          (void);

    /** Read relative humidity into @p pfData. */
    HTS221StatusTypeDef GetHumidity    (float *pfData);

    /** Read temperature into @p pfData. */
    HTS221StatusTypeDef GetTemperature (float *pfData);

	/** Get the output data rate and store it in @p odr. */
	HTS221StatusTypeDef GetODR         (float *odr);
	/** Set the output data rate to @p odr. */
	HTS221StatusTypeDef SetODR         (float odr);
	/** Read register @p reg into @p data. */
	HTS221StatusTypeDef ReadReg        (uint8_t reg, uint8_t *data);
	/** Write @p data to register @p reg. */
	HTS221StatusTypeDef WriteReg       (uint8_t reg, uint8_t data);

	/**
     * @brief Read bytes from the sensor over I2C.
     * @param pBuffer Destination buffer for the bytes read.
     * @param RegisterAddr Internal register address to read from.
     * @param NumByteToRead Number of bytes to read.
     * @return Zero.
     */
    uint8_t IO_Read(uint8_t* pBuffer, uint8_t RegisterAddr, uint16_t NumByteToRead)
    {
      dev_i2c->beginTransmission(((uint8_t)(((address) >> 1) & 0x7F)));
      dev_i2c->write(RegisterAddr);
      dev_i2c->endTransmission(false);

      dev_i2c->requestFrom(((uint8_t)(((address) >> 1) & 0x7F)), (byte) NumByteToRead);

      int i=0;
      while (dev_i2c->available())
      {
        pBuffer[i] = dev_i2c->read();
        i++;
      }

      return 0;
    }
    
    /**
    * @brief Write bytes to the sensor over I2C.
    * @param pBuffer Source buffer containing the bytes to write.
    * @param RegisterAddr Internal register address to write to.
    * @param NumByteToWrite Number of bytes to write.
    * @return Zero.
     */
    uint8_t IO_Write(uint8_t* pBuffer, uint8_t RegisterAddr, uint16_t NumByteToWrite)
    {
      dev_i2c->beginTransmission(((uint8_t)(((address) >> 1) & 0x7F)));

      dev_i2c->write(RegisterAddr);
      for (uint16_t i = 0 ; i < NumByteToWrite ; i++)
        dev_i2c->write(pBuffer[i]);

      dev_i2c->endTransmission(true);

      return 0;
    }

  private:
    /* Helper classes. */
    TwoWire *dev_i2c;

    /* Configuration */
    uint8_t address;
};

#ifdef __cplusplus
extern "C" {
#endif
uint8_t HTS221_IO_Write( void *handle, uint8_t WriteAddr, uint8_t *pBuffer, uint16_t nBytesToWrite );
uint8_t HTS221_IO_Read( void *handle, uint8_t ReadAddr, uint8_t *pBuffer, uint16_t nBytesToRead );
#ifdef __cplusplus
}
#endif

#endif