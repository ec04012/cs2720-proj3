import random

numTellers = 4
numCustomers = 150
customers = []

# Generate random customers
for i in range(0, numCustomers):	
	customer = {
		"name" : "Customer" + str(i + 1),
		"arrival" : random.randint(0,25200),
		"service" : random.randint(120, 480)
	}
	customers.append(customer)

# Sort customers from arrive time
customers = sorted(customers, key = lambda i: i['arrival'])
# Rename customers
for i in range(0, len(customers)):
	customer = customers[i]
	customer["name"] = "Customer" + str(i+1)

# Write to file
with open("randCustomers.txt", "w") as f:
	f.write("numTellers " + str(numTellers) + "\n")
	f.write("numCustomers " + str(len(customers)) + "\n\n")
	for customer in customers:
		f.write(customer["name"].ljust(13))
		f.write("arrival " + str(customer["arrival"]).rjust(5) + "\t")
		f.write("service " + str(customer["service"]))
		f.write("\n")
	