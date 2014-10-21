#! /usr/bin/octave -q
#prevent octave from thinking this is a function definition
1; 

#execute in interactive mode to show graph, from octave do: source filename.m
ty= linspace(-20,50,100)';
tx= linspace(-8,8,100)';
[xx,yy]=meshgrid(tx,ty);
tz= sqrt( (-2.0-(400.0).*(yy-xx.^2).*xx+(2.0).*xx).^2 + ((200.0).*yy-(200.0).*xx.^2).^2);

100.*(yy-xx.^2).^2  + (1-xx).^2;
mesh (tx,ty,tz);

print -dpng plot-deriv.png
