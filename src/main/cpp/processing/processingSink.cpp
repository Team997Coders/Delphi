#include "processing/processingSink.h"

#include "frame/frame.h"

ProcessingSink::ProcessingSink(){

};

ProcessingSink::~ProcessingSink(){

};

bool ProcessingSink::accept(const Frame *frame) { return false; };