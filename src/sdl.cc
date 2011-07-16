#include "sdl.h"

using namespace v8;

extern "C" void
init(Handle<Object> target)
{

  NODE_SET_METHOD(target, "init", sdl::Init);
  NODE_SET_METHOD(target, "initSubSystem", sdl::InitSubSystem);
  NODE_SET_METHOD(target, "quit", sdl::Quit);
  NODE_SET_METHOD(target, "quitSubSystem", sdl::QuitSubSystem);
  NODE_SET_METHOD(target, "wasInit", sdl::WasInit);
  NODE_SET_METHOD(target, "clearError", sdl::ClearError);
  NODE_SET_METHOD(target, "getError", sdl::GetError);
  NODE_SET_METHOD(target, "setError", sdl::SetError);
  NODE_SET_METHOD(target, "waitEvent", sdl::WaitEvent);
  NODE_SET_METHOD(target, "pollEvent", sdl::PollEvent);
  NODE_SET_METHOD(target, "setVideoMode", sdl::SetVideoMode);
  NODE_SET_METHOD(target, "videoModeOK", sdl::VideoModeOK);
  NODE_SET_METHOD(target, "numJoysticks", sdl::NumJoysticks);
  NODE_SET_METHOD(target, "joystickOpen", sdl::JoystickOpen);
  NODE_SET_METHOD(target, "joystickOpened", sdl::JoystickOpened);
  NODE_SET_METHOD(target, "joystickName", sdl::JoystickName);
  NODE_SET_METHOD(target, "joystickNumAxes", sdl::JoystickNumAxes);
  NODE_SET_METHOD(target, "joystickNumButtons", sdl::JoystickNumButtons);
  NODE_SET_METHOD(target, "joystickNumBalls", sdl::JoystickNumBalls);
  NODE_SET_METHOD(target, "joystickNumHats", sdl::JoystickNumHats);
  NODE_SET_METHOD(target, "joystickClose", sdl::JoystickClose);
  NODE_SET_METHOD(target, "joystickUpdate", sdl::JoystickUpdate);
  NODE_SET_METHOD(target, "joystickEventState", sdl::JoystickEventState);
  NODE_SET_METHOD(target, "flip", sdl::Flip);
  NODE_SET_METHOD(target, "fillRect", sdl::FillRect);
  NODE_SET_METHOD(target, "updateRect", sdl::UpdateRect);

  Local<Object> INIT = Object::New();
  target->Set(String::New("INIT"), INIT);
  INIT->Set(String::New("TIMER"), Number::New(SDL_INIT_TIMER));
  INIT->Set(String::New("AUDIO"), Number::New(SDL_INIT_AUDIO));
  INIT->Set(String::New("VIDEO"), Number::New(SDL_INIT_VIDEO));
  INIT->Set(String::New("JOYSTICK"), Number::New(SDL_INIT_JOYSTICK));
  INIT->Set(String::New("EVERYTHING"), Number::New(SDL_INIT_EVERYTHING));
  INIT->Set(String::New("NOPARACHUTE"), Number::New(SDL_INIT_NOPARACHUTE));
  
  Local<Object> SURFACE = Object::New();
  target->Set(String::New("SURFACE"), SURFACE);
  SURFACE->Set(String::New("ANYFORMAT"), Number::New(SDL_ANYFORMAT));
  SURFACE->Set(String::New("ASYNCBLIT"), Number::New(SDL_ASYNCBLIT));
  SURFACE->Set(String::New("DOUBLEBUF"), Number::New(SDL_DOUBLEBUF));
  SURFACE->Set(String::New("HWACCEL"), Number::New(SDL_HWACCEL));
  SURFACE->Set(String::New("HWPALETTE"), Number::New(SDL_HWPALETTE));
  SURFACE->Set(String::New("HWSURFACE"), Number::New(SDL_HWSURFACE));
  SURFACE->Set(String::New("FULLSCREEN"), Number::New(SDL_FULLSCREEN));
  SURFACE->Set(String::New("OPENGL"), Number::New(SDL_OPENGL));
  SURFACE->Set(String::New("RESIZABLE"), Number::New(SDL_RESIZABLE));
  SURFACE->Set(String::New("RLEACCEL"), Number::New(SDL_RLEACCEL));
  SURFACE->Set(String::New("SRCALPHA"), Number::New(SDL_SRCALPHA));
  SURFACE->Set(String::New("SRCCOLORKEY"), Number::New(SDL_SRCCOLORKEY));
  SURFACE->Set(String::New("SWSURFACE"), Number::New(SDL_SWSURFACE));
  SURFACE->Set(String::New("PREALLOC"), Number::New(SDL_PREALLOC));
  
  Local<Object> TTF = Object::New();
  target->Set(String::New("TTF"), TTF);
  NODE_SET_METHOD(TTF, "init", sdl::TTF::Init);
  NODE_SET_METHOD(TTF, "openFont", sdl::TTF::OpenFont);
  NODE_SET_METHOD(TTF, "renderTextBlended", sdl::TTF::RenderTextBlended);    

}

