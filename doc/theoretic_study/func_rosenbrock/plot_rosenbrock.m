#! /usr/bin/octave -q
#prevent octave from thinking this is a function definition
1; 

#execute in interactive mode to show graph, from octave do: source filename.m
ty= linspace(-20,30,100)';
tx= linspace(-10,10,100)';
[xx,yy]=meshgrid(tx,ty);
tz= 100.*(yy-xx.^2).^2  + (1-xx).^2;
mesh (tx,ty,tz);

print -dpng plot.png
