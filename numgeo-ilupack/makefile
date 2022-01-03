################################################################################
# Automatically-generated file. Do not edit!
################################################################################


RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk

# where are the headers
INCDIR=./include

# where are the libraries
LIBDIR=./lib

# libraries
LIBS=-lilupack_mumps -lmumps -lcamd -lamd -lmetisomp -lmetis -lmetisomp -lsparspak -lsuitesparseconfig -llapack -lblaslike -lblas


ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif


# All Target
all: numgeo-ilupack

# Tool invocations
numgeo-ilupack: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU Fortran Linker'
	mpif90 -fopenmp -fPIC -L./lib/ -o "numgeo-ilupack" $(OBJS) $(USER_OBJS) $(LIBDIR) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) numgeo-ilupack
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
