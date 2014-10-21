#! /usr/bin/Rscript 

# png("Rplots.png") # uncomment to save to png instead of pdf

args <- commandArgs(TRUE); # format is cmd file

s <- read.table(args[1],sep=";",header=TRUE);

f <- function(x,y) { 100*(y-x^2)^2 + (1-x)^2 }

z <- c();
r <- c();

for(i in 1:nrow(s)) z[i] <- f(s$p1[i],s$p2[i]);
for(i in 1:(length(z)-1)) r[i] <- z[i]-z[i-1];

plot(z,type="l");
