#! /usr/bin/Rscript 

# png("Rplots.png") # uncomment to save to png instead of pdf

args <- commandArgs(TRUE); # format is file RX RY theta phi ; R? are vectors

if(length(args) < 5){
    phi <- 18
} else { phi <- args[5];}

if (length(args) < 4) {
    theta <- 18;
} else { theta <- args[4];}

if (length(args) < 3){
    RY <- c(-10,30);
} else { RY <- eval(parse(text=args[3]));}

if (length(args) < 2){
    RX <- c(-9,9);
} else { RX <- eval(parse(text=args[2]));}

#prepare and draw the function
x <- seq(RX[1],RX[2],length=50) # default should be -9,9
y <- seq(RY[1],RY[2],length=50) #default -10,30
f <- function(x,y) { 100*(y-x^2)^2 + (1-x)^2 }
z <- outer(x,y,f)

persp(x,y,z,theta=theta,phi=phi,expand=0.5,col="lightblue",
      ltheta=120,shade=0.75,ticktype="detailed")->res;



# process points file and print path

if (length(args)>=1){
    s <- read.table(args[1],sep=";",header=TRUE);
} else {
    p1 <- c(-5,1,3,6,5,-2)
    p2 <- c(-5,2,4,6,15,25)
    s <- data.frame(p1,p2);
}


fcols <- colorRampPalette(c("red","yellow")); # creates a function
cols <- fcols(nrow(s)); # actual color gradient with nrow() colors


cl <- function(point, range){
    if(range[1]<=point && range[2]>=point){
        ret <- point;
    } else if(abs(point-range[1])<abs(point-range[2])){
        ret <- range[1];
    } else ret <- range[2];
    ret;
}
printsegment <- function(pO,pD,f,res,colO,colD) {
    fcols <- colorRampPalette(c(colO,colD)); # creates a function
    cols <- fcols(100); # actual color gradient with nrow() colors

    cx <- seq(pO[1],pD[1],length=100);
    cy <- seq(pO[2],pD[2],length=100);

    for (i in 1:99){
        if( RX[1]<= cx[i] && RX[2] >= cx[i] &&
            RY[1]<= cy[i] && RY[2] >= cy[i]){ # first point in range
            px <- c(cx[i],cl(cx[i+1],RX)); py <- c(cy[i],cl(cy[i+1],RY));
        } else{ # first point not in range
            if( RX[1]<= cx[i+1] && RX[2] >= cx[i+1] &&
               RY[1]<= cy[i+1] && RY[2] >= cy[i+1]){ # second point in range
                px <- c(cl(cx[i],RX),cx[i+1]); py <- c(cl(cy[i],RY),cy[i+1]);
            } else next;
        }

        lines(trans3d(px,py,f(px,py),res),
              col=cols[i],lwd=1.5);

    }
    if(RX[1]<= pO[1] && RX[2] >= pO[1] &&
       RY[1]<= pO[2] && RY[2] >= pO[2])
        points(trans3d(pO[1],pO[2],f(pO[1],pO[2]),res),
               col=colO,
               pch=16);

    if(RX[1]<= pD[1] && RX[2] >= pD[1] &&
       RY[1]<= pD[2] && RY[2] >= pD[2])
        points(trans3d(pD[1],pD[2],f(pD[1],pD[2]),res),
               col=colO,
               pch=16);
    
}

for(i in 1:(nrow(s)-1)){
    pointO <- c(s$p1[i],s$p2[i]);
    pointD <- c(s$p1[i+1],s$p2[i+1]);
    printsegment(pointO,pointD,f,res,cols[i],cols[i+1]);
}


if(RX[1]<= s$p1[1] && RX[2] >= s$p1[1] &&
   RY[1]<= s$p2[1] && RY[2] >= s$p2[1])
    points(trans3d(s$p1[1],s$p2[1],f(s$p1[1],s$p2[1]),res),
           col="black",
           pch=16);

N <- nrow(s)
if(RX[1]<= s$p1[N] && RX[2] >= s$p1[N] &&
   RY[1]<= s$p2[N] && RY[2] >= s$p2[N])
    points(trans3d(s$p1[N],s$p2[N],f(s$p1[N],s$p2[N]),res),
           col="white",
           pch=16);

## if(RX[1]<= pD[1] && RX[2] >= pD[1] &&
##    RY[1]<= pD[2] && RY[2] >= pD[2])
##     points(trans3d(pD[1],pD[2],f(pD[1],pD[2]),res),
##            col=colO,
##            pch=16);


## xE <- c(-1,1); xy <- expand.grid(c(1), c(1))
## points(trans3d(xy[,1], xy[,2], 0, pmat = res),
##        col = 2, #color
##        pch = 16); #width?

## p1<-c(-5,-5); p2<-c(1,1);

## cx=seq(p1[1],p2[1],length=100);
## cy=seq(p1[2],p2[2],length=100);

## lines(trans3d(cx,cy,f(cx,cy),res),
##       col="pink",
##       lwd=1.5);
