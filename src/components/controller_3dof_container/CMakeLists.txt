idf_component_register(
    SRCS controller_3dof_container_data.cpp controller_3dof_container.cpp
    INCLUDE_DIRS "."
)

# Deaktiviert die Warnung für uninitialisierte Variablen nur in dieser Komponente
# Von Simulink generierter Code kann solche Fehler enthalten, da Variablen nur in if cases initialisiert werden, 
# welche aber immer zutreffen und deshalb keine echten Fehler produzieren
target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-maybe-uninitialized")
