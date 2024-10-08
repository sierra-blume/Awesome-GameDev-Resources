function(add_custom_test TEST_NAME TEST_EXECUTABLE TEST_INPUT_LIST TEST_EXPECTED_OUTPUT_LIST)
    list(LENGTH TEST_INPUT_LIST num_tests)

    MATH(EXPR num_tests "${num_tests} - 1")
    message(STATUS "Adding ${num_tests} tests for ${TEST_NAME}.")

    set(TEST_COMMANDS "")
    foreach(index RANGE 0 ${num_tests})
        list(GET TEST_INPUT_LIST ${index} TEST_INPUT)
        list(GET TEST_EXPECTED_OUTPUT_LIST ${index} TEST_EXPECTED_OUTPUT)

        list(APPEND TEST_COMMANDS
                COMMAND ${CMAKE_COMMAND} -E echo "Running test: ${TEST_NAME}_${index}. Using input file: ${TEST_INPUT}"
                COMMAND ${CMAKE_COMMAND} -E cat ${TEST_INPUT}
                COMMAND ${CMAKE_COMMAND} -E echo "=================================="
                COMMAND ${CMAKE_COMMAND} -E echo "Expected Output from ${TEST_NAME}_${index}:"
                COMMAND ${CMAKE_COMMAND} -E cat ${TEST_EXPECTED_OUTPUT}
                COMMAND ${CMAKE_COMMAND} -E echo "=================================="
                COMMAND ${TEST_EXECUTABLE} < ${TEST_INPUT} > test_output_${index}.txt
                COMMAND ${CMAKE_COMMAND} -E echo "Actual Output from ${TEST_NAME}_${index}:"
                COMMAND ${CMAKE_COMMAND} -E cat test_output_${index}.txt
                COMMAND ${CMAKE_COMMAND} -E echo "=================================="
                COMMAND ${CMAKE_COMMAND} -E compare_files ${TEST_EXPECTED_OUTPUT} test_output_${index}.txt
                COMMAND ${CMAKE_COMMAND} -E echo "Test ${TEST_NAME}_${index} passed."
        )
    endforeach()

    add_custom_target(${TEST_NAME}
            ${TEST_COMMANDS}
            DEPENDS ${TEST_EXECUTABLE}
    )
endfunction()

add_subdirectory(assignments/flocking)
add_subdirectory(assignments/maze)
add_subdirectory(assignments/life)
add_subdirectory(assignments/rng)
#add_subdirectory(assignments/catchthecat)