/**
 ********************************************************************************
 * @file    DataBrokerMessageTypes.hpp
 * @author  Shivam Desai
 * @date    Nov 23, 2024
 * @brief
 ********************************************************************************
 */

#ifndef DATA_BROKER_MESSAGE_TYPES_HPP_
#define DATA_BROKER_MESSAGE_TYPES_HPP_

/************************************
 * INCLUDES
 ************************************/
#include <stdint.h>
#include <string>

/************************************
 * MACROS AND DEFINES
 ************************************/

/************************************
 * TYPEDEFS
 ************************************/
enum class DataBrokerMessageTypes : uint8_t {
  INVALID = 0,
  IMU32G_DATA,
  IMU16G_DATA,
  GPS_DATA,
  BARO07_DATA,
  BARO11_DATA,
  FILTER_DATA,
  MAG_DATA,
};

namespace DataBrokerMessageType {
/************************************
 * CLASS DEFINITIONS
 ************************************/

/************************************
 * FUNCTION DECLARATIONS
 ************************************/
std::string ToString(DataBrokerMessageTypes messageType);

inline std::string ToString(DataBrokerMessageTypes messageType) {
  switch (messageType) {
    case DataBrokerMessageTypes::IMU32G_DATA: {
      std::string type{"IMU32G_DATA"};
      return type;
    }
    case DataBrokerMessageTypes::IMU16G_DATA: {
          std::string type{"IMU16G_DATA"};
          return type;
        }
    case DataBrokerMessageTypes::GPS_DATA: {
          std::string type{"GPS_DATA"};
          return type;
        }
    case DataBrokerMessageTypes::BARO07_DATA: {
          std::string type{"BARO07_DATA"};
          return type;
        }
    case DataBrokerMessageTypes::BARO11_DATA: {
              std::string type{"BARO11_DATA"};
              return type;
        }
    case DataBrokerMessageTypes::FILTER_DATA: {
          std::string type{"FILTER_DATA"};
          return type;
    }
    case DataBrokerMessageTypes::MAG_DATA: {
          std::string type{"MAG_DATA"};
          return type;
        }
    case DataBrokerMessageTypes::INVALID:
      [[fallthrough]];
    default: {
      std::string type{"INVALID"};
      return type;
    }
  }
}

}  // namespace DataBrokerMessageType

#endif /* DATA_BROKER_MESSAGE_TYPES_HPP_ */
