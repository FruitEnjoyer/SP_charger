/* MCP342x library version 1.9.4

Writed by B@tto
Contact : batto@hotmail.fr


  MCP342x.cpp - ADC 18 bits i2c library for Wiring & Arduino
  Copyright (c) 2012 Yann LEFEBVRE.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/*
 * Modified by ruslan
 * Adapted for STM32L0
 * Contact: valeev.rl@phystech.edu
 * July 12, 2025
 */

#include "MCP342x.h"

MCP342x::MCP342x::MCP342x()
{
// TODO: поставить правильный адрес
    _adresse = 0x65;

}

MCP342x::MCP342x::~MCP342x()
{
}

void MCP342x::MCP342x::begin(uint8_t setMod)
{
#if 0
    Wire.begin();
#endif
}

uint8_t MCP342x::MCP342x::getAddress()
{
    return _adresse;
}
uint8_t MCP342x::MCP342x::getConfiguration()
{
#if 0
    Wire.requestFrom(_adresse, (_resolution == RESOLUTION_18_BITS) ? 4 : 3);
#endif
    uint8_t i = 0;

#if 0
    while(Wire.available())
    {
        _buffer[i++] = Wire.read();
    }
#endif

    return (_buffer[(_resolution == RESOLUTION_18_BITS ? 3 : 2)]);
}

void MCP342x::MCP342x::setConfiguration(byte channel, int resolution, int mode, int pga)
{

    channel    &= 0b11;
    resolution &= 0b11;
    mode       &= 0b01;
    pga        &= 0b11;

    uint8_t cfgbyte = 0;

    _resolution = resolution;
    _PGA = pga;
    uint32_t divisor = 1;
    _LSB = 2048000000 / (divisor << (resolutionConvert[_resolution] - 1));

    cfgbyte |= (channel & 0x3) << 5;
    cfgbyte |= (mode & 0x1) << 4;
    cfgbyte |= (resolution & 0x3) << 2;
    cfgbyte |= pga & 0x3;

#if 0
    Wire.beginTransmission(_adresse);
    Wire.write(cfgbyte);
    Wire.endTransmission();
#endif
}

void MCP342x::MCP342x::newConversion()
{
    uint8_t cfgbyte = getConfiguration();

#if 0
    Wire.beginTransmission(_adresse);
    Wire.write(cfgbyte |= 128);
    Wire.endTransmission();
#endif
}

bool MCP342x::MCP342x::isConversionFinished()
{
    uint8_t result = !(getConfiguration() & 0b10000000);
    return result;
}

void MCP342x::MCP342x::getRawDatas(uint8_t buffer[4])
{
    for(int i = 0; i < 4; ++i)
    {
        buffer[i] = _buffer[i];
    }
}

int32_t MCP342x::MCP342x::measure()
{
    union resultUnion
    {
        uint8_t asBytes[4];
        int32_t asLong;
    } result;

    while(isConversionFinished() == 0);

    if(_resolution == RESOLUTION_18_BITS)
    {
        result.asBytes[3] = (_buffer[0] & 0x80) ? 0xFF : 0x00;
        result.asBytes[2] = _buffer[0];
        result.asBytes[1] = _buffer[1];
        result.asBytes[0] = _buffer[2];
    }
    else
    {
        result.asBytes[3] = (_buffer[0] & 0x80) ? 0xFF : 0x00;
        result.asBytes[2] = (_buffer[0] & 0x80) ? 0xFF : 0x00;
        result.asBytes[1] = _buffer[0];
        result.asBytes[0] = _buffer[1];
    }

    return (result.asLong * _LSB / PGAConvert[_PGA]);
}
