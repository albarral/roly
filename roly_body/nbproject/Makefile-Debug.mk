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
	${OBJECTDIR}/src/roly/body/BodyBehaviour.o \
	${OBJECTDIR}/src/roly/body/BodyManager.o \
	${OBJECTDIR}/src/roly/body/modules/ArmSense2.o \
	${OBJECTDIR}/src/roly/body/modules/Artistic2.o \
	${OBJECTDIR}/src/roly/body/modules/Comfort2.o \
	${OBJECTDIR}/src/roly/body/modules/Expressive2.o


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
LDLIBSOPTIONS=-Wl,-rpath,../roly_bodycore/dist/Debug/GNU-Linux -L../roly_bodycore/dist/Debug/GNU-Linux -lroly_bodycore -Wl,-rpath,../../tron/tron_control/dist/Debug/GNU-Linux -L../../tron/tron_control/dist/Debug/GNU-Linux -ltron_control -Wl,-rpath,../../tron/tron_math/dist/Debug/GNU-Linux -L../../tron/tron_math/dist/Debug/GNU-Linux -ltron_math -Wl,-rpath,../../tron/tron_util/dist/Debug/GNU-Linux -L../../tron/tron_util/dist/Debug/GNU-Linux -ltron_util -Wl,-rpath,../../tron2/tron2_language/dist/Debug/GNU-Linux -L../../tron2/tron2_language/dist/Debug/GNU-Linux -ltron2_language -Wl,-rpath,../../tron2/tron2_moves/dist/Debug/GNU-Linux -L../../tron2/tron2_moves/dist/Debug/GNU-Linux -ltron2_moves -Wl,-rpath,../../tron2/tron2_knowledge/dist/Debug/GNU-Linux -L../../tron2/tron2_knowledge/dist/Debug/GNU-Linux -ltron2_knowledge -Wl,-rpath,../../amy/amy_interface2/dist/Debug/GNU-Linux -L../../amy/amy_interface2/dist/Debug/GNU-Linux -lamy_interface2

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}: ../roly_bodycore/dist/Debug/GNU-Linux/libroly_bodycore.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}: ../../tron/tron_control/dist/Debug/GNU-Linux/libtron_control.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}: ../../tron/tron_math/dist/Debug/GNU-Linux/libtron_math.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}: ../../tron/tron_util/dist/Debug/GNU-Linux/libtron_util.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}: ../../tron2/tron2_language/dist/Debug/GNU-Linux/libtron2_language.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}: ../../tron2/tron2_moves/dist/Debug/GNU-Linux/libtron2_moves.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}: ../../tron2/tron2_knowledge/dist/Debug/GNU-Linux/libtron2_knowledge.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}: ../../amy/amy_interface2/dist/Debug/GNU-Linux/libamy_interface2.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/roly/body/BodyBehaviour.o: src/roly/body/BodyBehaviour.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/body
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_bodycore/src -I../../tron/tron_control/src -I../../tron/tron_math/src -I../../tron/tron_coms/src -I../../tron/tron_interface/src -I../../tron/tron_topics/src -I../../tron/tron_util/src -I../../tron2/tron2_language/src -I../../tron2/tron2_moves/src -I../../tron2/tron2_knowledge/src -I../../amy/amy_interface2/src -I/usr/include/ignition/transport3 -I/usr/include/ignition/msgs0 -I/usr/include/ignition/math2 -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/body/BodyBehaviour.o src/roly/body/BodyBehaviour.cpp

${OBJECTDIR}/src/roly/body/BodyManager.o: src/roly/body/BodyManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/body
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_bodycore/src -I../../tron/tron_control/src -I../../tron/tron_math/src -I../../tron/tron_coms/src -I../../tron/tron_interface/src -I../../tron/tron_topics/src -I../../tron/tron_util/src -I../../tron2/tron2_language/src -I../../tron2/tron2_moves/src -I../../tron2/tron2_knowledge/src -I../../amy/amy_interface2/src -I/usr/include/ignition/transport3 -I/usr/include/ignition/msgs0 -I/usr/include/ignition/math2 -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/body/BodyManager.o src/roly/body/BodyManager.cpp

${OBJECTDIR}/src/roly/body/modules/ArmSense2.o: src/roly/body/modules/ArmSense2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/body/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_bodycore/src -I../../tron/tron_control/src -I../../tron/tron_math/src -I../../tron/tron_coms/src -I../../tron/tron_interface/src -I../../tron/tron_topics/src -I../../tron/tron_util/src -I../../tron2/tron2_language/src -I../../tron2/tron2_moves/src -I../../tron2/tron2_knowledge/src -I../../amy/amy_interface2/src -I/usr/include/ignition/transport3 -I/usr/include/ignition/msgs0 -I/usr/include/ignition/math2 -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/body/modules/ArmSense2.o src/roly/body/modules/ArmSense2.cpp

${OBJECTDIR}/src/roly/body/modules/Artistic2.o: src/roly/body/modules/Artistic2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/body/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_bodycore/src -I../../tron/tron_control/src -I../../tron/tron_math/src -I../../tron/tron_coms/src -I../../tron/tron_interface/src -I../../tron/tron_topics/src -I../../tron/tron_util/src -I../../tron2/tron2_language/src -I../../tron2/tron2_moves/src -I../../tron2/tron2_knowledge/src -I../../amy/amy_interface2/src -I/usr/include/ignition/transport3 -I/usr/include/ignition/msgs0 -I/usr/include/ignition/math2 -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/body/modules/Artistic2.o src/roly/body/modules/Artistic2.cpp

${OBJECTDIR}/src/roly/body/modules/Comfort2.o: src/roly/body/modules/Comfort2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/body/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_bodycore/src -I../../tron/tron_control/src -I../../tron/tron_math/src -I../../tron/tron_coms/src -I../../tron/tron_interface/src -I../../tron/tron_topics/src -I../../tron/tron_util/src -I../../tron2/tron2_language/src -I../../tron2/tron2_moves/src -I../../tron2/tron2_knowledge/src -I../../amy/amy_interface2/src -I/usr/include/ignition/transport3 -I/usr/include/ignition/msgs0 -I/usr/include/ignition/math2 -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/body/modules/Comfort2.o src/roly/body/modules/Comfort2.cpp

${OBJECTDIR}/src/roly/body/modules/Expressive2.o: src/roly/body/modules/Expressive2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/body/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_bodycore/src -I../../tron/tron_control/src -I../../tron/tron_math/src -I../../tron/tron_coms/src -I../../tron/tron_interface/src -I../../tron/tron_topics/src -I../../tron/tron_util/src -I../../tron2/tron2_language/src -I../../tron2/tron2_moves/src -I../../tron2/tron2_knowledge/src -I../../amy/amy_interface2/src -I/usr/include/ignition/transport3 -I/usr/include/ignition/msgs0 -I/usr/include/ignition/math2 -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/body/modules/Expressive2.o src/roly/body/modules/Expressive2.cpp

# Subprojects
.build-subprojects:
	cd ../roly_bodycore && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_control && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_math && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_util && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron2/tron2_language && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron2/tron2_moves && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron2/tron2_knowledge && ${MAKE}  -f Makefile CONF=Debug
	cd ../../amy/amy_interface2 && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../roly_bodycore && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_control && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_math && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_util && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron2/tron2_language && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron2/tron2_moves && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron2/tron2_knowledge && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../amy/amy_interface2 && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
