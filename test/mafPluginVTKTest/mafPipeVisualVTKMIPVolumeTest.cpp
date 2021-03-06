/*
 *  mafPipeVisualVTKMIPVolumeTest.cpp
 *  mafPluginVTK
 *
 *  Created by Daniele Giunchi on 24/06/11.
 *  Copyright 2011 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#include <mafTestSuite.h>
#include <mafCoreSingletons.h>
#include <mafEventBusManager.h>
#include <mafPipeVisualVTKMIPVolume.h>
#include <mafDataBoundaryAlgorithmVTK.h>
#include <mafResourcesRegistration.h>
#include <mafPipeVisual.h>
#include <mafProxy.h>
#include <mafPluginManager.h>
#include <mafPlugin.h>
#include <vtkDataSetReader.h>
#include <vtkSmartPointer.h>

#include <mafVTKWidget.h>

#include <vtkImageData.h>
#include <vtkActor.h>
#include <vtkSphereSource.h>
#include <vtkAlgorithmOutput.h>

// render window stuff
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#ifdef WIN32
    #define TEST_LIBRARY_NAME "mafPluginVTK.dll"
#else
  #ifdef __APPLE__
    #define TEST_LIBRARY_NAME "mafPluginVTK.dylib"
  #else
    #define TEST_LIBRARY_NAME "mafPluginVTK.so"
  #endif
#endif

using namespace mafCore;
using namespace mafEventBus;
using namespace mafResources;
using namespace mafPluginVTK;


/**
 Class name: mafPipeVisualVTKMIPVolumeTest
 This class import a vtk structuredpoints mafPipeVisualVTKMIPVolume
 */

//! <title>
//mafPipeVisualVTKMIPVolume
//! </title>
//! <description>
//mafPipeVisualVTKMIPVolume is a visual pipe used to render VTK volume.
//It takes a mafDataSet as input and returns a mafProxy<vtkActor>.
//! </description>

class mafPipeVisualVTKMIPVolumeTest : public QObject {
    Q_OBJECT

private slots:
    /// Initialize test variables
    void initTestCase() {
        mafMessageHandler::instance()->installMessageHandler();
        mafResourcesRegistration::registerResourcesObjects();
        mafRegisterObjectAndAcceptBind(mafPluginVTK::mafPipeVisualVTKMIPVolume)

        m_RenderWidget = new mafVTKWidget();
        
        m_VTKFile = "/Users/danielegiunchi/Desktop/sample/CropTestVolumeSP.vtk";
        
        // Import a vtk volume.
        m_Reader = vtkDataSetReader::New();
        m_Reader->SetFileName(m_VTKFile.toAscii().constData());
        m_Reader->Update();
        
        //! <snippet>
        //// Create a container with the outputPort of a vtkCubeSource
        //// m_DataSourceContainer is the container of type vtkAlgorithmOutput
        //// to "wrap" the 'vtkCubeSource' of type vtkPolyData just simply use the code below.
        m_DataSourceContainer.setClassTypeNameFunction(vtkClassTypeNameExtract);
        m_DataSourceContainer = m_Reader->GetOutputPort(0);

        //Insert data into VME
        m_VME = mafNEW(mafResources::mafVME);
        m_DataSet = mafNEW(mafResources::mafDataSet);
        mafDataBoundaryAlgorithmVTK *boundaryAlgorithm;
        boundaryAlgorithm = mafNEW(mafDataBoundaryAlgorithmVTK);
        m_DataSet->setBoundaryAlgorithm(boundaryAlgorithm);
        m_DataSet->setDataValue(&m_DataSourceContainer);
        m_VME->dataSetCollection()->insertItem(m_DataSet, 0);
        //! </snippet>
    }

    /// Cleanup test variables memory allocation.
    void cleanupTestCase() {
        mafDEL(m_DataSet);
        //here delete vtk stuff
        m_Reader->Delete();
        mafDEL(m_VME);
        mafMessageHandler::instance()->shutdown();
        delete m_RenderWidget;

    }

    /// Test the creation of the vtkActor
    void updatePipeTest();

