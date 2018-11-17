/**
 * Copyright (c) 2017. The WRENCH Team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include <cstring>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <iostream>
#include "BatchLogGenerator.h"

BatchLogGenerator::BatchLogGenerator() {
  // Set all the defaults
  this->seed = this->default_seed;

  std::mt19937(this->default_seed);
  this->max_job_size = this->default_max_job_size;
  this->duration = this->default_duration;
  this->p1 = this->default_p1;
  this->p2 = this->default_p2;

  // create the RNG
  this->rng = std::mt19937(this->seed);

}

void BatchLogGenerator::printUsage(char *exec_name) {
  std::cerr << "Usage: ";
  std::cerr << exec_name << "\n";
  std::cerr << "\t[--help | -h]\n";
  std::cerr << "\t[--seed <seed>]               (default: " + std::to_string(this->default_seed) + ")\n";
  std::cerr << "\t[--max_job_size <# of procs>] (default: " + std::to_string(this->default_max_job_size) + ")\n";
  std::cerr << "\t[--duration <# of hours>]     (default: " + std::to_string(this->default_duration) + ")\n";
  std::cerr << "\t[--p1 <probability>]          (default: " + std::to_string(this->default_p1) + ")\n";
  std::cerr << "\t[--p2 <probability>]          (default: " + std::to_string(this->default_p2) + ")\n";
  std::cerr << "\n";
}


void BatchLogGenerator::init(int argc, char **argv) {

  // Check if there is a --help or -h flag
  for (int i=1; i < argc; i++) {
    if ((!strcmp(argv[i],"--help")) or (!strcmp(argv[i], "-h"))) {
      printUsage(argv[0]);
      exit(0);
    }
  }

  for (int i=1; i < argc; i+=2) {
    if (!strcmp(argv[i],"--seed")) {
      if (sscanf(argv[i + 1], "%u", &(this->seed)) != 1) {
        throw std::invalid_argument("Invalid --seed value " + std::string(argv[i + 1]));
      }
    } else if (!strcmp(argv[i],"--max_job_size")) {
      if (sscanf(argv[i + 1], "%lu", &(this->max_job_size)) != 1) {
        throw std::invalid_argument("Invalid --max_job_size value " + std::string(argv[i + 1]));
      }
    } else if (!strcmp(argv[i],"--duration")) {
      if (sscanf(argv[i + 1], "%lu", &(this->duration)) != 1) {
        throw std::invalid_argument("Invalid --duration value " + std::string(argv[i + 1]));
      }
    } else if (!strcmp(argv[i],"--p1")) {
      if (sscanf(argv[i+1],"%lf",&(this->p1)) != 1) {
        throw std::invalid_argument("Invalid --p1 value " + std::string(argv[i+1]));
      }
    } else if (!strcmp(argv[i],"--p2")) {
      if (sscanf(argv[i + 1], "%lf", &(this->p2)) != 1) {
        throw std::invalid_argument("Invalid --p2 value " + std::string(argv[i + 1]));
      }
    }

    else {
      throw std::invalid_argument("Invalid option " + std::string(argv[i]));
    }
  }

  // Initialize (often argument-dependent) sub-parameters
  this->l = log2(2) - 0.2;
  this->m = log2(this->max_job_size) - 0.25;
  this->h = log2(this->max_job_size);
  this->p = 0.86;

}

void BatchLogGenerator::generate() {

  for (int i=0; i < 1000; i++) {
    std::cerr << "JOB SIZE: " << this->generateJobSize() << "\n";
  }
}

/*
 * Return true if the coin toss picks a value <= to probability
 */
bool BatchLogGenerator::tossCoin(double probability) {
  std::uniform_real_distribution<> d(0.0, 1.0);
  double coin = d(this->rng);
  return (coin <= this->p1);
}


unsigned long BatchLogGenerator::generateJobSize() {

  // Sequential Job?
  if (tossCoin(this->p1)) {
    return 1;
  }

  double logsize;

  // Sample a log job size from distribution
  if (tossCoin(this->p))  {
    // Sample uniformly between l and m
    std::uniform_real_distribution<> d(this->l, this->m);
    logsize = d(this->rng);
  }  else {
    // Sample uniformly between m and h
    std::uniform_real_distribution<> d(this->m, this->h);
    logsize = d(this->rng);
  }

  // Round the log size to nearest integer?
  if (tossCoin(this->p2)) {
    logsize = std::round(logsize);
    if (logsize < 1.0) {
      logsize = 1.0;
    }
    if (logsize > log2(this->max_job_size)) {
      logsize = floor(log2(this->max_job_size));
    }
  }

  double size = std::round(pow(2.0, logsize));
  return (unsigned long) size;
}
