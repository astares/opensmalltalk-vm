/* Automatically generated by
	SmartSyntaxPluginCodeGenerator VMMaker.oscog-eem.2347 uuid: 062614a7-e3da-4b30-997a-9568911b9ff5
   from
	HostWindowPlugin VMMaker.oscog-eem.2347 uuid: 062614a7-e3da-4b30-997a-9568911b9ff5
 */
static char __buildInfo[] = "HostWindowPlugin VMMaker.oscog-eem.2347 uuid: 062614a7-e3da-4b30-997a-9568911b9ff5 " __DATE__ ;



#include "config.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Default EXPORT macro that does nothing (see comment in sq.h): */
#define EXPORT(returnType) returnType

/* Do not include the entire sq.h file but just those parts needed. */
#include "sqConfig.h"			/* Configuration options */
#include "sqVirtualMachine.h"	/*  The virtual machine proxy definition */
#include "sqPlatformSpecific.h"	/* Platform specific definitions */

#define true 1
#define false 0
#define null 0  /* using 'null' because nil is predefined in Think C */
#ifdef SQUEAK_BUILTIN_PLUGIN
# undef EXPORT
# define EXPORT(returnType) static returnType
#endif

#include "HostWindowPlugin.h"
#include "sqMemoryAccess.h"


/*** Function Prototypes ***/
EXPORT(const char*) getModuleName(void);
EXPORT(sqInt) primitiveCloseHostWindow(void);
EXPORT(sqInt) primitiveCreateHostWindow(void);
EXPORT(sqInt) primitiveHostWindowPosition(void);
EXPORT(sqInt) primitiveHostWindowPositionSet(void);
#if TerfVM
EXPORT(sqInt) primitiveHostWindowScreenWorkAreaPosition(void);
#endif /* TerfVM */
#if TerfVM
EXPORT(sqInt) primitiveHostWindowScreenWorkAreaSize(void);
#endif /* TerfVM */
EXPORT(sqInt) primitiveHostWindowSize(void);
EXPORT(sqInt) primitiveHostWindowSizeSet(void);
EXPORT(sqInt) primitiveHostWindowTitle(void);
#if TerfVM
EXPORT(sqInt) primitiveNativeDisplayPosition(void);
#endif /* TerfVM */
#if TerfVM
EXPORT(sqInt) primitiveNativeDisplaySize(void);
#endif /* TerfVM */
#if TerfVM
EXPORT(sqInt) primitiveNativeWindowPosition(void);
#endif /* TerfVM */
#if TerfVM
EXPORT(sqInt) primitiveNativeWindowSize(void);
#endif /* TerfVM */
#if TerfVM
EXPORT(sqInt) primitiveSetCursorPosition(void);
#endif /* TerfVM */
EXPORT(sqInt) primitiveShowHostWindowRect(void);
#if TerfVM
EXPORT(sqInt) primitiveSqueakWindowHandle(void);
#endif /* TerfVM */
EXPORT(sqInt) setInterpreter(struct VirtualMachine*anInterpreter);
EXPORT(sqInt) shutdownModule(void);
static sqInt sqAssert(sqInt aBool);


/*** Variables ***/

