LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := NasNas-example

LOCAL_SRC_FILES := main.cpp
LOCAL_SRC_FILES += $(wildcard ${LOCAL_PATH}/../../../../../../src/NasNas/core/*.cpp)
LOCAL_SRC_FILES += $(wildcard ${LOCAL_PATH}/../../../../../../src/NasNas/core/**/*.cpp)
LOCAL_SRC_FILES += $(wildcard ${LOCAL_PATH}/../../../../../../src/NasNas/ecs/*.cpp)
LOCAL_SRC_FILES += $(wildcard ${LOCAL_PATH}/../../../../../../src/NasNas/ecs/**/*.cpp)
LOCAL_SRC_FILES += $(wildcard ${LOCAL_PATH}/../../../../../../src/NasNas/thirdparty/*.cpp)
LOCAL_SRC_FILES += $(wildcard ${LOCAL_PATH}/../../../../../../src/NasNas/tilemapping/*.cpp)
LOCAL_SRC_FILES += $(wildcard ${LOCAL_PATH}/../../../../../../src/NasNas/tween/*.cpp)
LOCAL_SRC_FILES += $(wildcard ${LOCAL_PATH}/../../../../../../src/NasNas/ui/*.cpp)

LOCAL_C_INCLUDES += ${LOCAL_PATH}/include
LOCAL_C_INCLUDES += ${LOCAL_PATH}/../../../../../../include

LOCAL_SHARED_LIBRARIES := sfml-system-d
LOCAL_SHARED_LIBRARIES += sfml-window-d
LOCAL_SHARED_LIBRARIES += sfml-graphics-d
LOCAL_SHARED_LIBRARIES += sfml-audio-d
LOCAL_SHARED_LIBRARIES += sfml-network-d
LOCAL_SHARED_LIBRARIES += sfml-activity-d
LOCAL_SHARED_LIBRARIES += openal
LOCAL_WHOLE_STATIC_LIBRARIES := sfml-main-d

include $(BUILD_SHARED_LIBRARY)

$(call import-module,third_party/sfml)
