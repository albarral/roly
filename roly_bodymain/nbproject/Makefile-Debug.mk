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
	${OBJECTDIR}/src/roly/bodymain/BodyControl.o \
	${OBJECTDIR}/src/roly/bodymain/BodyTest.o \
	${OBJECTDIR}/src/roly/bodymain/main.o


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
LDLIBSOPTIONS=-Wl,-rpath,../roly_body/dist/Debug/GNU-Linux -L../roly_body/dist/Debug/GNU-Linux -lroly_body -Wl,-rpath,../roly_bodycore/dist/Debug/GNU-Linux -L../roly_bodycore/dist/Debug/GNU-Linux -lroly_bodycore -Wl,-rpath,../roly_bodycoms/dist/Debug/GNU-Linux -L../roly_bodycoms/dist/Debug/GNU-Linux -lroly_bodycoms -Wl,-rpath,../../tron/maty/dist/Debug/GNU-Linux -L../../tron/maty/dist/Debug/GNU-Linux -ltron_maty -Wl,-rpath,../../tron/robot/dist/Debug/GNU-Linux -L../../tron/robot/dist/Debug/GNU-Linux -ltron_robot -Wl,-rpath,../../tron/talky2/dist/Debug/GNU-Linux -L../../tron/talky2/dist/Debug/GNU-Linux -ltron_talky2 -Wl,-rpath,../../tron/tuly/dist/Debug/GNU-Linux -L../../tron/tuly/dist/Debug/GNU-Linux -ltron_tuly -Wl,-rpath,../../tron/wire/dist/Debug/GNU-Linux -L../../tron/wire/dist/Debug/GNU-Linux -ltron_wire -Wl,-rpath,../../tron/wire2/dist/Debug/GNU-Linux -L../../tron/wire2/dist/Debug/GNU-Linux -ltron_wire2 -llog4cxx -lopencv_core -Wl,-rpath,../../tron/language/dist/Debug/GNU-Linux -L../../tron/language/dist/Debug/GNU-Linux -ltron_language

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody: ../roly_body/dist/Debug/GNU-Linux/libroly_body.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody: ../roly_bodycore/dist/Debug/GNU-Linux/libroly_bodycore.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody: ../roly_bodycoms/dist/Debug/GNU-Linux/libroly_bodycoms.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody: ../../tron/maty/dist/Debug/GNU-Linux/libtron_maty.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody: ../../tron/robot/dist/Debug/GNU-Linux/libtron_robot.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody: ../../tron/talky2/dist/Debug/GNU-Linux/libtron_talky2.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody: ../../tron/tuly/dist/Debug/GNU-Linux/libtron_tuly.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody: ../../tron/wire/dist/Debug/GNU-Linux/libtron_wire.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody: ../../tron/wire2/dist/Debug/GNU-Linux/libtron_wire2.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody: ../../tron/language/dist/Debug/GNU-Linux/libtron_language.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/roly/bodymain/BodyControl.o: src/roly/bodymain/BodyControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodymain
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_body/src -I../roly_bodycore/src -I../roly_bodycoms/src -I../../tron/maty/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/tuly/src -I../../tron/wire/src -I../../tron/wire2/src -I../../tron/language/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodymain/BodyControl.o src/roly/bodymain/BodyControl.cpp

${OBJECTDIR}/src/roly/bodymain/BodyTest.o: src/roly/bodymain/BodyTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodymain
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_body/src -I../roly_bodycore/src -I../roly_bodycoms/src -I../../tron/maty/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/tuly/src -I../../tron/wire/src -I../../tron/wire2/src -I../../tron/language/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodymain/BodyTest.o src/roly/bodymain/BodyTest.cpp

${OBJECTDIR}/src/roly/bodymain/main.o: src/roly/bodymain/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodymain
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_body/src -I../roly_bodycore/src -I../roly_bodycoms/src -I../../tron/maty/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/tuly/src -I../../tron/wire/src -I../../tron/wire2/src -I../../tron/language/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodymain/main.o src/roly/bodymain/main.cpp

# Subprojects
.build-subprojects:
	cd ../roly_body && ${MAKE}  -f Makefile CONF=Debug
	cd ../roly_bodycore && ${MAKE}  -f Makefile CONF=Debug
	cd ../roly_bodycoms && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/maty && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/robot && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/talky2 && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/wire && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/wire2 && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/language && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody

# Subprojects
.clean-subprojects:
	cd ../roly_body && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../roly_bodycore && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../roly_bodycoms && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/maty && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/robot && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/talky2 && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/wire && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/wire2 && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/language && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