#if !defined(SQUEAK_BUILTIN_PLUGIN)
static sqInt (*failed)(void);
static void * (*firstIndexableField)(sqInt oop);
static sqInt (*integerObjectOf)(sqInt value);
static sqInt (*isBytes)(sqInt oop);
static sqInt (*isWords)(sqInt oop);
static sqInt (*makePointwithxValueyValue)(sqInt xValue, sqInt yValue);
static sqInt (*pop)(sqInt nItems);
static sqInt (*popthenPush)(sqInt nItems, sqInt oop);
static sqInt (*positive32BitIntegerFor)(unsigned int integerValue);
static usqInt (*positive32BitValueOf)(sqInt oop);
static sqInt (*positive64BitIntegerFor)(usqLong integerValue);
static usqLong (*positive64BitValueOf)(sqInt oop);
static sqInt (*primitiveFail)(void);
static sqInt (*slotSizeOf)(sqInt oop);
static sqInt (*stackIntegerValue)(sqInt offset);
static sqInt (*stackValue)(sqInt offset);
static sqInt (*success)(sqInt aBoolean);
#else /* !defined(SQUEAK_BUILTIN_PLUGIN) */
extern sqInt failed(void);
extern void * firstIndexableField(sqInt oop);
extern sqInt integerObjectOf(sqInt value);
extern sqInt isBytes(sqInt oop);
extern sqInt isWords(sqInt oop);
extern sqInt makePointwithxValueyValue(sqInt xValue, sqInt yValue);
extern sqInt pop(sqInt nItems);
extern sqInt popthenPush(sqInt nItems, sqInt oop);
extern sqInt positive32BitIntegerFor(unsigned int integerValue);
extern usqInt positive32BitValueOf(sqInt oop);
extern sqInt positive64BitIntegerFor(usqLong integerValue);
extern usqLong positive64BitValueOf(sqInt oop);
extern sqInt primitiveFail(void);
extern sqInt slotSizeOf(sqInt oop);
extern sqInt stackIntegerValue(sqInt offset);
extern sqInt stackValue(sqInt offset);
extern sqInt success(sqInt aBoolean);
extern
#endif
struct VirtualMachine* interpreterProxy;
static const char *moduleName =
#ifdef SQUEAK_BUILTIN_PLUGIN
	"HostWindowPlugin VMMaker.oscog-eem.2347 (i)"
#else
	"HostWindowPlugin VMMaker.oscog-eem.2347 (e)"
#endif
;



/*	Note: This is hardcoded so it can be run from Squeak.
	The module name is used for validating a module *after*
	it is loaded to check if it does really contain the module
	we're thinking it contains. This is important! */

	/* InterpreterPlugin>>#getModuleName */
EXPORT(const char*)
getModuleName(void)
{
	return moduleName;
}


/*	Close a host window. windowIndex is the SmallInt handle returned
	previously by primitiveCreateHostWindow. Fail if the index is invalid or
	the platform code fails
 */

	/* HostWindowPlugin>>#primitiveCloseHostWindow: */
EXPORT(sqInt)
primitiveCloseHostWindow(void)
{
	sqInt ok;
	sqInt windowIndex;

	windowIndex = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	ok = closeWindow(windowIndex);
	if (!ok) {
		primitiveFail();
	}
	if (failed()) {
		return null;
	}
	pop(1);
	return null;
}


/*	Create a host window of width 'w' pixels, height 'h' with the origin of
	the user area at 'x@y' from the topleft corner of the screen.
	Return the SmallInt value of the internal index to the window description
	block - which is whatever the host platform code needs it to be.
 */

	/* HostWindowPlugin>>#primitiveCreateHostWindowWidth:height:originX:y:attributes: */
EXPORT(sqInt)
primitiveCreateHostWindow(void)
{
	sqInt h;
	char *list;
	sqInt listLength;
	sqInt w;
	sqInt windowIndex;
	sqInt x;
	sqInt y;
	sqInt _return_value;

	w = stackIntegerValue(4);
	h = stackIntegerValue(3);
	x = stackIntegerValue(2);
	y = stackIntegerValue(1);
	success(isBytes(stackValue(0)));
	list = ((char *) (firstIndexableField(stackValue(0))));
	if (failed()) {
		return null;
	}
	listLength = slotSizeOf(((sqInt)(sqIntptr_t)(list) - BaseHeaderSize));
	windowIndex = createWindowWidthheightoriginXyattrlength(w, h, x, y, list, listLength);
	if (windowIndex > 0) {
		_return_value = integerObjectOf(windowIndex);
		popthenPush(6, _return_value);
		return null;
	}
	else {
		primitiveFail();
		return null;
	}
}


