FUNCTION(GRESOURCE
    resource_dir
    resource_file
    output_dir
    output_source)

  FIND_PROGRAM(GLIB_COMPILE_RESOURCES
    NAMES glib-compile-resources)

  IF(NOT GLIB_COMPILE_RESOURCES)
    MESSAGE(FATAL "Could not find glib-compile-resources")
  ENDIF()
  
  # Get the output file path
  SET(output_c "${output_dir}/resource.c")
  SET(${output_source} ${output_c} PARENT_SCOPE)

  # Command to compile the resources
  ADD_CUSTOM_COMMAND(
    OUTPUT "${output_c}"
    WORKING_DIRECTORY ${resource_dir}
    COMMAND ${GLIB_COMPILE_RESOURCES}
    --generate-source --target=${output_c} ${resource_file}
    )

ENDFUNCTION()
