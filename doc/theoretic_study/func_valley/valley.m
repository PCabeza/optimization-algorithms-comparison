#! /usr/bin/octave -q
#prevent octave from thinking this is a function definition
1; 

#symbolic derivation
symbols;
x=sym("x");
y=sym("y");
z=x^4*Cos(x)+y^4; # actual function
dz_dx=differentiate(z,x);
dz_dy=differentiate(z,y);

dz_dxdx=differentiate(dz_dx,x);
dz_dxdy=differentiate(dz_dx,y);
dz_dydy=differentiate(dz_dy,y);


printf("gradient = (%s , %s)\n\n",to_char(dz_dx),to_char(dz_dy));

printf("hessian = \n%s\t%s\n%s\t%s\n\n",
       to_char(dz_dxdx),to_char(dz_dxdy),
       to_char(dz_dxdy),to_char(dz_dydy));


