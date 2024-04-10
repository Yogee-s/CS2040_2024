#include "queue_simulator.h"
#include "heap.hpp"



//vector<Customer> QueueSimulator::simulateQueue(const vector<Customer>& customers) {
//    vector<Customer> customers_served(customers.size());
//    Heap<Customer> queue;
//
//    int currentTime = 0;
//    //Time customer was served
//    int prevTime = 0;
//    int next_customer_time = 0;
//    int customer = 0;
//    int servedcustomer = 0;
//    currentTime = customers[0].arrival_time();
//    next_customer_time = currentTime + customers[0].processing_time();
//    customers_served[servedcustomer].set_service_time(currentTime);
//
//    servedcustomer++;
//    customer++;
//
//    while (!queue.empty() || (customer < customers.size()) ) {
//        if (customer < customers.size()){
//            if (customers[customer].arrival_time() > currentTime ) {
//                if (_priority_order) {
//                    Customer::set_compare_by_processing_time(true);
//                }
//                else {
//                    Customer::set_compare_by_processing_time(false);
//                }
//                queue.insert(customers[customer]);
//                customer++;
//            }
//        }
//        if (currentTime < next_customer_time) {
//            currentTime++;
//            continue;
//        }
//        //next customer
//        if (!queue.empty()) {
//            Customer current_customer = queue.extractMax();
//            customers_served[servedcustomer].set_service_time(currentTime);
//            next_customer_time = currentTime + current_customer.processing_time();
//            servedcustomer++;
//        }
//    currentTime++;
//    }
//
//    return customers_served;
//
//}



//Working code for priority
vector<Customer> QueueSimulator::simulateQueue(const vector<Customer>& customers) {
    vector<Customer> customers_served(customers.size());
    Heap<Customer> queue;

    int currentTime = 0;
    int customer = 0;
    int servedcustomer = 0;

    // Process customers until all are served
    while (!queue.empty() || customer < customers.size()) {
        // Add arriving customers to the queue
        while (customer < customers.size() && customers[customer].arrival_time() <= currentTime) {
            if (_priority_order) {
                Customer::set_compare_by_processing_time(true);
            }
            else {
                Customer::set_compare_by_processing_time(false);
            }
            queue.insert(customers[customer]);
            customer++;
        }

        // Serve the next customer
        if (!queue.empty()) {
            Customer current_customer = queue.extractMax();
            customers_served[servedcustomer] = current_customer;
            customers_served[servedcustomer].set_service_time(currentTime);
            servedcustomer++;

            // Update currentTime
            currentTime = std::max(currentTime, current_customer.arrival_time()) + current_customer.processing_time();
        }
        else {
            // If no customers in queue, advance time to next customer arrival
            currentTime = customers[customer].arrival_time();
        }
    }

    return customers_served;
}

