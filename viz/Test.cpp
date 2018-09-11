#include <iostream>
#include "Test.hpp"

using namespace vizkit3d;

struct Test::Data {
    // Copy of the value given to updateDataIntern.
    //
    // Making a copy is required because of how OSG works
     data;
};


Test::Test()
    : p(new Data)
{
}

Test::~Test()
{
    delete p;
}

osg::ref_ptr<osg::Node> Test::createMainNode()
{
    // Geode is a common node used for vizkit3d plugins. It allows to display
    // "arbitrary" geometries
    return new osg::Geode();
}

void Test::updateMainNode ( osg::Node* node )
{
    osg::Geode* geode = static_cast<osg::Geode*>(node);
    // Update the main node using the data in p->data
}

void Test::updateDataIntern( const& value)
{
    p->data = value;
    std::cout << "got new sample data" << std::endl;
}

//Macro that makes this plugin loadable in ruby, this is optional.
VizkitQtPlugin(Test)

