//#line 2 "/opt/ros/melodic/share/dynamic_reconfigure/cmake/../templates/ConfigType.h.template"
// *********************************************************
//
// File autogenerated for the sensor package
// by the dynamic_reconfigure package.
// Please do not edit.
//
// ********************************************************/

#ifndef __sensor__RADIUS_FUSIONCONFIG_H__
#define __sensor__RADIUS_FUSIONCONFIG_H__

#if __cplusplus >= 201103L
#define DYNAMIC_RECONFIGURE_FINAL final
#else
#define DYNAMIC_RECONFIGURE_FINAL
#endif

#include <dynamic_reconfigure/config_tools.h>
#include <limits>
#include <ros/node_handle.h>
#include <dynamic_reconfigure/ConfigDescription.h>
#include <dynamic_reconfigure/ParamDescription.h>
#include <dynamic_reconfigure/Group.h>
#include <dynamic_reconfigure/config_init_mutex.h>
#include <boost/any.hpp>

namespace sensor
{
  class radius_fusionConfigStatics;

  class radius_fusionConfig
  {
  public:
    class AbstractParamDescription : public dynamic_reconfigure::ParamDescription
    {
    public:
      AbstractParamDescription(std::string n, std::string t, uint32_t l,
          std::string d, std::string e)
      {
        name = n;
        type = t;
        level = l;
        description = d;
        edit_method = e;
      }

      virtual void clamp(radius_fusionConfig &config, const radius_fusionConfig &max, const radius_fusionConfig &min) const = 0;
      virtual void calcLevel(uint32_t &level, const radius_fusionConfig &config1, const radius_fusionConfig &config2) const = 0;
      virtual void fromServer(const ros::NodeHandle &nh, radius_fusionConfig &config) const = 0;
      virtual void toServer(const ros::NodeHandle &nh, const radius_fusionConfig &config) const = 0;
      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, radius_fusionConfig &config) const = 0;
      virtual void toMessage(dynamic_reconfigure::Config &msg, const radius_fusionConfig &config) const = 0;
      virtual void getValue(const radius_fusionConfig &config, boost::any &val) const = 0;
    };

    typedef boost::shared_ptr<AbstractParamDescription> AbstractParamDescriptionPtr;
    typedef boost::shared_ptr<const AbstractParamDescription> AbstractParamDescriptionConstPtr;

    // Final keyword added to class because it has virtual methods and inherits
    // from a class with a non-virtual destructor.
    template <class T>
    class ParamDescription DYNAMIC_RECONFIGURE_FINAL : public AbstractParamDescription
    {
    public:
      ParamDescription(std::string a_name, std::string a_type, uint32_t a_level,
          std::string a_description, std::string a_edit_method, T radius_fusionConfig::* a_f) :
        AbstractParamDescription(a_name, a_type, a_level, a_description, a_edit_method),
        field(a_f)
      {}

      T radius_fusionConfig::* field;

      virtual void clamp(radius_fusionConfig &config, const radius_fusionConfig &max, const radius_fusionConfig &min) const
      {
        if (config.*field > max.*field)
          config.*field = max.*field;

        if (config.*field < min.*field)
          config.*field = min.*field;
      }

      virtual void calcLevel(uint32_t &comb_level, const radius_fusionConfig &config1, const radius_fusionConfig &config2) const
      {
        if (config1.*field != config2.*field)
          comb_level |= level;
      }

      virtual void fromServer(const ros::NodeHandle &nh, radius_fusionConfig &config) const
      {
        nh.getParam(name, config.*field);
      }

      virtual void toServer(const ros::NodeHandle &nh, const radius_fusionConfig &config) const
      {
        nh.setParam(name, config.*field);
      }

      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, radius_fusionConfig &config) const
      {
        return dynamic_reconfigure::ConfigTools::getParameter(msg, name, config.*field);
      }

      virtual void toMessage(dynamic_reconfigure::Config &msg, const radius_fusionConfig &config) const
      {
        dynamic_reconfigure::ConfigTools::appendParameter(msg, name, config.*field);
      }

