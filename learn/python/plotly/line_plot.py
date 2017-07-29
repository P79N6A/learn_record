#!/usr/bin/env python
import plotly.offline as pltoff
import plotly.graph_objs as go

def line_plots(name="line_plots.html"):

    dataset = {
        'time': [],
        'rx': [],
        'tx': [],
        'util': []
    }
    with open("./log.txt") as f:
        i = 0
        for line in f:
            items = line.split()
            dataset['time'].append(i)
            dataset['rx'].append(items[0])
            dataset['tx'].append(items[1])
            dataset['util'].append(items[2])
            i += 1

    data_g = []
    tr = go.Scatter(
        x = dataset['time'],
        y = dataset['rx'],
        name = 'rx')
    data_g.append(tr)

    tr = go.Scatter(
        x = dataset['time'],
        y = dataset['tx'],
        name = 'tx')
    data_g.append(tr)

    tr = go.Scatter(
        x = dataset['time'],
        y = dataset['util'],
        name = 'util')
    data_g.append(tr)


    layout = go.Layout(title="Line plots", xaxis={'title':'time'}, yaxis={'title':'value'})
    fig = go.Figure(data=data_g, layout=layout)
    pltoff.plot(fig, filename=name)

if __name__=='__main__':
    line_plots()
