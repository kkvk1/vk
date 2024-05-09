def Add(ele, set_a):
    if ele not in set_a:
        set_a.append(ele)

def Remove(ele, set_a):
    if ele in set_a:
        set_a.remove(ele)

def Contains(ele, set_a):
    if ele in set_a:
        return True
    return False

def Size(set_a):
    s = 0
    for i in set_a:
        s = s + 1
    return s

def Intersection(set_a, set_b):
    new_set = []
    for ele in set_a:
        if ele in set_b:
            Add(ele, new_set)
    return new_set

def Union(set_a, set_b):
    new_set = set_a.copy()
    for ele in set_b:
        if ele not in new_set:
            Add(ele, new_set)
    return new_set

def Difference(set_a, set_b):
    new_set = []
    for ele in set_a:
        if ele not in set_b:
            Add(ele, new_set)
    return new_set

def Subset(set_a, set_b):
    for ele in set_a:
        if ele not in set_b:
            return False
    return True

def sub(temp_set):
    a = "A"
    b = "B"
    while True:
        print("\n1. Add Element.")
        print("2. Remove Element.")
        print("3. Contains Element.")
        print("4. Size of Set.")
        print("5. Display set.")
        print("6. Back to main Menu.")
        
        ch1 = int(input("\nEnter your choice: "))
        
        if ch1 == 1:
            num = int(input("Enter Element: "))
            Add(num, temp_set)
            print(f"{num} is Added in Set {a if temp_set == a else b}.")
        elif ch1 == 2:
            num = int(input("Enter Element to remove: "))
            Remove(num, temp_set)
            print(f"{num} is removed from {a if temp_set == a else b}.")
        elif ch1 == 3:
            temp = int(input("Enter Element: "))
            num = Contains(temp, temp_set)
            if num:
                print(f"{temp} is present in {a if temp_set == a else b}.")
            else:
                print(f"{temp} is not present in {a if temp_set == a else b}.")
        elif ch1 == 4:
            print(f"Size of set {temp_set} is {Size(temp_set)}.")
        elif ch1 == 5:
            print(temp_set)
        elif ch1 == 6:
            break

def main():
    A = []
    B = []
    
    while True:
        print("\n1. Operations on Set A")
        print("2. Operations on Set B")
        print("3. Intersection of Both")
        print("4. Union of Both")
        print("5. Difference A - B")
        print("6. Is A Subset of B?")
        print("7. Exit")
        
        ch = int(input("\nEnter your choice: "))
        
        if ch == 1:
            sub(A)
        elif ch == 2:
            sub(B)
        elif ch == 3:
            print("Intersection of A and B: ", Intersection(A, B))
        elif ch == 4:
            print("Union of A and B: ", Union(A, B))
        elif ch == 5:
            print("Difference of A - B: ", Difference(A, B))
        elif ch == 6:
            print("Result:", Subset(A, B))
        elif ch == 7:
            print("Exiting...")
            exit(0)

if __name__ == "__main__":
    main()
