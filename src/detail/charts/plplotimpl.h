/*
 * Copyright (C) 2018 Microchip Technology Inc.  All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef EGT_DETAIL_PLPLOTIMPL_H
#define EGT_DETAIL_PLPLOTIMPL_H

#include "egt/chart.h"
#include "egt/painter.h"
#include <memory>
#include <plstream.h>
#include <string>
#include <vector>

namespace egt
{
inline namespace v1
{
namespace detail
{

class PlPlotImpl
{
public:

    PlPlotImpl();

    void title(const std::string& title);

    void label(const std::string& xlabel, const std::string& ylabel, const std::string& title);

    virtual void draw(Painter& painter, const Rect& rect) = 0;

    void data(const ChartBase::DataArray& data);

    size_t data_size() const;

    void add_data(const ChartBase::DataArray& data);

    void data(const ChartBase::StringDataArray& data);

    void add_data(const ChartBase::StringDataArray& data);

    void remove_data(uint32_t count);

    void clear();

    void grid_style(ChartBase::GridFlag flag);

    void grid_width(int val);

    void line_width(int val);

    void line_style(int val);

    void point_type(int ptype);

    virtual void resize(const Size& size);

    void bank(float bank);

    virtual void invoke_damage() = 0;

    virtual ~PlPlotImpl();

protected:

    inline PLINT axis() const
    {
        return static_cast<PLINT>(m_grid);
    }

    ChartBase::GridFlag m_grid{ChartBase::GridFlag::box_ticks};

    std::unique_ptr<plstream> m_plstream;
    bool m_initalize{false};
    std::string m_xlabel;
    std::string m_ylabel;
    std::string m_title;

    /**
     * plenv
     * m_xmin and m_xmax cannot be same
     * m_ymin and m_ymax cannot be same
     */
    PLFLT m_xmin{0};
    PLFLT m_xmax{0};
    PLFLT m_ymin{0};
    PLFLT m_ymax{0};

    PLINT m_pattern{0};
    PLINT m_pointtype{17}; //code 17 represents to dot.

    PLINT m_grid_width{1};
    PLINT m_line_width{2};

    std::vector<PLFLT> m_xdata;
    std::vector<PLFLT> m_ydata;
    std::vector<std::string> m_sdata;

    void plplot_color(Color& color);

    void plplot_font(const Font& font);

    void plplot_verify_viewport();

    float m_bank{0};
};

class PlPlotLineChart: public PlPlotImpl
{
public:
    explicit PlPlotLineChart(LineChart& interface);

    virtual void draw(Painter& painter, const Rect& rect) override;

    virtual void invoke_damage() override
    {
        m_interface.damage();
    }

    virtual ~PlPlotLineChart();

protected:
    LineChart& m_interface;
};

class PlPlotPointChart: public PlPlotImpl
{
public:
    explicit PlPlotPointChart(PointChart& interface);

    virtual void draw(Painter& painter, const Rect& rect) override;

    virtual void invoke_damage() override
    {
        m_interface.damage();
    }

    virtual ~PlPlotPointChart();

protected:
    PointChart& m_interface;
};

class PlPlotBarChart: public PlPlotImpl
{
public:
    explicit PlPlotBarChart(BarChart& interface);

    virtual void draw(Painter& painter, const Rect& rect) override;

    virtual void invoke_damage() override
    {
        m_interface.damage();
    }

    virtual ~PlPlotBarChart();

protected:
    void plfbox(PLFLT x0, PLFLT y0);

protected:
    BarChart& m_interface;
};

class PlPlotHBarChart: public PlPlotImpl
{
public:
    explicit PlPlotHBarChart(HorizontalBarChart& interface);

    virtual void draw(Painter& painter, const Rect& rect) override;

    virtual void invoke_damage() override
    {
        m_interface.damage();
    }

    virtual ~PlPlotHBarChart();

protected:
    void plfHbox(PLFLT x0, PLFLT y0);

protected:
    HorizontalBarChart& m_interface;
};

class PlPlotPieChart: public PlPlotImpl
{
public:

    explicit PlPlotPieChart(PieChart& interface);

    virtual void draw(Painter& painter, const Rect& rect) override;

    virtual void invoke_damage() override
    {
        m_interface.damage();
    }

    virtual ~PlPlotPieChart();

protected:
    PieChart& m_interface;
};

} // end of namespace detail

} // end of namespace v1

} // end of namespace egt

#endif
