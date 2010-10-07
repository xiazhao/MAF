/*
 *  mafViewManager.h
 *  mafResources
 *
 *  Created by Paolo Quadrani on 30/12/09.
 *  Copyright 2009 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#ifndef MAFVIEWMANAGER_H
#define MAFVIEWMANAGER_H

#include "mafResourcesDefinitions.h"

namespace mafResources {

// Class forwarding list
class mafView;
class mafResource;
class mafVME;

/**
Class name: mafViewManager
This class provides the manager class for MAF3 views. The IDs are:
- maf.local.resources.view.create allows to create a new View.
- maf.local.resources.view.destroy allows to destroy a given View.
- maf.local.resources.view.select allows to select the active View on which show/hide VMEs.
- maf.local.resources.view.selected allows to retrieve the current selected View.
- maf.local.resources.view.show allow to show/hide a given VME in the selected View.
*/
class MAFRESOURCESSHARED_EXPORT mafViewManager : public mafCore::mafObjectBase {
    Q_OBJECT
    /// typedef macro.
    mafSuperclassMacro(mafCore::mafObjectBase);

public:
    /// Return an instance of the Manager
    static mafViewManager *instance();

    /// Destroy the singleton instance. To be called at the end of the application.
    void shutdown();

    /// Return the list of created views.
//    mafResourceList *createdViewList();

signals:
    /// Return the selected view
    mafCore::mafObjectBase *selectedViewSignal();

    /// Signal which allow to keep track of the selected view.
    void selectViewSignal(mafCore::mafObjectBase *view);

    /// Signal which allow to show/hide the given vme passed as argument.
    void vmeShowSignal(mafCore::mafObjectBase *vme, bool show = true);

    /// Signal which allow to remove the view from the manager.
    void destroyViewSignal(mafCore::mafObjectBase *view);

    /// Allow to cdreate a new mafView given the type name as string. Return the pointer to the created view on success.
    mafCore::mafObjectBase *createViewSignal(mafString view_type);

private slots:
    /// Return the selected view
    mafCore::mafObjectBase *selectedView();

    /// Allow to keep track of the selected view.
    void selectView(mafCore::mafObjectBase *view);

    /// Allow to show/hide the given vme passed as argument.
    void vmeShow(mafCore::mafObjectBase *vme, bool show = true);

    /// Remove the view from the manager.
    void destroyView(mafCore::mafObjectBase *view);

    /// Allow to cdreate a new mafView given the type name as string. Return the pointer to the created view on success.
    mafCore::mafObjectBase *createView(mafString view_type);

    /// Method called when a view has been destroyed (by someone else).
    void viewDestroyed();

private:
    /// Object constructor.
    mafViewManager(const mafString code_location = "");

    /// Object destructor
    /*virtual*/ ~mafViewManager();

    /// create IDs and connect signals with slots for View create, destroy, select and VME show.
    void initializeConnections();

    /// Add the created view to the view list.
    void addViewToCreatedList(mafView *v);

    /// Remove the given view from the created list
    void removeView(mafView *view);

    mafResourceList m_CreatedViewList; ///< List of created views.
    mafView *m_SelectedView; ///< Keep trak of the current selected view.
};

/////////////////////////////////////////////////////////////
// Inline methods
/////////////////////////////////////////////////////////////

//inline mafResourceList *mafViewManager::createdViewList() {
//    return &m_CreatedViewList;
//}

inline mafCore::mafObjectBase *mafViewManager::selectedView() {
    return (mafCore::mafObjectBase *)m_SelectedView;
}

} // namespace mafResources

#endif // MAFVIEWMANAGER_H
