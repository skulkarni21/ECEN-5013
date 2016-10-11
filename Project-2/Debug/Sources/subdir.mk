################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/LED.c \
../Sources/LPTMR.c \
../Sources/UART.c \
../Sources/circbuff.c \
../Sources/conversion.c \
../Sources/main.c \
../Sources/test_buff.c 

OBJS += \
./Sources/LED.o \
./Sources/LPTMR.o \
./Sources/UART.o \
./Sources/circbuff.o \
./Sources/conversion.o \
./Sources/main.o \
./Sources/test_buff.o 

C_DEPS += \
./Sources/LED.d \
./Sources/LPTMR.d \
./Sources/UART.d \
./Sources/circbuff.d \
./Sources/conversion.d \
./Sources/main.d \
./Sources/test_buff.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