      virtual void getValue(const radius_fusionConfig &config, boost::any &val) const
      {
        val = config.*field;
      }
    };

    class AbstractGroupDescription : public dynamic_reconfigure::Group
    {
      public:
      AbstractGroupDescription(std::string n, std::string t, int p, int i, bool s)
      {
        name = n;
        type = t;
        parent = p;
        state = s;
        id = i;
      }

      std::vector<AbstractParamDescriptionConstPtr> abstract_parameters;
      bool state;

      virtual void toMessage(dynamic_reconfigure::Config &msg, const boost::any &config) const = 0;
      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, boost::any &config) const =0;
      virtual void updateParams(boost::any &cfg, radius_fusionConfig &top) const= 0;
      virtual void setInitialState(boost::any &cfg) const = 0;


      void convertParams()
      {
        for(std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = abstract_parameters.begin(); i != abstract_parameters.end(); ++i)
        {
          parameters.push_back(dynamic_reconfigure::ParamDescription(**i));
        }
      }
    };

    typedef boost::shared_ptr<AbstractGroupDescription> AbstractGroupDescriptionPtr;
    typedef boost::shared_ptr<const AbstractGroupDescription> AbstractGroupDescriptionConstPtr;

    // Final keyword added to class because it has virtual methods and inherits
    // from a class with a non-virtual destructor.
    template<class T, class PT>
    class GroupDescription DYNAMIC_RECONFIGURE_FINAL : public AbstractGroupDescription
    {
    public:
      GroupDescription(std::string a_name, std::string a_type, int a_parent, int a_id, bool a_s, T PT::* a_f) : AbstractGroupDescription(a_name, a_type, a_parent, a_id, a_s), field(a_f)
      {
      }

      GroupDescription(const GroupDescription<T, PT>& g): AbstractGroupDescription(g.name, g.type, g.parent, g.id, g.state), field(g.field), groups(g.groups)
      {
        parameters = g.parameters;
        abstract_parameters = g.abstract_parameters;
      }

      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, boost::any &cfg) const
      {
        PT* config = boost::any_cast<PT*>(cfg);
        if(!dynamic_reconfigure::ConfigTools::getGroupState(msg, name, (*config).*field))
          return false;

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          boost::any n = &((*config).*field);
          if(!(*i)->fromMessage(msg, n))
            return false;
        }

        return true;
      }

      virtual void setInitialState(boost::any &cfg) const
      {
        PT* config = boost::any_cast<PT*>(cfg);
        T* group = &((*config).*field);
        group->state = state;

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          boost::any n = boost::any(&((*config).*field));
          (*i)->setInitialState(n);
        }

      }

      virtual void updateParams(boost::any &cfg, radius_fusionConfig &top) const
      {
        PT* config = boost::any_cast<PT*>(cfg);

        T* f = &((*config).*field);
        f->setParams(top, abstract_parameters);

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          boost::any n = &((*config).*field);
          (*i)->updateParams(n, top);
        }
      }

      virtual void toMessage(dynamic_reconfigure::Config &msg, const boost::any &cfg) const
      {
        const PT config = boost::any_cast<PT>(cfg);
        dynamic_reconfigure::ConfigTools::appendGroup<T>(msg, name, id, parent, config.*field);

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          (*i)->toMessage(msg, config.*field);
        }
      }

      T PT::* field;
      std::vector<radius_fusionConfig::AbstractGroupDescriptionConstPtr> groups;
    };

class DEFAULT
{
  public:
    DEFAULT()
    {
      state = true;
      name = "Default";
    }

    void setParams(radius_fusionConfig &config, const std::vector<AbstractParamDescriptionConstPtr> params)
    {
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator _i = params.begin(); _i != params.end(); ++_i)
      {
        boost::any val;
        (*_i)->getValue(config, val);

        if("switch_radius1_bool"==(*_i)->name){switch_radius1_bool = boost::any_cast<bool>(val);}
        if("switch_radius2_bool"==(*_i)->name){switch_radius2_bool = boost::any_cast<bool>(val);}
        if("switch_radius3_bool"==(*_i)->name){switch_radius3_bool = boost::any_cast<bool>(val);}
        if("maxsigma_deg"==(*_i)->name){maxsigma_deg = boost::any_cast<double>(val);}
        if("minsigma_deg"==(*_i)->name){minsigma_deg = boost::any_cast<double>(val);}
        if("maxsigma_kpx"==(*_i)->name){maxsigma_kpx = boost::any_cast<double>(val);}
        if("minsigma_kpx"==(*_i)->name){minsigma_kpx = boost::any_cast<double>(val);}
        if("maxsigma_kpy"==(*_i)->name){maxsigma_kpy = boost::any_cast<double>(val);}
        if("minsigma_kpy"==(*_i)->name){minsigma_kpy = boost::any_cast<double>(val);}
        if("log_level"==(*_i)->name){log_level = boost::any_cast<int>(val);}
      }
    }

    bool switch_radius1_bool;