/*	Return the origin position of the user area of the window in pixels from
	the topleft corner of the screen. Fail if the windowIndex is invalid or
	the platform routine returns -1 to indicate failure
 */

	/* HostWindowPlugin>>#primitiveHostWindowPosition: */
EXPORT(sqInt)
primitiveHostWindowPosition(void)
{
	sqInt pos;
	sqInt windowIndex;
	sqInt _return_value;

	windowIndex = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	pos = ioPositionOfWindow(windowIndex);
	if (pos == -1) {
		primitiveFail();
		return null;
	}
	if (failed()) {
		return null;
	}
	/* begin pointFromCompactPointEncoding: */
	_return_value = makePointwithxValueyValue(((short) (((usqInt) pos) >> 16)), ((short) (pos & 0xFFFF)));
	if (failed()) {
		return null;
	}
	popthenPush(2, _return_value);
	return null;
}


/*	Set the origin position of the user area of the window in pixels from the
	topleft corner of the screen- return the position actually set by the
	OS/GUI/window manager. Fail if the windowIndex is invalid or the platform
	routine returns -1 to indicate failure
 */

	/* HostWindowPlugin>>#primitiveHostWindowPositionSet:x:y: */
EXPORT(sqInt)
primitiveHostWindowPositionSet(void)
{
	sqInt pos;
	sqInt windowIndex;
	sqInt x;
	sqInt y;
	sqInt _return_value;

	windowIndex = stackIntegerValue(2);
	x = stackIntegerValue(1);
	y = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	pos = ioPositionOfWindowSetxy(windowIndex, x, y);
	if (pos == -1) {
		primitiveFail();
		return null;
	}
	if (failed()) {
		return null;
	}
	/* begin pointFromCompactPointEncoding: */
	_return_value = makePointwithxValueyValue(((short) (((usqInt) pos) >> 16)), ((short) (pos & 0xFFFF)));
	if (failed()) {
		return null;
	}
	popthenPush(4, _return_value);
	return null;
}


/*	Answer the platform's notion of the available work area on the screen
	containing the given window.
 */

	/* HostWindowPlugin>>#primitiveHostWindowScreenWorkAreaPosition: */
#if TerfVM
EXPORT(sqInt)
primitiveHostWindowScreenWorkAreaPosition(void)
{
	sqInt size;
	sqInt windex;
	sqInt _return_value;

	windex = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	size = ioPositionOfScreenWorkArea(windex);
	if (size == -1) {
		primitiveFail();
		return null;
	}
	if (failed()) {
		return null;
	}
	/* begin pointFromCompactPointEncoding: */
	_return_value = makePointwithxValueyValue(((short) (((usqInt) size) >> 16)), ((short) (size & 0xFFFF)));
	if (failed()) {
		return null;
	}
	popthenPush(2, _return_value);
	return null;
}
#endif /* TerfVM */


/*	Answer the platform's notion of the available work area on the screen
	containing the given window.
 */

	/* HostWindowPlugin>>#primitiveHostWindowScreenWorkAreaSize: */
#if TerfVM
EXPORT(sqInt)
primitiveHostWindowScreenWorkAreaSize(void)
{
	sqInt size;
	sqInt windex;
	sqInt _return_value;

	windex = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	size = ioSizeOfScreenWorkArea(windex);
	if (size == -1) {
		primitiveFail();
		return null;
	}
	if (failed()) {
		return null;
	}
	/* begin pointFromCompactPointEncoding: */
	_return_value = makePointwithxValueyValue(((short) (((usqInt) size) >> 16)), ((short) (size & 0xFFFF)));
	if (failed()) {
		return null;
	}
	popthenPush(2, _return_value);
	return null;
}
#endif /* TerfVM */


/*	Return the size of the user area of the window in pixels. Fail if the
	windowIndex is invalid or the platform routine returns -1 to indicate
	failure 
 */

	/* HostWindowPlugin>>#primitiveHostWindowSize: */
