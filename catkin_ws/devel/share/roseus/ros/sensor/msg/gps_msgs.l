;; Auto-generated. Do not edit!


(when (boundp 'sensor::gps_msgs)
  (if (not (find-package "SENSOR"))
    (make-package "SENSOR"))
  (shadow 'gps_msgs (find-package "SENSOR")))
(unless (find-package "SENSOR::GPS_MSGS")
  (make-package "SENSOR::GPS_MSGS"))

(in-package "ROS")
;;//! \htmlinclude gps_msgs.msg.html


(defclass sensor::gps_msgs
  :super ros::object
  :slots (_stamp _longitude _latitude _altitude _UTMx _UTMy _var_longitude _var_latitude _var_altitude _var_UTMx _var_UTMy ))

(defmethod sensor::gps_msgs
  (:init
   (&key
    ((:stamp __stamp) (instance ros::time :init))
    ((:longitude __longitude) 0.0)
    ((:latitude __latitude) 0.0)
    ((:altitude __altitude) 0.0)
    ((:UTMx __UTMx) 0.0)
    ((:UTMy __UTMy) 0.0)
    ((:var_longitude __var_longitude) 0.0)
    ((:var_latitude __var_latitude) 0.0)
    ((:var_altitude __var_altitude) 0.0)
    ((:var_UTMx __var_UTMx) 0.0)
    ((:var_UTMy __var_UTMy) 0.0)
    )
   (send-super :init)
   (setq _stamp __stamp)
   (setq _longitude (float __longitude))
   (setq _latitude (float __latitude))
   (setq _altitude (float __altitude))
   (setq _UTMx (float __UTMx))
   (setq _UTMy (float __UTMy))
   (setq _var_longitude (float __var_longitude))
   (setq _var_latitude (float __var_latitude))
   (setq _var_altitude (float __var_altitude))
   (setq _var_UTMx (float __var_UTMx))
   (setq _var_UTMy (float __var_UTMy))
   self)
  (:stamp
   (&optional __stamp)
   (if __stamp (setq _stamp __stamp)) _stamp)
  (:longitude
   (&optional __longitude)
   (if __longitude (setq _longitude __longitude)) _longitude)
  (:latitude
   (&optional __latitude)
   (if __latitude (setq _latitude __latitude)) _latitude)
  (:altitude
   (&optional __altitude)
   (if __altitude (setq _altitude __altitude)) _altitude)
  (:UTMx
   (&optional __UTMx)
   (if __UTMx (setq _UTMx __UTMx)) _UTMx)
  (:UTMy
   (&optional __UTMy)
   (if __UTMy (setq _UTMy __UTMy)) _UTMy)
  (:var_longitude
   (&optional __var_longitude)
   (if __var_longitude (setq _var_longitude __var_longitude)) _var_longitude)
  (:var_latitude
   (&optional __var_latitude)
   (if __var_latitude (setq _var_latitude __var_latitude)) _var_latitude)
  (:var_altitude
   (&optional __var_altitude)
   (if __var_altitude (setq _var_altitude __var_altitude)) _var_altitude)
  (:var_UTMx
   (&optional __var_UTMx)
   (if __var_UTMx (setq _var_UTMx __var_UTMx)) _var_UTMx)
  (:var_UTMy
   (&optional __var_UTMy)
   (if __var_UTMy (setq _var_UTMy __var_UTMy)) _var_UTMy)
  (:serialization-length
   ()
   (+
    ;; time _stamp
    8
    ;; float64 _longitude
    8
    ;; float64 _latitude
    8
    ;; float64 _altitude
    8
    ;; float64 _UTMx
    8
    ;; float64 _UTMy
    8
    ;; float64 _var_longitude
    8
    ;; float64 _var_latitude
    8
    ;; float64 _var_altitude
    8
    ;; float64 _var_UTMx
    8
    ;; float64 _var_UTMy
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; time _stamp
       (write-long (send _stamp :sec) s) (write-long (send _stamp :nsec) s)
     ;; float64 _longitude
       (sys::poke _longitude (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _latitude
       (sys::poke _latitude (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _altitude
       (sys::poke _altitude (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _UTMx
       (sys::poke _UTMx (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _UTMy
       (sys::poke _UTMy (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _var_longitude
       (sys::poke _var_longitude (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _var_latitude
       (sys::poke _var_latitude (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _var_altitude
       (sys::poke _var_altitude (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _var_UTMx
       (sys::poke _var_UTMx (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _var_UTMy
       (sys::poke _var_UTMy (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; time _stamp
     (send _stamp :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _stamp :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _longitude
     (setq _longitude (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _latitude
     (setq _latitude (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _altitude
     (setq _altitude (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _UTMx
     (setq _UTMx (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _UTMy
     (setq _UTMy (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _var_longitude
     (setq _var_longitude (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _var_latitude
     (setq _var_latitude (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _var_altitude
     (setq _var_altitude (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _var_UTMx
     (setq _var_UTMx (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _var_UTMy
     (setq _var_UTMy (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get sensor::gps_msgs :md5sum-) "36f3f8d772df83d6901c751002087a5c")
(setf (get sensor::gps_msgs :datatype-) "sensor/gps_msgs")
(setf (get sensor::gps_msgs :definition-)
      "time stamp
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

")



(provide :sensor/gps_msgs "36f3f8d772df83d6901c751002087a5c")


