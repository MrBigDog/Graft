/*  -*-c++-*-
 *  Copyright (C) 2015 Thomas Hogarth <tom@hogbox.com>, adapted from osgconv
 *
 * This library is open source and may be redistributed and/or modified under
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * OpenSceneGraph Public License for more details.
*/

#include <Graft/PluginRegistry.h>
#include <osgUtil/Optimizer>

namespace graft {

class OptimizeAction : public graft::Action
{
public:
    OptimizeAction()
        : graft::Action(),
        _allOptimzations(false)
    {}

    OptimizeAction(const OptimizeAction& op, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY)
     : graft::Action(op, copyop),
       _allOptimzations(op._allOptimzations)
    {
    }

    META_Object(graft,OptimizeAction)

    virtual std::string friendlyName(){ return "Optimize"; }
    virtual std::string description(){ return "Run the osgUtil Optimizer on the object";}
    virtual std::string category(){ return "Model"; }

    virtual void process(ActionData* aData) {
        if(aData->asNode() == NULL) return;
        osgUtil::Optimizer optimizer;
        optimizer.optimize(aData->asNode(), _allOptimzations ? osgUtil::Optimizer::ALL_OPTIMIZATIONS : osgUtil::Optimizer::DEFAULT_OPTIMIZATIONS);
    }

    void setAllOptimizations(bool useAll){ _allOptimzations = useAll; }
    bool getAllOptimizations() const { return _allOptimzations; }

protected:
    bool _allOptimzations;
};

} //end graft

REGISTER_OBJECT_WRAPPER( graft_OptimizeAction,
                         new graft::OptimizeAction,
                         graft::OptimizeAction,
                         "osg::Object graft::Action graft::OptimizeAction" )
{
    ADD_BOOL_SERIALIZER(AllOptimizations, false);
}
