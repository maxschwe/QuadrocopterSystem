idf_component_register(
    SRCS "rotor.cpp" "drone.cpp" "esc_timer.cpp"
    INCLUDE_DIRS "include"
    REQUIRES driver mpu6050
)