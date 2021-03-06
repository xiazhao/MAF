/*
 *  mafTreeItemSceneNodeDelegate.cpp
 *  mafGUI
 *
 *  Created by Roberto Mucci on 01/03/11.
 *  Copyright 2011 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#ifndef MAFTREEITEMSCENENODEDELEGATE_H
#define MAFTREEITEMSCENENODEDELEGATE_H

// Includes list
#include "mafGUIDefinitions.h"
#include <QStyledItemDelegate>
#include <QModelIndex>
#include <QObject>



namespace mafGUI {
/**
Class Name: mafTreeItemSceneNodeDelegate
This class is responsible for display and editing items of the tree model.
*/

class MAFGUISHARED_EXPORT mafTreeItemSceneNodeDelegate : public QStyledItemDelegate {
Q_OBJECT
public:
    /// Object constructor.
    /*explicit*/ mafTreeItemSceneNodeDelegate(QObject *parent = 0);

    /// Returns the widget used to edit the item specified by index for editing.
    /*virtual*/ QWidget *createEditor( QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const;

    /// Sets the contents of the given editor to the data for the item at the given index.
    /*virtual */ void setEditorData( QWidget * editor, const QModelIndex & index ) const;

    /// Gets data from the editor widget and stores it in the specified model at the item index.
    /*virtual */ void setModelData ( QWidget * editor, QAbstractItemModel * model, const QModelIndex & index ) const;

    /// Renders the delegate using the given painter and style option for the item specified by index.
    /*virtual */ void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    /// Whenever an event occurs, this function is called with the event model option and the index that corresponds to the item being edited.
    /*virtual*/ bool editorEvent ( QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index );

public slots:

private:
    /// Return the QObject corrisponding to index.
    QObject *objFromIndex(const QModelIndex &index) const;

    bool m_isSceneNode;
};

}

#endif // MAFTREEITEMSCENENODEDELEGATE_H
