################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
F90_SRCS += \
./src/main.f90

OBJS += \
./main.o 


# Each subdirectory must supply rules for building sources it contributes
main.o: ./src/main.f90 subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Fortran Compiler'
	mpif90 -fopenmp  -lpthread -fPIC -funderscoring -O3 -Wall -c -fmessage-length=0 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.o: ./src/main.f90


