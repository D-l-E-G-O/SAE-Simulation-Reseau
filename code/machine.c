#include <machine.h>



void init_machine(machine*  machine,void* machine_pointer,type type){

    machine->machine = machine_pointer;
    machine->type = type;

}

void desinit_machine(machine machine){
    if(machine->type == SWITCH){
        desinit_bridge((bridge * )machine);
    }
    else{
         desinit_bridge((station * )machine);
    }
};

void connect_two_machine(machine* machine1,machine* machine2){

};