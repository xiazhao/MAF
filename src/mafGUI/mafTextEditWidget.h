/*
 *  mafTextEditWidget.h
 *  mafGUI
 *
 *  Created by Daniele Giunchi on 14/01/11.
 *  Copyright 2010 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#ifndef MAFTEXTEDITWIDGET_H
#define MAFTEXTEDITWIDGET_H

#include "mafGUIDefinitions.h"

namespace mafGUI {
/**
    Class Name: mafTextEditWidget
    This class extend functionalities of a text normal editor or browser:
    - add syntax highlighting
*/
class MAFGUISHARED_EXPORT mafTextEditWidget : public QWidget {
    Q_OBJECT
    
public:
    /// Object constructor.
    mafTextEditWidget(QWidget *parent = 0);

    /// Overloaded object constructor
    mafTextEditWidget(QSyntaxHighlighter *highlighter, QWidget *parent = 0);

    /// Object destructor.
    virtual ~mafTextEditWidget();

    /// Set the highlighter to the text widget
    void setHighlighter(QSyntaxHighlighter *highlighter);

    /// enable/disable editing
    void enableEditing(bool enable);

    /// load Highlight Dictionary from CSV file
    void loadDictionaryFromCSV(const QString &csvFile);

    /// append Text in the area.
    void append(const QString text);

public slots:
    /// clear text area.
    void clear();

    /// find text.
    void find(QString textToFind);
    
signals:
    /// Signal needed to update the text into the Text Widget.
    void updateText(const QString text);

private:
    /// set the layout of this composite widget
    void initialize();

    QTextEdit *m_TextEditor; ///< text editor widget in which browse or edit text.
    QSyntaxHighlighter *m_Highlighter; ///< syntax highlighter to apply on text editor.

    // GUARDARE l'esempio qcompleter!!

};

} // namespace mafGUI

#endif // MAFTEXTEDITWIDGET_H
