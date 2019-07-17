#include "tsal.hpp"
#include <thread>
#include <condition_variable>
#include <iostream>
#include <queue>

class SharedQueue {
  public:
    void produce(int item) {
      std::unique_lock<std::mutex> lk(mMutex);
      mCondition.wait(lk, [this]{return mQueue.size() < mMaxQueueSize;}); 
      mQueue.push(item);
      synth.noteOn(++mNote);
      lk.unlock();
      mCondition.notify_all();
    };
    int consume() {
      std::unique_lock<std::mutex> lk(mMutex);
      mCondition.wait(lk, [this]{return mQueue.size() > 0;});
      const int front = mQueue.front();
      mQueue.pop();
      synth.noteOn(--mNote);
      lk.unlock();
      mCondition.notify_all();
      return front;  
    };
    tsal::Synth& getSynth() { return synth; };
  private:
    tsal::Synth synth;
    unsigned mNote = 60;
    std::condition_variable mCondition;
    std::mutex mMutex;
    std::queue<int> mQueue;
    unsigned mMaxQueueSize = 12;
};

void produce(SharedQueue* queue, tsal::Mixer* mixer) {
  tsal::Synth synth;
  mixer->add(synth);
  synth.setVolume(0.2);
  synth.setMode(tsal::Oscillator::SQUARE);

  int item;
  while (true) {
    tsal::Util::thread_sleep(rand() % 5000);
    item = rand() % 10;
    std::cout << "producing: " << item << std::endl;
    queue->produce(item);
    synth.noteOn(30 + item);
    tsal::Util::thread_sleep(100);
    synth.noteOff();
  }
}

void consume(SharedQueue* queue, tsal::Mixer* mixer) {
  tsal::Synth synth;
  mixer->add(synth);
  synth.setVolume(0.2);
  synth.setMode(tsal::Oscillator::SAW);

  int item;
  while (true) {
    tsal::Util::thread_sleep(rand() % 5000);
    item = queue->consume();
    std::cout << "consuming: " << item << std::endl;
    synth.noteOn(80 + item);
    tsal::Util::thread_sleep(100);
    synth.noteOff();
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
  SharedQueue queue;
  auto& queueSynth = queue.getSynth();
  mixer.add(queueSynth);
  queueSynth.setVolume(0.5);
  queueSynth.noteOn(tsal::C4);


  std::thread producers[numProducers];
  std::thread consumers[numConsumers];
  for (int i = 0; i < numProducers; i++) {
    producers[i] = std::thread(produce, &queue, &mixer);
  }
  for (int i = 0; i < numConsumers; i++) {
    consumers[i] = std::thread(consume, &queue, &mixer);
  }

  for (int i = 0; i < numProducers; i++) {
    producers[i].join();
  }
  for (int i = 0; i < numConsumers; i++) {
    consumers[i].join();
  }

  return 0;
}
