// UnityNativeCallback.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"
#include <cstdio>
#include "UnityNativeCallback.h"


extern "C" {

	IUnityInterfaces* unityInterfaces = nullptr;

	Callback callbackOnUnityPluginLoad = nullptr;
	Callback callbackOnUnityPluginUnload = nullptr;
	CallbackGraphicsDeviceEvent callbackOnGraphicsDeviceEvent = nullptr;

	void SetOnUnityPluginLoad(Callback callback) {
		DEBUG_LOG("SetOnUnityPluginLoad");
		callbackOnUnityPluginLoad = callback;
	}
	void SetOnUnityPluginUnload(Callback callback) {
		DEBUG_LOG("SetOnUnityPluginUnload");
		callbackOnUnityPluginUnload = callback;
	}
	void SetOnGraphicsDeviceEvent(CallbackGraphicsDeviceEvent callback) {
		DEBUG_LOG("SetOnGraphicsDeviceEvent");
		callbackOnGraphicsDeviceEvent = callback;
	}
	void ClearCallbacks() {
		callbackOnUnityPluginLoad = nullptr;
		callbackOnUnityPluginUnload = nullptr;
		callbackOnGraphicsDeviceEvent = nullptr;
	}

	void UNITY_INTERFACE_API OnGraphicsDeviceEvent(UnityGfxDeviceEventType event_type) {
		DEBUG_LOG("OnGraphicsDeviceEvent:event=%d", event_type);
		if (callbackOnGraphicsDeviceEvent != nullptr)
			(callbackOnGraphicsDeviceEvent)(event_type);

		switch (event_type) {
			case kUnityGfxDeviceEventInitialize:
			{
				break;
			}
			case kUnityGfxDeviceEventShutdown:
			{
				ClearCallbacks();
				break;
			}
			case kUnityGfxDeviceEventBeforeReset:
			{
				break;
			}
			case kUnityGfxDeviceEventAfterReset:
			{
				break;
			}
		};
	}


	void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces* interfaces) {
#if defined(_DEBUG)
		FILE * pConsole;
		AllocConsole();
		freopen_s(&pConsole, "CONOUT$", "wb", stdout);
#endif

		DEBUG_LOG("UnityPluginLoad");
		unityInterfaces = interfaces;
		unityInterfaces->Get<IUnityGraphics>()->RegisterDeviceEventCallback(OnGraphicsDeviceEvent);

		if (callbackOnUnityPluginLoad != nullptr)
			(callbackOnUnityPluginLoad)();

		OnGraphicsDeviceEvent(UnityGfxDeviceEventType::kUnityGfxDeviceEventInitialize);
	}
	void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginUnload() {
		DEBUG_LOG("UnityPluginUnload");
		if (callbackOnUnityPluginUnload != nullptr)
			(callbackOnUnityPluginUnload)();

		if (unityInterfaces != nullptr)
			unityInterfaces->Get<IUnityGraphics>()->UnregisterDeviceEventCallback(OnGraphicsDeviceEvent);

		unityInterfaces = nullptr;
	}

}
