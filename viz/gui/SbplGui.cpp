#include "SbplGui.h"
#include <QFileDialog>
#include <QPushButton>
#include <thread>
#include <boost/filesystem.hpp>
#include <boost/archive/binary_iarchive.hpp>


SbplGui::SbplGui(): QObject()
{
    setupUI();
    setupSbpl();
}

void SbplGui::setupUI()
{
    widget = new vizkit3d::Vizkit3DWidget();
    widget->setCameraManipulator(vizkit3d::ORBIT_MANIPULATOR);
    widget->addPlugin(&splineViz);
    widget->addPlugin(&gridViz);

    splineViz.setPluginEnabled(true);
    gridViz.setPluginEnabled(true);

    QVBoxLayout* layout = new QVBoxLayout();    
       
    layout->addWidget(widget);    
    computePrimitivesPushButton = new QPushButton("Compute Primitives");
    computePrimitivesPushButton->setEnabled(true);

    gridSizeSpinBox = new QDoubleSpinBox();
    gridSizeSpinBox->setMinimum(0.1);
    gridSizeSpinBox->setValue(0.1);
    gridSizeSpinBox->setMaximum(1);
    connect(gridSizeSpinBox, SIGNAL(editingFinished()), this, SLOT(gridSizeEditingFinished()));
    QHBoxLayout* gridSizeRow = new QHBoxLayout();
    QLabel* gridSizeLabel = new QLabel();
    gridSizeLabel->setText("Grid Size:");
    gridSizeRow->addWidget(gridSizeLabel);
    gridSizeRow->addWidget(gridSizeSpinBox);
    gridSizeRow->addWidget(computePrimitivesPushButton);
    layout->addLayout(gridSizeRow);
    connect(computePrimitivesPushButton, SIGNAL(pressed()), this, SLOT(computePressed()));


    QHBoxLayout* startAnglesRow = new QHBoxLayout();
    startAnglesSpinBox = new QDoubleSpinBox();
    startAnglesSpinBox->setMinimum(1);
    startAnglesSpinBox->setMaximum(1000);
    startAnglesSpinBox->setValue(42);
    QLabel* startAnglesLabel = new QLabel();
    startAnglesLabel->setText("Start Angles:");
    startAnglesRow->addWidget(startAnglesLabel);
    startAnglesRow->addWidget(startAnglesSpinBox);
    layout->addLayout(startAnglesRow);
    connect(startAnglesSpinBox, SIGNAL(editingFinished()), this, SLOT(startAnglesEditingFinished()));
   

    QHBoxLayout* endAnglesRow = new QHBoxLayout();
    endAnglesSpinBox = new QDoubleSpinBox();
    endAnglesSpinBox->setMinimum(1);
    endAnglesSpinBox->setMaximum(1000);
    endAnglesSpinBox->setValue(21);
    QLabel* endAnglesLabel = new QLabel();
    endAnglesLabel->setText("End Angles:");
    endAnglesRow->addWidget(endAnglesLabel);
    endAnglesRow->addWidget(endAnglesSpinBox);
    layout->addLayout(endAnglesRow);
    connect(endAnglesSpinBox, SIGNAL(editingFinished()), this, SLOT(endAnglesEditingFinished()));

    QHBoxLayout* destinationCircleRadiusRow = new QHBoxLayout();
    destinationCircleRadiusSpinBox = new QDoubleSpinBox();
    destinationCircleRadiusSpinBox->setMinimum(1);
    destinationCircleRadiusSpinBox->setMaximum(100);
    destinationCircleRadiusSpinBox->setValue(10);
    QLabel* destinationCircleRadiusLabel = new QLabel();
    destinationCircleRadiusLabel->setText("Destination Circle Radius:");
    destinationCircleRadiusRow->addWidget(destinationCircleRadiusLabel);
    destinationCircleRadiusRow->addWidget(destinationCircleRadiusSpinBox);
    layout->addLayout(destinationCircleRadiusRow);
    connect(destinationCircleRadiusSpinBox, SIGNAL(editingFinished()), this, SLOT(destinationCircleRadiusEditingFinished()));  

    QHBoxLayout* cellSkipFactorRow = new QHBoxLayout();
    cellSkipFactorSpinBox = new QDoubleSpinBox();
    cellSkipFactorSpinBox->setMinimum(0.1);
    cellSkipFactorSpinBox->setMaximum(100);
    cellSkipFactorSpinBox->setValue(1);
    QLabel* cellSkipFactorLabel = new QLabel();
    cellSkipFactorLabel->setText("Cell Skip Factor:");
    cellSkipFactorRow->addWidget(cellSkipFactorLabel);
    cellSkipFactorRow->addWidget(cellSkipFactorSpinBox);
    layout->addLayout(cellSkipFactorRow);
    connect(cellSkipFactorSpinBox, SIGNAL(editingFinished()), this, SLOT(cellSkipFactorEditingFinished())); 

    QHBoxLayout* minTurningRadiusRow = new QHBoxLayout();
    minTurningRadiusSpinBox = new QDoubleSpinBox();
    minTurningRadiusSpinBox->setMinimum(0.1);
    minTurningRadiusSpinBox->setMaximum(100);
    minTurningRadiusSpinBox->setValue(2);
    QLabel* minTurningRadiusLabel = new QLabel();
    minTurningRadiusLabel->setText("Minimum Turning Radius:");
    minTurningRadiusRow->addWidget(minTurningRadiusLabel);
    minTurningRadiusRow->addWidget(minTurningRadiusSpinBox);
    layout->addLayout(minTurningRadiusRow);
    connect(minTurningRadiusSpinBox, SIGNAL(editingFinished()), this, SLOT(minTurningRadiusEditingFinished())); 

    QHBoxLayout* maxCurveLengthRow = new QHBoxLayout();
    maxCurveLengthSpinBox = new QDoubleSpinBox();
    maxCurveLengthSpinBox->setMinimum(0.1);
    maxCurveLengthSpinBox->setMaximum(100);
    maxCurveLengthSpinBox->setValue(100);
    QLabel* maxCurveLengthLabel = new QLabel();
    maxCurveLengthLabel->setText("Maximum Curve Length:");
    maxCurveLengthRow->addWidget(maxCurveLengthLabel);
    maxCurveLengthRow->addWidget(maxCurveLengthSpinBox);
    layout->addLayout(maxCurveLengthRow);
    connect(maxCurveLengthSpinBox, SIGNAL(editingFinished()), this, SLOT(maxCurveLengthEditingFinished())); 

    QHBoxLayout* splineOrderRow = new QHBoxLayout();
    splineOrderSpinBox = new QDoubleSpinBox();
    splineOrderSpinBox->setMinimum(1);
    splineOrderSpinBox->setMaximum(4);
    splineOrderSpinBox->setValue(3);
    QLabel* splineOrderLabel = new QLabel();
    splineOrderLabel->setText("Spline Order:");
    splineOrderRow->addWidget(splineOrderLabel);
    splineOrderRow->addWidget(splineOrderSpinBox);
    layout->addLayout(splineOrderRow);
    connect(splineOrderSpinBox, SIGNAL(editingFinished()), this, SLOT(splineOrderEditingFinished())); 

    QHBoxLayout* generateMotionsRow = new QHBoxLayout();
    
    generateForwardMotionsCheckBox = new QCheckBox();
    generateForwardMotionsCheckBox->setCheckable(true);
    generateForwardMotionsCheckBox->setChecked(true); 
    QLabel* forwardMotion = new QLabel();
    forwardMotion->setText("Forward:");
    generateMotionsRow->addWidget(forwardMotion);
    generateMotionsRow->addWidget(generateForwardMotionsCheckBox);

    generateBackwardMotionsCheckBox = new QCheckBox();
    generateBackwardMotionsCheckBox->setCheckable(true);
    generateBackwardMotionsCheckBox->setChecked(true); 
    QLabel* backwardMotion = new QLabel();
    backwardMotion->setText("Backward:");
    generateMotionsRow->addWidget(backwardMotion);
    generateMotionsRow->addWidget(generateBackwardMotionsCheckBox);

    generateLateralMotionsCheckBox = new QCheckBox();
    generateLateralMotionsCheckBox->setCheckable(true);
    generateLateralMotionsCheckBox->setChecked(true); 
    QLabel* lateralMotion = new QLabel();
    lateralMotion->setText("Lateral:");
    generateMotionsRow->addWidget(lateralMotion);
    generateMotionsRow->addWidget(generateLateralMotionsCheckBox);

    generatePointTurnMotionsCheckBox = new QCheckBox();
    generatePointTurnMotionsCheckBox->setCheckable(true);
    generatePointTurnMotionsCheckBox->setChecked(true); 
    QLabel* pointTurnMotion = new QLabel();
    pointTurnMotion->setText("Point Turn:");
    generateMotionsRow->addWidget(pointTurnMotion);
    generateMotionsRow->addWidget(generatePointTurnMotionsCheckBox);

    connect(generateForwardMotionsCheckBox, SIGNAL(stateChanged(int)), this, SLOT(generateForwardMotionsCheckBoxEditingFinished())); 
    connect(generateBackwardMotionsCheckBox, SIGNAL(stateChanged(int)), this, SLOT(generateBackwardMotionsCheckBoxEditingFinished())); 
    connect(generateLateralMotionsCheckBox, SIGNAL(stateChanged(int)), this, SLOT(generateLateralMotionsCheckBoxEditingFinished())); 
    connect(generatePointTurnMotionsCheckBox, SIGNAL(stateChanged(int)), this, SLOT(generatePointTurnMotionsEditingFinished())); 


    layout->addLayout(generateMotionsRow);
    window.setLayout(layout);
}

