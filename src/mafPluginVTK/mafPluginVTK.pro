# -------------------------------------------------
# Project created by QtCreator 2010-02-15T12:35:58
# -------------------------------------------------
# QT -= gui
TARGET = mafPluginVTK
TEMPLATE = lib
CONFIG += create_prl
CONFIG += link_prl
win32:CONFIG += dll
DEFINES += mafPluginVTK_EXPORTS

SOURCES += mafDataBoundaryAlgorithmVTK.cpp \
    mafPluginRegistrator.cpp \
    mafPipeVisualVTKSurface.cpp \
    mafViewVTK.cpp \
    mafPipeDataImageThreshold.cpp \
    mafExternalDataCodecVTK.cpp \
    mafPipeVisualSelection.cpp \
    mafVTKWidget.cpp \
    mafVTKInteractorPicker.cpp \
    mafVTKParametricSurface.cpp \
    mafVTKParametricSurfaceSphere.cpp \
    mafVTKParametricSurfaceCube.cpp \
    mafVTKParametricSurfaceCone.cpp \
    mafVTKParametricSurfaceCylinder.cpp \
    mafVTKParametricSurfaceEllipsoid.cpp \
    mafOpParametricSurface.cpp

HEADERS += mafPluginVTK_global.h \
    mafPluginVTKDefinitions.h \
    mafPluginRegistrator.h \
    mafPipeVisualVTKSurface.h \
    mafViewVTK.h \
    mafPipeDataImageThreshold.h \
    mafExternalDataCodecVTK.h \
    mafPipeVisualSelection.h \
    mafDataBoundaryAlgorithmVTK.h \
    mafVTKWidget.h \
    mafVTKInteractorPicker.h \
    mafVTKParametricSurface.h \
    mafVTKParametricSurfaceSphere.h \
    mafVTKParametricSurfaceCube.h \
    mafVTKParametricSurfaceCone.h \
    mafVTKParametricSurfaceCylinder.h \
    mafVTKParametricSurfaceEllipsoid.h \
    mafOpParametricSurface.h

# mafDataPipeSurface.h \
include(../mafInstallModule.pri)
include(../mafImportVXL.pri)
include(../mafImportVTK.pri)
include(../mafImportQXMLRPC.pri)
include(../mafImportQtSoap.pri)
INCLUDEPATH += ../mafResources \
    ../mafEventBus \
    ../mafCore
LIBS += -L$$DESTDIR \
    -lmafResources$$BUILD_EXT \
    -lmafEventBus$$BUILD_EXT \
    -lmafCore$$BUILD_EXT

# install the mafplugin library (but leaving the generated library for test suite linking pourposes)
win32:QMAKE_POST_LINK += $$CP_CMD \
    $$DESTDIR\\$${LIB_PREFIX}$${TARGET}.dll \
    $$DESTDIR\\$${LIB_PREFIX}$${TARGET}.mafplugin
!macx:unix:QMAKE_POST_LINK += $$CP_CMD \
    $$DESTDIR/$${LIB_PREFIX}$${TARGET}.so.1.0.0 \
    $$DESTDIR/$${LIB_PREFIX}$${TARGET}.mafplugin
macx:QMAKE_POST_LINK += $$CP_CMD \
    $$DESTDIR/$${LIB_PREFIX}$${TARGET}.1.0.0.dylib \
    $$DESTDIR/$${LIB_PREFIX}$${TARGET}.mafplugin

system($$CP_CMD $$quote($$_PRO_FILE_PWD_/mafOpParametricSurface.ui) $$DESTDIR)