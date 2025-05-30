#include <machine.h>
#include <stdlib.h>
#include <stdio.h>

void init_machine(machine*  machine,void* machine_pointer,type type,mac addr){

    machine->machine = machine_pointer;
    machine->type = type;
    machine->add_mac = addr;
    if (type == SWITCH) {
    char macprintbuffer[1024]; 
    bridge *br = (bridge *)(machine->machine); 

    printf("Switch: MAC=%s, Ports=%ld, Priorite=%ld\n",
           to_string_mac(&addr, macprintbuffer),
           br->nb_ports,
           br->priorite);
    }else{
    char bufferIP[1024];
    char bufferMAC[1024];
    station *sta = (station *)(machine->machine); 
    printf("Station: MAC=%s, IP=%s\n", to_string_mac(&addr,bufferIP), to_string_ipv4(&sta->addr_ip,bufferIP));
    }


}

void desinit_machine(machine* machine){
       
    char macprintbuffer[1024]; 
    printf(" desinit de : %s\n",to_string_mac(&machine->add_mac, macprintbuffer));
    if(machine->type == SWITCH){
        desinit_bridge((bridge * )machine->machine);
    }
    else{
         desinit_station((station * )machine->machine);
    }
    machine->add_mac =-1;
    free(machine->machine);
    machine = NULL;
};

void connect_two_machine(machine* machine1,machine* machine2){

};

void add_interface(machine* machine , interface * inter){
    machine->interface =inter;
};

bool is_it_for_me_question_mark(machine *mach,trame* t){
    return(compare_mac(&mach->add_mac,&t->dest));
}
