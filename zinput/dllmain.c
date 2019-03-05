#include <windows.h>
#include <dinput.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "hook/process.h"
#include "hook/table.h"

#include "util/dprintf.h"

static unsigned long WINAPI my_AddRef(IUnknown *self);

static unsigned long WINAPI my_Release(IUnknown *self);

static HRESULT WINAPI my_CreateDevice(
        IDirectInput8W *self,
        REFGUID rguid,
        LPDIRECTINPUTDEVICE8W * lplpDirectInputDevice,
        LPUNKNOWN pUnkOuter);

static HRESULT WINAPI my_EnumDevices(
        IDirectInput8W *self,
        DWORD dwDevType,
        LPDIENUMDEVICESCALLBACKW lpCallback,
        LPVOID pvRef,
        DWORD dwFlags);

static HRESULT WINAPI my_SetDataFormat(
        IDirectInputDevice8W *self,
        LPCDIDATAFORMAT lpdf);

static HRESULT WINAPI my_SetCooperativeLevel(
        IDirectInputDevice8W *self,
        HWND hwnd,
        DWORD flags);

static HRESULT WINAPI my_Acquire(IDirectInputDevice8W *self);

static HRESULT WINAPI my_GetDeviceState(
        IDirectInputDevice8W *self,
        DWORD cbData,
        LPVOID lpvData);

static const IDirectInput8WVtbl api_vtbl = {
    .AddRef             = (void *) my_AddRef,
    .Release            = (void *) my_Release,
    .CreateDevice       = my_CreateDevice,
    .EnumDevices        = my_EnumDevices,
};

static const IDirectInput8W api = { (void *) &api_vtbl };

static const IDirectInputDevice8WVtbl dev_vtbl = {
    .AddRef             = (void *) my_AddRef,
    .Release            = (void *) my_Release,
    .SetDataFormat      = my_SetDataFormat,
    .SetCooperativeLevel= my_SetCooperativeLevel,
    .Acquire            = my_Acquire,
    .Unacquire          = my_Acquire, // not a c&p error
    .GetDeviceState     = my_GetDeviceState,
};

static const IDirectInputDevice8W dev = { (void *) &dev_vtbl };

HRESULT WINAPI DirectInput8Create(
         HINSTANCE hinst,
         DWORD dwVersion,
         REFIID riidltf,
         LPVOID *ppvOut,
         LPUNKNOWN punkOuter)
{
    dprintf("%s\n", __func__);
    *ppvOut = (void *) &api;

    return S_OK;
}

static unsigned long WINAPI my_AddRef(IUnknown *self)
{
    return 1;
}

static unsigned long WINAPI my_Release(IUnknown *self)
{
    return 1;
}

static HRESULT WINAPI my_CreateDevice(
        IDirectInput8W *self,
        REFGUID rguid,
        LPDIRECTINPUTDEVICE8W *lplpDirectInputDevice,
        LPUNKNOWN pUnkOuter)
{
    dprintf("%s\n", __func__);
    *lplpDirectInputDevice = (void *) &dev;

    return S_OK;
}

static HRESULT WINAPI my_EnumDevices(
        IDirectInput8W *self,
        DWORD dwDevType,
        LPDIENUMDEVICESCALLBACKW lpCallback,
        LPVOID pvRef,
        DWORD dwFlags)
{
    dprintf("%s\n", __func__);

    return S_OK;
}

static HRESULT WINAPI my_SetDataFormat(
        IDirectInputDevice8W *self,
        LPCDIDATAFORMAT lpdf)
{
    dprintf("%s\n", __func__);

    return S_OK;
}

static HRESULT WINAPI my_SetCooperativeLevel(
        IDirectInputDevice8W *self,
        HWND hwnd,
        DWORD flags)
{
    dprintf("%s\n", __func__);

    return S_OK;
}

static HRESULT WINAPI my_Acquire(IDirectInputDevice8W *self)
{
    return S_OK;
}

static HRESULT WINAPI my_GetDeviceState(
        IDirectInputDevice8W *self,
        DWORD cbData,
        LPVOID lpvData)
{
    memset(lpvData, 0, cbData);

    return S_OK;
}
