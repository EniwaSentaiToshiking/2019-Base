mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS +=


APPL_CXXOBJS += \
    DistanceDetecter.o \
    SonarSensorDriver.o \
    TouchSensorDriver.o \
    ColorSensorDriver.o \
    WheelMotorDriver.o \
    TailMotorDriver.o \
    RunCommander.o \
    WheelInfo.o \
    Localization.o \
    CourceMonitor.o \
    SpeedCal.o \
    UI.o \
    PID.o \
    PIDController.o \
    Filter.o \
    Logger.o \
    RunStatus.o \
    CourseRun.o \
    Stop.o \
    RunStyle.o \
    LineTrace.o \
    RunPattern.o \
    RunManager.o \

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

APPL_DIRS += \
	$(mkfile_path)Detecters \
    $(mkfile_path)Devices \
    $(mkfile_path)Observer \
    $(mkfile_path)UI \
    $(mkfile_path)Utils \
    $(mkfile_path)RunStyles \
    $(mkfile_path)RunMethods \
    $(mkfile_path)RunMethods/Commanders \
    $(mkfile_path)RunMethods/Status \



INCLUDES += \
	-I$(mkfile_path)Detecters \
    -I$(mkfile_path)Devices \
    -I$(mkfile_path)Observer \
    -I$(mkfile_path)UI \
    -I$(mkfile_path)Utils \
    -I$(mkfile_path)RunStyles \
    -I$(mkfile_path)RunMethods \
    -I$(mkfile_path)RunMethods/Commanders \
    -I$(mkfile_path)RunMethods/Status \


#COPTS += -fno-use-cxa-atexit
