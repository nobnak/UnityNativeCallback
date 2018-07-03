using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace UnityNativeCallbackSystem.Examples {

    public class TestEvents : MonoBehaviour {
        private void Awake() {
            UnityNativeCallback.RegisterCallbacks();

            UnityNativeCallback.EventOnUnityPluginLoad += () => {
                Debug.Log("Load");
            };
            UnityNativeCallback.EventOnUnityPluginUnload += () => {
                Debug.Log("Unload");
            };
        }
        private void OnDestroy()
        {
            UnityNativeCallback.UnregisterCallbacks();
        }
    }
}
