################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CU_SRCS += \
../source/kernel.cu 

CPP_SRCS += \
../source/IPNCLImage.cpp 

OBJS += \
./source/IPNCLImage.o \
./source/kernel.o 

CU_DEPS += \
./source/kernel.d 

CPP_DEPS += \
./source/IPNCLImage.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-6.5/bin/nvcc -I/usr/include/opencv -G -g -O0 -gencode arch=compute_12,code=sm_12  -odir "source" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-6.5/bin/nvcc -I/usr/include/opencv -G -g -O0 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/%.o: ../source/%.cu
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-6.5/bin/nvcc -I/usr/include/opencv -G -g -O0 -gencode arch=compute_12,code=sm_12  -odir "source" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-6.5/bin/nvcc -I/usr/include/opencv -G -g -O0 --compile --relocatable-device-code=false -gencode arch=compute_12,code=compute_12 -gencode arch=compute_12,code=sm_12  -x cu -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


