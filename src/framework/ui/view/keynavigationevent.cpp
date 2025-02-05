//=============================================================================
//  MuseScore
//  Music Composition & Notation
//
//  Copyright (C) 2021 MuseScore BVBA and others
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//=============================================================================
#include "keynavigationevent.h"

#include "log.h"

using namespace mu::ui;

KeyNavigationEvent::KeyNavigationEvent(IKeyNavigation::EventPtr event)
    : m_event(event)
{
}

void KeyNavigationEvent::setEvent(IKeyNavigation::EventPtr event)
{
    m_event = event;
}

KeyNavigationEvent::Type KeyNavigationEvent::type() const
{
    IF_ASSERT_FAILED(m_event) {
        return Undefined;
    }
    return static_cast<Type>(m_event->type);
}

void KeyNavigationEvent::setAccepted(bool accepted)
{
    IF_ASSERT_FAILED(m_event) {
        return;
    }
    m_event->accepted = accepted;
}

bool KeyNavigationEvent::accepted() const
{
    IF_ASSERT_FAILED(m_event) {
        return false;
    }
    return m_event->accepted;
}
