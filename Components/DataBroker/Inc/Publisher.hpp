/**
 ********************************************************************************
 * @file    Publisher.hpp
 * @author  Shivam Desai
 * @date    Nov 23, 2024
 * @brief
 ********************************************************************************
 */

#ifndef PUBLISHER_HPP_
#define PUBLISHER_HPP_

/************************************
 * INCLUDES
 ************************************/
#include <DataBrokerMessageTypes.hpp>
#include <stdint.h>
#include <array>
#include "Task.hpp"
#include "Subscriber.hpp"
#include "SystemDefines.hpp"
#include "SensorDataTypes.hpp"

/************************************
 * MACROS AND DEFINES
 ************************************/

/************************************
 * TYPEDEFS
 ************************************/

/************************************
 * CLASS DEFINITIONS
 ************************************/
template<typename T, uint8_t MaxSubscribers = 5>
class Publisher {
public:
	// Constructor
	Publisher(DataBrokerMessageTypes messageType) {
		publisherMessageType = messageType;
	}

	// subscribe
	bool Subscribe(Task *taskToSubscribe) {
		// Check if subscriber already exists
		for (Subscriber &subscriber : subscribersList) {
			if (subscriber.getSubscriberTaskHandle() == taskToSubscribe) {
				return true;
			}
		}

		// Add the subscriber
		for (Subscriber &subscriber : subscribersList) {
			if (subscriber.getSubscriberTaskHandle() == nullptr) {
				subscriber.Init(taskToSubscribe);
				return true;
			}
		}

		SOAR_ASSERT(true, "Failed to add subscriber\n");
		return false;
	}

	// subscribe
	bool Subscribe(Task *taskToSubscribe, Queue *queueToSubscribe) {
		// Check if subscriber already exists
		for (Subscriber &subscriber : subscribersList) {
			if (subscriber.getSubscriberTaskHandle() == taskToSubscribe) {
				return true;
			}
		}

		// Add the subscriber
		for (Subscriber &subscriber : subscribersList) {
			if (subscriber.getSubscriberTaskHandle() == nullptr) {
				subscriber.Init(taskToSubscribe, queueToSubscribe);
				return true;
			}
		}

		SOAR_ASSERT(true, "Failed to add subscriber\n");
		return false;
	}

	// unsubscribe
	bool Unsubscribe(Task *taskToUnsubscribe) {
		for (Subscriber &subscriber : subscribersList) {
			if (subscriber.getSubscriberTaskHandle() == taskToUnsubscribe) {
				subscriber.Delete();
				return true;
			}
		}

		SOAR_ASSERT(true, "Subscriber not Deleted\n");
		return false;
	}

	// publish
	void Publish(T *dataToPublish) {
		for (const Subscriber &subscriber : subscribersList) {
			if (subscriber.getSubscriberTaskHandle() != nullptr) {

				// if sensorId is -1, that subscriber wants all sensor data. -1 is the default value.
				if (subscriber.getSensorId() != -1) {
					if constexpr (std::is_same_v<T, IMUData> || std::is_same_v<T, BaroData>) {
						// if not -1, the subscriber only wants data from one sensor. If the id does not match, continue without publishing.
						if (dataToPublish->id != subscriber.getSensorId()) {
							continue;
						}
					}
				}

				// create command
				uint16_t messageType =
						static_cast<uint16_t>(publisherMessageType);

				Command brokerData(DATA_BROKER_COMMAND, messageType);

				uint8_t *messsageData =
						reinterpret_cast<uint8_t*>(dataToPublish);

				// copy data to command
				brokerData.CopyDataToCommand(messsageData, sizeof(T));

				// We should overwrite queues of length 1 rather than sending. This is NOT contractually defined anywhere and we should change it later.
				uint8_t queueDepth =
						subscriber.getSubscriberQueueHandle()->GetQueueDepth();
				if (queueDepth == 1) {
					subscriber.getSubscriberQueueHandle()->Overwrite(
							brokerData);
				} else {
					subscriber.getSubscriberQueueHandle()->Send(brokerData);
				}

			}
		}
	}

	DataBrokerMessageTypes GetPublisherMessageType() {
		return publisherMessageType;
	}

private:
	// list of subscribers
	Subscriber subscribersList[MaxSubscribers] = { };

	// message type for system routing
	DataBrokerMessageTypes publisherMessageType =
			DataBrokerMessageTypes::INVALID;
};

/************************************
 * FUNCTION DECLARATIONS
 ************************************/

#endif /* PUBLISHER_HPP_ */
