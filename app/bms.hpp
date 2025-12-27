/*
 * bms.hpp
 *
 *  Created on: Jul 12, 2025
 *      Author: ruslan
 */

#pragma once

#include "../third_party/MCP342x.h"

namespace BMS{

enum BMS_status {UPPER_OPEN, LOWER_OPEN, ALL_OPEN, ALL_CLOSE};

class Controller
{
public:
    Controller();
    ~Controller();
    void DoBalance();
    
private:
    BMS_status status;
    MCP342x::MCP342x mcp3422;
};

};
