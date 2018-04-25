#ifndef LUPULUS_BUFFER_H
#define LUPULUS_BUFFER_H

#include <cstddef>
#include <memory>

namespace lpl
{
    template<class T>
    class Buffer
    {
    public:
        Buffer(std::size_t channels);

        ~Buffer();
        Buffer(Buffer<T> &&buf) noexcept;
        Buffer<T> &operator=(Buffer<T> &&buf) noexcept;

        void push(const T &val);
        decltype(auto) pop();

    private:
        class Impl;
        std::unique_ptr<Impl> pimpl;
    };
}

#endif