EXPORT(sqInt)
primitiveHostWindowSize(void)
{
	sqInt size;
	sqInt windowIndex;
	sqInt _return_value;

	windowIndex = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	size = ioSizeOfWindow(windowIndex);
	if (size == -1) {
		primitiveFail();
		return null;
	}
	if (failed()) {
		return null;
	}
	/* begin pointFromCompactPointEncoding: */
	_return_value = makePointwithxValueyValue(((short) (((usqInt) size) >> 16)), ((short) (size & 0xFFFF)));
	if (failed()) {
		return null;
	}
	popthenPush(2, _return_value);
	return null;
}


/*	Set the size of the user area of the window in pixels - return what is
	actually set by the OS/GUI/window manager. Fail if the windowIndex is
	invalid or the platform routine returns -1 to indicate failure
 */

	/* HostWindowPlugin>>#primitiveHostWindowSizeSet:x:y: */
EXPORT(sqInt)
primitiveHostWindowSizeSet(void)
{
	sqInt size;
	sqInt windowIndex;
	sqInt x;
	sqInt y;
	sqInt _return_value;

	windowIndex = stackIntegerValue(2);
	x = stackIntegerValue(1);
	y = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	size = ioSizeOfWindowSetxy(windowIndex, x, y);
	if (size == -1) {
		primitiveFail();
		return null;
	}
	if (failed()) {
		return null;
	}
	/* begin pointFromCompactPointEncoding: */
	_return_value = makePointwithxValueyValue(((short) (((usqInt) size) >> 16)), ((short) (size & 0xFFFF)));
	if (failed()) {
		return null;
	}
	popthenPush(4, _return_value);
	return null;
}


/*	Set the title bar label of the window. Fail if the windowIndex is invalid
	or the platform routine returns -1 to indicate failure
 */

	/* HostWindowPlugin>>#primitiveHostWindowTitle:string: */
EXPORT(sqInt)
primitiveHostWindowTitle(void)
{
	sqInt id;
	sqInt res;
	sqInt titleLength;
	char *titleString;

	id = stackIntegerValue(1);
	success(isBytes(stackValue(0)));
	titleString = ((char *) (firstIndexableField(stackValue(0))));
	if (failed()) {
		return null;
	}
	titleLength = slotSizeOf(((sqInt)(sqIntptr_t)(titleString) - BaseHeaderSize));
	res = ioSetTitleOfWindow(id, titleString, titleLength);
	if (res == -1) {
		primitiveFail();
	}
	if (failed()) {
		return null;
	}
	pop(2);
	return null;
}


/*	Answer the origin position of the user area of the given native window in
	pixels from the topleft corner of the screen.
	Fail if the windowHandle is invalid or the platform routine returns -1 to
	indicate failure
 */

	/* HostWindowPlugin>>#primitiveNativeDisplayPosition: */
#if TerfVM
EXPORT(sqInt)
primitiveNativeDisplayPosition(void)
{
	sqInt pos;
	usqIntptr_t windowHandle;
	sqInt _return_value;

	windowHandle = (BytesPerOop == 4
		? positive32BitValueOf(stackValue(0))
		: positive64BitValueOf(stackValue(0)));
	if (failed()) {
		return null;
	}
	pos = ioPositionOfNativeDisplay(windowHandle);
	if (pos == -1) {
		primitiveFail();
		return null;
	}
	if (failed()) {
		return null;
	}
	/* begin pointFromCompactPointEncoding: */
	_return_value = makePointwithxValueyValue(((short) (((usqInt) pos) >> 16)), ((short) (pos & 0xFFFF)));
	if (failed()) {
		return null;
	}
	popthenPush(2, _return_value);
	return null;
}
#endif /* TerfVM */


/*	Answer the size of the user area of the given native window in pixels.
	Fail if the windowHandle is invalid or the platform routine returns -1 to
	indicate failure */

	/* HostWindowPlugin>>#primitiveNativeDisplaySize: */
