/*
 * Copyright (C) 2018 Microchip Technology Inc.  All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "detail/charts/plplotimpl.h"
#include "egt/chart.h"

namespace egt
{
inline namespace v1
{

LineChart::LineChart(const Rect& rect)
    : ChartBase(rect),
      m_impl(std::make_unique<detail::PlPlotLineChart>(*this))
{
    name("LineChart" + std::to_string(m_widgetid));
}

void LineChart::draw(Painter& painter, const Rect& rect)
{
    return m_impl->draw(painter, rect);
}

void LineChart::data(const DataArray& data)
{
    m_impl->data(data);
}

size_t LineChart::data_size() const
{
    return m_impl->data_size();
}

void LineChart::add_data(const DataArray& data)
{
    m_impl->add_data(data);
}

void LineChart::remove_data(uint32_t count)
{
    m_impl->remove_data(count);
}

void LineChart::clear()
{
    m_impl->clear();
}

void LineChart::grid_style(GridFlag flag)
{
    m_impl->grid_style(flag);
}

void LineChart::grid_width(const int val)
{
    m_impl->grid_width(val);
}

void LineChart::line_width(const int val)
{
    m_impl->line_width(val);
}

void LineChart::line_style(LinePattern pattern)
{
    m_impl->line_style(static_cast<int>(pattern));
}

void LineChart::label(const std::string& xlabel, const std::string& ylabel, const std::string& title)
{
    m_impl->label(xlabel, ylabel, title);
}

void LineChart::resize(const Size& size)
{
    if (size != this->size())
    {
        m_impl->resize(size);
        Widget::resize(size);
    }
}

void LineChart::bank(float bank)
{
    m_impl->bank(bank);
}

LineChart::~LineChart() = default;

PointChart::PointChart(const Rect& rect)
    : ChartBase(rect),
      m_impl(std::make_unique<detail::PlPlotPointChart>(*this))
{
    name("PointChart" + std::to_string(m_widgetid));
}

void PointChart::draw(Painter& painter, const Rect& rect)
{
    m_impl->draw(painter, rect);
}

void PointChart::data(const DataArray& data)
{
    m_impl->data(data);
}

size_t PointChart::data_size() const
{
    return m_impl->data_size();
}

void PointChart::add_data(const DataArray& data)
{
    m_impl->add_data(data);
}

void PointChart::remove_data(uint32_t count)
{
    m_impl->remove_data(count);
}

void PointChart::clear()
{
    m_impl->clear();
}

void PointChart::point_type(const PointType ptype)
{
    m_impl->point_type(static_cast<int>(ptype));
}

void PointChart::label(const std::string& xlabel, const std::string& ylabel, const std::string& title)
{
    m_impl->label(xlabel, ylabel, title);
}

void PointChart::resize(const Size& size)
{
    if (size != this->size())
    {
        m_impl->resize(size);
        Widget::resize(size);
    }
}

void PointChart::bank(float bank)
{
    m_impl->bank(bank);
}

void PointChart::grid_style(GridFlag flag)
{
    m_impl->grid_style(flag);
}

void PointChart::grid_width(const int val)
{
    m_impl->grid_width(val);
}

PointChart::~PointChart() = default;

BarChart::BarChart(const Rect& rect)
    : ChartBase(rect),
      m_impl(std::make_unique<detail::PlPlotBarChart>(*this))
{
    name("BarChart" + std::to_string(m_widgetid));
}

BarChart::BarChart(const Rect& rect, std::unique_ptr<detail::PlPlotImpl>&& impl)
    : ChartBase(rect),
      m_impl(std::move(impl))
{
    name("BarChart" + std::to_string(m_widgetid));
}

void BarChart::draw(Painter& painter, const Rect& rect)
{
    m_impl->draw(painter, rect);
}

void BarChart::bar_style(BarPattern pattern)
{
    m_impl->line_style(static_cast<int>(pattern));
}

void BarChart::label(const std::string& xlabel, const std::string& ylabel, const std::string& title)
{
    m_impl->label(xlabel, ylabel, title);
}

void BarChart::data(const DataArray& data)
{
    m_impl->data(data);
}

size_t BarChart::data_size() const
{
    return m_impl->data_size();
}

void BarChart::add_data(const DataArray& data)
{
    m_impl->add_data(data);
}

void BarChart::data(const StringDataArray& data)
{
    m_impl->data(data);
}

void BarChart::add_data(const StringDataArray& data)
{
    m_impl->add_data(data);
}

void BarChart::remove_data(uint32_t count)
{
    m_impl->remove_data(count);
}

void BarChart::clear()
{
    m_impl->clear();
}

void BarChart::grid_style(GridFlag flag)
{
    m_impl->grid_style(flag);
}

void BarChart::grid_width(const int val)
{
    m_impl->grid_width(val);
}

void BarChart::resize(const Size& size)
{
    if (size != this->size())
    {
        m_impl->resize(size);
        Widget::resize(size);
    }
}

void BarChart::bank(float bank)
{
    m_impl->bank(bank);
}

BarChart::~BarChart() = default;

HorizontalBarChart::HorizontalBarChart(const Rect& rect)
    : BarChart(rect, std::make_unique<detail::PlPlotHBarChart>(*this))
{
    name("HorizontalBarChart" + std::to_string(m_widgetid));
}

HorizontalBarChart::~HorizontalBarChart() = default;

PieChart::PieChart(const Rect& rect)
    : Widget(rect),
      m_impl(std::make_unique<detail::PlPlotPieChart>(*this))
{
    name("PieChart" + std::to_string(m_widgetid));
}

void PieChart::draw(Painter& painter, const Rect& rect)
{
    m_impl->draw(painter, rect);
}

void PieChart::title(const std::string& title)
{
    return m_impl->title(title);
}

void PieChart::data(const StringDataArray& data)
{
    m_impl->data(data);
}

size_t PieChart::data_size() const
{
    return m_impl->data_size();
}

void PieChart::add_data(const StringDataArray& data)
{
    m_impl->add_data(data);
}

void PieChart::remove_data(uint32_t count)
{
    m_impl->remove_data(count);
}

void PieChart::clear()
{
    m_impl->clear();
}

void PieChart::resize(const Size& size)
{
    if (size != this->size())
    {
        m_impl->resize(size);
        Widget::resize(size);
    }
}

PieChart::~PieChart() = default;

}
}
