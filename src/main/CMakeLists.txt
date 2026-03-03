idf_component_register(
    SRCS "main.cpp"
    INCLUDE_DIRS "."
    REQUIRES controller_6dof_container drone mpu6050 tests               
)