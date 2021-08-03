;; Auto-generated. Do not edit!


(when (boundp 'sensor::cyscan_msgs)
  (if (not (find-package "SENSOR"))
    (make-package "SENSOR"))
  (shadow 'cyscan_msgs (find-package "SENSOR")))
(unless (find-package "SENSOR::CYSCAN_MSGS")
  (make-package "SENSOR::CYSCAN_MSGS"))

(in-package "ROS")
;;//! \htmlinclude cyscan_msgs.msg.html


(defclass sensor::cyscan_msgs
  :super ros::object
  :slots (_stamp _x _y _deg ))

(defmethod sensor::cyscan_msgs
  (:init
   (&key
    ((:stamp __stamp) (instance ros::time :init))
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:deg __deg) 0.0)
    )
   (send-super :init)
   (setq _stamp __stamp)
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _deg (float __deg))
   self)
  (:stamp
   (&optional __stamp)
   (if __stamp (setq _stamp __stamp)) _stamp)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:deg
   (&optional __deg)
   (if __deg (setq _deg __deg)) _deg)
  (:serialization-length
   ()
   (+
    ;; time _stamp
    8
    ;; float64 _x
    8
    ;; float64 _y
    8
    ;; float64 _deg
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; time _stamp
       (write-long (send _stamp :sec) s) (write-long (send _stamp :nsec) s)
     ;; float64 _x
       (sys::poke _x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y
       (sys::poke _y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _deg
       (sys::poke _deg (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; time _stamp
     (send _stamp :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _stamp :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _x
     (setq _x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y
     (setq _y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _deg
     (setq _deg (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get sensor::cyscan_msgs :md5sum-) "c0b0ac57a0e348a96526a4b17c9b0e83")
(setf (get sensor::cyscan_msgs :datatype-) "sensor/cyscan_msgs")
(setf (get sensor::cyscan_msgs :definition-)
      "time stamp
float64 x
float64 y 
float64 deg

")



(provide :sensor/cyscan_msgs "c0b0ac57a0e348a96526a4b17c9b0e83")


