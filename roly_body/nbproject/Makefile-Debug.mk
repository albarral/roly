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
	${OBJECTDIR}/src/roly/body/BodyManager.o \
	${OBJECTDIR}/src/roly/body/modules/Artistic.o \
	${OBJECTDIR}/src/roly/body/modules/BodyModule.o \
	${OBJECTDIR}/src/roly/body/modules/ComfortableArm.o \
	${OBJECTDIR}/src/roly/body/modules/Expressive.o \
	${OBJECTDIR}/src/roly/body/moves/ArmMovement.o


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
LDLIBSOPTIONS=-Wl,-rpath,../roly_bodycore/dist/Debug/GNU-Linux -L../roly_bodycore/dist/Debug/GNU-Linux -lroly_bodycore -Wl,-rpath,../../tron/language/dist/Debug/GNU-Linux -L../../tron/language/dist/Debug/GNU-Linux -ltron_language -Wl,-rpath,../../tron/maty/dist/Debug/GNU-Linux -L../../tron/maty/dist/Debug/GNU-Linux -ltron_maty -Wl,-rpath,../../tron/moves/dist/Debug/GNU-Linux -L../../tron/moves/dist/Debug/GNU-Linux -ltron_moves -Wl,-rpath,../../tron/robot/dist/Debug/GNU-Linux -L../../tron/robot/dist/Debug/GNU-Linux -ltron_robot -Wl,-rpath,../../tron/talky2/dist/Debug/GNU-Linux -L../../tron/talky2/dist/Debug/GNU-Linux -ltron_talky2 -Wl,-rpath,../../tron/tuly/dist/Debug/GNU-Linux -L../../tron/tuly/dist/Debug/GNU-Linux -ltron_tuly -Wl,-rpath,../../tron/wire/dist/Debug/GNU-Linux -L../../tron/wire/dist/Debug/GNU-Linux -ltron_wire -Wl,-rpath,../../tron/wire2/dist/Debug/GNU-Linux -L../../tron/wire2/dist/Debug/GNU-Linux -ltron_wire2

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}: ../roly_bodycore/dist/Debug/GNU-Linux/libroly_bodycore.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}: ../../tron/language/dist/Debug/GNU-Linux/libtron_language.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}: ../../tron/maty/dist/Debug/GNU-Linux/libtron_maty.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}: ../../tron/moves/dist/Debug/GNU-Linux/libtron_moves.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}: ../../tron/robot/dist/Debug/GNU-Linux/libtron_robot.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}: ../../tron/talky2/dist/Debug/GNU-Linux/libtron_talky2.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}: ../../tron/tuly/dist/Debug/GNU-Linux/libtron_tuly.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}: ../../tron/wire/dist/Debug/GNU-Linux/libtron_wire.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}: ../../tron/wire2/dist/Debug/GNU-Linux/libtron_wire2.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/roly/body/BodyManager.o: src/roly/body/BodyManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/body
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_bodycore/src -I../../tron/language/src -I../../tron/maty/src -I../../tron/moves/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/tuly/src -I../../tron/wire/src -I../../tron/wire2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/body/BodyManager.o src/roly/body/BodyManager.cpp

${OBJECTDIR}/src/roly/body/modules/Artistic.o: src/roly/body/modules/Artistic.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/body/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_bodycore/src -I../../tron/language/src -I../../tron/maty/src -I../../tron/moves/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/tuly/src -I../../tron/wire/src -I../../tron/wire2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/body/modules/Artistic.o src/roly/body/modules/Artistic.cpp

${OBJECTDIR}/src/roly/body/modules/BodyModule.o: src/roly/body/modules/BodyModule.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/body/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_bodycore/src -I../../tron/language/src -I../../tron/maty/src -I../../tron/moves/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/tuly/src -I../../tron/wire/src -I../../tron/wire2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/body/modules/BodyModule.o src/roly/body/modules/BodyModule.cpp

${OBJECTDIR}/src/roly/body/modules/ComfortableArm.o: src/roly/body/modules/ComfortableArm.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/body/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_bodycore/src -I../../tron/language/src -I../../tron/maty/src -I../../tron/moves/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/tuly/src -I../../tron/wire/src -I../../tron/wire2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/body/modules/ComfortableArm.o src/roly/body/modules/ComfortableArm.cpp

${OBJECTDIR}/src/roly/body/modules/Expressive.o: src/roly/body/modules/Expressive.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/body/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_bodycore/src -I../../tron/language/src -I../../tron/maty/src -I../../tron/moves/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/tuly/src -I../../tron/wire/src -I../../tron/wire2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/body/modules/Expressive.o src/roly/body/modules/Expressive.cpp

${OBJECTDIR}/src/roly/body/moves/ArmMovement.o: src/roly/body/moves/ArmMovement.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/body/moves
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_bodycore/src -I../../tron/language/src -I../../tron/maty/src -I../../tron/moves/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/tuly/src -I../../tron/wire/src -I../../tron/wire2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/body/moves/ArmMovement.o src/roly/body/moves/ArmMovement.cpp

# Subprojects
.build-subprojects:
	cd ../roly_bodycore && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/language && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/maty && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/moves && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/robot && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/talky2 && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/wire && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/wire2 && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../roly_bodycore && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/language && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/maty && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/moves && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/robot && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/talky2 && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/wire && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/wire2 && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
