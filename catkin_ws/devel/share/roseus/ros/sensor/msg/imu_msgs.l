;; Auto-generated. Do not edit!


(when (boundp 'sensor::imu_msgs)
  (if (not (find-package "SENSOR"))
    (make-package "SENSOR"))
  (shadow 'imu_msgs (find-package "SENSOR")))
(unless (find-package "SENSOR::IMU_MSGS")
  (make-package "SENSOR::IMU_MSGS"))

(in-package "ROS")
;;//! \htmlinclude imu_msgs.msg.html


(defclass sensor::imu_msgs
  :super ros::object
  :slots (_stamp _roll _pitch _head _var_roll _var_pitch _var_head ))

(defmethod sensor::imu_msgs
  (:init
   (&key
    ((:stamp __stamp) (instance ros::time :init))
    ((:roll __roll) 0.0)
    ((:pitch __pitch) 0.0)
    ((:head __head) 0.0)
    ((:var_roll __var_roll) 0.0)
    ((:var_pitch __var_pitch) 0.0)
    ((:var_head __var_head) 0.0)
    )
   (send-super :init)
   (setq _stamp __stamp)
   (setq _roll (float __roll))
   (setq _pitch (float __pitch))
   (setq _head (float __head))
   (setq _var_roll (float __var_roll))
   (setq _var_pitch (float __var_pitch))
   (setq _var_head (float __var_head))
   self)
  (:stamp
   (&optional __stamp)
   (if __stamp (setq _stamp __stamp)) _stamp)
  (:roll
   (&optional __roll)
   (if __roll (setq _roll __roll)) _roll)
  (:pitch
   (&optional __pitch)
   (if __pitch (setq _pitch __pitch)) _pitch)
  (:head
   (&optional __head)
   (if __head (setq _head __head)) _head)
  (:var_roll
   (&optional __var_roll)
   (if __var_roll (setq _var_roll __var_roll)) _var_roll)
  (:var_pitch
   (&optional __var_pitch)
   (if __var_pitch (setq _var_pitch __var_pitch)) _var_pitch)
  (:var_head
   (&optional __var_head)
   (if __var_head (setq _var_head __var_head)) _var_head)
  (:serialization-length
   ()
   (+
    ;; time _stamp
    8
    ;; float64 _roll
    8
    ;; float64 _pitch
    8
    ;; float64 _head
    8
    ;; float64 _var_roll
    8
    ;; float64 _var_pitch
    8
    ;; float64 _var_head
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; time _stamp
       (write-long (send _stamp :sec) s) (write-long (send _stamp :nsec) s)
     ;; float64 _roll
       (sys::poke _roll (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _pitch
       (sys::poke _pitch (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _head
       (sys::poke _head (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _var_roll
       (sys::poke _var_roll (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _var_pitch
       (sys::poke _var_pitch (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _var_head
       (sys::poke _var_head (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; time _stamp
     (send _stamp :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _stamp :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _roll
     (setq _roll (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _pitch
     (setq _pitch (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _head
     (setq _head (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _var_roll
     (setq _var_roll (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _var_pitch
     (setq _var_pitch (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _var_head
     (setq _var_head (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get sensor::imu_msgs :md5sum-) "5ebb085607169f8db0078a888ed031ff")
(setf (get sensor::imu_msgs :datatype-) "sensor/imu_msgs")
(setf (get sensor::imu_msgs :definition-)
      "time stamp
float64 roll
float64 pitch 
float64 head
float64 var_roll
float64 var_pitch 
float64 var_head
")



(provide :sensor/imu_msgs "5ebb085607169f8db0078a888ed031ff")