Handle<Value> sdl::Init(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected Init(Number)")));
  }

  if (SDL_Init(args[0]->Int32Value()) < 0) return ThrowSDLException(__func__);

  return Undefined();
}

Handle<Value> sdl::InitSubSystem(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected InitSubSystem(Number)")));
  }

  if (SDL_InitSubSystem(args[0]->Int32Value()) < 0) return ThrowSDLException(__func__);

  return Undefined();
}

Handle<Value> sdl::Quit(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 0)) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected Quit()")));
  }

  SDL_Quit();

  return Undefined();
}

Handle<Value> sdl::QuitSubSystem(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected QuitSubSystem(Number)")));
  }

  SDL_QuitSubSystem(args[0]->Int32Value());

  return Undefined();
}

Handle<Value> sdl::WasInit(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected WasInit(Number)")));
  }
  
  return Number::New(SDL_WasInit(args[0]->Int32Value()));  
}

Handle<Value> sdl::ClearError(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 0)) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected ClearError()")));
  }

  SDL_ClearError();

  return Undefined();
}

Handle<Value> sdl::GetError(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 0)) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected GetError()")));
  }

  return String::New(SDL_GetError());
}

Handle<Value> sdl::SetError(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsString())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected SetError(String)")));
  }
  
  String::Utf8Value message(args[1]);
  
  SDL_SetError(*message);

  return Undefined();
}

static int sdl::EIO_WaitEvent(eio_req *req) {
  sdl::closure_t *closure = (sdl::closure_t *) req->data;
  closure->status = SDL_WaitEvent(NULL);
  return 0;
}

static int sdl::EIO_OnEvent(eio_req *req) {
  HandleScope scope;

  sdl::closure_t *closure = (sdl::closure_t *) req->data;
  ev_unref(EV_DEFAULT_UC);

  Handle<Value> argv[1];
  if (closure->status == 0) {
    argv[0] = MakeSDLException("WaitEvent");
  } else {
    argv[0] = Undefined();
  }
  
  closure->fn->Call(Context::GetCurrent()->Global(), 1, argv);

  closure->fn.Dispose();
  free(closure);
  return 0;
}

static Handle<Value> sdl::WaitEvent(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsFunction())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected WaitEvent(Function)")));
  }

  closure_t *closure = (closure_t*) malloc(sizeof(closure_t));
  closure->fn = Persistent<Function>::New(Handle<Function>::Cast(args[0]));
  eio_custom(EIO_WaitEvent, EIO_PRI_DEFAULT, EIO_OnEvent, closure);
  ev_ref(EV_DEFAULT_UC);
  return Undefined();
}



