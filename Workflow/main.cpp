#include <iostream>
#include "Workflow.h"

int main() {
    Workflow wf("Workflow.txt");
    wf.handle();
    return 0;
}