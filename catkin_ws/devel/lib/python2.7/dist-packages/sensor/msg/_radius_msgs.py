# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from sensor/radius_msgs.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import genpy

class radius_msgs(genpy.Message):
  _md5sum = "c0b0ac57a0e348a96526a4b17c9b0e83"
  _type = "sensor/radius_msgs"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """time stamp
float64 x
float64 y 
float64 deg
"""
  __slots__ = ['stamp','x','y','deg']
  _slot_types = ['time','float64','float64','float64']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       stamp,x,y,deg

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(radius_msgs, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.stamp is None:
        self.stamp = genpy.Time()
      if self.x is None:
        self.x = 0.
      if self.y is None:
        self.y = 0.
      if self.deg is None:
        self.deg = 0.
    else:
      self.stamp = genpy.Time()
      self.x = 0.
      self.y = 0.
      self.deg = 0.

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_get_struct_2I3d().pack(_x.stamp.secs, _x.stamp.nsecs, _x.x, _x.y, _x.deg))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      if self.stamp is None:
        self.stamp = genpy.Time()
      end = 0
      _x = self
      start = end
      end += 32
      (_x.stamp.secs, _x.stamp.nsecs, _x.x, _x.y, _x.deg,) = _get_struct_2I3d().unpack(str[start:end])
      self.stamp.canon()
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_2I3d().pack(_x.stamp.secs, _x.stamp.nsecs, _x.x, _x.y, _x.deg))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      if self.stamp is None:
        self.stamp = genpy.Time()
      end = 0
      _x = self
      start = end
      end += 32
      (_x.stamp.secs, _x.stamp.nsecs, _x.x, _x.y, _x.deg,) = _get_struct_2I3d().unpack(str[start:end])
      self.stamp.canon()
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_2I3d = None
def _get_struct_2I3d():
    global _struct_2I3d
    if _struct_2I3d is None:
        _struct_2I3d = struct.Struct("<2I3d")
    return _struct_2I3d
