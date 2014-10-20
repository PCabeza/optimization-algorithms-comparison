#! /usr/bin/octave -q
#prevent octave from thinking this is a function definition
1; 

#execute in interactive mode to show graph, from octave do: source filename.m
tx=ty= linspace(-5,5,60)';
[xx,yy]=meshgrid(tx,ty);
tz= (yy.^2)./10 + cos((xx.^2 + yy.^2)./2)./4 -1./(xx.^2 + yy.^2 + 1);
mesh (tx,ty,tz);

print -dpng plot.png
