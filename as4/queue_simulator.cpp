#include "queue_simulator.h"
#include "heap.hpp"

//vector<Customer> QueueSimulator::simulateQueue(
//    const vector<Customer>& customers) {
//  // TODO: Implement this function.
//    vector<Customer> customer = customers;
//    Heap<int> queue;
//    int index = 0;
//    queue.printHeapArray();
//    while (index < customers.size()) {
//
//        for (int i = 0; i < customers.size(); i++) {
//            queue.insert(customers[i].arrival_time());
//            index++;
//        }
//        queue.printHeapArray();
//
//        int index = 0;
//        while (!queue.empty()) {
//            Customer maxCustomer = queue.extractMax();
//            maxCustomer.set_service_time(maxCustomer.arrival_time() + maxCustomer.processing_time());
//            customer[index] = maxCustomer;
//            
//        }
//    }
//
//
//
//  /*return customers;*/
//    return customer;
//}

vector<Customer> QueueSimulator::simulateQueue(
    const vector<Customer>& customers) {
  // TODO: Implement this function.
    vector<Customer> customer(customers.size());
    Heap<Customer> queue;

    int currentTime = 0;
    int prevTime = 0;
    int index = 0;

    while (index < customer.size()) {

        for (int i = prevTime; i < currentTime; i++) {
            queue.insert(customers[i]);
            index++;
        }

        while (!queue.empty()) {

            Customer nextCustomer = queue.extractMax();
            nextCustomer.set_service_time(nextCustomer.arrival_time() + currentTime);
            currentTime += (nextCustomer.service_time() + nextCustomer.processing_time());
            customer.push_back(nextCustomer);
            
        }
    }
    return customer;
}
