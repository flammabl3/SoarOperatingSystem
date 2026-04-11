/**
 ********************************************************************************
 * @file    Subscriber.hpp
 * @author  Shivam Desai
 * @date    Nov 23, 2024
 * @brief
 ********************************************************************************
 */

#ifndef SUBSCRIBER_HPP_
#define SUBSCRIBER_HPP_

/************************************
 * INCLUDES
 ************************************/
#include "Task.hpp"
#include "SystemDefines.hpp"

/************************************
 * MACROS AND DEFINES
 ************************************/

/************************************
 * TYPEDEFS
 ************************************/

/************************************
 * CLASS DEFINITIONS
 ************************************/
class Subscriber {
 public:
  void Init(Task* subscriberTaskHandle) {
    if (taskHandle != nullptr || taskQueue != nullptr) {
      SOAR_ASSERT(false, "You cannot overwrite a subscriber");
      return;
    }
    taskHandle = subscriberTaskHandle;
    taskQueue = taskHandle->GetEventQueue();
  }

  // If a pointer to a specified Queue is given, taskQueue will
  // reference queueToSubscribe rather than the Task's getEventQueue();
  void Init(Task* subscriberTaskHandle, Queue* queueToSubscribe) {
    if (taskHandle != nullptr || taskQueue != nullptr) {
      SOAR_ASSERT(false, "You cannot overwrite a subscriber");
      return;
    }
    taskHandle = subscriberTaskHandle;
    taskQueue = queueToSubscribe;
  }

  // Filter data by ID, for data types with multiple associated sensors.
  void Init(Task* subscriberTaskHandle, Queue* queueToSubscribe, uint8_t sensorId) {
    if (taskHandle != nullptr || taskQueue != nullptr) {
      SOAR_ASSERT(false, "You cannot overwrite a subscriber");
      return;
    }
    taskHandle = subscriberTaskHandle;
    taskQueue = queueToSubscribe;
    sensorId = sensorId;
  }

  void Delete() {
    taskHandle = nullptr;
    taskQueue = nullptr;
    sensorId = 255;
  }

  inline const Task* getSubscriberTaskHandle() const { return taskHandle; }

  inline Queue* getSubscriberQueueHandle() const { return taskQueue; }

  inline uint8_t getSensorId() const { return sensorId; }

 private:
  Task* taskHandle = nullptr;
  Queue* taskQueue = nullptr;
  uint8_t sensorId = 255;
};

/************************************
 * FUNCTION DECLARATIONS
 ************************************/

#endif /* SUBSCRIBER_HPP_ */