Handle<Value> sdl::PollEvent(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 0)) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected PollEvent()")));
  }

  SDL_Event event;
  if (!SDL_PollEvent(&event)) {
    return Undefined();
  }

  Local<Object> evt = Object::New();

  switch (event.type) {
    case SDL_ACTIVEEVENT:
      evt->Set(String::New("type"), String::New("ACTIVEEVENT"));
      evt->Set(String::New("gain"), Boolean::New(event.active.gain));
      evt->Set(String::New("state"), Number::New(event.active.state));
      break;
    case SDL_KEYDOWN:
    case SDL_KEYUP:
      evt->Set(String::New("type"), String::New(event.type == SDL_KEYDOWN ? "KEYDOWN" : "KEYUP"));
      evt->Set(String::New("scancode"), Number::New(event.key.keysym.scancode));
      evt->Set(String::New("sym"), Number::New(event.key.keysym.sym));
      evt->Set(String::New("mod"), Number::New(event.key.keysym.mod));
      break;
    case SDL_MOUSEMOTION:
      evt->Set(String::New("type"), String::New("MOUSEMOTION"));
      evt->Set(String::New("state"), Number::New(event.motion.state));
      evt->Set(String::New("which"), Number::New(event.motion.which));
      evt->Set(String::New("x"), Number::New(event.motion.x));
      evt->Set(String::New("y"), Number::New(event.motion.y));
      evt->Set(String::New("xrel"), Number::New(event.motion.xrel));
      evt->Set(String::New("yrel"), Number::New(event.motion.yrel));
      break;
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
      evt->Set(String::New("type"), String::New(event.type == SDL_MOUSEBUTTONDOWN ? "MOUSEBUTTONDOWN" : "MOUSEBUTTONUP"));
      evt->Set(String::New("button"), Number::New(event.button.button));
      evt->Set(String::New("which"), Number::New(event.button.which));
      evt->Set(String::New("x"), Number::New(event.button.x));
      evt->Set(String::New("y"), Number::New(event.button.y));
      break;
    case SDL_JOYAXISMOTION:
      evt->Set(String::New("type"), String::New("JOYAXISMOTION"));
      evt->Set(String::New("which"), Number::New(event.jaxis.which));
      evt->Set(String::New("axis"), Number::New(event.jaxis.axis));
      evt->Set(String::New("value"), Number::New(event.jaxis.value));
      break;
    case SDL_JOYBALLMOTION:
      evt->Set(String::New("type"), String::New("JOYBALLMOTION"));
      evt->Set(String::New("which"), Number::New(event.jball.which));
      evt->Set(String::New("ball"), Number::New(event.jball.ball));
      evt->Set(String::New("xrel"), Number::New(event.jball.xrel));
      evt->Set(String::New("yrel"), Number::New(event.jball.yrel));
      break;
    case SDL_JOYHATMOTION:
      evt->Set(String::New("type"), String::New("JOYHATMOTION"));
      evt->Set(String::New("which"), Number::New(event.jhat.which));
      evt->Set(String::New("hat"), Number::New(event.jhat.hat));
      evt->Set(String::New("value"), Number::New(event.jhat.value));
      break;
    case SDL_JOYBUTTONDOWN:
    case SDL_JOYBUTTONUP:
      evt->Set(String::New("type"), String::New(event.type == SDL_JOYBUTTONDOWN ? "JOYBUTTONDOWN" : "JOYBUTTONUP"));
      evt->Set(String::New("which"), Number::New(event.jbutton.which));
      evt->Set(String::New("button"), Number::New(event.jbutton.button));
      break;
    case SDL_QUIT:
      evt->Set(String::New("type"), String::New("QUIT"));
      break;
    default:
      evt->Set(String::New("type"), String::New("UNKNOWN"));
      evt->Set(String::New("typeCode"), Number::New(event.type));
      break;
  }

  return scope.Close(evt);
}

