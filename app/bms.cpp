/*
 * bms.cpp
 *
 *  Created on: Jul 12, 2025
 *      Author: ruslan
 */

#include "bms.hpp"

BMS::Controller::Controller()
{
    status = ALL_CLOSE;
}

void BMS::Controller::DoBalance()
{
    mcp3422.newConversion();
}
