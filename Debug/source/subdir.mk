################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/adc.c \
../source/lcd.c \
../source/led.c \
../source/llfifo.c \
../source/main.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/temp_sensor.c \
../source/timer.c \
../source/uart0.c 

C_DEPS += \
./source/adc.d \
./source/lcd.d \
./source/led.d \
./source/llfifo.d \
./source/main.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/temp_sensor.d \
./source/timer.d \
./source/uart0.d 

OBJS += \
./source/adc.o \
./source/lcd.o \
./source/led.o \
./source/llfifo.o \
./source/main.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/temp_sensor.o \
./source/timer.o \
./source/uart0.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DPRINTF_FLOAT_ENABLE=1 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"D:\FALL_2022\PES\hints\PES-Final_Project-main\Final_project\board" -I"D:\FALL_2022\PES\hints\PES-Final_Project-main\Final_project\source" -I"D:\FALL_2022\PES\hints\PES-Final_Project-main\Final_project" -I"D:\FALL_2022\PES\hints\PES-Final_Project-main\Final_project\drivers" -I"D:\FALL_2022\PES\hints\PES-Final_Project-main\Final_project\CMSIS" -I"D:\FALL_2022\PES\hints\PES-Final_Project-main\Final_project\utilities" -I"D:\FALL_2022\PES\hints\PES-Final_Project-main\Final_project\startup" -O0 -fno-common -g3 -Wall -Werror -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/adc.d ./source/adc.o ./source/lcd.d ./source/lcd.o ./source/led.d ./source/led.o ./source/llfifo.d ./source/llfifo.o ./source/main.d ./source/main.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/temp_sensor.d ./source/temp_sensor.o ./source/timer.d ./source/timer.o ./source/uart0.d ./source/uart0.o

.PHONY: clean-source

