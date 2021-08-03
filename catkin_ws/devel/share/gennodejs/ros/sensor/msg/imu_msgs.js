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

class imu_msgs {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.stamp = null;
      this.roll = null;
      this.pitch = null;
      this.head = null;
      this.var_roll = null;
      this.var_pitch = null;
      this.var_head = null;
    }
    else {
      if (initObj.hasOwnProperty('stamp')) {
        this.stamp = initObj.stamp
      }
      else {
        this.stamp = {secs: 0, nsecs: 0};
      }
      if (initObj.hasOwnProperty('roll')) {
        this.roll = initObj.roll
      }
      else {
        this.roll = 0.0;
      }
      if (initObj.hasOwnProperty('pitch')) {
        this.pitch = initObj.pitch
      }
      else {
        this.pitch = 0.0;
      }
      if (initObj.hasOwnProperty('head')) {
        this.head = initObj.head
      }
      else {
        this.head = 0.0;
      }
      if (initObj.hasOwnProperty('var_roll')) {
        this.var_roll = initObj.var_roll
      }
      else {
        this.var_roll = 0.0;
      }
      if (initObj.hasOwnProperty('var_pitch')) {
        this.var_pitch = initObj.var_pitch
      }
      else {
        this.var_pitch = 0.0;
      }
      if (initObj.hasOwnProperty('var_head')) {
        this.var_head = initObj.var_head
      }
      else {
        this.var_head = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type imu_msgs
    // Serialize message field [stamp]
    bufferOffset = _serializer.time(obj.stamp, buffer, bufferOffset);
    // Serialize message field [roll]
    bufferOffset = _serializer.float64(obj.roll, buffer, bufferOffset);
    // Serialize message field [pitch]
    bufferOffset = _serializer.float64(obj.pitch, buffer, bufferOffset);
    // Serialize message field [head]
    bufferOffset = _serializer.float64(obj.head, buffer, bufferOffset);
    // Serialize message field [var_roll]
    bufferOffset = _serializer.float64(obj.var_roll, buffer, bufferOffset);
    // Serialize message field [var_pitch]
    bufferOffset = _serializer.float64(obj.var_pitch, buffer, bufferOffset);
    // Serialize message field [var_head]
    bufferOffset = _serializer.float64(obj.var_head, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type imu_msgs
    let len;
    let data = new imu_msgs(null);
    // Deserialize message field [stamp]
    data.stamp = _deserializer.time(buffer, bufferOffset);
    // Deserialize message field [roll]
    data.roll = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [pitch]
    data.pitch = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [head]
    data.head = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [var_roll]
    data.var_roll = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [var_pitch]
    data.var_pitch = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [var_head]
    data.var_head = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 56;
  }

  static datatype() {
    // Returns string type for a message object
    return 'sensor/imu_msgs';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '5ebb085607169f8db0078a888ed031ff';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    time stamp
    float64 roll
    float64 pitch 
    float64 head
    float64 var_roll
    float64 var_pitch 
    float64 var_head
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new imu_msgs(null);
    if (msg.stamp !== undefined) {
      resolved.stamp = msg.stamp;
    }
    else {
      resolved.stamp = {secs: 0, nsecs: 0}
    }

    if (msg.roll !== undefined) {
      resolved.roll = msg.roll;
    }
    else {
      resolved.roll = 0.0
    }

    if (msg.pitch !== undefined) {
      resolved.pitch = msg.pitch;
    }
    else {
      resolved.pitch = 0.0
    }

    if (msg.head !== undefined) {
      resolved.head = msg.head;
    }
    else {
      resolved.head = 0.0
    }

    if (msg.var_roll !== undefined) {
      resolved.var_roll = msg.var_roll;
    }
    else {
      resolved.var_roll = 0.0
    }

    if (msg.var_pitch !== undefined) {
      resolved.var_pitch = msg.var_pitch;
    }
    else {
      resolved.var_pitch = 0.0
    }

    if (msg.var_head !== undefined) {
      resolved.var_head = msg.var_head;
    }
    else {
      resolved.var_head = 0.0
    }

    return resolved;
    }
};

module.exports = imu_msgs;
