#pragma once
#include <QObject>
#include <QtWidgets>

#ifndef Q_MOC_RUN
#include <vizkit3d/Vizkit3DWidget.hpp>
#include <vizkit3d/SbplSplineVisualization.hpp>
#include <vizkit3d/GridVisualization.hpp>
#include <base/Eigen.hpp>
#endif

class SbplGui : public QObject
{
    Q_OBJECT;

    void setupUI();
    void setupSbpl();
    
public:

    SbplGui();    
    void show();

public slots:
    
signals:
    
private slots:
    void gridSizeEditingFinished();
    void startAnglesEditingFinished();
    void endAnglesEditingFinished();
    void destinationCircleRadiusEditingFinished();
    void cellSkipFactorEditingFinished();
    void minTurningRadiusEditingFinished();
    void maxCurveLengthEditingFinished();
    void splineOrderEditingFinished();
    void generatePointTurnMotionsEditingFinished();
    void generateLateralMotionsCheckBoxEditingFinished();
    void generateBackwardMotionsCheckBoxEditingFinished();
    void generateForwardMotionsCheckBoxEditingFinished();
    void computePressed();

private:
    
private:
    vizkit3d::Vizkit3DWidget* widget;
    QPushButton* computePrimitivesPushButton;
    QDoubleSpinBox* gridSizeSpinBox;
    QDoubleSpinBox* startAnglesSpinBox;
    QDoubleSpinBox* endAnglesSpinBox;
    QDoubleSpinBox* destinationCircleRadiusSpinBox;
    QDoubleSpinBox* cellSkipFactorSpinBox;
    QDoubleSpinBox* minTurningRadiusSpinBox;
    QDoubleSpinBox* maxCurveLengthSpinBox;    
    QDoubleSpinBox* splineOrderSpinBox;
    QCheckBox* generatePointTurnMotionsCheckBox;
    QCheckBox* generateLateralMotionsCheckBox;
    QCheckBox* generateBackwardMotionsCheckBox;
    QCheckBox* generateForwardMotionsCheckBox;
    QWidget window;
    vizkit3d::SbplSplineVisualization splineViz;
    vizkit3d::GridVisualization gridViz;
    sbpl_spline_primitives::SplinePrimitivesConfig config;

    double minTurningRadius;
    double maxCurveLength;
};
