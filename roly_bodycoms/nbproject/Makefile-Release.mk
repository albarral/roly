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
	${OBJECTDIR}/src/roly/bodycoms/BodyComs.o \
	${OBJECTDIR}/src/roly/bodycoms/in/ComsInBodyControl.o \
	${OBJECTDIR}/src/roly/bodycoms/in/ComsInBodySense.o \
	${OBJECTDIR}/src/roly/bodycoms/modules/BodyAware.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycoms.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycoms.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycoms.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/roly/bodycoms/BodyComs.o: src/roly/bodycoms/BodyComs.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodycoms
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodycoms/BodyComs.o src/roly/bodycoms/BodyComs.cpp

${OBJECTDIR}/src/roly/bodycoms/in/ComsInBodyControl.o: src/roly/bodycoms/in/ComsInBodyControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodycoms/in
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodycoms/in/ComsInBodyControl.o src/roly/bodycoms/in/ComsInBodyControl.cpp

${OBJECTDIR}/src/roly/bodycoms/in/ComsInBodySense.o: src/roly/bodycoms/in/ComsInBodySense.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodycoms/in
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodycoms/in/ComsInBodySense.o src/roly/bodycoms/in/ComsInBodySense.cpp

${OBJECTDIR}/src/roly/bodycoms/modules/BodyAware.o: src/roly/bodycoms/modules/BodyAware.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/roly/bodycoms/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/roly/bodycoms/modules/BodyAware.o src/roly/bodycoms/modules/BodyAware.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libroly_bodycoms.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
