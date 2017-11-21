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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/roly/body/BodyManager.o \
	${OBJECTDIR}/src/roly/body/modules/ArmMover.o \
	${OBJECTDIR}/src/roly/body/modules/BodyModule.o \
	${OBJECTDIR}/src/roly/body/modules/Comfortable.o \
	${OBJECTDIR}/src/roly/body/moves/CyclicMove.o \
	${OBJECTDIR}/src/roly/body/moves/MoveFactory.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/roly/body/BodyManager.o: src/roly/body/BodyManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/body
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/body/BodyManager.o src/roly/body/BodyManager.cpp

${OBJECTDIR}/src/roly/body/modules/ArmMover.o: src/roly/body/modules/ArmMover.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/body/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/body/modules/ArmMover.o src/roly/body/modules/ArmMover.cpp

${OBJECTDIR}/src/roly/body/modules/BodyModule.o: src/roly/body/modules/BodyModule.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/body/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/body/modules/BodyModule.o src/roly/body/modules/BodyModule.cpp

${OBJECTDIR}/src/roly/body/modules/Comfortable.o: src/roly/body/modules/Comfortable.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/body/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/body/modules/Comfortable.o src/roly/body/modules/Comfortable.cpp

${OBJECTDIR}/src/roly/body/moves/CyclicMove.o: src/roly/body/moves/CyclicMove.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/body/moves
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/body/moves/CyclicMove.o src/roly/body/moves/CyclicMove.cpp

${OBJECTDIR}/src/roly/body/moves/MoveFactory.o: src/roly/body/moves/MoveFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/body/moves
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/body/moves/MoveFactory.o src/roly/body/moves/MoveFactory.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_body.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
