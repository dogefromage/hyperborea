if(NOT LIBREMIDI_HAS_STD_SEMAPHORE)
  message(STATUS "libremidi: std::binary_semaphore not available, skipping JACK backend")
  set(LIBREMIDI_HAS_JACK 0)
  return()
endif()

find_path(WEAKJACK_PATH weakjack/weak_libjack.h HINTS "${WEAKJACK_FOLDER}")
find_path(JACK_PATH jack/jack.h)

if(WEAKJACK_PATH AND JACK_PATH)
  message(STATUS "libremidi: using WeakJACK")
  set(LIBREMIDI_HAS_JACK 1)
  set(LIBREMIDI_HAS_WEAKJACK 1)

  target_include_directories(libremidi ${_public} $<BUILD_INTERFACE:${WEAKJACK_PATH}> $<BUILD_INTERFACE:${JACK_PATH}>)
  target_link_libraries(libremidi ${_public} ${CMAKE_DL_LIBS})
elseif(JACK_PATH)
  find_library(JACK_LIBRARIES jack)
  if(JACK_LIBRARIES)
    message(STATUS "libremidi: using linked JACK")
    set(LIBREMIDI_HAS_JACK 1)

    target_link_libraries(libremidi ${_public} ${JACK_LIBRARIES})
    target_include_directories(libremidi ${_public} $<BUILD_INTERFACE:${JACK_PATH}>)
  endif()
endif()

if(LIBREMIDI_HAS_JACK)
  target_compile_definitions(libremidi ${_public} LIBREMIDI_JACK)
  if(LIBREMIDI_HAS_WEAKJACK)
    target_compile_definitions(libremidi ${_public} LIBREMIDI_WEAKJACK)
  endif()
endif()
