import threading
import time
import random
import collections
import os
import pandas as pd

class Producer(threading.Thread):
    def __init__(self, buffer, empty, full, mutex, items_to_produce, producer_id, sleep_time):
        super().__init__()
        self.buffer = buffer
        self.empty = empty
        self.full = full
        self.mutex = mutex
        self.items_to_produce = items_to_produce
        self.producer_id = producer_id
        self.sleep_time = sleep_time

    def run(self):
        for _ in range(self.items_to_produce):
            time.sleep(random.uniform(0.1, self.sleep_time))  # Simulate production time
            item = f"Item-{self.producer_id}-{_}"
            self.empty.acquire()  # Wait if the buffer is full
            self.mutex.acquire()  # Lock the buffer
            self.buffer.append(item)  # Produce an item
            print(f"Producer {self.producer_id} produced {item}")
            self.mutex.release()  # Release the buffer lock
            self.full.release()  # Signal that the buffer is not empty


class Consumer(threading.Thread):
    def __init__(self, buffer, empty, full, mutex, items_to_consume, consumer_id, sleep_time):
        super().__init__()
        self.buffer = buffer
        self.empty = empty
        self.full = full
        self.mutex = mutex
        self.items_to_consume = items_to_consume
        self.consumer_id = consumer_id
        self.sleep_time = sleep_time

    def run(self):
        for _ in range(self.items_to_consume):
            self.full.acquire()  # Wait if the buffer is empty
            self.mutex.acquire()  # Lock the buffer
            item = self.buffer.popleft()  # Consume an item
            print(f"Consumer {self.consumer_id} consumed {item}")
            self.mutex.release()  # Release the buffer lock
            self.empty.release()  # Signal that the buffer is not full
            time.sleep(random.uniform(0.1, self.sleep_time))  # Simulate consumption time


def main(buffer_size, num_items, num_producers, num_consumers, sleep_time):
    buffer = collections.deque(maxlen=buffer_size)
    empty = threading.Semaphore(buffer_size)  # Initially, buffer_size slots are empty
    full = threading.Semaphore(0)  # Initially, 0 slots are full
    mutex = threading.Lock()  # Mutex for buffer access

    producers = [
        Producer(buffer, empty, full, mutex, num_items // num_producers, i + 1, sleep_time)
        for i in range(num_producers)
    ]
    consumers = [
        Consumer(buffer, empty, full, mutex, num_items // num_consumers, i + 1, sleep_time)
        for i in range(num_consumers)
    ]

    start_time = time.time()

    # Start producers and consumers
    for p in producers:
        p.start()
    for c in consumers:
        c.start()

    # Wait for all producers and consumers to finish
    for p in producers:
        p.join()
    for c in consumers:
        c.join()

    end_time = time.time()
    turnaround_time = end_time - start_time
    print(f"Turnaround time: {turnaround_time:.2f} seconds")
    return turnaround_time


if __name__ == "__main__":
    # Test parameters
    test_cases = [
        {"buffer_size": 5, "num_items": 100, "num_producers": 2, "num_consumers": 2, "sleep_time": 0.5},
        {"buffer_size": 10, "num_items": 100, "num_producers": 2, "num_consumers": 2, "sleep_time": 0.5},
        {"buffer_size": 20, "num_items": 100, "num_producers": 2, "num_consumers": 2, "sleep_time": 0.5},
        {"buffer_size": 5, "num_items": 100, "num_producers": 3, "num_consumers": 3, "sleep_time": 0.3},
        {"buffer_size": 10, "num_items": 100, "num_producers": 3, "num_consumers": 3, "sleep_time": 0.3},
        {"buffer_size": 20, "num_items": 100, "num_producers": 3, "num_consumers": 3, "sleep_time": 0.3},
    ]

    results = []
    for params in test_cases:
        print(f"\nTesting with parameters: {params}")
        turnaround_time = main(
            params["buffer_size"],
            params["num_items"],
            params["num_producers"],
            params["num_consumers"],
            params["sleep_time"]
        )
        results.append({**params, "turnaround_time": turnaround_time})

    # Convert results to DataFrame
    df_results = pd.DataFrame(results)

    # Ensure the output directory exists
    output_dir = '../output'
    os.makedirs(output_dir, exist_ok=True)

    # Write results to the file
    results_file_path = os.path.join(output_dir, 'results.txt')
    with open(results_file_path, 'w') as file:
        file.write("Results:\n")
        file.write(df_results.to_string(index=False))
        file.write("\n")

    # Print the results table to the console
    print("\nResults Table:")
    print(df_results)

    print("\nResults written to output/results.txt")