void SbplGui::setupSbpl()
{
    config.gridSize = 0.1;
    config.numAngles = 42;
    config.numEndAngles = 21;
    config.destinationCircleRadius = 10;
    config.cellSkipFactor = 1.0;
    config.generatePointTurnMotions = true;
    config.generateLateralMotions = true;
    config.generateBackwardMotions = true;
    config.generateForwardMotions = true;
    config.splineOrder = 3;
    
    minTurningRadius = 2; // increase this to reduce the number of available motion primitives
    maxCurveLength   = 100;
    sbpl_spline_primitives::SbplSplineMotionPrimitives primitives(config);
    splineViz.setMaxCurvature(1/minTurningRadius);
    splineViz.updateData(primitives);
}

void SbplGui::startAnglesEditingFinished()
{
    config.numAngles = startAnglesSpinBox->value();
}

void SbplGui::gridSizeEditingFinished()
{
    config.gridSize = gridSizeSpinBox->value();
}

void SbplGui::endAnglesEditingFinished()
{
    config.numEndAngles = endAnglesSpinBox->value();
}

void SbplGui::destinationCircleRadiusEditingFinished()
{
    config.destinationCircleRadius = destinationCircleRadiusSpinBox->value();
}

void SbplGui::cellSkipFactorEditingFinished()
{
    config.cellSkipFactor = cellSkipFactorSpinBox->value();
}

