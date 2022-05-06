#ifndef sbpl_spline_primitives_MotionPlanningLibrariesSbplSplineVisualization_H
#define sbpl_spline_primitives_MotionPlanningLibrariesSbplSplineVisualization_H

#include <boost/noncopyable.hpp>
#include <vizkit3d/Vizkit3DPlugin.hpp>
#include <vizkit3d/ColorConversionHelper.hpp>
#include <osg/Geode>
#include <sbpl_spline_primitives/SbplSplineMotionPrimitives.hpp>

namespace vizkit3d
{
    class SbplSplineVisualization
        : public vizkit3d::Vizkit3DPlugin< sbpl_spline_primitives::SbplSplineMotionPrimitives>
        , boost::noncopyable
    {
    Q_OBJECT  
    
    Q_PROPERTY(int angleNum READ getAngleNum WRITE setAngleNum)
    Q_PROPERTY(int endAngle READ getEndAngle WRITE setEndAngle)
    Q_PROPERTY(double maxCurvature READ getMaxCurvature WRITE setMaxCurvature)
    Q_PROPERTY(double maxCurveLength READ getMaxCurveLength WRITE setMaxCurveLength)
    
    public:
        SbplSplineVisualization();
        ~SbplSplineVisualization();

    Q_INVOKABLE void updateData(sbpl_spline_primitives::SbplSplineMotionPrimitives const &data)
    {
        vizkit3d::Vizkit3DPlugin< sbpl_spline_primitives::SbplSplineMotionPrimitives>::updateData(data);
    }
    
    public slots:
        int getAngleNum() const;
        void setAngleNum(int num);
        int getEndAngle() const;
        void setEndAngle(int num);
        bool allAnglesShown() const;
        void setShowAllAngles(bool enabled);
        double getMaxCurvature() const;
        double getMaxCurveLength() const;
        void setMaxCurvature(const double value);
        void setMaxCurveLength(const double value);

    protected:
        int mAngleNum;
        int mEndAngle;
        bool mAllAnglesShown;
        double maxCurvature = 10000;
        double maxCurveLength = 10000;
        
        virtual osg::ref_ptr<osg::Node> createMainNode();
        virtual void updateMainNode(osg::Node* node);
        virtual void updateDataIntern(sbpl_spline_primitives::SbplSplineMotionPrimitives const& data);
        void addPrimitives(osg::Group* group, sbpl_spline_primitives::SbplSplineMotionPrimitives& primitives);
        
    private:
        struct Data;
        Data* p;
    };

    VizkitQtPlugin(SbplSplineVisualization)
}
#endif
