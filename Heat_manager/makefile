OBJS	= i2c.o  main.o  key.o led.o  lcd.o  motor.o error.o lcd_utils.o  timer.o buzzer.o
flags	=$(shell zdev-config --cflags --libs zkit-arm-1343)

int.bin:	int.elf
	arm-none-eabi-objcopy int.elf -O binary int.bin
	lpc-crc int.bin

int.elf:	$(OBJS)
	arm-none-eabi-gcc $(OBJS)  $(flags) -o int.elf

lcd_utils.o: src/lcd_utils.c
	arm-none-eabi-gcc $(flags) -I./include  -c $<

%.o:	src/%.c include/%_var.h	
	arm-none-eabi-gcc $(flags) -I./include  -c $<
clean:
	rm *.o
	rm *.elf
	rm *.bin
