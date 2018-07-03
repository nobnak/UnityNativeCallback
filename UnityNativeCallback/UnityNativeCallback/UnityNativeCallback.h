#pragma once

#include "../Unity/IUnityInterface.h"
#include "../Unity/IUnityGraphics.h"

#if defined(_DEBUG)
#define DEBUG_LOG(fmt, ...) std::printf("UnityNativeCallback: "#fmt"\n", __VA_ARGS__)
#else
#define DEBUG_LOG(fmt, ...)
#endif

extern "C" {
	using Callback = void(*)();
	using CallbackGraphicsDeviceEvent = void(*)(UnityGfxDeviceEventType event_type);

	void UNITY_INTERFACE_EXPORT SetOnUnityPluginLoad(Callback callback);
	void UNITY_INTERFACE_EXPORT SetOnUnityPluginUnload(Callback callback);
	void UNITY_INTERFACE_EXPORT SetOnGraphicsDeviceEvent(CallbackGraphicsDeviceEvent callback);
}
