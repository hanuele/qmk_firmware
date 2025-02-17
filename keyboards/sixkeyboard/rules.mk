# MCU name
MCU = atmega16u2

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = atmel-dfu

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no		# Mouse keys
EXTRAKEY_ENABLE = no		# Audio control and System control
CONSOLE_ENABLE = no		# Console for debug
COMMAND_ENABLE = no		# Commands for debug and configuration
SLEEP_LED_ENABLE = no	# Breathing sleep LED during USB suspend
NKRO_ENABLE = no			# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no	# Enable keyboard backlight functionality
MIDI_ENABLE = no			# MIDI controls
AUDIO_ENABLE = no
UNICODE_ENABLE = no		# Unicode
BLUETOOTH_ENABLE = no	# Enable Bluetooth with the Adafruit EZ-Key HID
CUSTOM_MATRIX = yes

SRC = matrix.c
