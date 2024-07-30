import threading
import time
import random
from queue import Queue

class ProducerConsumer:
    def __init__(self, num_producers, num_consumers, buffer_size):
        self.buffer = Queue(maxsize=buffer_size)
        self.num_producers = num_producers
        self.num_consumers = num_consumers
        self.producers = []
        self.consumers = []
        self.producer_stop_event = threading.Event()
        self.consumer_stop_event = threading.Event()
    
    def producer(self, id):
        while not self.producer_stop_event.is_set():
            item = random.randint(1, 100)
            self.buffer.put(item)
            print(f"Producer {id} produced {item}")
            time.sleep(random.uniform(0.1, 0.5))
    
    def consumer(self, id):
        while not self.consumer_stop_event.is_set() or not self.buffer.empty():
            item = self.buffer.get()
            print(f"Consumer {id} consumed {item}")
            time.sleep(random.uniform(0.1, 0.5))
    
    def start(self):
        for i in range(self.num_producers):
            t = threading.Thread(target=self.producer, args=(i,))
            t.start()
            self.producers.append(t)
        
        for i in range(self.num_consumers):
            t = threading.Thread(target=self.consumer, args=(i,))
            t.start()
            self.consumers.append(t)
    

    def stop(self):
        self.producer_stop_event.set()
        for t in self.producers:
            t.join()
        
        self.consumer_stop_event.set()
        for t in self.consumers:
            t.join()   
def main():
    num_producers = 4
    num_consumers =2
    buffer_size = 10

    pc = ProducerConsumer(num_producers, num_consumers, buffer_size)
    pc.start()

    #Run the simulation for a certain time
    time.sleep(5)

    pc.stop()

    #print results
    with open("../output/results.txt", "w") as f:
        f.write("Simulation complete")

if __name__ == "__main__":
    main()
