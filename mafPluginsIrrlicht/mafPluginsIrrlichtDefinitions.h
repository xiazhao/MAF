/*
 *  mafPluginsIrrlichtDefinitions.h
 *  mafPluginsIrrlicht
 *
 *  Created by Daniele Giunchi on 30/12/09.
 *  Copyright 2009 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#ifndef MAFPLUGINSIRRLICHTDEFINITIONS_H
#define MAFPLUGINSIRRLICHTDEFINITIONS_H


// Includes list
#include "mafPluginsIrrlicht_global.h"
#include <mafCoreRegistration.h>
#include <mafResourcesRegistration.h>
#include <mafResourcesDefinitions.h>
#include <mafContainer.h>
#include "irrlicht.h"

struct IrrlichtDeviceWrapper {
    IrrlichtDeviceWrapper(): m_Device(NULL){};
    IrrlichtDeviceWrapper(irr::IrrlichtDevice *device): m_Device(device){};
    irr::IrrlichtDevice *m_Device;
};
typedef IrrlichtDeviceWrapper * IrrlichtDeviceWrapperPointer;


Q_DECLARE_METATYPE(IrrlichtDeviceWrapperPointer)

#endif // MAFPLUGINSIRRLICHTDEFINITIONS_H