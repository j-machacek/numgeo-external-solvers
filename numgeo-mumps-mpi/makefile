#=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~=~
#                                          numgeo
#                     Copyright (C) 2021 Jan Machacek, Patrick Staubach
#=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~=~
#
# PROGRAM: numgeo-mumps-mpi
#
#> author: Jan Machacek, jan-machacek@outlook.com
#
#
#>### SUMMARY: 
#> Program that solves a linear system of equations given in coordinate format using the
#> mpi-version of the mumps solver. This software is part of the numgeo software developed by
#> Jan Machacek and Patrick Staubach.
#
#
#>### REVISION HISTORY
#> 06.01.2021, J. Machacek - Initial version
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
	mpif90 -fopenmp  -lpthread -fPIC -funderscoring -O3 -Wall -c -fmessage-length=0 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.o: ./src/main.f90

# Objects
USER_OBJS :=

LIBS := -ldmumps -lmumps_common -lpord -lscalapack-openmpi -lopenblas -lesmumps -lscotch -lscotcherr -lscotcherrexit -lscotchmetis -lmetis


ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invSocations to the build variables 

# All Target
all: numgeo-mumps-mpi

# Tool invocations
numgeo-mumps-mpi: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU Fortran Linker'
	mpif90 -fopenmp -lpthread -fPIC -L./lib/ -o "numgeo-mumps-mpi" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) numgeo-mumps-mpi
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
