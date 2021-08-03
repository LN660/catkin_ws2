
(cl:in-package :asdf)

(defsystem "sensor-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "cyscan_msgs" :depends-on ("_package_cyscan_msgs"))
    (:file "_package_cyscan_msgs" :depends-on ("_package"))
    (:file "gps_msgs" :depends-on ("_package_gps_msgs"))
    (:file "_package_gps_msgs" :depends-on ("_package"))
    (:file "imu_msgs" :depends-on ("_package_imu_msgs"))
    (:file "_package_imu_msgs" :depends-on ("_package"))
    (:file "radius_msgs" :depends-on ("_package_radius_msgs"))
    (:file "_package_radius_msgs" :depends-on ("_package"))
  ))