#include <node.h>
#include <windows.h>
#include <delib.h>

using namespace v8;

void openModule(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	unsigned long module = 0, nr = 0;

	module = (unsigned long)args[0]->IntegerValue();
	nr = (unsigned long)args[1]->IntegerValue();

	unsigned long handle = DapiOpenModule(module, nr);

	args.GetReturnValue().Set(Integer::New(isolate, handle));
}

void getDELIBVersion(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	unsigned long version = DapiGetDELIBVersion(0, 0);

	args.GetReturnValue().Set(Integer::New(isolate, version));
}

void closeModule(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	unsigned long module = (unsigned long)args[0]->IntegerValue();
	DapiCloseModule(module);
}

void getLastError(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	unsigned long error = DapiGetLastError();

	args.GetReturnValue().Set(Integer::New(isolate, error));
}

void getLastErrorText(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	char msg[1024];
	DapiGetLastErrorText((unsigned char*)msg, sizeof(msg));

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, msg));
}


void adSetMode(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	unsigned long module = (unsigned long)args[0]->IntegerValue();
	unsigned long channel = (unsigned long)args[1]->IntegerValue();
	unsigned long mode = (unsigned long)args[2]->IntegerValue();

	DapiADSetMode(module, channel, mode);
}

void adGetMode(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	unsigned long module = (unsigned long)args[0]->IntegerValue();
	unsigned long channel = (unsigned long)args[1]->IntegerValue();

	unsigned long mode = DapiADGetMode(module, channel);

	args.GetReturnValue().Set(Integer::New(isolate, mode));
}

void adGetVolt(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	unsigned long module = (unsigned long)args[0]->IntegerValue();
	unsigned long channel = (unsigned long)args[1]->IntegerValue();

	float value = DapiADGetVolt(module, channel);

	args.GetReturnValue().Set(Number::New(isolate, value));
}

void daSetMode(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	unsigned long module = (unsigned long)args[0]->IntegerValue();
	unsigned long channel = (unsigned long)args[1]->IntegerValue();
	unsigned long mode = (unsigned long)args[2]->IntegerValue();

	DapiDASetMode(module, channel, mode);
}

void daGetMode(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	unsigned long module = (unsigned long)args[0]->IntegerValue();
	unsigned long channel = (unsigned long)args[1]->IntegerValue();

	unsigned long mode = DapiDAGetMode(module, channel);

	args.GetReturnValue().Set(Integer::New(isolate, mode));
}

void daSetVolt(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	unsigned long module = (unsigned long)args[0]->IntegerValue();
	unsigned long channel = (unsigned long)args[1]->IntegerValue();
	float value = (float)args[2]->NumberValue();

	DapiDASetVolt(module, channel, value);
}

template<typename TypeName>
inline void NODE_SET_PROPERTY(TypeName& recv, const char* name, unsigned long value) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope handle_scope(isolate);

	Local<Integer> _value = Integer::New(isolate, value);
	Local<String> _name = String::NewFromUtf8(isolate, name);
	recv->Set(_name, _value);
}