static Handle<Value> sdl::SetVideoMode(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 4 && args[0]->IsNumber() && args[1]->IsNumber() && args[2]->IsNumber() && args[3]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected SetVideoMode(Number, Number, Number, Number)")));
  }

  int width = (args[0]->Int32Value());
  int height = (args[1]->Int32Value());
  int bpp = (args[2]->Int32Value());
  int flags = (args[3]->Int32Value());

  SDL_Surface* screen = SDL_SetVideoMode(width, height, bpp, flags);
  if (screen == NULL) return ThrowSDLException(__func__);
  return scope.Close(WrapSurface(screen));
}

static Handle<Value> sdl::VideoModeOK(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 4 && args[0]->IsNumber() && args[1]->IsNumber() && args[2]->IsNumber() && args[3]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected VideoModeOK(Number, Number, Number, Number)")));
  }

  int width = (args[0]->Int32Value());
  int height = (args[1]->Int32Value());
  int bpp = (args[2]->Int32Value());
  int flags = (args[3]->Int32Value());

  return Number::New(SDL_VideoModeOK(width, height, bpp, flags));
}

static Handle<Value> sdl::NumJoysticks(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 0)) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected NumJoysticks()")));
  }

  return Number::New(SDL_NumJoysticks());
}

static Handle<Value> sdl::JoystickOpen(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected JoystickOpen(Number)")));
  }

  SDL_Joystick* joystick = SDL_JoystickOpen(args[0]->Int32Value());
  if (!joystick) return ThrowSDLException(__func__);
  return scope.Close(WrapJoystick(joystick));
}

static Handle<Value> sdl::JoystickOpened(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected JoystickOpened(Number)")));
  }

  return Number::New(SDL_JoystickOpened(args[0]->Int32Value()));
}


static Handle<Value> sdl::JoystickName(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected JoystickName(Number)")));
  }
  
  return String::New(SDL_JoystickName(args[0]->Int32Value()));
}

static Handle<Value> sdl::JoystickNumAxes(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsObject())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected JoystickNumAxes(Joystick)")));
  }
  
  return Number::New(SDL_JoystickNumAxes(UnwrapJoystick(args[0]->ToObject())));
}

static Handle<Value> sdl::JoystickNumButtons(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsObject())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected JoystickNumButtons(Joystick)")));
  }
  
  return Number::New(SDL_JoystickNumButtons(UnwrapJoystick(args[0]->ToObject())));
}

static Handle<Value> sdl::JoystickNumBalls(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsObject())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected JoystickNumBalls(Joystick)")));
  }
  
  return Number::New(SDL_JoystickNumBalls(UnwrapJoystick(args[0]->ToObject())));
}

static Handle<Value> sdl::JoystickNumHats(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsObject())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected JoystickNumHats(Joystick)")));
  }
  
  return Number::New(SDL_JoystickNumHats(UnwrapJoystick(args[0]->ToObject())));
}

static Handle<Value> sdl::JoystickClose(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsObject())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected JoystickClose(Joystick)")));
  }
  
  SDL_JoystickClose(UnwrapJoystick(args[0]->ToObject()));

  return Undefined();
}

static Handle<Value> sdl::JoystickUpdate(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 0)) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected JoystickUpdate()")));
  }

  SDL_JoystickUpdate();
  return Undefined();
}

static Handle<Value> sdl::JoystickEventState(const Arguments& args) {
  HandleScope scope;

  int state;
  if (args.Length() == 0) {
    state = SDL_QUERY;
  } else {
    if (!(args.Length() == 1 && args[0]->IsBoolean())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected JoystickEventState([Boolean])")));
    }
    state = args[0]->BooleanValue() ? SDL_ENABLE : SDL_IGNORE;
  }
  return Boolean::New(SDL_JoystickEventState(state));
}


static Handle<Value> sdl::Flip(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsObject())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected Flip(Surface)")));
  }

  SDL_Flip(UnwrapSurface(args[0]->ToObject()));
  
  return Undefined();
}

