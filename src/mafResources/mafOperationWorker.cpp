/*
 *  mafOperationWorker.cpp
 *  mafResources
 *
 *  Created by Paolo Quadrani on 04/03/11.
 *  Copyright 2011 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#include "mafOperationWorker.h"
#include "mafOperation.h"

using namespace mafCore;
using namespace mafResources;

mafOperationWorker::mafOperationWorker() {
}

mafOperationWorker::mafOperationWorker(mafOperation *op) :  m_Operation(op) {
    m_Operation->retain();
    m_Operation->moveToThread(this);
    initializeWorkflow();
}

mafOperationWorker::~mafOperationWorker() {
    qDebug() << "Destroying operation " << m_Operation->objectName() << " ref: " << m_Operation->referenceCount();
    mafDEL(m_Operation);
}

void mafOperationWorker::initializeWorkflow() {
    connect(m_Operation, SIGNAL(executionEnded()), this, SIGNAL(workDone()), Qt::DirectConnection);

    connect(this, SIGNAL(workAborted()), m_Operation, SLOT(abort()), Qt::DirectConnection);
    connect(this, SIGNAL(workAborted()), m_Operation, SLOT(terminate()), Qt::DirectConnection);
}

void mafOperationWorker::run() {
   // chiamare execute op
    m_Operation->execute();
}

void mafOperationWorker::abortExecution() {
    if ( m_Operation->canAbort() ) {
        emit workAborted();
    }
}
