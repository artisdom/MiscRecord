# setwd('C:/Users/lenovo/Documents/convolve')
# system("R CMD SHLIB convolve.c")  #���������ļ�convolve.dll,convolve.o
                                  #windows �õ�convolve.dll

dyn.load("convolve.dll")
conv <- function(a, b){
	.C("convolve",
	as.double(a), as.integer(length(a)),
	as.double(b), as.integer(length(b)),
	ab=double(length(a)+length(b)-1)
	)$ab
}
a=3
b=4
conv(a,b)
