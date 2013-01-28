cmake_minimum_required (VERSION 2.6)

project(GSM)

# Cmake Variables

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${CMAKE_SOURCE_DIR}/lib)
set(__KDE_HAVE_GCC_VISIBILITY)
set(CMAKE_LIBRARY_PATH ..)

# My Variables

set (Src "src")

set (Classes			"${Src}/classes")
##    set (ARoom    		"${Classes}/ARoom")
##    set (Client    		"${Classes}/Client")
##    set (RoomManager		"${Classes}/RoomManager")
    set (Server   		"${Classes}/Server")
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
 	       set (LinuxMultiplexer   	"${LinuxFactory}/LinuxMultiplexer")
 	       set (LinuxMutex   	"${LinuxFactory}/LinuxMutex")
 	       set (LinuxSocket   	"${LinuxFactory}/LinuxSocket")
	       	   set (LinuxSocketTCP  "${LinuxSocket}/LinuxSocketTCP")
	       	   set (LinuxSocketUDP  "${LinuxSocket}/LinuxSocketUDP")
 	       set (LinuxThread   	"${LinuxFactory}/LinuxThread")
        set (WindowsFactory   	"${Concret}/WindowsFactory")
 	       set (WindowsCondVar   	"${WindowsFactory}/WindowsCondVar")
 	       set (WindowsMutex   	"${WindowsFactory}/WindowsMutex")
 	       set (WindowsSocket   	"${WindowsFactory}/WindowsSocket")
	       	   set (WindowsSocketTCP  "${WindowsSocket}/WindowsSocketTCP")
	       	   set (WindowsSocketUDP  "${WindowsSocket}/WindowsSocketUDP")
 	       set (WindowsThread   	"${WindowsFactory}/WindowsThread")

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
 	${WindowsSocketTCP}
 	${WindowsSocketUDP}
 	${WindowsThread}
)
elseif(UNIX)
include_directories(
	${LinuxCondVar}
	${LinuxFactory}
 	${LinuxMultiplexer}
 	${LinuxMutex}
 	${LinuxSocket}
 	${LinuxSocketTCP}
 	${LinuxSocketUDP}
 	${LinuxThread}
)
endif()

## Sources Files

file(
	GLOB
	srcs

	${AFactory}/AFactory.cpp
	${AFactory}/AFactory.hpp
	${AFactory}/Factories.hpp

	${AThread}/AThread.cpp
	${AThread}/AThread.hpp

	${ARoom}/ARoom.cpp
	${ARoom}/ARoom.hpp

	${Buffer}/Buffer.cpp
	${Buffer}/Buffer.hpp

	${Client}/Client.cpp
	${Client}/Client.hpp

	${Functor}/Functor.cpp
	${Functor}/Functor.hpp

	${ICondvar}/ICondvar.cpp
	${ICondvar}/ICondvar.hpp

	${IMutex}/IMutex.cpp
	${IMutex}/IMutex.hpp

	${InstanceCounter}/InstanceCounter.cpp
	${InstanceCounter}/InstanceCounter.hpp

	${ISocket}/ISocket.cpp
	${ISocket}/ISocket.hpp

	${ReferenceCounter}/ReferenceCounter.cpp
	${ReferenceCounter}/ReferenceCounter.hpp

	${RoomManager}/RoomManager.cpp
	${RoomManager}/RoomManager.hpp

	${Server}/Server.cpp
	${Server}/Server.hpp

	${SharedPointer}/SharedPointer.cpp
	${SharedPointer}/SharedPointer.hpp

	${ThreadPool}/ThreadPool.cpp
	${ThreadPool}/ThreadPool.hpp
)

if(WIN32)
file(
	GLOB
	srcs

	${srcs}

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
	srcs
	${srcs}

	${LinuxCondVar}/LinuxCondVar.cpp
	${LinuxCondVar}/LinuxCondVar.h
	${LinuxCondVar}/LinuxCondVar.hpp

	${LinuxFactory}/LinuxFactory.hpp

 	${LinuxMultiplexer}/LinuxMultiplexer.cpp
 	${LinuxMultiplexer}/LinuxMultiplexer.h
 	${LinuxMultiplexer}/LinuxMultiplexer.hpp

 	${LinuxMutex}/LinuxMutex.cpp
 	${LinuxMutex}/LinuxMutex.h
 	${LinuxMutex}/LinuxMutex.hpp

 	${LinuxSocket}/ALinuxSocket.cpp
 	${LinuxSocket}/ALinuxSocket.h
 	${LinuxSocket}/ALinuxSocket.hpp

 	${LinuxSocketTCP}/ALinuxSocketTCP.cpp
 	${LinuxSocketTCP}/ALinuxSocketTCP.h
 	${LinuxSocketTCP}/ALinuxSocketTCP.hpp

 	${LinuxSocketUDP}/ALinuxSocketUDP.cpp
 	${LinuxSocketUDP}/ALinuxSocketUDP.h
 	${LinuxSocketUDP}/ALinuxSocketUDP.hpp

 	${LinuxThread}/LinuxThread.cpp
 	${LinuxThread}/LinuxThread.h
 	${LinuxThread}/LinuxThread.hpp
)
endif()

## Compile Flags

SET(CMAKE_BUILD_TYPE release)
SET(CMAKE_CXX_FLAGS_RELEASE "-W -Wall -Werror -Wextra -pedantic -O2")

## ...Finally...

add_executable(
	R-Type
	${srcs}
	${Mains}/main.cpp
)

## Components

find_package(
	Threads
)

target_link_libraries (
		      R-Type
		      ${CMAKE_THREAD_LIBS_INIT}
)
