/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    driver and application

--*/

//
// Define an Interface Guid so that apps can find the device and talk to it.
//

DEFINE_GUID (GUID_DEVINTERFACE_TestUmdf2Driver,
    0x87393c1f,0x7e03,0x492c,0x82,0x55,0x8c,0x6a,0xf2,0x40,0xfc,0x31);
// {87393c1f-7e03-492c-8255-8c6af240fc31}