void init(Handle<Object> exports) {

	// Modules
	NODE_SET_PROPERTY(exports, "USB_Interface8", USB_Interface8);
	NODE_SET_PROPERTY(exports, "USB_CAN_STICK", USB_CAN_STICK);
	NODE_SET_PROPERTY(exports, "USB_LOGI_500", USB_LOGI_500);
	NODE_SET_PROPERTY(exports, "USB_SER_DEBUG", USB_SER_DEBUG);
	NODE_SET_PROPERTY(exports, "RO_SER", RO_SER);
	NODE_SET_PROPERTY(exports, "USB_BITP_200", USB_BITP_200);
	NODE_SET_PROPERTY(exports, "RO_USB1", RO_USB1);
	NODE_SET_PROPERTY(exports, "RO_USB", RO_USB);
	NODE_SET_PROPERTY(exports, "RO_ETH", RO_ETH);
	NODE_SET_PROPERTY(exports, "USB_MINI_STICK", USB_MINI_STICK);
	NODE_SET_PROPERTY(exports, "USB_LOGI_18", USB_LOGI_18);
	NODE_SET_PROPERTY(exports, "RO_CAN", RO_CAN);
	NODE_SET_PROPERTY(exports, "USB_SPI_MON", USB_SPI_MON);
	NODE_SET_PROPERTY(exports, "USB_WATCHDOG", USB_WATCHDOG);
	NODE_SET_PROPERTY(exports, "USB_OPTOIN_8", USB_OPTOIN_8);
	NODE_SET_PROPERTY(exports, "USB_RELAIS_8", USB_RELAIS_8);
	NODE_SET_PROPERTY(exports, "USB_OPTOIN_8_RELAIS_8", USB_OPTOIN_8_RELAIS_8);
	NODE_SET_PROPERTY(exports, "USB_OPTOIN_16_RELAIS_16", USB_OPTOIN_16_RELAIS_16);
	NODE_SET_PROPERTY(exports, "USB_OPTOIN_32", USB_OPTOIN_32);
	NODE_SET_PROPERTY(exports, "USB_RELAIS_32", USB_RELAIS_32);
	NODE_SET_PROPERTY(exports, "USB_OPTOIN_32_RELAIS_32", USB_OPTOIN_32_RELAIS_32);
	NODE_SET_PROPERTY(exports, "USB_OPTOIN_64", USB_OPTOIN_64);
	NODE_SET_PROPERTY(exports, "USB_RELAIS_64", USB_RELAIS_64);
	NODE_SET_PROPERTY(exports, "BS_USB_8", BS_USB_8);
	NODE_SET_PROPERTY(exports, "BS_USB_16", BS_USB_16);
	NODE_SET_PROPERTY(exports, "BS_USB_32", BS_USB_32);
	NODE_SET_PROPERTY(exports, "USB_TTL_32", USB_TTL_32);
	NODE_SET_PROPERTY(exports, "USB_TTL_64", USB_TTL_64);
	NODE_SET_PROPERTY(exports, "RO_ETH_INTERN", RO_ETH_INTERN);
	NODE_SET_PROPERTY(exports, "BS_SER", BS_SER);
	NODE_SET_PROPERTY(exports, "BS_CAN", BS_CAN);
	NODE_SET_PROPERTY(exports, "BS_ETH", BS_ETH);
	NODE_SET_PROPERTY(exports, "NET_ETH", NET_ETH);
	NODE_SET_PROPERTY(exports, "RO_CAN2", RO_CAN2);
	NODE_SET_PROPERTY(exports, "RO_USB2", RO_USB2);
	NODE_SET_PROPERTY(exports, "RO_ETH_LC", RO_ETH_LC);
	NODE_SET_PROPERTY(exports, "ETH_RELAIS_8", ETH_RELAIS_8);
	NODE_SET_PROPERTY(exports, "ETH_OPTOIN_8", ETH_OPTOIN_8);
	NODE_SET_PROPERTY(exports, "ETH_O4_R4_ADDA", ETH_O4_R4_ADDA);
	NODE_SET_PROPERTY(exports, "MAX_NR_OF_MODULES", MAX_NR_OF_MODULES);

	// Errorcodes
	NODE_SET_PROPERTY(exports, "ERR_NONE", DAPI_ERR_NONE);
	NODE_SET_PROPERTY(exports, "ERR_DEVICE_NOT_FOUND", DAPI_ERR_DEVICE_NOT_FOUND);
	NODE_SET_PROPERTY(exports, "ERR_COMMUNICATION_ERROR", DAPI_ERR_COMMUNICATION_ERROR);
	NODE_SET_PROPERTY(exports, "ERR_ILLEGAL_HANDLE", DAPI_ERR_ILLEGAL_HANDLE);
	NODE_SET_PROPERTY(exports, "ERR_FUNCTION_NOT_DEFINED", DAPI_ERR_FUNCTION_NOT_DEFINED);
	NODE_SET_PROPERTY(exports, "ERR_ILLEGAL_COM_HANDLE", DAPI_ERR_ILLEGAL_COM_HANDLE);
	NODE_SET_PROPERTY(exports, "ERR_ILLEGAL_MODE", DAPI_ERR_ILLEGAL_MODE);
	NODE_SET_PROPERTY(exports, "ERR_WITH_TEXT", DAPI_ERR_WITH_TEXT);
	NODE_SET_PROPERTY(exports, "ERR_SW_FEATURE_NOT_SUPPORTED", DAPI_ERR_SW_FEATURE_NOT_SUPPORTED);
	NODE_SET_PROPERTY(exports, "ERR_ILLEGAL_IO_TYPE", DAPI_ERR_ILLEGAL_IO_TYPE);
	NODE_SET_PROPERTY(exports, "ERR_ILLEGAL_CHANNEL", DAPI_ERR_ILLEGAL_CHANNEL);

	// D/A A/D Modes
	NODE_SET_PROPERTY(exports, "ADDA_MODE_UNIPOL_10V", DAPI_ADDA_MODE_UNIPOL_10V);
	NODE_SET_PROPERTY(exports, "ADDA_MODE_UNIPOL_5V", DAPI_ADDA_MODE_UNIPOL_5V);
	NODE_SET_PROPERTY(exports, "ADDA_MODE_UNIPOL_2V5", DAPI_ADDA_MODE_UNIPOL_2V5);
	NODE_SET_PROPERTY(exports, "ADDA_MODE_BIPOL_10V", DAPI_ADDA_MODE_BIPOL_10V);
	NODE_SET_PROPERTY(exports, "ADDA_MODE_BIPOL_5V", DAPI_ADDA_MODE_BIPOL_5V);
	NODE_SET_PROPERTY(exports, "ADDA_MODE_BIPOL_2V5", DAPI_ADDA_MODE_BIPOL_2V5);
	NODE_SET_PROPERTY(exports, "ADDA_MODE_0_20mA", DAPI_ADDA_MODE_0_20mA);
	NODE_SET_PROPERTY(exports, "ADDA_MODE_4_20mA", DAPI_ADDA_MODE_4_20mA);
	NODE_SET_PROPERTY(exports, "ADDA_MODE_0_24mA", DAPI_ADDA_MODE_0_24mA);
	NODE_SET_PROPERTY(exports, "ADDA_MODE_0_50mA", DAPI_ADDA_MODE_0_50mA);
	NODE_SET_PROPERTY(exports, "ADDA_MODE_DA_DISABLE", DAPI_ADDA_MODE_DA_DISABLE);
	NODE_SET_PROPERTY(exports, "ADDA_MODE_DA_ENABLE", DAPI_ADDA_MODE_DA_ENABLE);
	NODE_SET_PROPERTY(exports, "ADDA_MODE_PREVENT_DAPI_MODE_ERROR", DAPI_ADDA_MODE_PREVENT_DAPI_MODE_ERROR);


	NODE_SET_METHOD(exports, "openModule", openModule);
	NODE_SET_METHOD(exports, "getDELIBVersion", getDELIBVersion);
	NODE_SET_METHOD(exports, "closeModule", closeModule);
	NODE_SET_METHOD(exports, "getLastError", getLastError);
	NODE_SET_METHOD(exports, "getLastErrorText", getLastErrorText);

	NODE_SET_METHOD(exports, "adSetMode", adSetMode);
	NODE_SET_METHOD(exports, "adGetMode", adGetMode);
	NODE_SET_METHOD(exports, "adGetVolt", adGetVolt);

	NODE_SET_METHOD(exports, "daSetMode", daSetMode);
	NODE_SET_METHOD(exports, "daGetMode", daGetMode);
	NODE_SET_METHOD(exports, "daSetVolt", daSetVolt);
}

NODE_MODULE(addon, init)
