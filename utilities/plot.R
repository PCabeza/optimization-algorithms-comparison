#! /usr/bin/Rscript 

## Plot the diferent surfaces (given by the func filename) and
## represent over it some points (given by data). All these options
## control how it is visualized.

library('getopt');

spec <- matrix(c(
    'data',  'd' , 1 , "character", #dataset of points
    'xrange','x' , 1 , "character", # range of x var
    'yrange','y' , 1 , "character", # range of y var
    'theta', 't' , 1 , "double", # the theta of perspective
    'phi',   'p' , 1 , "double", # the phi of perspective
    'png',   'n' , 2 , "character", # whether to print to png
    'line',  'l' , 0 , "logical", # wheter path should be stright or not
    'func', 'f' , 1 , "character", # file where to get function descr
    'interpolation' ,'i',1,"integer", # number of points to interpolate path
    'expansion', 'e' ,1 , "double", # the expansion factor
    'areapoints' , 'a' ,1 , "integer", # the number of points for perspective
    'border', 'b' , 2 , "character", # whether the surface has border or not
    'psize', 's' , 1 , "double" # the size of the points
    ) ,byrow=TRUE,ncol=4);

opt <- getopt(spec);
    

if(is.null(opt$phi)) opt$phi <- 18;
if(is.null(opt$theta)) opt$theta <- 18;
if(is.null(opt$yrange)) opt$yrange <- "c(-10,10)";
if(is.null(opt$xrange)) opt$xrange <- "c(-10,10)";
if(is.null(opt$interpolation)) opt$interpolation <- 100;
if(!is.null(opt$line)) opt$interpolation <- 2;
if(is.null(opt$expansion)) opt$expansion <- 0.5;
if(is.null(opt$areapoints)) opt$areapoints <- 50;
if(is.null(opt$psize)) opt$psize <- 1;


if(is.null(opt$border)){
    opt$border <- "#2C90B2";
} else if(opt$border==TRUE){
    opt$border <- NA;
} else if(opt$border=="NULL") opt$border <- NULL;

            
RX <- eval(parse(text=opt$xrange));
RY <- eval(parse(text=opt$yrange));

if(!is.null(opt$png)){ png(filename="plot.png",
                           width=1200,height=1200,
                           bg="transparent");}

if(is.null(opt$func)){ f <- function(x,y) { 100*(y-x^2)^2 + (1-x)^2 }
}else{
    parsedf <- parse(text=readChar(opt$func,file.info(opt$func)$size));
    f <- function(x,y) { eval(parsedf); }
}


#prepare and draw the function
x <- seq(RX[1],RX[2],length=opt$areapoints) # default should be -9,9
y <- seq(RY[1],RY[2],length=opt$areapoints) #default -10,30
z <- outer(x,y,f)

persp(x,y,z,theta=opt$theta,phi=opt$phi,expand=opt$expansion,col="lightblue",
      ltheta=120,shade=0.75,ticktype="detailed",border=opt$border)->res;



# process points file and print path if any
if(is.null(opt$data)) q(status=1);
s <- read.table(opt$data,sep=";",header=TRUE);


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
    cols <- fcols(opt$interpolation); # color gradient

    cx <- seq(pO[1],pD[1],length=opt$interpolation);
    cy <- seq(pO[2],pD[2],length=opt$interpolation);

    for (i in 1:(length(cx)-1)){
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
               pch=16,cex=opt$psize);

    if(RX[1]<= pD[1] && RX[2] >= pD[1] &&
       RY[1]<= pD[2] && RY[2] >= pD[2])
        points(trans3d(pD[1],pD[2],f(pD[1],pD[2]),res),
               col=colO,
               pch=16,
               cex=opt$psize);
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
           pch=16,
           cex=opt$psize);

N <- nrow(s)
if(RX[1]<= s$p1[N] && RX[2] >= s$p1[N] &&
   RY[1]<= s$p2[N] && RY[2] >= s$p2[N])
    points(trans3d(s$p1[N],s$p2[N],f(s$p1[N],s$p2[N]),res),
           col="white",
           pch=16,
           cex=opt$psize);
