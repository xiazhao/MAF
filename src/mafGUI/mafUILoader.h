/*
 *  mafUILoader.h
 *  mafGUI
 *
 *  Created by Daniele Giunchi on 29/10/10.
 *  Copyright 2010 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#ifndef MAFUILOADER_H
#define MAFUILOADER_H

// Includes list
#include "mafGUIDefinitions.h"
#include <mafObjectBase.h>
#include <mafProxyInterface.h>

namespace mafGUI {
/**
  Class Name: mafUILoader
  UILoader represents the interface class for loading graphical user interface from
  file (generally XML). It parse xml and instantiates at runtime graphical objects which
  can be attached to panels, windows etc...
  */
class MAFGUISHARED_EXPORT mafUILoader : public mafCore::mafObjectBase {
    Q_OBJECT
    /// typedef macro.
    mafSuperclassMacro(mafCore::mafObjectBase);

signals:
    /// signal for inform that the user interface has been loaded from file
    void uiLoadedSignal(mafCore::mafProxyInterface *guiWidget);

public:
    /// Object constructor.
    mafUILoader(const QString code_location = "");

    /// load from external file (generally an xml) the GUI
    virtual void uiLoad(const QString &fileName) = 0;

protected:
    /// Object destructor.
    /* virtual */ ~mafUILoader();
};

} //end namespace mafGUI

#endif // MAFUILOADER_H
