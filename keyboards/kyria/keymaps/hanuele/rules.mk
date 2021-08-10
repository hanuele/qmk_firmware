EXTRAFLAGS += -flto        # Link time optimization
LTO_ENABLE = yes
SRC += oneshot.c
OLED_DRIVER_ENABLE = yes   # Enables the use of OLED displays
ENCODER_ENABLE = yes       # Enables the use of one or more encoders
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
MOUSEKEY_ENABLE = yes	   # It uses some space,  but my settings for the mouse keys are a bliss in combination with tobii gaze and talon head tracking.
TAP_DANCE_ENABLE = yes	   # Enable the Tab Dance feature
# Save space,  no other reason to disable
COMMAND_ENABLE   = no 	   # Commands for debug and configuration
UNICODE_ENABLE   = no	   # Unicode
LEADER_ENABLE = no         # Enable the Leader Key feature
NO_USB_STARTUP_CHECK = yes
SPACE_CADET_ENABLE    = no
GRAVE_ESC_ENABLE      = no
MAGIC_ENABLE = no

PIMORONI_TRACKBALL_ENABLE = yes

ifeq ($(strip $(PIMORONI_TRACKBALL_ENABLE)), yes)
    SRC += pimoroni_trackball.c
    OPT_DEFS += -DPIMORONI_TRACKBALL_ENABLE
    POINTING_DEVICE_ENABLE := yes
    QUANTUM_LIB_SRC = i2c_master.c
endif



VERBOSE 		 = no 
DEBUG_MATRIX_SCAN_RATE   = no
DEBUG_BALLER 		 = no
DEBUG_MATRIX		 = no