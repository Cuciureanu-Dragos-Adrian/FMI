#Cuciureanu Dragos-Adrian

# exercitiul 3 

#subpunctul a
v <- rnorm(100, mean = 1, sd = 0.3)
print(v)

mean_v = mean(v)
print(mean_v)


median_v = median(v)
print(median_v)


getmode <- function(v)
{
  uniqv <- unique(v)
  uniqv[which.max(tabulate(match(v, uniqv)))]
}

mode_v = getmode(v)
print(mode_v)

#subpunctul b
# Give the chart file a name.
png(file = "histogram.png")

# Create the histogram.
hist(v, xlab = "Value", col = "yellow", border = "black")

# Save the file.
dev.off()


#exercitiul 4
generareM = function(i, j)
{
  1 / sqrt( (i+2) * (j+2) )
}

generareN = function(i, j)
{
  (i+1) / (j+1)
}

i = 1:15
j = 1:15

matriceaM = outer(i, j, generareM)
matriceaN = outer(i, j, generareN)

print(matriceaM)
print(matriceaN)

matriceaMN = matriceaM %*% matriceaN

print(matriceaMN)

detMN = det(matriceaMN)

if(detMN == 0) {
  print("matricea este neinversabila")
} else {
  print("matricea este inversabila")
}
