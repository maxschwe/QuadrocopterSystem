idf_component_register(
    SRCS "main.cpp"
    INCLUDE_DIRS "."
    REQUIRES controller_3dof drone mpu6050 tests               
)