static Handle<Value> sdl::FillRect(const Arguments& args) {
  HandleScope scope;

  if (!
    ((args.Length() == 3 && args[0]->IsObject() && (args[1]->IsObject() || args[1]->IsNull()) && args[2]->IsNumber()) ||
    (args.Length() == 6 && args[0]->IsObject() && args[1]->IsNumber() && args[2]->IsNumber() && args[3]->IsNumber() && args[4]->IsNumber() && args[5]->IsNumber()))
  ) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected FillRect(Surface, Rect, Number) or (Surface, Number, Number, Number, Number, Number)")));
  }
  
  SDL_Surface* surface = UnwrapSurface(args[0]->ToObject());
  SDL_Rect* rect;
  int color;
  if (args.Length() == 6) {
    SDL_Rect r;
    r.x = args[1]->Int32Value();
    r.y = args[2]->Int32Value();
    r.w = args[3]->Int32Value();
    r.h = args[4]->Int32Value();
    rect = &r;
    color = args[5]->Int32Value();
  } else {
    rect = args[1]->IsNull() ? NULL : UnwrapRect(args[1]->ToObject());
    color = args[2]->Int32Value();
  }

  if (SDL_FillRect (surface, rect, color) < 0) return ThrowSDLException(__func__);

  return Undefined();
}

static Handle<Value> sdl::UpdateRect(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 2 && args[0]->IsObject() && args[1]->IsObject())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected UpdateRect(Surface, Rect)")));
  }

  SDL_Surface* surface = UnwrapSurface(args[0]->ToObject());
  SDL_Rect* rect = UnwrapRect(args[0]->ToObject());

  SDL_UpdateRect(surface, rect->x, rect->y, rect->w, rect->h);
  
  return Undefined();
}


static Handle<Value> sdl::TTF::Init(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 0)) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected TTF::Init()")));
  }

  if (TTF_Init() < 0) {
    return ThrowException(Exception::Error(String::Concat(
      String::New("TTF::Init: "),
      String::New(TTF_GetError())
    )));
  }
  
  return Undefined();
}

static Handle<Value> sdl::TTF::OpenFont(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 2 && args[0]->IsString() && args[1]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected TTF::OpenFont(String, Number)")));
  }

  String::Utf8Value file(args[0]);
  int ptsize = (args[1]->Int32Value());

  TTF_Font* font = TTF_OpenFont(*file, ptsize);
  if (font == NULL) {
    return ThrowException(Exception::Error(String::Concat(
      String::New("TTF::OpenFont: "),
      String::New(TTF_GetError())
    )));
  }
  return scope.Close(WrapFont(font));
}

static Handle<Value> sdl::TTF::RenderTextBlended(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 6 && args[0]->IsObject() && args[1]->IsObject() && args[2]->IsString() && args[3]->IsNumber() && args[4]->IsNumber() && args[5]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected TTF::RenderTextBlended(Surface, Font, String, Number, Number, Number)")));
  }

  SDL_Surface* screen = UnwrapSurface(args[0]->ToObject());
  TTF_Font* font = UnwrapFont(args[1]->ToObject());
  String::Utf8Value text(args[2]);
  int x = args[3]->Int32Value();
  int y = args[4]->Int32Value();
  int colorCode = args[5]->Int32Value();

  Uint8 r, g, b;
  SDL_GetRGB(colorCode, screen->format, &r, &g, &b);

  SDL_Color color;
  color.r = r;
  color.g = g;
  color.b = b;

  SDL_Surface *resulting_text;
  resulting_text = TTF_RenderText_Blended(font, *text, color);
  if (!resulting_text) {
    return ThrowException(Exception::Error(String::Concat(
      String::New("TTF::RenderTextBlended: "),
      String::New(TTF_GetError())
    )));
  }

  SDL_Rect destRect;
  destRect.x = x;
  destRect.y = y;

  int result = SDL_BlitSurface(resulting_text, NULL, screen, &destRect);
  if (result < 0) {
    return ThrowException(Exception::Error(String::Concat(
      String::New("TTF::RenderTextBlended: "),
      String::New(SDL_GetError())
    )));
  }

  SDL_FreeSurface(resulting_text);

  return Undefined();
}


