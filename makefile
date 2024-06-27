TARGET = chargerHandler
SRC = main
CC = avr-gcc
CPU_Freq = F_CPU=16000000
CFLAG_1 = -Wall -Og -mmcu=atmega328p -Wl,--print-memory > progmem.txt
CFLAG_2 = -std=gnu99
CFLAGS = $(CFLAG_1) $(CFLAG_2)
CURR_DIR = $(shell pwd)
USB_PORT = /dev/ttyUSB0
PREF_SRC = $(CURR_DIR)/src/
PREF_OBJ = $(CURR_DIR)/obj/

SRC = $(wildcard $(PREF_SRC)*.c)
OBJ = $(patsubst $(PREF_SRC)%.c, $(PREF_OBJ)%.o, $(SRC))
 
all: $(TARGET).hex

$(TARGET).hex: $(TARGET)
	avr-objcopy -O ihex -R .eeprom $< $@

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(PREF_OBJ)%.o: $(PREF_SRC)%.c
	$(CC) $(CFLAGS) -D${CPU_Freq} -c $< -o $@ 

deploy:	$(TARGET).hex
	avrdude -F -V -c avrdude -p atmega328p -P $(USB_PORT) -b 9500 -U flash:w:$@	

clean:
	rm $(TARGET) $(PREF_OBJ)*.o *.hex progmem.txt

