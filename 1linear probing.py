class LinearProbing:
    def __init__(self, size):
        self.size = size
        self.keys = [None] * size
        self.collisions = [0] * size

    def hash_func(self, key):
        return key % self.size

    def insert_lp(self, key):
        i = self.hash_func(key)

        while self.keys[i] is not None:
            i = (i + 1) % self.size
            self.collisions[i] += 1
            if i == self.hash_func(key):
                print("Hash table is full. Cannot insert.")
                return

        self.keys[i] = key

    def search_lp(self, key):
        i = self.hash_func(key)

        while self.keys[i] is not None:
            if self.keys[i] == key:
                return i
            i = (i + 1) % self.size
            if i == self.hash_func(key):
                break

        return None

    def display(self):
        print("| Index | Key | Collisions |")
        print("|-------|-----|------------|")
        for i in range(self.size):  
            print(f"|   {i}   |  {self.keys[i]}  |     {self.collisions[i]}     |")


def main():
    size = int(input("Enter the size of the hash table: "))
    linear_table = LinearProbing(size)
    submenu(linear_table, "Linear Probing")


def submenu(hash_table, technique):
    while True:
        
        print("Select one of these options:")
        print("1) Insert")
        print("2) Search")
        print("3) Display")
        print("4) Return to Main Menu")

        choice = int(input("Enter your choice: "))

        if choice == 1:
            value = int(input("Enter the value to insert: "))
            hash_table.insert_lp(value)
        elif choice == 2:
            value = int(input("Enter the value to search: "))
            result = hash_table.search_lp(value)
            if result is not None:
                print(f"{technique}: Value found at index {result}.")
            else:
                print(f"{technique}: Value not found.")
        elif choice == 3:
            hash_table.display()
        elif choice == 4:
            break
        else:
            print("Invalid choice. Please enter a valid option.")


if __name__ == "__main__":
    main()
