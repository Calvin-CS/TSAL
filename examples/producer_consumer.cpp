#include "tsal.hpp"
#include <thread>
#include <condition_variable>
#include <iostream>
#include <queue>

using namespace tsal;

bool run = true;

class SharedQueue {
  public:
    void produce(Synth* item) {
      std::unique_lock<std::mutex> lk(mMutex);
      mCondition.wait(lk, [this]{return mQueue.size() < mMaxQueueSize;}); 
      item->setVolume(0.1);
      item->setMode(Oscillator::SQUARE);
      mQueue.push(item);
      lk.unlock();
      mCondition.notify_all();
    };
    Synth* consume() {
      std::unique_lock<std::mutex> lk(mMutex);
      mCondition.wait(lk, [this]{return mQueue.size() > 0;});
      Synth* front = mQueue.front();
      mQueue.pop();
      lk.unlock();
      mCondition.notify_all();
      return front; 
    };
  private:
    std::condition_variable mCondition;
    std::mutex mMutex;
    std::queue<Synth*> mQueue;
    unsigned mMaxQueueSize = 12;
};

void produce(SharedQueue* queue, Mixer* mixer) {
  Synth* item = nullptr;
  while (run) {
    Util::thread_sleep(rand() % 5000);
    item = new Synth();
    mixer->add(*item);
    item->setVolume(0.5);
    item->setEnvelopeActive(false);
    item->noteOn(C3 + rand() % (C4 - C3));
    for (int i = 0; i < 100; i++) {
      item->noteOn(item->getNote() + 0.1);
      Util::thread_sleep(5);
    }
    queue->produce(item);
  }
}

void consume(SharedQueue* queue, Mixer* mixer) {
  Synth* item = nullptr;
  while (run) {
    Util::thread_sleep(rand() % 5000);
    item = queue->consume();
    item->setVolume(0.5);
    item->setMode(Oscillator::SINE);
    for (int i = 0; i < 100; i++) {
      item->noteOn(item->getNote() + 0.1);
      Util::thread_sleep(5);
    }
    item->noteOff();
    mixer->remove(*item);
    delete item;
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
  Mixer mixer;
  SharedQueue queue;

  std::thread producers[numProducers];
  std::thread consumers[numConsumers];
  for (int i = 0; i < numProducers; i++) {
    producers[i] = std::thread(produce, &queue, &mixer);
  }
  for (int i = 0; i < numConsumers; i++) {
    consumers[i] = std::thread(consume, &queue, &mixer);
  }

  // Wait for the user to stop the synth
  char input;
  std::cout << "Press <enter> to quit:" << std::flush;
  std::cin.get(input);
  run = false;
  std::cout << "Quitting..." << std::endl;

  for (int i = 0; i < numProducers; i++) {
    producers[i].join();
  }
  for (int i = 0; i < numConsumers; i++) {
    consumers[i].join();
  }

  return 0;
}
