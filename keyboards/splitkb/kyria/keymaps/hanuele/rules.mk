LTO_ENABLE = yes # Link time optimization
SRC += oneshot.c
OLED_DRIVER_ENABLE = no  # Enables the use of OLED displays
ENCODER_ENABLE = yes       # Enables the use of one or more encoders
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
RGBLIGHT_STARTUP_ANIMATION =  no
MOUSEKEY_ENABLE = yes	   # It uses some space,  but my settings for the mouse keys are a bliss in combination with tobii gaze and talon head tracking.
TAP_DANCE_ENABLE = yes	   # Enable the Tab Dance feature
# Save space,  no other reason to disable
COMMAND_ENABLE   = no 	   # Commands for debug and configuration
UNICODE_ENABLE   = no	   # Unicode
LEADER_ENABLE = no         # Enable the Leader Key feature
SPACE_CADET_ENABLE    = no
GRAVE_ESC_ENABLE      = no
MAGIC_ENABLE = no
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
CONSOLE_ENABLE = no        # Console for debug
KEY_LOCK_ENABLE = no
COMBO_ENABLE = no
BLUETOOTH_ENABLE = no      # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = no          # Audio output on port C6
SPLIT_KEYBOARD = yes       # Split common
NKRO_ENABLE = no          # USB Nkey Rollover

PIMORONI_TRACKBALL_ENABLE = yes

ifeq ($(strip $(PIMORONI_TRACKBALL_ENABLE)), yes)
    SRC += pimoroni_trackball.c
    OPT_DEFS += -DPIMORONI_TRACKBALL_ENABLE
    POINTING_DEVICE_ENABLE := yes
    QUANTUM_LIB_SRC = i2c_master.c
endif

# Bootloader selection
BOOTLOADER = atmel-dfu