#if TerfVM
EXPORT(sqInt)
primitiveNativeDisplaySize(void)
{
	sqInt size;
	usqIntptr_t windowHandle;
	sqInt _return_value;

	windowHandle = (BytesPerOop == 4
		? positive32BitValueOf(stackValue(0))
		: positive64BitValueOf(stackValue(0)));
	if (failed()) {
		return null;
	}
	size = ioSizeOfNativeDisplay(windowHandle);
	if (size == -1) {
		primitiveFail();
		return null;
	}
	if (failed()) {
		return null;
	}
	/* begin pointFromCompactPointEncoding: */
	_return_value = makePointwithxValueyValue(((short) (((usqInt) size) >> 16)), ((short) (size & 0xFFFF)));
	if (failed()) {
		return null;
	}
	popthenPush(2, _return_value);
	return null;
}
#endif /* TerfVM */


/*	Answer the origin position of the given native window in pixels from the
	topleft corner of the screen.
	Fail if the windowHandle is invalid or the platform routine returns -1 to
	indicate failure
 */

	/* HostWindowPlugin>>#primitiveNativeWindowPosition: */
#if TerfVM
EXPORT(sqInt)
primitiveNativeWindowPosition(void)
{
	sqInt pos;
	usqIntptr_t windowHandle;
	sqInt _return_value;

	windowHandle = (BytesPerOop == 4
		? positive32BitValueOf(stackValue(0))
		: positive64BitValueOf(stackValue(0)));
	if (failed()) {
		return null;
	}
	pos = ioPositionOfNativeWindow(windowHandle);
	if (pos == -1) {
		primitiveFail();
		return null;
	}
	if (failed()) {
		return null;
	}
	/* begin pointFromCompactPointEncoding: */
	_return_value = makePointwithxValueyValue(((short) (((usqInt) pos) >> 16)), ((short) (pos & 0xFFFF)));
	if (failed()) {
		return null;
	}
	popthenPush(2, _return_value);
	return null;
}
#endif /* TerfVM */


/*	Answer the size of the given native window in pixels.
	Fail if the windowHandle is invalid or the platform routine returns -1 to
	indicate failure */

	/* HostWindowPlugin>>#primitiveNativeWindowSize: */
#if TerfVM
EXPORT(sqInt)
primitiveNativeWindowSize(void)
{
	sqInt size;
	usqIntptr_t windowHandle;
	sqInt _return_value;

	windowHandle = (BytesPerOop == 4
		? positive32BitValueOf(stackValue(0))
		: positive64BitValueOf(stackValue(0)));
	if (failed()) {
		return null;
	}
	size = ioSizeOfNativeWindow(windowHandle);
	if (size == -1) {
		primitiveFail();
		return null;
	}
	if (failed()) {
		return null;
	}
	/* begin pointFromCompactPointEncoding: */
	_return_value = makePointwithxValueyValue(((short) (((usqInt) size) >> 16)), ((short) (size & 0xFFFF)));
	if (failed()) {
		return null;
	}
	popthenPush(2, _return_value);
	return null;
}
#endif /* TerfVM */


/*	Set the position of the cursor to the specified position on the desktop.
	Fail if the platform routine returns -1 to indicate failure. */

	/* HostWindowPlugin>>#primitiveSetCursorPositionX:Y: */
#if TerfVM
EXPORT(sqInt)
primitiveSetCursorPosition(void)
{
	sqInt result;
	sqInt x;
	sqInt y;

	x = stackIntegerValue(1);
	y = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	result = ioSetCursorPositionXY(x, y);
	if (result == -1) {
		primitiveFail();
		return null;
	}
	if (failed()) {
		return null;
	}
	pop(2);
	return null;
}
#endif /* TerfVM */


/*	Host window analogue of DisplayScreen> primShowRectLeft:right:top:bottom:
	(Interpreter>primitiveShowDisplayRect) which takes the window index,
	bitmap details and the rectangle bounds. Fail if the windowIndex is
	invalid or the
	platform routine returns false to indicate failure
 */

	/* HostWindowPlugin>>#primitiveShowHostWindow:bits:width:height:depth:left:right:top:bottom: */
