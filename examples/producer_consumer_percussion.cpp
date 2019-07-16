#include "tsal.hpp"
#include <thread>
#include <condition_variable>
#include <iostream>
#include <queue>

class SharedQueue {
  public:
    void produce(int item) {
      std::unique_lock<std::mutex> lk(mMutex);
      mCondition.wait(lk, [this]{return mQueue.size() < MaxQueueSize;}); 
      mQueue.push(item);
      tsal::Util::thread_sleep(rand() % 2000);
      lk.unlock();
      mCondition.notify_all();
    };
    int consume() {
      std::unique_lock<std::mutex> lk(mMutex);
      mCondition.wait(lk, [this]{return mQueue.size() > 0;});
      const int front = mQueue.front();
      mQueue.pop();
      tsal::Util::thread_sleep(rand() % 2000);
      lk.unlock();
      mCondition.notify_all();
      return front;  
    };
    unsigned size() {
      return mQueue.size();
    }
    unsigned MaxQueueSize = 12;
  private:
    std::condition_variable mCondition;
    std::mutex mMutex;
    std::queue<int> mQueue;
};

void monitor(SharedQueue* queue, tsal::Mixer* mixer) {
  tsal::SoundFont sf("/usr/share/soundfonts/FluidR3_GM.sf2");
  sf.setPreset(20);
  mixer->add(sf);

  int size;
  while(true) {
    size = queue->size();
    tsal::Util::thread_sleep(size + 1 * 1000);
    sf.noteOn(30 + size);
    tsal::Util::thread_sleep(2000);
    sf.noteOff(30 + size);
  }
}

void produce(SharedQueue* queue, tsal::Mixer* mixer) {
  tsal::SoundFont sf("/usr/share/soundfonts/FluidR3_GM.sf2");
  sf.setPreset(10);
  mixer->add(sf);

  int item;
  while (true) {
    tsal::Util::thread_sleep(rand() % 2000);
    item = rand() % 50;
    std::cout << "producing: " << item << std::endl;
    queue->produce(item);
    sf.noteOn(36);
    tsal::Util::thread_sleep(500);
    sf.noteOff(36);
    
  }
}

void consume(SharedQueue* queue, tsal::Mixer* mixer) {
  tsal::SoundFont sf("/usr/share/soundfonts/FluidR3_GM.sf2");
  sf.setPreset(4);
  mixer->add(sf);

  int item;
  while (true) {
    tsal::Util::thread_sleep(rand() % 2000);
    item = queue->consume();
    std::cout << "consuming: " << item << std::endl;
    sf.noteOn(38);
    tsal::Util::thread_sleep(500);
    sf.noteOff(38);
  }
}

/** @example producer_consumer.cpp
 * 
 * Producer and consumer is a common example of synchonization between multiple processes or threads.
 * The SharedQueue class acts as a monitor between the producers and consumers. The sine wave 
 * pitch corresponds to the fullness of the queue, the square wave blips correspond to a production,
 * and the saw wave blips correspond to consumption
 * 
 * Parse the parameter\n
 * Create the mixer and the SharedQueue
 * Start the producer and consumer threads
 * Producer threads:
 * - Make a random item
 * - Add the item to the queue
 * - Play a square wave with pitch based on item
 * Consumer threads:
 * - Consume an item from the queue
 * - Play a saw wave with pitch based on item
 * SharedQueue:
 * - Provide the synchronized access to the underlying queue
 * - Change the pitch of the sine wave whenever a item is added or removed
 */
int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << "Invalid arguments\n\n"
              << "producer_consumer <producers> <consumers>\n" 
              << "\tproducers = the number of producers\n" 
              << "\tconsumers = the number of consumers\n"
              << std::endl;
    return 0;
  }
  const int numProducers = atoi(argv[1]);
  const int numConsumers = atoi(argv[2]);
  tsal::Mixer mixer;
  tsal::Delay delay;
  mixer.add(delay);
  
  SharedQueue queue;

  std::thread producers[numProducers];
  std::thread consumers[numConsumers];
  for (int i = 0; i < numProducers; i++) {
    producers[i] = std::thread(produce, &queue, &mixer);
  }
  for (int i = 0; i < numConsumers; i++) {
    consumers[i] = std::thread(consume, &queue, &mixer);
  }
  std::thread monitor_thread = std::thread(monitor, &queue, &mixer);

  for (int i = 0; i < numProducers; i++) {
    producers[i].join();
  }
  for (int i = 0; i < numConsumers; i++) {
    consumers[i].join();
  }
  monitor_thread.join();

  return 0;
}
