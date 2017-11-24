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
	${OBJECTDIR}/src/roly/bodycoms/modules/BodyCommander.o \
	${OBJECTDIR}/src/roly/bodycoms/modules/BodyInspector.o


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
LDLIBSOPTIONS=-Wl,-rpath,../roly_bodycore/dist/Debug/GNU-Linux -L../roly_bodycore/dist/Debug/GNU-Linux -lroly_bodycore -Wl,-rpath,../../tron/tuly/dist/Debug/GNU-Linux -L../../tron/tuly/dist/Debug/GNU-Linux -ltron_tuly -Wl,-rpath,../../tron/nety/dist/Debug/GNU-Linux -L../../tron/nety/dist/Debug/GNU-Linux -ltron_nety -Wl,-rpath,../../tron/talky/dist/Debug/GNU-Linux -L../../tron/talky/dist/Debug/GNU-Linux -ltron_talky -Wl,-rpath,../../tron/comy/dist/Debug/GNU-Linux -L../../tron/comy/dist/Debug/GNU-Linux -ltron_comy

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycoms.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycoms.${CND_DLIB_EXT}: ../roly_bodycore/dist/Debug/GNU-Linux/libroly_bodycore.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycoms.${CND_DLIB_EXT}: ../../tron/tuly/dist/Debug/GNU-Linux/libtron_tuly.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycoms.${CND_DLIB_EXT}: ../../tron/nety/dist/Debug/GNU-Linux/libtron_nety.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycoms.${CND_DLIB_EXT}: ../../tron/talky/dist/Debug/GNU-Linux/libtron_talky.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycoms.${CND_DLIB_EXT}: ../../tron/comy/dist/Debug/GNU-Linux/libtron_comy.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycoms.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycoms.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/roly/bodycoms/BodyComs.o: src/roly/bodycoms/BodyComs.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodycoms
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_bodycore/src -I../../tron/tuly/src -I../../tron/nety/src -I../../tron/talky/src -I../../tron/comy/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodycoms/BodyComs.o src/roly/bodycoms/BodyComs.cpp

${OBJECTDIR}/src/roly/bodycoms/modules/BodyCommander.o: src/roly/bodycoms/modules/BodyCommander.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodycoms/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_bodycore/src -I../../tron/tuly/src -I../../tron/nety/src -I../../tron/talky/src -I../../tron/comy/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodycoms/modules/BodyCommander.o src/roly/bodycoms/modules/BodyCommander.cpp

${OBJECTDIR}/src/roly/bodycoms/modules/BodyInspector.o: src/roly/bodycoms/modules/BodyInspector.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodycoms/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_bodycore/src -I../../tron/tuly/src -I../../tron/nety/src -I../../tron/talky/src -I../../tron/comy/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodycoms/modules/BodyInspector.o src/roly/bodycoms/modules/BodyInspector.cpp

# Subprojects
.build-subprojects:
	cd ../roly_bodycore && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/nety && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/talky && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/comy && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycoms.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../roly_bodycore && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/nety && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/talky && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/comy && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
