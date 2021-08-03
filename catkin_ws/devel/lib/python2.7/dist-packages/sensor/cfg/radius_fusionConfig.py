## *********************************************************
##
## File autogenerated for the sensor package
## by the dynamic_reconfigure package.
## Please do not edit.
##
## ********************************************************/

from dynamic_reconfigure.encoding import extract_params

inf = float('inf')

config_description = {'upper': 'DEFAULT', 'lower': 'groups', 'srcline': 246, 'name': 'Default', 'parent': 0, 'srcfile': '/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'cstate': 'true', 'parentname': 'Default', 'class': 'DEFAULT', 'field': 'default', 'state': True, 'parentclass': '', 'groups': [], 'parameters': [{'srcline': 291, 'description': 'switch of RADIUS 1', 'max': True, 'cconsttype': 'const bool', 'ctype': 'bool', 'srcfile': '/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'switch_radius1_bool', 'edit_method': '', 'default': True, 'level': 0, 'min': False, 'type': 'bool'}, {'srcline': 291, 'description': 'switch of RADIUS 2', 'max': True, 'cconsttype': 'const bool', 'ctype': 'bool', 'srcfile': '/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'switch_radius2_bool', 'edit_method': '', 'default': True, 'level': 0, 'min': False, 'type': 'bool'}, {'srcline': 291, 'description': 'switch of RADIUS 3', 'max': True, 'cconsttype': 'const bool', 'ctype': 'bool', 'srcfile': '/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'switch_radius3_bool', 'edit_method': '', 'default': False, 'level': 0, 'min': False, 'type': 'bool'}, {'srcline': 291, 'description': 'superier of variance', 'max': 10000.0, 'cconsttype': 'const double', 'ctype': 'double', 'srcfile': '/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'maxsigma_deg', 'edit_method': '', 'default': 1000.0, 'level': 0, 'min': 0.0, 'type': 'double'}, {'srcline': 291, 'description': 'inferier of variance', 'max': 10.0, 'cconsttype': 'const double', 'ctype': 'double', 'srcfile': '/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'minsigma_deg', 'edit_method': '', 'default': 0.0, 'level': 0, 'min': 0.0, 'type': 'double'}, {'srcline': 291, 'description': 'superier of variance', 'max': 10000.0, 'cconsttype': 'const double', 'ctype': 'double', 'srcfile': '/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'maxsigma_kpx', 'edit_method': '', 'default': 1000.0, 'level': 0, 'min': 0.0, 'type': 'double'}, {'srcline': 291, 'description': 'inferier of variance', 'max': 10.0, 'cconsttype': 'const double', 'ctype': 'double', 'srcfile': '/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'minsigma_kpx', 'edit_method': '', 'default': 0.0, 'level': 0, 'min': 0.0, 'type': 'double'}, {'srcline': 291, 'description': 'superier of variance', 'max': 10000.0, 'cconsttype': 'const double', 'ctype': 'double', 'srcfile': '/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'maxsigma_kpy', 'edit_method': '', 'default': 1000.0, 'level': 0, 'min': 0.0, 'type': 'double'}, {'srcline': 291, 'description': 'inferier of variance', 'max': 10.0, 'cconsttype': 'const double', 'ctype': 'double', 'srcfile': '/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'minsigma_kpy', 'edit_method': '', 'default': 0.0, 'level': 0, 'min': 0.0, 'type': 'double'}, {'srcline': 291, 'description': 'Set Log Level', 'max': 2, 'cconsttype': 'const int', 'ctype': 'int', 'srcfile': '/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'log_level', 'edit_method': "{'enum_description': 'Set Log Level', 'enum': [{'srcline': 19, 'description': 'log print flag:INFO', 'srcfile': '/home/scar1et/catkin_ws/src/sensor/cfg/radius_fusion_dyn.cfg', 'cconsttype': 'const int', 'value': 0, 'ctype': 'int', 'type': 'int', 'name': 'info'}, {'srcline': 20, 'description': 'log print flag:WARN', 'srcfile': '/home/scar1et/catkin_ws/src/sensor/cfg/radius_fusion_dyn.cfg', 'cconsttype': 'const int', 'value': 1, 'ctype': 'int', 'type': 'int', 'name': 'warn'}, {'srcline': 21, 'description': 'log print flag:ERROR', 'srcfile': '/home/scar1et/catkin_ws/src/sensor/cfg/radius_fusion_dyn.cfg', 'cconsttype': 'const int', 'value': 2, 'ctype': 'int', 'type': 'int', 'name': 'error'}]}", 'default': 0, 'level': 0, 'min': 0, 'type': 'int'}], 'type': '', 'id': 0}

min = {}
max = {}
defaults = {}
level = {}
type = {}
all_level = 0

#def extract_params(config):
#    params = []
#    params.extend(config['parameters'])
#    for group in config['groups']:
#        params.extend(extract_params(group))
#    return params

for param in extract_params(config_description):
    min[param['name']] = param['min']
    max[param['name']] = param['max']
    defaults[param['name']] = param['default']
    level[param['name']] = param['level']
    type[param['name']] = param['type']
    all_level = all_level | param['level']

radius_fusion_info = 0
radius_fusion_warn = 1
radius_fusion_error = 2