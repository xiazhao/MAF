/*
 *  mafUILoaderQt.cpp
 *  mafGUI
 *
 *  Created by Daniele Giunchi on 29/10/10.
 *  Copyright 2010 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#include "mafUILoaderQt.h"
#include <mafProxy.h>

using namespace mafCore;
using namespace mafEventBus;
using namespace mafGUI;

mafUILoaderQt::mafUILoaderQt(const QString code_location) : mafUILoader(code_location) {
}

mafUILoaderQt::~mafUILoaderQt() {
}

void mafUILoaderQt::uiLoad(const QString &fileName) {
    QFile file(fileName.toAscii());
    file.open(QFile::ReadOnly);
    mafProxy<QWidget> *arg = new mafProxy<QWidget>();
    *arg = m_UILoaderQt.load(&file);
    file.close();

    mafProxyInterface *gui = arg;
    mafEventArgumentsList list;
    list.append(mafEventArgument(mafCore::mafProxyInterface *, gui));
    mafEventBusManager::instance()->notifyEvent("maf.local.gui.uiloaded", mafEventTypeLocal, &list);
}