EXPORT(sqInt)
primitiveShowHostWindowRect(void)
{
	sqInt bottom;
	sqInt d;
	unsigned *dispBits;
	sqInt h;
	sqInt left;
	sqInt ok;
	sqInt right;
	sqInt top;
	sqInt w;
	sqInt windowIndex;

	windowIndex = stackIntegerValue(8);
	success(isWords(stackValue(7)));
	dispBits = ((unsigned *) (firstIndexableField(stackValue(7))));
	w = stackIntegerValue(6);
	h = stackIntegerValue(5);
	d = stackIntegerValue(4);
	left = stackIntegerValue(3);
	right = stackIntegerValue(2);
	top = stackIntegerValue(1);
	bottom = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	ok = ioShowDisplayOnWindow(dispBits, w, h, d, left, right, top,
bottom, windowIndex);
	if (!ok) {
		primitiveFail();
	}
	if (failed()) {
		return null;
	}
	pop(9);
	return null;
}


/*	Answer the native Squeak window handle, presumably a pointer, as an
	unsigned integer.
	This value should be usable in native calls to the window manager as well
	as the argument to primitiveNativeWindowPosition: */

	/* HostWindowPlugin>>#primitiveSqueakWindowHandle */
#if TerfVM
EXPORT(sqInt)
primitiveSqueakWindowHandle(void)
{
	void *handle;
	usqIntptr_t value;
	sqInt _return_value;

	handle = ioGetWindowHandle();
	if (handle == 0) {
		primitiveFail();
		return null;
	}
	if (failed()) {
		return null;
	}
	/* begin positiveMachineIntegerFor: */
	value = ((sqInt) handle);
	_return_value = (BytesPerWord == 8
		? positive64BitIntegerFor(value)
		: positive32BitIntegerFor(value));
	if (failed()) {
		return null;
	}
	popthenPush(1, _return_value);
	return null;
}
#endif /* TerfVM */


/*	Note: This is coded so that it can be run in Squeak. */

	/* InterpreterPlugin>>#setInterpreter: */
EXPORT(sqInt)
setInterpreter(struct VirtualMachine*anInterpreter)
{
	sqInt ok;

	interpreterProxy = anInterpreter;
	ok = ((interpreterProxy->majorVersion()) == (VM_PROXY_MAJOR))
	 && ((interpreterProxy->minorVersion()) >= (VM_PROXY_MINOR));
	if (ok) {
		
#if !defined(SQUEAK_BUILTIN_PLUGIN)
		failed = interpreterProxy->failed;
		firstIndexableField = interpreterProxy->firstIndexableField;
		integerObjectOf = interpreterProxy->integerObjectOf;
		isBytes = interpreterProxy->isBytes;
		isWords = interpreterProxy->isWords;
		makePointwithxValueyValue = interpreterProxy->makePointwithxValueyValue;
		pop = interpreterProxy->pop;
		popthenPush = interpreterProxy->popthenPush;
		positive32BitIntegerFor = interpreterProxy->positive32BitIntegerFor;
		positive32BitValueOf = interpreterProxy->positive32BitValueOf;
		positive64BitIntegerFor = interpreterProxy->positive64BitIntegerFor;
		positive64BitValueOf = interpreterProxy->positive64BitValueOf;
		primitiveFail = interpreterProxy->primitiveFail;
		slotSizeOf = interpreterProxy->slotSizeOf;
		stackIntegerValue = interpreterProxy->stackIntegerValue;
		stackValue = interpreterProxy->stackValue;
		success = interpreterProxy->success;
#endif /* !defined(SQUEAK_BUILTIN_PLUGIN) */
	}
	return ok;
}


/*	do any window related VM closing down work your platform requires. */

	/* HostWindowPlugin>>#shutdownModule */
EXPORT(sqInt)
shutdownModule(void)
{
	return ioCloseAllWindows();
}

	/* SmartSyntaxInterpreterPlugin>>#sqAssert: */
