cmake_minimum_required (VERSION 2.6)

project(GSM)

# Cmake Variables

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${CMAKE_SOURCE_DIR}/lib)
set(__KDE_HAVE_GCC_VISIBILITY)
set(CMAKE_LIBRARY_PATH ..)

# My Variables

set (Src "src")

set (Classes			"${src}/classes")
    set (ARoom    		"${Classes}/ARoom")
    set (Client    		"${Classes}/Client")
    set (RoomManager		"${Classes}/RoomManager")
    set (ThreadPool   		"${Classes}/ThreadPool")

set (Mains			"${Src}/mains")

set (PortabilitySolution	"${Src}/portabilitySolution")
    set (Abstract  		"${PortabilitySolution}/abstract")
    	set(AFactory		"${Abstract}/AFactory")
    	set(AThread		"${Abstract}/AThread")
    	set(ICondvar		"${Abstract}/ICondVar")
    	set(IMutex		"${Abstract}/IMutex")
    	set(ISocket		"${Abstract}/ISocket")

    set (Concret   		"${PortabilitySolution}/concret")
        set (LinuxFactory   	"${Concret}/LinuxFactory")
 	       set (LinuxCondVar   	"${LinuxFactory}/LinuxCondVar")
 	       set (LinuxMutex   	"${LinuxFactory}/LinuxMutex")
 	       set (LinuxSocket   	"${LinuxFactory}/LinuxSocket")
 	       set (LinuxThread   	"${LinuxFactory}/LinuxThread")
        set (WindowsFactory   	"${Concret}/WindowsFactory")
 	       set (WindowsCondVar   	"${WindowsFactory}/WindowsCondVar")
 	       set (WindowsMutex   	"${WindowsFactory}/WindowsMutex")
 	       set (WindowsSocket   	"${WindowsFactory}/WindowsSocket")
 	       set (WindowsThread   	"${WindowsFactory}/WindowsThread")

set (Server			"${Src}/Server")

set (Templates			"${Src}/templates")
    set (Buffer    		"${Templates}/Buffer")
    set (Functor    		"${Templates}/Functor")
    set (InstanceCounter    	"${Templates}/InstanceCounter")
    set (ReferenceCounter    	"${Templates}/ReferenceCounter")
    set (SharedPointer		"${Templates}/SharedPointer")

## Includes Directories

include_directories(
	${AFactory}
	${AThread}
	${ARoom}
	${Buffer}
	${Client}
	${Functor}
	${ICondvar}
	${IMutex}
	${InstanceCounter}
	${ISocket}
	${ReferenceCounter}
	${RoomManager}
	${Server}
	${SharedPointer}
	${ThreadPool}
)

if(WIN32)
include_directories(
	${WindowsCondVar}
	${WindowsFactory}
 	${WindowsMutex}
 	${WindowsSocket}
 	${WindowsThread}
)
elseif(UNIX)
include_directories(
	${LinuxCondVar}
	${LinuxFactory}
 	${LinuxMutex}
 	${LinuxSocket}
 	${LinuxThread}
)
endif()

## Sources Files

file(
	GLOB
	${AFactory}/AFactory.cpp

	${AFactory}/AFactory.hh

	${AThread}
	${ARoom}
	${Buffer}
	${Client}
	${Functor}
	${ICondvar}
	${IMutex}
	${InstanceCounter}
	${ISocket}
	${ReferenceCounter}
	${RoomManager}
	${Server}
	${SharedPointer}
	${ThreadPool}
)

if(WIN32)
file(
	GLOB
	${WindowsCondVar}/WindowsCondVar.cpp
	${WindowsCondVar}/WindowsCondVar.h
	${WindowsCondVar}/WindowsCondVar.hh

	${WindowsFactory}/WindowsFactory.hh

 	${WindowsMutex}/WindowsMutex.cpp
 	${WindowsMutex}/WindowsMutex.h
 	${WindowsMutex}/WindowsMutex.hh

 	${WindowsSocket}/WindowsSocket.cpp
 	${WindowsSocket}/WindowsSocket.h
 	${WindowsSocket}/WindowsSocket.hh

 	${WindowsThread}/WindowsThread.cpp
 	${WindowsThread}/WindowsThread.h
 	${WindowsThread}/WindowsThread.hh
)
elseif(UNIX)
file(
	GLOB
	${LinuxCondVar}/LinuxCondVar.cpp
	${LinuxCondVar}/LinuxCondVar.h
	${LinuxCondVar}/LinuxCondVar.hh

	${LinuxFactory}/LinuxFactory.hh

 	${LinuxMutex}/LinuxMutex.cpp
 	${LinuxMutex}/LinuxMutex.h
 	${LinuxMutex}/LinuxMutex.hh

 	${LinuxSocket}/LinuxSocket.cpp
 	${LinuxSocket}/LinuxSocket.h
 	${LinuxSocket}/LinuxSocket.hh

 	${LinuxThread}/LinuxThread.cpp
 	${LinuxThread}/LinuxThread.h
 	${LinuxThread}/LinuxThread.hh
)
endif()

## Compile Flags

## SET(GCC_COVERAGE_COMPILE_FLAGS "-w -Wall -Werror -Wextra -pedantic")
## SET( CMAKE_CXX_FLAGS  " ${GCC_COVERAGE_COMPILE_FLAGS}" )

## Components

find_package(
	Threads
)

target_link_libraries (
		      R-Type ${CMAKE_THREAD_LIBS_INIT} ${GCC_COVERAGE_LINK_FLAGS}
)

## ...Finally...

add_executable(
	R-Type
	${srcs}
)
