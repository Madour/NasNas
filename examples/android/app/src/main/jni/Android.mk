LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := NasNas-example

LOCAL_SRC_FILES := main.cpp

LOCAL_C_INCLUDES += ${LOCAL_PATH}/include

LOCAL_SHARED_LIBRARIES := sfml-system-d
LOCAL_SHARED_LIBRARIES += sfml-window-d
LOCAL_SHARED_LIBRARIES += sfml-graphics-d
LOCAL_SHARED_LIBRARIES += sfml-audio-d
LOCAL_SHARED_LIBRARIES += sfml-network-d
LOCAL_SHARED_LIBRARIES += sfml-activity-d
LOCAL_SHARED_LIBRARIES += openal

LOCAL_SHARED_LIBRARIES += NasNas-d

LOCAL_WHOLE_STATIC_LIBRARIES := sfml-main-d

include $(BUILD_SHARED_LIBRARY)

$(call import-module,third_party/nasnas)
