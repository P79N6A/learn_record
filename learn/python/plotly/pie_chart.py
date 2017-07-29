#!/usr/bin/env python
import plotly.offline as pltoff
import plotly.graph_objs as go

def pie_charts(name='pie_chart.html'):
    dataset = {
        'labels':['Windows', 'Linux', 'MacOS'],
        'values':[280, 10, 30]}
    data_g = []
    tr_p = go.Pie(
    labels = dataset['labels'],
    values = dataset['values']

    )
    data_g.append(tr_p)
    layout = go.Layout(title="pie charts")
    fig = go.Figure(data=data_g, layout=layout)
    pltoff.plot(fig, filename=name)

if __name__=='__main__':
    pie_charts()
