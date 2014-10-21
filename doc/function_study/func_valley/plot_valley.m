#! /usr/bin/octave -q
#prevent octave from thinking this is a function definition
1; 

#execute in interactive mode to show graph, from octave do: source filename.m
tx=ty= linspace(-20,20,100)';
[xx,yy]=meshgrid(tx,ty);
tz= (xx.^4).*cos(xx) + yy.^4;
mesh (tx,ty,tz);

print -dpng plot.png