static sqInt
sqAssert(sqInt aBool)
{
	/* missing DebugCode */;
	return aBool;
}


#ifdef SQUEAK_BUILTIN_PLUGIN

static char _m[] = "HostWindowPlugin";
void* HostWindowPlugin_exports[][3] = {
	{(void*)_m, "getModuleName", (void*)getModuleName},
	{(void*)_m, "primitiveCloseHostWindow\000\000", (void*)primitiveCloseHostWindow},
	{(void*)_m, "primitiveCreateHostWindow\000\000", (void*)primitiveCreateHostWindow},
	{(void*)_m, "primitiveHostWindowPosition\000\000", (void*)primitiveHostWindowPosition},
	{(void*)_m, "primitiveHostWindowPositionSet\000\000", (void*)primitiveHostWindowPositionSet},
#if TerfVM
	{(void*)_m, "primitiveHostWindowScreenWorkAreaPosition\000\000", (void*)primitiveHostWindowScreenWorkAreaPosition},
#endif /* TerfVM */
#if TerfVM
	{(void*)_m, "primitiveHostWindowScreenWorkAreaSize\000\000", (void*)primitiveHostWindowScreenWorkAreaSize},
#endif /* TerfVM */
	{(void*)_m, "primitiveHostWindowSize\000\000", (void*)primitiveHostWindowSize},
	{(void*)_m, "primitiveHostWindowSizeSet\000\000", (void*)primitiveHostWindowSizeSet},
	{(void*)_m, "primitiveHostWindowTitle\000\000", (void*)primitiveHostWindowTitle},
#if TerfVM
	{(void*)_m, "primitiveNativeDisplayPosition\000\377", (void*)primitiveNativeDisplayPosition},
#endif /* TerfVM */
#if TerfVM
	{(void*)_m, "primitiveNativeDisplaySize\000\377", (void*)primitiveNativeDisplaySize},
#endif /* TerfVM */
#if TerfVM
	{(void*)_m, "primitiveNativeWindowPosition\000\377", (void*)primitiveNativeWindowPosition},
#endif /* TerfVM */
#if TerfVM
	{(void*)_m, "primitiveNativeWindowSize\000\377", (void*)primitiveNativeWindowSize},
#endif /* TerfVM */
#if TerfVM
	{(void*)_m, "primitiveSetCursorPosition\000\000", (void*)primitiveSetCursorPosition},
#endif /* TerfVM */
	{(void*)_m, "primitiveShowHostWindowRect\000\000", (void*)primitiveShowHostWindowRect},
#if TerfVM
	{(void*)_m, "primitiveSqueakWindowHandle\000\377", (void*)primitiveSqueakWindowHandle},
#endif /* TerfVM */
	{(void*)_m, "setInterpreter", (void*)setInterpreter},
	{(void*)_m, "shutdownModule\000\377", (void*)shutdownModule},
	{NULL, NULL, NULL}
};

#else /* ifdef SQ_BUILTIN_PLUGIN */

signed char primitiveCloseHostWindowAccessorDepth = 0;
signed char primitiveCreateHostWindowAccessorDepth = 0;
signed char primitiveHostWindowPositionAccessorDepth = 0;
signed char primitiveHostWindowPositionSetAccessorDepth = 0;
#if TerfVM
signed char primitiveHostWindowScreenWorkAreaPositionAccessorDepth = 0;
#endif /* TerfVM */
#if TerfVM
signed char primitiveHostWindowScreenWorkAreaSizeAccessorDepth = 0;
#endif /* TerfVM */
signed char primitiveHostWindowSizeAccessorDepth = 0;
signed char primitiveHostWindowSizeSetAccessorDepth = 0;
signed char primitiveHostWindowTitleAccessorDepth = 0;
#if TerfVM
signed char primitiveSetCursorPositionAccessorDepth = 0;
#endif /* TerfVM */
signed char primitiveShowHostWindowRectAccessorDepth = 0;

#endif /* ifdef SQ_BUILTIN_PLUGIN */
