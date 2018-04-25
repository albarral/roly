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
	${OBJECTDIR}/src/roly/bodycore/ArtisticBus.o \
	${OBJECTDIR}/src/roly/bodycore/BodyBus.o \
	${OBJECTDIR}/src/roly/bodycore/config/ArtisticConfig.o \
	${OBJECTDIR}/src/roly/bodycore/config/BodyConfig.o \
	${OBJECTDIR}/src/roly/bodycore/config/ComfortableConfig.o


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
LDLIBSOPTIONS=-Wl,-rpath,../../tron/tron_control/dist/Debug/GNU-Linux -L../../tron/tron_control/dist/Debug/GNU-Linux -ltron_control

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycore.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycore.${CND_DLIB_EXT}: ../../tron/tron_control/dist/Debug/GNU-Linux/libtron_control.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycore.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycore.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/roly/bodycore/ArtisticBus.o: src/roly/bodycore/ArtisticBus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodycore
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/tron_control/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodycore/ArtisticBus.o src/roly/bodycore/ArtisticBus.cpp

${OBJECTDIR}/src/roly/bodycore/BodyBus.o: src/roly/bodycore/BodyBus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodycore
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/tron_control/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodycore/BodyBus.o src/roly/bodycore/BodyBus.cpp

${OBJECTDIR}/src/roly/bodycore/config/ArtisticConfig.o: src/roly/bodycore/config/ArtisticConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodycore/config
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/tron_control/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodycore/config/ArtisticConfig.o src/roly/bodycore/config/ArtisticConfig.cpp

${OBJECTDIR}/src/roly/bodycore/config/BodyConfig.o: src/roly/bodycore/config/BodyConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodycore/config
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/tron_control/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodycore/config/BodyConfig.o src/roly/bodycore/config/BodyConfig.cpp

${OBJECTDIR}/src/roly/bodycore/config/ComfortableConfig.o: src/roly/bodycore/config/ComfortableConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodycore/config
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/tron_control/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodycore/config/ComfortableConfig.o src/roly/bodycore/config/ComfortableConfig.cpp

# Subprojects
.build-subprojects:
	cd ../../tron/tron_control && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycore.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../../tron/tron_control && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
