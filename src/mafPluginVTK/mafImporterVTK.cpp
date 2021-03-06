/*
 *  mafImporterVTK.cpp
 *  mafPluginVTK
 *
 *  Created by Paolo Quadrani on 04/04/11.
 *  Copyright 2011 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#include "mafImporterVTK.h"

#include <vtkDataSetReader.h>

using namespace mafPluginVTK;
using namespace mafResources;

mafImporterVTK::mafImporterVTK(const QString code_location) : mafImporter(code_location) {
    m_Reader = vtkDataSetReader::New();
    setProperty("wildcard", mafTr("VTK Files (*.vtk)"));
}

mafImporterVTK::~mafImporterVTK() {
    m_Reader->Delete();
}

void mafImporterVTK::execute() {
    QMutex mutex(QMutex::Recursive);
    QMutexLocker locker(&mutex);

    m_Status = mafOperationStatusExecuting;
    
    if (!filename().isEmpty()) {
        checkImportFile();
        if (m_Status == mafOperationStatusAborted) {
            cleanup();
            return;
        }
    }
    
    m_Reader->SetFileName(filename().toAscii().constData());
    m_Reader->Update();
    
    m_ImportedData = m_Reader->GetOutputPort();
    m_ImportedData.setExternalCodecType("VTK");
    m_ImportedData.setClassTypeNameFunction(vtkClassTypeNameExtract);
    
    //here set the mafDataset with the vtk data
    importedData(&m_ImportedData);
    
    //set the default boundary algorithm for vtk vme
    mafResources::mafVME * vme = qobject_cast<mafResources::mafVME *> (this->m_Output);
    vme->dataSetCollection()->itemAtCurrentTime()->setBoundaryAlgorithmName("mafPluginVTK::mafDataBoundaryAlgorithmVTK");
    
    emit executionEnded();
}

