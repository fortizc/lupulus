#include "index.h"
#include <lupulus/buffer.h>
#include <queue>
#include <vector>
#include <mutex>

namespace lpl
{
    template<class T>
    class Buffer<T>::Impl
    {
    public:
        Impl(std::size_t channels);
        void push(const T &val);
        decltype(auto) pop();

    private:

        Index ins_idx;
        Index del_idx;
        std::vector<std::queue<T> >channels;
        std::vector<std::mutex> ch_mtx;
    };
}


template<class T>
lpl::Buffer<T>::Impl::Impl(std::size_t channels)
    : ins_idx(channels), del_idx(channels), ch_mtx(channels)
{
    for (auto i = 0; i < channels; ++i)
        this->channels[i].push_back(std::queue<T>());

    this->channels.shrink_to_fit();
}


template<class T>
void lpl::Buffer<T>::Impl::push(const T &val)
{
    auto idx = ins_idx.get();
    std::lock_guard<std::mutex> lck(ch_mtx[idx]);
    channels[idx].push(val);
}


template<class T>
decltype(auto) lpl::Buffer<T>::Impl::pop()
{

    auto idx = del_idx.get();
    auto &ch = channels[idx];

    while (ch.empty())
    {
        idx = del_idx.get();
        ch = channels[idx];
    }

    decltype(auto) data = ch.front();

    std::lock_guard<std::mutex> lck(ch_mtx[idx]);
    ch.pop();

    return data;
}

// Public API

template<class T>
lpl::Buffer<T>::~Buffer() = default;
template<class T>
lpl::Buffer<T>::Buffer(lpl::Buffer<T> &&buff) noexcept = default;
template<class T>
lpl::Buffer<T> &lpl::Buffer<T>::operator=(lpl::Buffer<T> &&buff) noexcept = default;

template<class T>
lpl::Buffer<T>::Buffer(std::size_t channels)
    : pimpl(std::make_unique<Impl>(channels))
{
}

template<class T>
void lpl::Buffer<T>::push(const T &val)
{
    pimpl->push(val);
}


template<class T>
decltype(auto) lpl::Buffer<T>::pop()
{
    return pimpl->pop();
}
