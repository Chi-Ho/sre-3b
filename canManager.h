#ifndef _CANMANAGER_H
#define _CANMANAGER_H

#include "IO_Driver.h" 
#include "IO_CAN.h"

#include "avlTree.h"
#include "motorController.h"
#include "bms.h"
#include "wheelSpeeds.h"

typedef enum { CAN0_HIPRI, CAN1_LOPRI } CanChannel;

typedef struct _CanManager CanManager;

typedef struct _CanMessageNode CanMessageNode;

//Note: Sum of messageLimits must be < 128 (hardware only does 128 total messages)
CanManager* CanManager_new(ubyte2 can0_busSpeed, ubyte1 can0_read_messageLimit, ubyte1 can0_write_messageLimit
                         , ubyte2 can1_busSpeed, ubyte1 can1_read_messageLimit, ubyte1 can1_write_messageLimit
                         , ubyte2 defaultSendDelayMs);
IO_ErrorType CanManager_send(CanManager* me, CanChannel channel, IO_CAN_DATA_FRAME canMessages[], ubyte1 canMessageCount);

//Reads and distributes can messages to their appropriate subsystem objects so they can updates themselves
void CanManager_read(CanManager* me, CanChannel channel, MotorController* mcm, BatteryManagementSystem* bms);

void canOutput_sendSensorMessages(CanManager* me);
void canOutput_sendMCUControl(CanManager* me, MotorController* mcm, bool sendEvenIfNoChanges);
void canOutput_sendDebugMessage(CanManager* me, TorqueEncoder* tps, BrakePressureSensor* bps, MotorController* mcm, WheelSpeeds* wss, SafetyChecker* sc);

#endif // _CANMANAGER_H is defined