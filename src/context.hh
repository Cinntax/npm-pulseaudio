#ifndef __CONTEXT_HH__
#define __CONTEXT_HH__

#include "common.hh"

namespace pulse {
  enum InfoType {
    INFO_SOURCE_LIST,
    INFO_SINK_LIST,
		INFO_MODULE_LIST
  };
  
  class Context: public ObjectWrap {
    friend class Stream;
  protected:
    pa_context *pa_ctx;
    
    Context(String::Utf8Value *client_name);
    ~Context();
    
    /* state */
    Persistent<Function> state_callback;
    pa_context_state_t pa_state;
    static void StateCallback(pa_context *c, void *ud);
    void state_listener(Handle<Value> callback);
    
    /* connection */
    int connect(String::Utf8Value *server_name, pa_context_flags flags);
    void disconnect();

    static void EventCallback(pa_context *c, const char *name, pa_proplist *p, void *ud);
    
    /* introspection */
    void info(InfoType infotype, Handle<Function> callback);
		void loadmodule(String::Utf8Value *module_name, String::Utf8Value *argument_list, Handle<Function> callback);
		void unloadmodule(int index, Handle<Function> callback);

		void set_source_volume_by_name(String::Utf8Value *source_name, uint32_t volume, Handle<Function> callback);
  public:
    static pa_mainloop_api mainloop_api;
    
    static void Init(Handle<Object> target);
    
    static Handle<Value> New(const Arguments& args);
    
    static Handle<Value> Connect(const Arguments& args);
    static Handle<Value> Disconnect(const Arguments& args);
    
    static Handle<Value> Info(const Arguments& args);

		static Handle<Value> LoadModule(const Arguments& args);
		static Handle<Value> UnloadModule(const Arguments& args);
		static Handle<Value> SetSourceVolumeByName(const Arguments& args);
  };
}

#endif//__CONTEXT_HH__
