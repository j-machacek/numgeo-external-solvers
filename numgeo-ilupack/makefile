#=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~=~
#                                          numgeo
#                     Copyright (C) 2022 Jan Machacek, Patrick Staubach
#=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~=~
#
# PROGRAM: numgeo-ilupack
#
#> author: Jan Machacek, jan-machacek@outlook.com
#
#
#>### SUMMARY: 
#> Program that solves a linear system of equations given in coordinate format using the
#> ILUPACK library. This software is part of the numgeo software developed by
#> Jan Machacek and Patrick Staubach.
#
#
#>### REVISION HISTORY
#> 03.01.2022, J. Machacek - Initial version
#
#>### DISCLAIMER
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR PARTICULAR PURPOSE.
#
#=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~=~

-include ../makefile.init

RM := rm -rf

# Every subdirectory with source files must be described here
SUBDIRS := \
. \

# Add inputs and outputs from these tool invocations to the build variables 
F90_SRCS += \
./src/main.f90 

OBJS += \
./main.o 

# Each subdirectory must supply rules for building sources it contributes
main.o: ./src/main.f90 
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Fortran Compiler'
	gfortran -fopenmp -funderscoring -O3 -Wall -c -fmessage-length=0 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.o: ./src/main.f90

# Objects
USER_OBJS :=
LIBS := -lilupack_mumps -lmumps -lcamd -lamd -lmetisomp -lmetis -lmetisomp -lsparspak -lsuitesparseconfig -llapack -lblaslike -lblas


ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := numgeo-ilupack
BUILD_ARTIFACT_EXTENSION :=
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: main-build

# Main-build Target
main-build: numgeo-ilupack

# Tool invocations
numgeo-ilupack: $(OBJS) $(USER_OBJS) $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU Fortran Linker'
	gfortran -fopenmp -fPIC -L./lib -o "numgeo-ilupack" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) numgeo-ilupack
	-@echo ' '

.PHONY: all clean dependents main-build

-include ../makefile.targets
