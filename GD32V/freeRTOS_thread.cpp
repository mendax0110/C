// include the libraries
#include <thread>
#include <system_error>
#include <cerrno>
#include <freeRTOS.h>
#include <gthr_key_type.h>

// namespace
namespace free_rtos_std
{
    extern Key *s_key;
}

// free rtos thread
namespace std
{
    static void __execute_native_thread_routine(void *__p)
    {
        __gthread_t local{*static_cast<__gthread_t *>(__p)};
        {
            thread :: _State_ptr __t{static_cast<thread :: _State *>(local.arg())};
            local.notify_started();
            __t -> _M_run();
        }

        if(free_rtos_std :: s_key)
            free_rtos_std :: s_key -> CallDestructor(__gthread_t :: self().native_task_handle());

        local.notify_joined();
    }

    thread :: _State :: ~_State() = default;

    // start thread
    void thread :: _M_start_thread(_State_ptr state, void (*)())
    {
        const int err = __gthread_create(&_M_id._M_thread, __execute_native_thread_routine, state.get());

        if (err)
            __throw_system_error(err);

        state.release();
    }

    // join thread
    void thread :: join()
    {
        id invalid;
        if (_M_id._M_thread != invalid._M_thread)
            __gthread_join(_M_id._M_thread, nullptr);
        else
            __throw_system_error(EINVAL);

        _M_id = std :: move(invalid);
    }

    // detach thread
    void thread :: detach()
    {
        id invalid;
        if (_M_id._M_thread != invalid._M_thread)
            __gthread_detach(_M_id._M_thread);
        else
            __throw_system_error(EINVAL);

        __M_id = std :: move(invalid);
    }

    // hardware concurrency
    unsigned int thread :: hardware_concurrency() noexcept
    {
        return 0;
    }

    // sleep
    void this_thread :: __sleep_for(chrono :: seconds sec, chrono :: nanoseconds nsec)
    {
        long ms = nsec.count() / 1'000'000;
        if (sec.count() == 0 && ms == 0 && nsec.count() > 0)
            ms = 1;
        
        vTaskDelay(pdMS_TO_TICKS(chrono :: milliseconds(sec).count() + ms));
    }
}