bool switch_radius2_bool;
bool switch_radius3_bool;
double maxsigma_deg;
double minsigma_deg;
double maxsigma_kpx;
double minsigma_kpx;
double maxsigma_kpy;
double minsigma_kpy;
int log_level;

    bool state;
    std::string name;

    
}groups;



//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      bool switch_radius1_bool;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      bool switch_radius2_bool;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      bool switch_radius3_bool;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double maxsigma_deg;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double minsigma_deg;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double maxsigma_kpx;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double minsigma_kpx;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double maxsigma_kpy;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double minsigma_kpy;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      int log_level;
//#line 228 "/opt/ros/melodic/share/dynamic_reconfigure/cmake/../templates/ConfigType.h.template"

    bool __fromMessage__(dynamic_reconfigure::Config &msg)
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();

      int count = 0;
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        if ((*i)->fromMessage(msg, *this))
          count++;

      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); i ++)
      {
        if ((*i)->id == 0)
        {
          boost::any n = boost::any(this);
          (*i)->updateParams(n, *this);
          (*i)->fromMessage(msg, n);
        }
      }

      if (count != dynamic_reconfigure::ConfigTools::size(msg))
      {
        ROS_ERROR("radius_fusionConfig::__fromMessage__ called with an unexpected parameter.");
        ROS_ERROR("Booleans:");
        for (unsigned int i = 0; i < msg.bools.size(); i++)
          ROS_ERROR("  %s", msg.bools[i].name.c_str());
        ROS_ERROR("Integers:");
        for (unsigned int i = 0; i < msg.ints.size(); i++)
          ROS_ERROR("  %s", msg.ints[i].name.c_str());
        ROS_ERROR("Doubles:");
        for (unsigned int i = 0; i < msg.doubles.size(); i++)
          ROS_ERROR("  %s", msg.doubles[i].name.c_str());
        ROS_ERROR("Strings:");
        for (unsigned int i = 0; i < msg.strs.size(); i++)
          ROS_ERROR("  %s", msg.strs[i].name.c_str());
        // @todo Check that there are no duplicates. Make this error more
        // explicit.
        return false;
      }
      return true;
    }

    // This version of __toMessage__ is used during initialization of
    // statics when __getParamDescriptions__ can't be called yet.
    void __toMessage__(dynamic_reconfigure::Config &msg, const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__, const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__) const
    {
      dynamic_reconfigure::ConfigTools::clear(msg);
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->toMessage(msg, *this);

      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); ++i)
      {
        if((*i)->id == 0)
        {
          (*i)->toMessage(msg, *this);
        }
      }
    }

    void __toMessage__(dynamic_reconfigure::Config &msg) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();
      __toMessage__(msg, __param_descriptions__, __group_descriptions__);
    }

    void __toServer__(const ros::NodeHandle &nh) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->toServer(nh, *this);
    }

    void __fromServer__(const ros::NodeHandle &nh)
    {
      static bool setup=false;

      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->fromServer(nh, *this);

      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();
      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); i++){
        if (!setup && (*i)->id == 0) {
          setup = true;
          boost::any n = boost::any(this);
          (*i)->setInitialState(n);
        }
      }
    }

    void __clamp__()
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const radius_fusionConfig &__max__ = __getMax__();
      const radius_fusionConfig &__min__ = __getMin__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->clamp(*this, __max__, __min__);
    }

    uint32_t __level__(const radius_fusionConfig &config) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      uint32_t level = 0;
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->calcLevel(level, config, *this);
      return level;
    }

    static const dynamic_reconfigure::ConfigDescription &__getDescriptionMessage__();
    static const radius_fusionConfig &__getDefault__();
    static const radius_fusionConfig &__getMax__();
    static const radius_fusionConfig &__getMin__();
    static const std::vector<AbstractParamDescriptionConstPtr> &__getParamDescriptions__();
    static const std::vector<AbstractGroupDescriptionConstPtr> &__getGroupDescriptions__();

  private:
    static const radius_fusionConfigStatics *__get_statics__();
  };

  template <> // Max and min are ignored for strings.
  inline void radius_fusionConfig::ParamDescription<std::string>::clamp(radius_fusionConfig &config, const radius_fusionConfig &max, const radius_fusionConfig &min) const
  {
    (void) config;
    (void) min;
    (void) max;
    return;
  }

  class radius_fusionConfigStatics
  {
    friend class radius_fusionConfig;

    radius_fusionConfigStatics()
    {
radius_fusionConfig::GroupDescription<radius_fusionConfig::DEFAULT, radius_fusionConfig> Default("Default", "", 0, 0, true, &radius_fusionConfig::groups);
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.switch_radius1_bool = 0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.switch_radius1_bool = 1;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.switch_radius1_bool = 1;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(radius_fusionConfig::AbstractParamDescriptionConstPtr(new radius_fusionConfig::ParamDescription<bool>("switch_radius1_bool", "bool", 0, "switch of RADIUS 1", "", &radius_fusionConfig::switch_radius1_bool)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(radius_fusionConfig::AbstractParamDescriptionConstPtr(new radius_fusionConfig::ParamDescription<bool>("switch_radius1_bool", "bool", 0, "switch of RADIUS 1", "", &radius_fusionConfig::switch_radius1_bool)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.switch_radius2_bool = 0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.switch_radius2_bool = 1;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.switch_radius2_bool = 1;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(radius_fusionConfig::AbstractParamDescriptionConstPtr(new radius_fusionConfig::ParamDescription<bool>("switch_radius2_bool", "bool", 0, "switch of RADIUS 2", "", &radius_fusionConfig::switch_radius2_bool)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(radius_fusionConfig::AbstractParamDescriptionConstPtr(new radius_fusionConfig::ParamDescription<bool>("switch_radius2_bool", "bool", 0, "switch of RADIUS 2", "", &radius_fusionConfig::switch_radius2_bool)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.switch_radius3_bool = 0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.switch_radius3_bool = 1;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.switch_radius3_bool = 0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(radius_fusionConfig::AbstractParamDescriptionConstPtr(new radius_fusionConfig::ParamDescription<bool>("switch_radius3_bool", "bool", 0, "switch of RADIUS 3", "", &radius_fusionConfig::switch_radius3_bool)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(radius_fusionConfig::AbstractParamDescriptionConstPtr(new radius_fusionConfig::ParamDescription<bool>("switch_radius3_bool", "bool", 0, "switch of RADIUS 3", "", &radius_fusionConfig::switch_radius3_bool)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.maxsigma_deg = 0.0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.maxsigma_deg = 10000.0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.maxsigma_deg = 1000.0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(radius_fusionConfig::AbstractParamDescriptionConstPtr(new radius_fusionConfig::ParamDescription<double>("maxsigma_deg", "double", 0, "superier of variance", "", &radius_fusionConfig::maxsigma_deg)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(radius_fusionConfig::AbstractParamDescriptionConstPtr(new radius_fusionConfig::ParamDescription<double>("maxsigma_deg", "double", 0, "superier of variance", "", &radius_fusionConfig::maxsigma_deg)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.minsigma_deg = 0.0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.minsigma_deg = 10.0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.minsigma_deg = 0.0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(radius_fusionConfig::AbstractParamDescriptionConstPtr(new radius_fusionConfig::ParamDescription<double>("minsigma_deg", "double", 0, "inferier of variance", "", &radius_fusionConfig::minsigma_deg)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(radius_fusionConfig::AbstractParamDescriptionConstPtr(new radius_fusionConfig::ParamDescription<double>("minsigma_deg", "double", 0, "inferier of variance", "", &radius_fusionConfig::minsigma_deg)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.maxsigma_kpx = 0.0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.maxsigma_kpx = 10000.0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.maxsigma_kpx = 1000.0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(radius_fusionConfig::AbstractParamDescriptionConstPtr(new radius_fusionConfig::ParamDescription<double>("maxsigma_kpx", "double", 0, "superier of variance", "", &radius_fusionConfig::maxsigma_kpx)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(radius_fusionConfig::AbstractParamDescriptionConstPtr(new radius_fusionConfig::ParamDescription<double>("maxsigma_kpx", "double", 0, "superier of variance", "", &radius_fusionConfig::maxsigma_kpx)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.minsigma_kpx = 0.0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.minsigma_kpx = 10.0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.minsigma_kpx = 0.0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(radius_fusionConfig::AbstractParamDescriptionConstPtr(new radius_fusionConfig::ParamDescription<double>("minsigma_kpx", "double", 0, "inferier of variance", "", &radius_fusionConfig::minsigma_kpx)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(radius_fusionConfig::AbstractParamDescriptionConstPtr(new radius_fusionConfig::ParamDescription<double>("minsigma_kpx", "double", 0, "inferier of variance", "", &radius_fusionConfig::minsigma_kpx)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.maxsigma_kpy = 0.0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.maxsigma_kpy = 10000.0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.maxsigma_kpy = 1000.0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(radius_fusionConfig::AbstractParamDescriptionConstPtr(new radius_fusionConfig::ParamDescription<double>("maxsigma_kpy", "double", 0, "superier of variance", "", &radius_fusionConfig::maxsigma_kpy)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(radius_fusionConfig::AbstractParamDescriptionConstPtr(new radius_fusionConfig::ParamDescription<double>("maxsigma_kpy", "double", 0, "superier of variance", "", &radius_fusionConfig::maxsigma_kpy)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.minsigma_kpy = 0.0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.minsigma_kpy = 10.0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.minsigma_kpy = 0.0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(radius_fusionConfig::AbstractParamDescriptionConstPtr(new radius_fusionConfig::ParamDescription<double>("minsigma_kpy", "double", 0, "inferier of variance", "", &radius_fusionConfig::minsigma_kpy)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(radius_fusionConfig::AbstractParamDescriptionConstPtr(new radius_fusionConfig::ParamDescription<double>("minsigma_kpy", "double", 0, "inferier of variance", "", &radius_fusionConfig::minsigma_kpy)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.log_level = 0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.log_level = 2;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.log_level = 0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(radius_fusionConfig::AbstractParamDescriptionConstPtr(new radius_fusionConfig::ParamDescription<int>("log_level", "int", 0, "Set Log Level", "{'enum_description': 'Set Log Level', 'enum': [{'srcline': 19, 'description': 'log print flag:INFO', 'srcfile': '/home/scar1et/catkin_ws/src/sensor/cfg/radius_fusion_dyn.cfg', 'cconsttype': 'const int', 'value': 0, 'ctype': 'int', 'type': 'int', 'name': 'info'}, {'srcline': 20, 'description': 'log print flag:WARN', 'srcfile': '/home/scar1et/catkin_ws/src/sensor/cfg/radius_fusion_dyn.cfg', 'cconsttype': 'const int', 'value': 1, 'ctype': 'int', 'type': 'int', 'name': 'warn'}, {'srcline': 21, 'description': 'log print flag:ERROR', 'srcfile': '/home/scar1et/catkin_ws/src/sensor/cfg/radius_fusion_dyn.cfg', 'cconsttype': 'const int', 'value': 2, 'ctype': 'int', 'type': 'int', 'name': 'error'}]}", &radius_fusionConfig::log_level)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(radius_fusionConfig::AbstractParamDescriptionConstPtr(new radius_fusionConfig::ParamDescription<int>("log_level", "int", 0, "Set Log Level", "{'enum_description': 'Set Log Level', 'enum': [{'srcline': 19, 'description': 'log print flag:INFO', 'srcfile': '/home/scar1et/catkin_ws/src/sensor/cfg/radius_fusion_dyn.cfg', 'cconsttype': 'const int', 'value': 0, 'ctype': 'int', 'type': 'int', 'name': 'info'}, {'srcline': 20, 'description': 'log print flag:WARN', 'srcfile': '/home/scar1et/catkin_ws/src/sensor/cfg/radius_fusion_dyn.cfg', 'cconsttype': 'const int', 'value': 1, 'ctype': 'int', 'type': 'int', 'name': 'warn'}, {'srcline': 21, 'description': 'log print flag:ERROR', 'srcfile': '/home/scar1et/catkin_ws/src/sensor/cfg/radius_fusion_dyn.cfg', 'cconsttype': 'const int', 'value': 2, 'ctype': 'int', 'type': 'int', 'name': 'error'}]}", &radius_fusionConfig::log_level)));
//#line 246 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.convertParams();
//#line 246 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __group_descriptions__.push_back(radius_fusionConfig::AbstractGroupDescriptionConstPtr(new radius_fusionConfig::GroupDescription<radius_fusionConfig::DEFAULT, radius_fusionConfig>(Default)));
//#line 366 "/opt/ros/melodic/share/dynamic_reconfigure/cmake/../templates/ConfigType.h.template"

      for (std::vector<radius_fusionConfig::AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); ++i)
      {
        __description_message__.groups.push_back(**i);
      }
      __max__.__toMessage__(__description_message__.max, __param_descriptions__, __group_descriptions__);
      __min__.__toMessage__(__description_message__.min, __param_descriptions__, __group_descriptions__);
      __default__.__toMessage__(__description_message__.dflt, __param_descriptions__, __group_descriptions__);
    }
    std::vector<radius_fusionConfig::AbstractParamDescriptionConstPtr> __param_descriptions__;
    std::vector<radius_fusionConfig::AbstractGroupDescriptionConstPtr> __group_descriptions__;
    radius_fusionConfig __max__;
    radius_fusionConfig __min__;
    radius_fusionConfig __default__;
    dynamic_reconfigure::ConfigDescription __description_message__;

    static const radius_fusionConfigStatics *get_instance()
    {
      // Split this off in a separate function because I know that
      // instance will get initialized the first time get_instance is
      // called, and I am guaranteeing that get_instance gets called at
      // most once.
      static radius_fusionConfigStatics instance;
      return &instance;
    }
  };

  inline const dynamic_reconfigure::ConfigDescription &radius_fusionConfig::__getDescriptionMessage__()
  {
    return __get_statics__()->__description_message__;
  }

  inline const radius_fusionConfig &radius_fusionConfig::__getDefault__()
  {
    return __get_statics__()->__default__;
  }

  inline const radius_fusionConfig &radius_fusionConfig::__getMax__()
  {
    return __get_statics__()->__max__;
  }

  inline const radius_fusionConfig &radius_fusionConfig::__getMin__()
  {
    return __get_statics__()->__min__;
  }

  inline const std::vector<radius_fusionConfig::AbstractParamDescriptionConstPtr> &radius_fusionConfig::__getParamDescriptions__()
  {
    return __get_statics__()->__param_descriptions__;
  }

  inline const std::vector<radius_fusionConfig::AbstractGroupDescriptionConstPtr> &radius_fusionConfig::__getGroupDescriptions__()
  {
    return __get_statics__()->__group_descriptions__;
  }

  inline const radius_fusionConfigStatics *radius_fusionConfig::__get_statics__()
  {
    const static radius_fusionConfigStatics *statics;

    if (statics) // Common case
      return statics;

    boost::mutex::scoped_lock lock(dynamic_reconfigure::__init_mutex__);

    if (statics) // In case we lost a race.
      return statics;

    statics = radius_fusionConfigStatics::get_instance();

    return statics;
  }

//#line 19 "/home/scar1et/catkin_ws/src/sensor/cfg/radius_fusion_dyn.cfg"
      const int radius_fusion_info = 0;
//#line 20 "/home/scar1et/catkin_ws/src/sensor/cfg/radius_fusion_dyn.cfg"
      const int radius_fusion_warn = 1;
//#line 21 "/home/scar1et/catkin_ws/src/sensor/cfg/radius_fusion_dyn.cfg"
      const int radius_fusion_error = 2;
}

#undef DYNAMIC_RECONFIGURE_FINAL

#endif // __RADIUS_FUSIONRECONFIGURATOR_H__
