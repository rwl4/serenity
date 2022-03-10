/*
 * Copyright (c) 2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/NonnullOwnPtr.h>
#include <LibWeb/Layout/Box.h>
#include <LibWeb/Layout/LineBox.h>
#include <LibWeb/Layout/TextNode.h>
#include <LibWeb/Painting/StackingContext.h>

namespace Web::Painting {

class Paintable : public RefCounted<Paintable> {
    AK_MAKE_NONMOVABLE(Paintable);
    AK_MAKE_NONCOPYABLE(Paintable);

public:
    virtual ~Paintable() = default;

    virtual void paint(PaintContext&, PaintPhase) const { }
    virtual void before_children_paint(PaintContext&, PaintPhase) const { }
    virtual void after_children_paint(PaintContext&, PaintPhase) const { }

    virtual bool wants_mouse_events() const { return false; }
    virtual void handle_mousedown(Badge<EventHandler>, const Gfx::IntPoint&, unsigned button, unsigned modifiers);
    virtual void handle_mouseup(Badge<EventHandler>, const Gfx::IntPoint&, unsigned button, unsigned modifiers);
    virtual void handle_mousemove(Badge<EventHandler>, const Gfx::IntPoint&, unsigned buttons, unsigned modifiers);
    virtual bool handle_mousewheel(Badge<EventHandler>, const Gfx::IntPoint&, unsigned buttons, unsigned modifiers, int wheel_delta_x, int wheel_delta_y);

    Layout::Node const& layout_node() const { return m_layout_node; }
    Layout::Node& layout_node() { return const_cast<Layout::Node&>(m_layout_node); }

    auto const& computed_values() const { return m_layout_node.computed_values(); }

    HTML::BrowsingContext const& browsing_context() const { return m_layout_node.browsing_context(); }
    HTML::BrowsingContext& browsing_context() { return layout_node().browsing_context(); }

    void set_needs_display() const { const_cast<Layout::Node&>(m_layout_node).set_needs_display(); }

protected:
    explicit Paintable(Layout::Node const& layout_node)
        : m_layout_node(layout_node)
    {
    }

private:
    Layout::Node const& m_layout_node;
};

}
