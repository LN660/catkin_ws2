// Auto-generated. Do not edit!

// (in-package sensor.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class gps_msgs {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.stamp = null;
      this.longitude = null;
      this.latitude = null;
      this.altitude = null;
      this.UTMx = null;
      this.UTMy = null;
      this.var_longitude = null;
      this.var_latitude = null;
      this.var_altitude = null;
      this.var_UTMx = null;
      this.var_UTMy = null;
    }
    else {
      if (initObj.hasOwnProperty('stamp')) {
        this.stamp = initObj.stamp
      }
      else {
        this.stamp = {secs: 0, nsecs: 0};
      }
      if (initObj.hasOwnProperty('longitude')) {
        this.longitude = initObj.longitude
      }
      else {
        this.longitude = 0.0;
      }
      if (initObj.hasOwnProperty('latitude')) {
        this.latitude = initObj.latitude
      }
      else {
        this.latitude = 0.0;
      }
      if (initObj.hasOwnProperty('altitude')) {
        this.altitude = initObj.altitude
      }
      else {
        this.altitude = 0.0;
      }
      if (initObj.hasOwnProperty('UTMx')) {
        this.UTMx = initObj.UTMx
      }
      else {
        this.UTMx = 0.0;
      }
      if (initObj.hasOwnProperty('UTMy')) {
        this.UTMy = initObj.UTMy
      }
      else {
        this.UTMy = 0.0;
      }
      if (initObj.hasOwnProperty('var_longitude')) {
        this.var_longitude = initObj.var_longitude
      }
      else {
        this.var_longitude = 0.0;
      }
      if (initObj.hasOwnProperty('var_latitude')) {
        this.var_latitude = initObj.var_latitude
      }
      else {
        this.var_latitude = 0.0;
      }
      if (initObj.hasOwnProperty('var_altitude')) {
        this.var_altitude = initObj.var_altitude
      }
      else {
        this.var_altitude = 0.0;
      }
      if (initObj.hasOwnProperty('var_UTMx')) {
        this.var_UTMx = initObj.var_UTMx
      }
      else {
        this.var_UTMx = 0.0;
      }
      if (initObj.hasOwnProperty('var_UTMy')) {
        this.var_UTMy = initObj.var_UTMy
      }
      else {
        this.var_UTMy = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type gps_msgs
    // Serialize message field [stamp]
    bufferOffset = _serializer.time(obj.stamp, buffer, bufferOffset);
    // Serialize message field [longitude]
    bufferOffset = _serializer.float64(obj.longitude, buffer, bufferOffset);
    // Serialize message field [latitude]
    bufferOffset = _serializer.float64(obj.latitude, buffer, bufferOffset);
    // Serialize message field [altitude]
    bufferOffset = _serializer.float64(obj.altitude, buffer, bufferOffset);
    // Serialize message field [UTMx]
    bufferOffset = _serializer.float64(obj.UTMx, buffer, bufferOffset);
    // Serialize message field [UTMy]
    bufferOffset = _serializer.float64(obj.UTMy, buffer, bufferOffset);
    // Serialize message field [var_longitude]
    bufferOffset = _serializer.float64(obj.var_longitude, buffer, bufferOffset);
    // Serialize message field [var_latitude]
    bufferOffset = _serializer.float64(obj.var_latitude, buffer, bufferOffset);
    // Serialize message field [var_altitude]
    bufferOffset = _serializer.float64(obj.var_altitude, buffer, bufferOffset);
    // Serialize message field [var_UTMx]
    bufferOffset = _serializer.float64(obj.var_UTMx, buffer, bufferOffset);
    // Serialize message field [var_UTMy]
    bufferOffset = _serializer.float64(obj.var_UTMy, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type gps_msgs
    let len;
    let data = new gps_msgs(null);
    // Deserialize message field [stamp]
    data.stamp = _deserializer.time(buffer, bufferOffset);
    // Deserialize message field [longitude]
    data.longitude = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [latitude]
    data.latitude = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [altitude]
    data.altitude = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [UTMx]
    data.UTMx = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [UTMy]
    data.UTMy = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [var_longitude]
    data.var_longitude = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [var_latitude]
    data.var_latitude = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [var_altitude]
    data.var_altitude = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [var_UTMx]
    data.var_UTMx = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [var_UTMy]
    data.var_UTMy = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 88;
  }

  static datatype() {
    // Returns string type for a message object
    return 'sensor/gps_msgs';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '36f3f8d772df83d6901c751002087a5c';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    time stamp
    float64 longitude
    float64 latitude
    float64 altitude
    float64 UTMx
    float64 UTMy
    float64 var_longitude
    float64 var_latitude
    float64 var_altitude
    float64 var_UTMx
    float64 var_UTMy
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new gps_msgs(null);
    if (msg.stamp !== undefined) {
      resolved.stamp = msg.stamp;
    }
    else {
      resolved.stamp = {secs: 0, nsecs: 0}
    }

    if (msg.longitude !== undefined) {
      resolved.longitude = msg.longitude;
    }
    else {
      resolved.longitude = 0.0
    }

    if (msg.latitude !== undefined) {
      resolved.latitude = msg.latitude;
    }
    else {
      resolved.latitude = 0.0
    }

    if (msg.altitude !== undefined) {
      resolved.altitude = msg.altitude;
    }
    else {
      resolved.altitude = 0.0
    }

    if (msg.UTMx !== undefined) {
      resolved.UTMx = msg.UTMx;
    }
    else {
      resolved.UTMx = 0.0
    }

    if (msg.UTMy !== undefined) {
      resolved.UTMy = msg.UTMy;
    }
    else {
      resolved.UTMy = 0.0
    }

    if (msg.var_longitude !== undefined) {
      resolved.var_longitude = msg.var_longitude;
    }
    else {
      resolved.var_longitude = 0.0
    }

    if (msg.var_latitude !== undefined) {
      resolved.var_latitude = msg.var_latitude;
    }
    else {
      resolved.var_latitude = 0.0
    }

    if (msg.var_altitude !== undefined) {
      resolved.var_altitude = msg.var_altitude;
    }
    else {
      resolved.var_altitude = 0.0
    }

    if (msg.var_UTMx !== undefined) {
      resolved.var_UTMx = msg.var_UTMx;
    }
    else {
      resolved.var_UTMx = 0.0
    }

    if (msg.var_UTMy !== undefined) {
      resolved.var_UTMy = msg.var_UTMy;
    }
    else {
      resolved.var_UTMy = 0.0
    }

    return resolved;
    }
};

module.exports = gps_msgs;
