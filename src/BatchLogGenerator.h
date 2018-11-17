/**
 * Copyright (c) 2017. The WRENCH Team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef SWF_BATCH_LOG_GENERATOR_BATCHLOGGENERATOR_H
#define SWF_BATCH_LOG_GENERATOR_BATCHLOGGENERATOR_H


#include <random>

class BatchLogGenerator {

public:
    BatchLogGenerator();

    void init(int argc, char **argv);
    void generate();

private:
    // Parameters

    unsigned int seed;
    unsigned int default_seed = 0;

    unsigned long max_job_size;
    unsigned long default_max_job_size = 128;

    unsigned long duration; // trace duration in hours
    unsigned long default_duration = 24;

    double p1; // p1 parameter for the job size model
    double default_p1 = 0.24;

    double p2; // p2 parameter for the job size model
    double default_p2 = 0.75;

    double l, m, h, p;  // l, m, h, p parameters

    // RNG
    std::mt19937 rng;

private:
    void printUsage(char *exec_name);

    unsigned long generateJobSize();

    bool tossCoin(double probability);
};


#endif //SWF_BATCH_LOG_GENERATOR_BATCHLOGGENERATOR_H
