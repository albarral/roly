#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/roly/bodycoms/BodyComs.o \
	${OBJECTDIR}/src/roly/bodycoms/BodyConnector.o \
	${OBJECTDIR}/src/roly/bodycoms/modules/BodyAware.o \
	${OBJECTDIR}/src/roly/bodycoms/modules/BodyServer.o \
	${OBJECTDIR}/src/roly/bodycoms/server/ArtisticChannelServer.o \
	${OBJECTDIR}/src/roly/bodycoms/server/ExpressiveChannelServer.o \
	${OBJECTDIR}/src/roly/bodycoms/server/ExtraChannelServer.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-Wl,-rpath,../roly_bodycore/dist/Debug/GNU-Linux -L../roly_bodycore/dist/Debug/GNU-Linux -lroly_bodycore -Wl,-rpath,../../tron/robot/dist/Debug/GNU-Linux -L../../tron/robot/dist/Debug/GNU-Linux -ltron_robot -Wl,-rpath,../../tron/talky2/dist/Debug/GNU-Linux -L../../tron/talky2/dist/Debug/GNU-Linux -ltron_talky2 -Wl,-rpath,../../tron/tuly/dist/Debug/GNU-Linux -L../../tron/tuly/dist/Debug/GNU-Linux -ltron_tuly -Wl,-rpath,../../tron/wire/dist/Debug/GNU-Linux -L../../tron/wire/dist/Debug/GNU-Linux -ltron_wire -Wl,-rpath,../../tron/wire2/dist/Debug/GNU-Linux -L../../tron/wire2/dist/Debug/GNU-Linux -ltron_wire2

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycoms.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycoms.${CND_DLIB_EXT}: ../roly_bodycore/dist/Debug/GNU-Linux/libroly_bodycore.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycoms.${CND_DLIB_EXT}: ../../tron/robot/dist/Debug/GNU-Linux/libtron_robot.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycoms.${CND_DLIB_EXT}: ../../tron/talky2/dist/Debug/GNU-Linux/libtron_talky2.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycoms.${CND_DLIB_EXT}: ../../tron/tuly/dist/Debug/GNU-Linux/libtron_tuly.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycoms.${CND_DLIB_EXT}: ../../tron/wire/dist/Debug/GNU-Linux/libtron_wire.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycoms.${CND_DLIB_EXT}: ../../tron/wire2/dist/Debug/GNU-Linux/libtron_wire2.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycoms.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycoms.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/roly/bodycoms/BodyComs.o: src/roly/bodycoms/BodyComs.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodycoms
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_bodycore/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/tuly/src -I../../tron/wire/src -I../../tron/wire2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodycoms/BodyComs.o src/roly/bodycoms/BodyComs.cpp

${OBJECTDIR}/src/roly/bodycoms/BodyConnector.o: src/roly/bodycoms/BodyConnector.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodycoms
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_bodycore/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/tuly/src -I../../tron/wire/src -I../../tron/wire2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodycoms/BodyConnector.o src/roly/bodycoms/BodyConnector.cpp

${OBJECTDIR}/src/roly/bodycoms/modules/BodyAware.o: src/roly/bodycoms/modules/BodyAware.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodycoms/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_bodycore/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/tuly/src -I../../tron/wire/src -I../../tron/wire2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodycoms/modules/BodyAware.o src/roly/bodycoms/modules/BodyAware.cpp

${OBJECTDIR}/src/roly/bodycoms/modules/BodyServer.o: src/roly/bodycoms/modules/BodyServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodycoms/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_bodycore/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/tuly/src -I../../tron/wire/src -I../../tron/wire2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodycoms/modules/BodyServer.o src/roly/bodycoms/modules/BodyServer.cpp

${OBJECTDIR}/src/roly/bodycoms/server/ArtisticChannelServer.o: src/roly/bodycoms/server/ArtisticChannelServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodycoms/server
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_bodycore/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/tuly/src -I../../tron/wire/src -I../../tron/wire2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodycoms/server/ArtisticChannelServer.o src/roly/bodycoms/server/ArtisticChannelServer.cpp

${OBJECTDIR}/src/roly/bodycoms/server/ExpressiveChannelServer.o: src/roly/bodycoms/server/ExpressiveChannelServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodycoms/server
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_bodycore/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/tuly/src -I../../tron/wire/src -I../../tron/wire2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodycoms/server/ExpressiveChannelServer.o src/roly/bodycoms/server/ExpressiveChannelServer.cpp

${OBJECTDIR}/src/roly/bodycoms/server/ExtraChannelServer.o: src/roly/bodycoms/server/ExtraChannelServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodycoms/server
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_bodycore/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/tuly/src -I../../tron/wire/src -I../../tron/wire2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodycoms/server/ExtraChannelServer.o src/roly/bodycoms/server/ExtraChannelServer.cpp

# Subprojects
.build-subprojects:
	cd ../roly_bodycore && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/robot && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/talky2 && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/wire && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/wire2 && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycoms.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../roly_bodycore && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/robot && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/talky2 && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/wire && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/wire2 && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
