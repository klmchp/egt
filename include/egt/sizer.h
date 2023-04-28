/*
 * Copyright (C) 2018 Microchip Technology Inc.  All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef EGT_SIZER_H
#define EGT_SIZER_H

/**
 * @file
 * @brief Working with sizers.
 */

#include <egt/detail/alignment.h>
#include <egt/detail/meta.h>
#include <egt/frame.h>
#include <memory>
#include <utility>

namespace egt
{
inline namespace v1
{

/**
 * @defgroup sizers Sizing and Positioning
 * Sizing and positioning widgets.
 *
 * These widgets, different from other types of widgets like @ref controls, are
 * used specifically for managing position and size of child widgets as well as
 * themselves.
 *
 * @see @ref layout_intro
 */

/**
 * Positions and sizes widgets by Orientation.
 *
 * BoxSizer will position widgets added to it in a horizontal or vertical
 * Orientation. The BoxSizer can be homogeneous, which means all widgets will be
 * given equal space, or not.  Also, space can be specified that should be
 * between each widget.
 *
 * An added Widget's minimum_size_hint() will be used.
 *
 * @ingroup sizers
 */
class EGT_API BoxSizer : public Frame
{
public:

    /**
     * @param[in] orient Vertical or horizontal Orientation.
     * @param[in] justify Justification of child widgets.
     */
    explicit BoxSizer(Orientation orient = Orientation::horizontal,
                      Justification justify = Justification::middle)
        : m_orient(orient),
          m_justify(justify)
    {
        name("BoxSizer" + std::to_string(m_widgetid));
    }

    /**
     * @param[in] parent The parent Frame.
     * @param[in] orient Vertical or horizontal Orientation.
     * @param[in] justify Justification of child widgets.
     */
    explicit BoxSizer(Frame& parent,
                      Orientation orient = Orientation::horizontal,
                      Justification justify = Justification::middle)
        : BoxSizer(orient, justify)
    {
        parent.add(*this);
    }

    /**
     * @param[in] props list of widget argument and its properties.
     */
    explicit BoxSizer(Serializer::Properties& props)
        : BoxSizer(props, false)
    {
    }

protected:

    explicit BoxSizer(Serializer::Properties& props, bool is_derived);

public:

    /**
     * @warning The layout library, that is used to position widgets, handles
     * coordinates with 16-bits integers, be careful about overflows.
     */
    void layout() override;

    /**
     * Get the justify.
     */
    EGT_NODISCARD Justification justify() const { return m_justify; }

    /**
     * Set the justify.
     */
    void justify(Justification justify)
    {
        if (detail::change_if_diff<>(m_justify, justify))
            layout();
    }

    /**
     * Get the Orientation.
     */
    EGT_NODISCARD Orientation orient() const { return m_orient; }

    /**
     * Set the Orientation.
     */
    void orient(Orientation orient)
    {
        if (detail::change_if_diff<>(m_orient, orient))
            layout();
    }

    void serialize(Serializer& serializer) const override;

protected:

    /// Calculate the super rectangle of all the children
    EGT_NODISCARD Size super_rect() const
    {
        if (orient() == Orientation::flex)
        {
            Rect result = size();
            for (auto& child : children())
                result = Rect::merge(result, child->box());

            return result.size();
        }

        DefaultDim width = 0;
        DefaultDim height = 0;

        if (orient() == Orientation::horizontal)
        {
            for (auto& child : children())
            {
                if (!child->align().is_set(AlignFlag::expand_horizontal))
                {
                    width += child->box().width();
                    height = std::max(child->box().height(), height);
                }
            }
        }
        else
        {
            for (auto& child : children())
            {
                if (!child->align().is_set(AlignFlag::expand_vertical))
                {
                    width = std::max(child->box().width(), width);
                    height += child->box().height();
                }
            }
        }
        width += 2. * moat();
        height += 2. * moat();

        if (align().is_set(AlignFlag::expand_horizontal))
            if (width < box().width())
                width = box().width();

        if (align().is_set(AlignFlag::expand_vertical))
            if (height < box().height())
                height = box().height();

        return {width, height};
    }

    /// @private
    Orientation m_orient{Orientation::horizontal};
    /// @private
    Justification m_justify{Justification::start};

private:

    void deserialize(Serializer::Properties& props);
};

/**
 * HorizontalBoxSizer helper variation of BoxSizer.
 *
 * @ingroup sizers
 */
class EGT_API HorizontalBoxSizer : public BoxSizer
{
public:

    /**
     * @param[in] justify Justification of child widgets.
     */
    explicit HorizontalBoxSizer(Justification justify = Justification::middle)
        : BoxSizer(Orientation::horizontal, justify)
    {
        name("HorizontalBoxSizer" + std::to_string(m_widgetid));
    }

    explicit HorizontalBoxSizer(Serializer::Properties& props)
        : HorizontalBoxSizer(props, false)
    {
    }

protected:

    explicit HorizontalBoxSizer(Serializer::Properties& props, bool is_derived)
        : BoxSizer(props, true)
    {
        if (!is_derived)
            deserialize_leaf(props);
    }

public:

    /**
     * @param[in] parent The parent Frame.
     * @param[in] justify Justification of child widgets.
     */
    explicit HorizontalBoxSizer(Frame& parent, Justification justify = Justification::middle)
        : BoxSizer(parent, Orientation::horizontal, justify)
    {}
};

/**
 * VerticalBoxSizer helper variation of BoxSizer.
 *
 * @ingroup sizers
 */
class EGT_API VerticalBoxSizer : public BoxSizer
{
public:

    /**
     * @param[in] justify Justification of child widgets.
     */
    explicit VerticalBoxSizer(Justification justify = Justification::middle)
        : BoxSizer(Orientation::vertical, justify)
    {
        name("VerticalBoxSizer" + std::to_string(m_widgetid));
    }

    explicit VerticalBoxSizer(Serializer::Properties& props)
        : VerticalBoxSizer(props, false)
    {
    }

protected:

    explicit VerticalBoxSizer(Serializer::Properties& props, bool is_derived)
        : BoxSizer(props, true)
    {
        if (!is_derived)
            deserialize_leaf(props);
    }

public:

    /**
     * @param[in] parent The parent Frame.
     * @param[in] justify Justification of child widgets.
     */
    explicit VerticalBoxSizer(Frame& parent, Justification justify = Justification::middle)
        : BoxSizer(parent, Orientation::vertical, justify)
    {}
};

/**
 * FlexBoxSizer helper variation of BoxSizer.
 *
 * @ingroup sizers
 */
class EGT_API FlexBoxSizer : public BoxSizer
{
public:

    /**
     * @param[in] justify Justification of child widgets.
     */
    explicit FlexBoxSizer(Justification justify = Justification::middle)
        : BoxSizer(Orientation::flex, justify)
    {
        name("FlexBoxSizer" + std::to_string(m_widgetid));
    }

    /**
     * @param[in] parent The parent Frame.
     * @param[in] justify Justification of child widgets.
     */
    explicit FlexBoxSizer(Frame& parent, Justification justify = Justification::middle)
        : BoxSizer(parent, Orientation::flex, justify)
    {}

    explicit FlexBoxSizer(Serializer::Properties& props)
        : FlexBoxSizer(props, false)
    {
    }

protected:

    explicit FlexBoxSizer(Serializer::Properties& props, bool is_derived)
        : BoxSizer(props, true)
    {
        if (!is_derived)
            deserialize_leaf(props);
    }
};

}
}

#endif
