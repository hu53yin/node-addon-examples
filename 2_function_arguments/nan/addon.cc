#include <nan.h>

void Add(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();

  if (info.Length() < 2) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!info[0]->IsNumber() || !info[1]->IsNumber()) {
    Nan::ThrowTypeError("Wrong arguments");
    return;
  }

  double arg0 = info[0]->NumberValue(context).FromJust();
  double arg1 = info[1]->NumberValue(context).FromJust();
  v8::Local<v8::Number> num = Nan::New(arg0 + arg1);

  info.GetReturnValue().Set(num);
}

void Init(v8::Local<v8::Object> exports) {
  v8::Local<v8::Context> context = exports->CreationContext();
  exports->Set(Nan::New("add").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Add)
                   ->GetFunction(context)
                   .ToLocalChecked());
}

NODE_MODULE(addon, Init)
