/*
 *  mafViewVTK.h
 *  mafResources
 *
 *  Created by Roberto Mucci on 20/03/10.
 *  Copyright 2009 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#ifndef MAFVIEWVTK_H
#define MAFVIEWVTK_H

// Includes list
#include "mafPluginVTKDefinitions.h"
#include <mafView.h>

// Class forwarding list
class vtkRenderer;

namespace mafPluginVTK {

class mafVTKWidget;

/**
 Class name: mafViewVTK
 This is the VTK MAF3 views.
 */
class MAFPLUGINVTKSHARED_EXPORT mafViewVTK : public mafResources::mafView {
    Q_OBJECT
    /// typedef macro.
    mafSuperclassMacro(mafResources::mafView);

public:
    /// Object constructor.
    mafViewVTK(const QString code_location = "");

    /// Crete view.
    /*virtual*/ void create();

    /// Remove scene node passed as argument.
    /*virtual*/ void removeSceneNode(mafResources::mafSceneNode *node);

    /// Show scene node passed as argument.
    /*virtual*/ void showSceneNode(mafResources::mafSceneNode *node, bool show = true);

    /// Update view.
    /*virtual*/ void updateView();
    
    /// Select a scene node.
    /*virtual*/ void selectSceneNode(mafResources::mafSceneNode *node, bool select);

protected:
    /// Object destructor.
    /* virtual */ ~mafViewVTK();
    
    /// factory method for creating scenenode VTK.
    /*virtual*/ mafResources::mafSceneNode *createSceneNode(mafResources::mafVME *vme);


private:
    //mafCore::mafProxy<mafPluginVTK::mafVTKWidget> m_Widget; ///< VTK Widget on which will be rendered the scene.
    mafVTKWidget *m_Widget; ///< VTK Widget on which will be rendered the scene.
    vtkRenderer *m_Renderer; ///< VTK render.
};

} //namespace mafPluginVTK

#endif // MAFVIEWVTK_H
