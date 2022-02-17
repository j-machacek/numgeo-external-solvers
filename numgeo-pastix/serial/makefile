#=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~=~
#                                          numgeo
#                     Copyright (C) 2022 Jan Machacek, Patrick Staubach
#=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~=~
#
# PROGRAM: numgeo-pastix
#
#> author: Jan Machacek, jan-machacek@outlook.com
#
#
#>### SUMMARY: 
#> Program that solves a linear system of equations given in coordinate format using the PaStiX library
# (see https://gitlab.inria.fr/solverstack/pastix).
#  Many thanks to Mathieu Faverge (mathieu.faverge@inria.fr) from INRIA helping us setting up PaStiX! 
#
# This software is part of the numgeo software developed by Jan Machacek and Patrick Staubach.
#
#
#>### REVISION HISTORY
#> 19.01.2021, J. Machacek - Initial version
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
./src/main.f90 \
./src/pastix_enums.f90 \
./src/pastixf.f90 \
./src/spm_enums.f90 \
./src/spmf.f90 

OBJS += \
./main.o \
./pastix_enums.o \
./pastixf.o \
./spm_enums.o \
./spmf.o 


# Each subdirectory must supply rules for building sources it contributes

# This is the actual program
main.o: ./src/main.f90
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Fortran Compiler'
	gfortran -funderscoring -O3 -Wall -c -fmessage-length=0  -fopenmp -cpp -lpthread -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
main.o: ./src/main.f90 pastix_enums.o pastixf.o spmf.o

# Needed py PaStiX
pastix_enums.o: ./src/pastix_enums.f90
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Fortran Compiler'
	gfortran -funderscoring -O3 -Wall -c -fmessage-length=0  -fopenmp -cpp -lpthread -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
pastix_enums.o: ./src/pastix_enums.f90

# Needed py PaStiX (Fortran interface)
pastixf.o: ./src/pastixf.f90
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Fortran Compiler'
	gfortran -funderscoring -O3 -Wall -c -fmessage-length=0  -fopenmp -cpp -lpthread -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
pastixf.o: ./src/pastixf.f90 pastix_enums.o spmf.o

# Needed py PaStiX (sparse matrix package)
spm_enums.o: ./src/spm_enums.f90
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Fortran Compiler'
	gfortran -funderscoring -O3 -Wall -c -fmessage-length=0  -fopenmp -cpp -lpthread -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
spm_enums.o: ./src/spm_enums.f90

# Needed py PaStiX (sparse matrix package, Fortran interface)
spmf.o: ./src/spmf.f90
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Fortran Compiler'
	gfortran -funderscoring -O3 -Wall -c -fmessage-length=0  -fopenmp -cpp -lpthread -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
spmf.o: ./src/spmf.f90 spm_enums.o


# Objects and libraries
USER_OBJS :=
LIBS := -lpastixf -lspmf -lpastix -lpastix_kernels -lspm -llapacke -lopenblas -lpthread -lscotch -lscotcherrexit -lz -lm -lrt -lhwloc


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


BUILD_ARTIFACT_NAME := numgeo-pastix
BUILD_ARTIFACT_EXTENSION :=
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: main-build

# Main-build Target
main-build: numgeo-pastix

# Tool invocations
numgeo-pastix: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU Fortran Linker'
	gfortran -L./lib -fopenmp -lpthread -o "numgeo-pastix" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) numgeo-pastix
	-@echo ' '

.PHONY: all clean dependents main-build

-include ../makefile.targets
