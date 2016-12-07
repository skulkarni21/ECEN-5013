################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/ADC.c \
../Sources/I2C.c \
../Sources/LED.c \
../Sources/Messege.c \
../Sources/TSI.c \
../Sources/TSL2561.c \
../Sources/UART.c \
../Sources/circbuff.c \
../Sources/conversion.c \
../Sources/humidity.c \
../Sources/log.c \
../Sources/main.c \
../Sources/timer.c 

OBJS += \
./Sources/ADC.o \
./Sources/I2C.o \
./Sources/LED.o \
./Sources/Messege.o \
./Sources/TSI.o \
./Sources/TSL2561.o \
./Sources/UART.o \
./Sources/circbuff.o \
./Sources/conversion.o \
./Sources/humidity.o \
./Sources/log.o \
./Sources/main.o \
./Sources/timer.o 

C_DEPS += \
./Sources/ADC.d \
./Sources/I2C.d \
./Sources/LED.d \
./Sources/Messege.d \
./Sources/TSI.d \
./Sources/TSL2561.d \
./Sources/UART.d \
./Sources/circbuff.d \
./Sources/conversion.d \
./Sources/humidity.d \
./Sources/log.d \
./Sources/main.d \
./Sources/timer.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


