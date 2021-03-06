/*
 *  mafTreeWidget.cpp
 *  mafGUI
 *
 *  Created by Daniele Giunchi on 26/10/10.
 *  Copyright 2010 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#include "mafTreeWidget.h"
#include <QMenu>

using namespace mafGUI;

mafTreeWidget::mafTreeWidget(QWidget *parent) : QTreeView(parent) {
    m_ActionShow = new QAction(mafTr("Show"), this);
    m_ActionDelete = new QAction(mafTr("Delete"), this);
}

void mafTreeWidget::contextMenuEvent(QContextMenuEvent *e) {
    QList<QAction *> actions;
    if (this->indexAt(e->pos()).isValid()) {
        actions.append(m_ActionShow);
        actions.append(m_ActionDelete);
    }
    if (actions.count() > 0) {
        QMenu::exec(actions, e->globalPos());
    }
}
