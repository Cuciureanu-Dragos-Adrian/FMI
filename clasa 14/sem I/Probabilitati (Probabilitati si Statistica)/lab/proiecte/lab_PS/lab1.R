# Problema 8


zile = c(106, 123, 123, 111, 125, 113, 130, 113, 114, 100, 120, 130, 118, 114, 127, 112, 121, 114, 120, 119, 127, 114, 108, 127, 131, 157, 102, 133)
medieZile = c(0, 0, 0, 0, 0, 0, 0)
numeZile = c("Luni", "Marti", "Miercuri", "Joi", "Vineri", "Sambata", "Duminica")


for(i in 1 : length(zile))
{
  ziSaptamana = i %% 7
  nrLuna = (i - 1) %/% 7 + 1
  
  if(ziSaptamana == 0)
  {
    ziSaptamana = 7
  }
  
  medieZile[ziSaptamana] = medieZile[ziSaptamana] + zile[i]
  
  if(zile[i] > 120)
  {
    cat("Am vorbit mai mult de 120 de minute in saptamana", nrLuna, numeZile[ziSaptamana], "\n", sep = " ")
  }
}

nrLuni = (length(zile) - 1) %/% 7 + 1
nrZiMin = 1
nrZiMax = 1

for(i in 1 : 7)
{
  if(medieZile[nrZiMax] < medieZile[i])
  {
    nrZiMax = i
  }
  
  if(medieZile[nrZiMin] > medieZile[i])
  {
    nrZiMin = i
  }
}

cat("S-a vorbit cel mai mult in zilele: ")
for(i in 1 : 7)
{
  if(medieZile[nrZiMax] == medieZile[i])
  {
    cat(numeZile[i])
  }
}

cat("S-a vorbit cel mai putin in zilele: ")
for(i in 1 : 7)
{
  if(medieZile[nrZiMin] == medieZile[i])
  {
    cat(numeZile[i])
  }
}

cat(medieZile)




# Problema 9


# Subpunctul a

print(mtcars)
data(mtcars)

automaticTransmissionCars = (mtcars[which(mtcars$am == 0), ])[, 6]
manualTransmissionCars = (mtcars[which(mtcars$am == 1), ])[, 6]

meanAutomaticTransmissionCars = mean(automaticTransmissionCars)
meanManualTransmissionCars = mean(manualTransmissionCars)

cat("Greutatea medie a masinilor cu transmisie automata este:", meanAutomaticTransmissionCars, "\n", sep = " ")
cat("Greutatea medie a masinilor cu transmisie manual este:", meanManualTransmissionCars, "\n", sep = " ")


# Subpunctul b

cars4cylinders = (mtcars[which(mtcars$cyl == 4), ])[, 6]
cars6cylinders = (mtcars[which(mtcars$cyl == 6), ])[, 6]
cars8cylinders = (mtcars[which(mtcars$cyl == 8), ])[, 6]

meanCars4cylinders = mean(cars4cylinders)
meanCars6cylinders = mean(cars6cylinders)
meanCars8cylinders = mean(cars8cylinders)

cat("Greutatea medie a masinilor cu 4 cilindrii este:", meanCars4cylinders, "\n", sep = " ")
cat("Greutatea medie a masinilor cu 6 cilindrii este:", meanCars6cylinders, "\n", sep = " ")
cat("Greutatea medie a masinilor cu 8 cilindrii este:", meanCars8cylinders, "\n", sep = " ")


# Subpunctul c

carsA4C = (mtcars[which(mtcars$am == 0 & mtcars$cyl == 4), ])[, 1]
carsA6C = (mtcars[which(mtcars$am == 0 & mtcars$cyl == 6), ])[, 1]
carsA8C = (mtcars[which(mtcars$am == 0 & mtcars$cyl == 8), ])[, 1]
carsM4C = (mtcars[which(mtcars$am == 1 & mtcars$cyl == 4), ])[, 1]
carsM6C = (mtcars[which(mtcars$am == 1 & mtcars$cyl == 6), ])[, 1]
carsM8C = (mtcars[which(mtcars$am == 1 & mtcars$cyl == 8), ])[, 1]

meanCarsA4C = mean(carsA4C)
meanCarsA6C = mean(carsA6C)
meanCarsA8C = mean(carsA8C)
meanCarsM4C = mean(carsM4C)
meanCarsM6C = mean(carsM6C)
meanCarsM8C = mean(carsM8C)

cat("Consumul mediu al masinilor automate cu 4 cilindrii este:", meanCarsA4C, "\n", sep = " ")
cat("Consumul mediu al masinilor automate cu 6 cilindrii este:", meanCarsA6C, "\n", sep = " ")
cat("Consumul mediu al masinilor automate cu 8 cilindrii este:", meanCarsA8C, "\n", sep = " ")
cat("Consumul mediu al masinilor manuale cu 4 cilindrii este:", meanCarsM4C, "\n", sep = " ")
cat("Consumul mediu al masinilor manuale cu 6 cilindrii este:", meanCarsM6C, "\n", sep = " ")
cat("Consumul mediu al masinilor manuale cu 8 cilindrii este:", meanCarsM8C, "\n", sep = " ")




# Problema 10


generareM = function(i, j)
{
  return (1 / (sqrt(abs(i - j) + 1)))
}

generareN = function(i, j)
{
  return (i / (j ^ 2))
}

i = 1:10
j = 1:10

matriceaM = outer(i, j, generareM)
matriceaN = outer(i, j, generareN)

print(matriceaM)
print(matricean)

colnames(matriceaM) = i
rownames(matriceaM) = j
colnames(matriceaN) = i
rownames(matriceaN) = j



# Create data for the graph.
v <-  c(9,13,21,8,36,22,12,41,31,33,19)

# Give the chart file a name.
png(file = "histogram.png")

# Create the histogram.
hist(v,xlab = "Weight",col = "yellow",border = "blue")

# Save the file.
dev.off()



# Create data for the graph.
v <- c(9,13,21,8,36,22,12,41,31,33,19)

# Give the chart file a name.
png(file = "histogram.png")

# Create the histogram.
hist(v,xlab = "Weight",col = "green",border = "red", xlim = c(0,40), ylim = c(0,5),
     breaks = 5)

# Save the file.
dev.off()







#matrice
# Elements are arranged sequentially by row.
M <- matrix(c(3:14), nrow = 4, byrow = TRUE)
print(M)

for (i in 1:4)
{
  sumaLinie = sum (M[i, ])
  print(sumaLinie)
}

for (j in 1:3)
{
  sumaColoana = sum (M[, j])
  print(sumaColoana)
}

colSums(M)
rowSums(M)

for(i in rowSums(M))
{
  print(i)
}