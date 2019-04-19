find_program(PYTHON "python")

set (PACKAGE_VERSION "0.1.0")

if (PYTHON)
    set(SETUP_PY_IN "${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in")
    set(SETUP_PY    "${CMAKE_CURRENT_SOURCE_DIR}/setup.py")
    set(LIB         "${CMAKE_CURRENT_SOURCE_DIR}/lib/__init__.py")
    set(BUILD       "${CMAKE_CURRENT_SOURCE_DIR}/build")
    set(TIMESTAMP   "timestamp")

    configure_file(${SETUP_PY_IN} ${SETUP_PY})

    # I have some problems to execute the following commands
    add_custom_command(
        OUTPUT  ${BUILD}/${TIMESTAMP}
        DEPENDS ${LIB}  
        COMMAND echo "building pylib ..."
        COMMAND ${PYTHON} ${SETUP_PY} build
        COMMAND ${CMAKE_COMMAND} -E touch ${BUILD}/${TIMESTAMP}
        # COMMAND bash -c "date +\"%s\" > ${BUILD}/${TIMESTAMP}"
        VERBATIM     
        )
    
    add_custom_target( PYLIB ALL DEPENDS ${BUILD}/${TIMESTAMP})

    install(CODE "execute_process(COMMAND ${PYTHON} ${SETUP_PY} install)")

endif()