    /// Test the creation of the vtkActor
    void updatePipeTestFromPlugIn();

private:
    mafVME *m_VME; ///< Contain the only item vtkPolydata representing a surface.
    mafResources::mafDataSet *m_DataSet;
    mafProxy<vtkAlgorithmOutput> m_DataSourceContainer; ///< Container of the Data Source
    vtkDataSetReader *m_DataSetReader; /// reader used for import
    vtkDataSetReader *m_Reader;
    QString m_VTKFile; ///< file name of the vtk test
    QObject *m_RenderWidget; /// renderer widget
};

void mafPipeVisualVTKMIPVolumeTest::updatePipeTest() {
    vtkRenderer *renderer = vtkRenderer::New();
    vtkRenderWindow *renWin = ((mafVTKWidget*)m_RenderWidget)->GetRenderWindow();

    mafPipeVisualVTKMIPVolume *pipe;
    pipe = mafNEW(mafPluginVTK::mafPipeVisualVTKMIPVolume);
    pipe->setInput(m_VME);
    pipe->setGraphicObject(m_RenderWidget);
    pipe->updatePipe();

    // Get the vtkActor from the visual pipe
    // And assign to a mafProxy
    mafProxy<vtkActor> *actor = mafProxyPointerTypeCast(vtkActor, pipe->output());
    QVERIFY(actor != NULL);

    renWin->AddRenderer(renderer);
    
    // Connect the actor (contained into the container) with the renderer.
    renderer->AddActor(*actor);

    renderer->SetBackground(0.1, 0.1, 0.1);
    renWin->SetSize(640, 480);
    renWin->SetPosition(400,0);

    renWin->Render();
    //iren->Start();
    QTest::qSleep(2000);

    renderer->Delete();
    pipe->setGraphicObject(NULL);
    mafDEL(pipe);
}

void mafPipeVisualVTKMIPVolumeTest::updatePipeTestFromPlugIn() {
    mafPluginManager *pluginManager = mafPluginManager::instance();
    QString pluginName = TEST_LIBRARY_NAME;

    // Load the library containing the visual pipe that I want to plug-in.
    pluginManager->loadPlugin(pluginName);

    // Dump the plug-in information.
    mafPluginInfo info = pluginManager->pluginInformation(pluginName);
    qDebug() << "Plug-in Information:";
    qDebug() << "Varsion: " << info.m_Version;
    qDebug() << "Author: " << info.m_Author;
    qDebug() << "Vendor: " << info.m_Vendor;
    qDebug() << "Description: " << info.m_Description;

    QStringList binding_class_list;
    binding_class_list = mafCoreRegistration::acceptObject(m_VME);
    int num = binding_class_list.count();
    QVERIFY(num != 0);

    QString check("mafPluginVTK::mafPipeVisualVTKMIPVolume");
    QVERIFY(binding_class_list.contains(check));


    //! <snippet>
    mafPipeVisual *visualPipe = (mafPipeVisual *)mafNEWFromString("mafPluginVTK::mafPipeVisualVTKMIPVolume");
    visualPipe->setInput(m_VME);
    visualPipe->setGraphicObject(m_RenderWidget);
    visualPipe->updatePipe();
    //! </snippet>

    //! <snippet>
    mafProxy<vtkActor> *actor = mafProxyPointerTypeCast(vtkActor, visualPipe->output());
    //! </snippet>
    
    vtkRenderWindow *m_RenWin = vtkRenderWindow::New();
    vtkRenderer *m_Renderer = vtkRenderer::New();
    m_Renderer->AddActor(*actor);
    vtkRenderWindowInteractor *m_Iren = vtkRenderWindowInteractor::New();
    m_RenWin->AddRenderer(m_Renderer);
    m_Iren->SetRenderWindow(m_RenWin);
    
    m_Renderer->SetBackground(1.0, 1.0, 1.0);
    m_RenWin->SetSize(640, 480);
    m_RenWin->SetPosition(200,0);

    m_RenWin->Render();
    //iren->Start();
    QTest::qSleep(2000);

    //Change scalarVisibility flag
    m_Iren->Delete();
    m_RenWin->Delete();
    m_Renderer->Delete();
    mafDEL(visualPipe);

    pluginManager->shutdown();
}

//MAF_REGISTER_TEST(mafPipeVisualVTKMIPVolumeTest);
#include "mafPipeVisualVTKMIPVolumeTest.moc"
