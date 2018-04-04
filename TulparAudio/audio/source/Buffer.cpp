/*
* Copyright (C) 2018 by Godlike
* This code is licensed under the MIT license (MIT)
* (http://opensource.org/licenses/MIT)
*/

#include <tulpar/audio/Buffer.hpp>

#include <tulpar/internal/BufferCollection.hpp>

namespace tulpar
{
namespace audio
{

Buffer::Buffer()
    : m_parent()
    , m_handle(0)
{

}

bool Buffer::IsValid() const
{
    return !m_parent.expired() && m_parent.lock()->IsValid(m_handle);
}

bool Buffer::BindData(mule::asset::Handler asset)
{
    assert(IsValid());

    auto parent = m_parent.lock();

    parent->SetBufferName(m_handle, asset.GetName());

    return parent->SetBufferData(m_handle, asset.GetContent());
}

std::string Buffer::GetDataName() const
{
    assert(IsValid());

    return m_parent.lock()->GetBufferName(m_handle);
}

uint8_t Buffer::GetChannelCount() const
{
    assert(IsValid());

    return m_parent.lock()->GetBufferChannelCount(m_handle);
}

uint32_t Buffer::GetFrequencyHz() const
{
    assert(IsValid());

    return m_parent.lock()->GetBufferFrequencyHz(m_handle);
}

uint32_t Buffer::GetSampleCount() const
{
    assert(IsValid());

    return m_parent.lock()->GetBufferSampleCount(m_handle);
}

std::chrono::seconds Buffer::GetDuration() const
{
    assert(IsValid());

    return m_parent.lock()->GetBufferDuration(m_handle);
}

bool Buffer::Reset()
{
    assert(IsValid());

    return m_parent.lock()->ResetBuffer(m_handle);
}

Buffer::Buffer(Handle handle, std::weak_ptr<internal::BufferCollection> parent)
    : m_parent(parent)
    , m_handle(handle)
{

}

}
}
