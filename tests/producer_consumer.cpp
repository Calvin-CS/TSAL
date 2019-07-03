#include "tsal.hpp"
#include <thread>
#include <condition_variable>
#include <iostream>
#include <queue>

#include <chrono>
#include <thread>
void thread_sleep(unsigned milliseconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

class SharedQueue {
  public:
    SharedQueue() {
      synth.setVolume(0.3);
      synth.noteOn(mNote);
    };
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
    tsal::Synth* getSynth() { return &synth; };
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
  synth.setVolume(0.2);
  synth.setMode(tsal::Oscillator::SQUARE);
  mixer->add(synth);

  int item;
  while (true) {
    thread_sleep(rand() % 5000);
    item = rand() % 50;
    std::cout << "producing: " << item << std::endl;
    queue->produce(item);
    synth.noteOn(30 + item);
    thread_sleep(100);
    synth.noteOff();
  }
}

void consume(SharedQueue* queue, tsal::Mixer* mixer) {
  tsal::Synth synth;
  synth.setVolume(0.2);
  synth.setMode(tsal::Oscillator::SAW);
  mixer->add(synth);

  int item;
  while (true) {
    thread_sleep(rand() % 5000);
    item = queue->consume();
    std::cout << "consuming: " << item << std::endl;
    synth.noteOn(30 + item);
    thread_sleep(100);
    synth.noteOff();
  }
}

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
  mixer.add(*queue.getSynth());


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
