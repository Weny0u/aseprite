// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "app/cmd/add_frame_tag.h"

#include "doc/frame_tag.h"
#include "doc/frame_tag_io.h"
#include "doc/sprite.h"

namespace app {
namespace cmd {

using namespace doc;

AddFrameTag::AddFrameTag(Sprite* sprite, FrameTag* frameTag)
  : WithSprite(sprite)
  , WithFrameTag(frameTag)
{
}

void AddFrameTag::onExecute()
{
  Sprite* sprite = this->sprite();
  FrameTag* frameTag = this->frameTag();

  sprite->frameTags().add(frameTag);
}

void AddFrameTag::onUndo()
{
  Sprite* sprite = this->sprite();
  FrameTag* frameTag = this->frameTag();
  write_frame_tag(m_stream, frameTag);

  sprite->frameTags().remove(frameTag);
  delete frameTag;
}

void AddFrameTag::onRedo()
{
  Sprite* sprite = this->sprite();
  FrameTag* frameTag = read_frame_tag(m_stream);
  sprite->frameTags().add(frameTag);

  m_stream.str(std::string());
  m_stream.clear();
}

size_t AddFrameTag::onMemSize() const
{
  return sizeof(*this)
    + (size_t)const_cast<std::stringstream*>(&m_stream)->tellp();
}

} // namespace cmd
} // namespace app
