#ifndef LUPULUS_INDEX_H
#define LUPULUS_INDEX_H

#include <mutex>
#include <cstddef>


namespace lpl
{
    class Index
    {
    public:
        Index(std::size_t max)
            : max(max), idx(0)
        {
        }

        std::size_t get()
        {
            std::lock_guard<std::mutex> lck(mtx);
            idx = idx == max ? 0 : idx + 1;
            return idx;
        }

    private:
        std::size_t max;
        srd::size_t idx;
    };
}

#endif
