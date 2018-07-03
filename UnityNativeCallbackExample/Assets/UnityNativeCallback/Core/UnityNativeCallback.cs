using AOT;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

namespace UnityNativeCallbackSystem {
    public enum UnityGfxDeviceEventType {
        kUnityGfxDeviceEventInitialize = 0,
        kUnityGfxDeviceEventShutdown = 1,
        kUnityGfxDeviceEventBeforeReset = 2,
        kUnityGfxDeviceEventAfterReset = 3,
    }

    public static class UnityNativeCallback {
        public const string DLL_NAME = "UnityNativeCallback";

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void DelegateCallback();
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void DelegateCallbackGraphicsDeviceEvent(UnityGfxDeviceEventType event_type);

        [DllImport(DLL_NAME)]
        public static extern void SetOnUnityPluginLoad(DelegateCallback callback);
        [DllImport(DLL_NAME)]
        public static extern void SetOnUnityPluginUnload(DelegateCallback callback);
        [DllImport(DLL_NAME)]
        public static extern void SetOnGraphicsDeviceEvent(DelegateCallbackGraphicsDeviceEvent callback);

        public static event System.Action EventOnUnityPluginLoad;
        public static event System.Action EventOnUnityPluginUnload;
        public static event System.Action<UnityGfxDeviceEventType> EventOnGraphicsDeviceEvent;

        [MonoPInvokeCallback(typeof(DelegateCallback))]
        static void CallbackOnUnityPluginLoad() {
            if (EventOnUnityPluginLoad != null)
                EventOnUnityPluginLoad();
            else
                Debug.LogFormat("{0}:{1}", DLL_NAME, "UnityPluginLoad");
        }
        [MonoPInvokeCallback(typeof(DelegateCallback))]
        static void CallbackOnUnityPluginUnload() {
            if (EventOnUnityPluginUnload != null)
                EventOnUnityPluginUnload();
            else
                Debug.LogFormat("{0}:{1}", DLL_NAME, "UnityPluginUnload");
        }
        [MonoPInvokeCallback(typeof(DelegateCallbackGraphicsDeviceEvent))]
        static void CallbackOnGraphicsDeviceEvent(UnityGfxDeviceEventType event_type) {
            if (EventOnGraphicsDeviceEvent != null)
                EventOnGraphicsDeviceEvent(event_type);
            else
                Debug.LogFormat("{0}:{1} event={2}", DLL_NAME, "GraphicsDeviceEvent", event_type);
        }

        public static void RegisterCallbacks() {
            SetOnUnityPluginLoad(CallbackOnUnityPluginLoad);
            SetOnUnityPluginUnload(CallbackOnUnityPluginUnload);
            SetOnGraphicsDeviceEvent(CallbackOnGraphicsDeviceEvent);
        }
        public static void UnregisterCallbacks() {
            SetOnUnityPluginLoad(null);
            SetOnUnityPluginUnload(null);
            SetOnGraphicsDeviceEvent(null);
        }

        static UnityNativeCallback() {
            RegisterCallbacks();
        }
    }
}
