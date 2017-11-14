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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/roly_bodymain

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/roly_bodymain: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/roly_bodymain ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/roly/bodymain/BodyControl.o: src/roly/bodymain/BodyControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodymain
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodymain/BodyControl.o src/roly/bodymain/BodyControl.cpp

${OBJECTDIR}/src/roly/bodymain/BodyTest.o: src/roly/bodymain/BodyTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodymain
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodymain/BodyTest.o src/roly/bodymain/BodyTest.cpp

${OBJECTDIR}/src/roly/bodymain/main.o: src/roly/bodymain/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodymain
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodymain/main.o src/roly/bodymain/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/roly_bodymain

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
