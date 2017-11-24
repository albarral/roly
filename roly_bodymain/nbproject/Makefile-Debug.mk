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
LDLIBSOPTIONS=-Wl,-rpath,../roly_body/dist/Debug/GNU-Linux -L../roly_body/dist/Debug/GNU-Linux -lroly_body -Wl,-rpath,../roly_bodycore/dist/Debug/GNU-Linux -L../roly_bodycore/dist/Debug/GNU-Linux -lroly_bodycore -Wl,-rpath,../roly_bodycoms/dist/Debug/GNU-Linux -L../roly_bodycoms/dist/Debug/GNU-Linux -lroly_bodycoms -Wl,-rpath,../../tron/tuly/dist/Debug/GNU-Linux -L../../tron/tuly/dist/Debug/GNU-Linux -ltron_tuly -Wl,-rpath,../../tron/nety/dist/Debug/GNU-Linux -L../../tron/nety/dist/Debug/GNU-Linux -ltron_nety -Wl,-rpath,../../tron/talky/dist/Debug/GNU-Linux -L../../tron/talky/dist/Debug/GNU-Linux -ltron_talky -Wl,-rpath,../../tron/comy/dist/Debug/GNU-Linux -L../../tron/comy/dist/Debug/GNU-Linux -ltron_comy -Wl,-rpath,../../tron/maty/dist/Debug/GNU-Linux -L../../tron/maty/dist/Debug/GNU-Linux -ltron_maty -llog4cxx

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody: ../roly_body/dist/Debug/GNU-Linux/libroly_body.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody: ../roly_bodycore/dist/Debug/GNU-Linux/libroly_bodycore.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody: ../roly_bodycoms/dist/Debug/GNU-Linux/libroly_bodycoms.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody: ../../tron/tuly/dist/Debug/GNU-Linux/libtron_tuly.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody: ../../tron/nety/dist/Debug/GNU-Linux/libtron_nety.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody: ../../tron/talky/dist/Debug/GNU-Linux/libtron_talky.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody: ../../tron/comy/dist/Debug/GNU-Linux/libtron_comy.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody: ../../tron/maty/dist/Debug/GNU-Linux/libtron_maty.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/roly/bodymain/BodyControl.o: src/roly/bodymain/BodyControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodymain
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_body/src -I../roly_bodycore/src -I../roly_bodycoms/src -I../../tron/tuly/src -I../../tron/nety/src -I../../tron/talky/src -I../../tron/comy/src -I../../tron/maty/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodymain/BodyControl.o src/roly/bodymain/BodyControl.cpp

${OBJECTDIR}/src/roly/bodymain/BodyTest.o: src/roly/bodymain/BodyTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodymain
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_body/src -I../roly_bodycore/src -I../roly_bodycoms/src -I../../tron/tuly/src -I../../tron/nety/src -I../../tron/talky/src -I../../tron/comy/src -I../../tron/maty/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodymain/BodyTest.o src/roly/bodymain/BodyTest.cpp

${OBJECTDIR}/src/roly/bodymain/main.o: src/roly/bodymain/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodymain
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../roly_body/src -I../roly_bodycore/src -I../roly_bodycoms/src -I../../tron/tuly/src -I../../tron/nety/src -I../../tron/talky/src -I../../tron/comy/src -I../../tron/maty/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodymain/main.o src/roly/bodymain/main.cpp

# Subprojects
.build-subprojects:
	cd ../roly_body && ${MAKE}  -f Makefile CONF=Debug
	cd ../roly_bodycore && ${MAKE}  -f Makefile CONF=Debug
	cd ../roly_bodycoms && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/nety && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/talky && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/comy && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/maty && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rolybody

# Subprojects
.clean-subprojects:
	cd ../roly_body && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../roly_bodycore && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../roly_bodycoms && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/nety && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/talky && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/comy && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/maty && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
