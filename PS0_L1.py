C = float(input("Enter the maximum storage capacity of the port in kg: "))

N = int(input("Enter the number of containers: "))
max_w, min_w, total_w = 0, 0, 0

for i in range(N) :
    w = float(input("Enter the weight of container " + str(i+1) + ":"))

    if i == 0:
        min_w = w
    if w >= max_w:
        max_w = w
    if w <= min_w:
        min_w = w

    total_w += w

print("Total Shipment Weight: ", total_w)
print("Average container weight: ", total_w/N)
print("Heaviest Container: ", max_w)
print("Lightest Container: ", min_w)

if total_w >= 200:
    print("Classification: Heavy")
else:
    print("Classification: Light")
print("Port Capacity: ",C)
if total_w <= C:
    print("Shipment can be unloaded.")
else:
    print("Shipment exceeds port capacity.")