void SbplGui::minTurningRadiusEditingFinished()
{
    minTurningRadius = minTurningRadiusSpinBox->value();
}

void SbplGui::maxCurveLengthEditingFinished()
{
    maxCurveLength = maxCurveLengthSpinBox->value();
    std::cout << "New max curve length " << maxCurveLength << std::endl;
}

void SbplGui::splineOrderEditingFinished()
{
    config.splineOrder = splineOrderSpinBox->value();
}

void SbplGui::generatePointTurnMotionsEditingFinished()
{
    config.generatePointTurnMotions = generatePointTurnMotionsCheckBox->isChecked();
}

void SbplGui::generateBackwardMotionsCheckBoxEditingFinished()
{
    config.generateBackwardMotions = generateBackwardMotionsCheckBox->isChecked();
}

void SbplGui::generateForwardMotionsCheckBoxEditingFinished()
{
    config.generateForwardMotions = generateForwardMotionsCheckBox->isChecked();
}

void SbplGui::generateLateralMotionsCheckBoxEditingFinished()
{
    config.generateLateralMotions = generateLateralMotionsCheckBox->isChecked();
}

void SbplGui::show()
{
    window.show();
}

void SbplGui::computePressed()
{
    std::cout << "Primitives are updated." << std::endl;
    sbpl_spline_primitives::SbplSplineMotionPrimitives primitives(config);
    splineViz.setMaxCurvature(1/minTurningRadius);
    splineViz.setMaxCurveLength(maxCurveLength);
    splineViz.updateData(primitives);
}



