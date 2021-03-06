/*
 *  mafVTKParametricSurfaceCube.h
 *  mafPluginVTK
 *
 *  Created by Roberto Mucci on 19/01/11.
 *  Copyright 2011 B3C.s All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#ifndef MAFVTKPARAMETRICSURFACECUBE_H
#define MAFVTKPARAMETRICSURFACECUBE_H

// Includes list
#include "mafPluginVTKDefinitions.h"
#include "mafVTKParametricSurface.h"

// Foundation Class forwarding list
class vtkAlgorithmOutput;
class vtkCubeSource;

namespace mafPluginVTK {

/**
Class name: mafVTKParametricSurfaceCube
This class represent a VTK cube surface with modificable parametrs.
*/
class MAFPLUGINVTKSHARED_EXPORT mafVTKParametricSurfaceCube : public mafPluginVTK::mafVTKParametricSurface {
    Q_OBJECT
    Q_PROPERTY(double cubeXLength READ cubeXLength WRITE setCubeXLength)
    Q_PROPERTY(double cubeYLength READ cubeYLength WRITE setCubeYLength)
    Q_PROPERTY(double cubeZLength READ cubeZLength WRITE setCubeZLength)
    /// typedef macro.
    mafSuperclassMacro(mafPluginVTK::mafVTKParametricSurface);

public:
    /// Object constructor.
    mafVTKParametricSurfaceCube(const QString code_location = "");

public slots:

    /// Update surface with parameters.
    /*virtual*/ void updateSurface();

protected:
    /// Object destructor.
    /*virtual*/ ~mafVTKParametricSurfaceCube();

private slots:
    /// Set the X Length for the parametric cube.
    void setCubeXLength(double XLength);

    /// Set the Y Length for the parametric cube.
    void setCubeYLength(double YLength);

    /// Set the Z Length for the parametric cube.
    void setCubeZLength(double ZLength);

    /// Get the X Length for the parametric cube.
    double cubeXLength();

    /// Get the Y Length for the parametric cube.
    double cubeYLength();

    /// Get the Z Length for the parametric cube.
    double cubeZLength();

private:
    vtkCubeSource *m_CubeSource; ///< Polydata representig a cube.

    double m_CubeXLength; ///< Length X of the cube;
    double m_CubeYLength; ///< Length Y of the cube;
    double m_CubeZLength; ///< Length Z of the cube;
};

/////////////////////////////////////////////////////////////
// Inline methods
/////////////////////////////////////////////////////////////

inline void mafVTKParametricSurfaceCube::setCubeXLength(double XLength){
    m_CubeXLength = XLength;
}

inline void mafVTKParametricSurfaceCube::setCubeYLength(double YLength){
    m_CubeYLength = YLength;
}

inline void mafVTKParametricSurfaceCube::setCubeZLength(double ZLength){
    m_CubeZLength = ZLength;
}

inline double mafVTKParametricSurfaceCube::cubeXLength(){
    return m_CubeXLength;
}

inline double mafVTKParametricSurfaceCube::cubeYLength(){
    return m_CubeYLength;
}

inline double mafVTKParametricSurfaceCube::cubeZLength(){
    return m_CubeZLength;
}

}

#endif // MAFVTKPARAMETRICSURFACECUBE_H

