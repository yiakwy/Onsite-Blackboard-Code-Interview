function(echo)
	foreach(e ${ARGN})
		message(STATUS ${e})
	endforeach()
endfunction()

