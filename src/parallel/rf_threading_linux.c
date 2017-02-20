/**
 * @author: Lefteris Karapetsas
 * @licence: BSD3 (Check repository root for details)
 */
#include <rfbase/parallel/rf_threading.h>
#include <memory.h>

int rf_thread_get_id()
{
    pthread_t ptid = pthread_self();
    int thread_id = 0;
    size_t copy_size = sizeof(ptid);
    if (sizeof(thread_id) < copy_size) {
        copy_size = sizeof(thread_id);
    }
    memcpy(&thread_id, &ptid, copy_size);
    return thread_id;
}

i_INLINE_INS bool rf_mutex_init(struct RFmutex *mutex);
i_INLINE_INS bool rf_mutex_lock(struct RFmutex *mutex);
i_INLINE_INS bool rf_mutex_unlock(struct RFmutex *mutex);
i_INLINE_INS bool rf_mutex_deinit(struct RFmutex *mutex);
