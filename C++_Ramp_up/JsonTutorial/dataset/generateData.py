import json
import random

def generate_random_name():
    names = ["Alice", "Bob", "Charlie", "Dave", "Eve", "Frank", "Grace", "Hannah", "Ivy", "Jack"]
    return random.choice(names)

def generate_random_vip_status():
    return random.choice([True, False])

def generate_random_amount():
    return random.randint(0, 5)  # Random amount between 0 and 5

def main():
    transactions = []
    result = 0;

    for _ in range(10000000):
        temp = generate_random_amount();
        result += temp

        transaction = {
            "name": generate_random_name(),
            "vip": generate_random_vip_status(),
            "amount": temp
        }
        transactions.append(transaction)

    json_data = {"transactions": transactions}

    with open("transactions.json", "w") as file:
        json.dump(json_data, file, indent=4)  # Pretty print with 4 spaces indentation

    print("JSON file created successfully.")
    print(result)

if __name__ == "__main__":
    main()